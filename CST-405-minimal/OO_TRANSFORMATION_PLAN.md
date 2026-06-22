# Turning the Minimal Compiler into an Object-Oriented Language

A concrete, phase-by-phase roadmap grounded in the existing codebase
(`scanner.l`, `parser.y`, `ast.{c,h}`, `symtab.{c,h}`, `semantic.c`,
`tac.{c,h}`, `codegen.c`). Target stays MIPS.

---

## 0. Where you already are

You are not starting from zero. The current `struct` machinery is a
proto-object system:

| OO concept | What already exists | File |
|---|---|---|
| Object layout | `StructTypeInfo` with fields + byte offsets | `symtab.h` |
| Field storage | Per-field 4-byte slots, `totalSize` | `symtab.h` |
| Field read | `expr is field` → `TAC_MEMBER_LOAD` | `parser.y`, `tac.c` |
| Field write | `obj is field = expr` → `TAC_MEMBER_STORE` | `parser.y`, `tac.c` |
| Default values | `health = 10;` inside the struct body | `symtab.c` |
| Offset resolution | `baseOffset + f->offset` in codegen | `codegen.c` |
| Functions/calls | `func`, args in `$a0–$a3`, return in `$v0`, `jal func_NAME` | `codegen.c` |

The job is to teach `struct` (rename it `class`, or keep `struct`) three
new tricks: **methods**, **inheritance**, and **dynamic dispatch**. Each
maps onto infrastructure you already have.

---

## Design decisions I'm making for you (override any of these)

Because you asked for no interim questions, here are the concrete syntax
calls. They're chosen to fit your existing grammar style (`is`, `end x;`,
`Program_Start()`), so the parser changes stay small.

1. **Keyword:** keep `struct` as the class keyword (least churn). A class
   is `struct Name extends Parent { fields; methods; }`.
2. **Method definition:** reuse `func` *inside* the class body:
   `func area(int s) ... end result;`
3. **Method call:** reuse `is` for dispatch:
   `obj is area(s)` — same operator that reads a field, now also calls.
4. **Self reference:** the keyword `self` inside a method body refers to
   the receiver (compiles to an implicit hidden first parameter).
5. **Constructor:** a method named `init`; `new Name(args)` allocates and
   calls it.
6. **`extends` is single inheritance.** (Multiple inheritance is a
   separate, much larger effort — out of scope here.)
7. **Polymorphism = vtable + dynamic dispatch** on every method (Java-
   style: all methods virtual). Simpler than a `virtual` keyword and
   matches the teaching goal.

---

## Phase 1 — Encapsulation: methods on objects

Goal: `obj is method(args)` works, with `self` available inside.

### Scanner (`scanner.l`)
- Add keywords: `extends`, `new`, `self` (and optionally `class` as an
  alias for `struct`). Each is a one-line rule returning a new token,
  identical in form to the existing `"is"` / `"struct"` rules.

### AST (`ast.h`, `ast.c`)
- New node types: `NODE_METHOD_DEF`, `NODE_METHOD_CALL`, `NODE_NEW`.
- `NODE_METHOD_DEF` can literally reuse the `func_def` struct layout plus
  one field: `char* ownerClass`.
- `NODE_METHOD_CALL` mirrors `struct_access` (`base` + name) plus an
  `args` list — i.e. a cross between `NODE_STRUCT_ACCESS` and
  `NODE_FUNC_CALL`.
- Add constructors `createMethodDef`, `createMethodCall`, `createNew`.

### Symbol table (`symtab.h`, `symtab.c`)
- Extend `StructTypeInfo` with a method table:
  ```c
  typedef struct {
      char name[64];
      char mangledLabel[96];   /* e.g. "Circle_area" */
      int  paramCount;
      int  vtableIndex;        /* filled in Phase 3 */
  } StructMethod;
  StructMethod methods[MAX_STRUCT_METHODS];
  int methodCount;
  char parentName[64];         /* "" if none — used in Phase 2 */
  ```
- Add `addStructMethod`, `findStructMethod`.

### Parser (`parser.y`)
- Extend `struct_def`'s `field_body` to also accept `func_decl` items.
  When a `func` appears in a class body, build a `NODE_METHOD_DEF` and
  register it.
- Add `obj is ID ( arg_list )` as a new alternative wherever `is` field
  access is parsed → `NODE_METHOD_CALL`.
- Add `new ID ( arg_list )` as an expression → `NODE_NEW`.

### Semantic (`semantic.c`)
- Pass 1 already registers functions; extend it to register class methods
  into each `StructTypeInfo`.
- Check: method calls reference a method that exists on the receiver's
  class; arg count matches (you already do this for free functions —
  reuse that code path).
- `self` resolves to the receiver's class type inside a method body.

### TAC (`tac.h`, `tac.c`)
- **No new opcodes needed for static methods.** A method is compiled as a
  normal function whose name is mangled `Class_method`, and whose
  *first argument is the object's address* (`self`).
- `obj is m(a, b)` lowers to: push address-of-`obj` as arg0, then `a`,
  `b`, then `TAC_CALL Class_m`.
- You need an "address of object" notion. Add `TAC_ADDR` (`result =
  &arg1`) so `self`/`obj` can be passed by reference; field access inside
  the method becomes `self[offset]` exactly like today's struct codegen.

### Codegen (`codegen.c`)
- Emit each method as `func_Class_method:` using the existing function
  prologue/epilogue.
- `TAC_ADDR var` → `addiu $tX, $sp, offset` (or compute global address).
- Inside methods, field access uses `self` (in `$a0`) as the base
  register instead of `$sp` — generalize the current
  `baseOffset + f->offset` logic to take a base register parameter.

**Milestone:** objects with methods and `self`, no inheritance yet.

---

## Phase 2 — Inheritance (single, `extends`)

Goal: a subclass gets its parent's fields and methods; can add/override.

### Symbol table / layout
- When registering `struct B extends A`, **copy A's fields first**, then
  append B's own fields. This guarantees an A-pointer and a B-pointer see
  identical offsets for inherited fields — the core trick that makes
  upcasting safe. `totalSize` = parent size + own fields.
- Copy A's method table into B, then let B's own methods **override** by
  name (replace the entry, keep the same `vtableIndex`) or **extend**
  (append new entries).
- Set `parentName`.

### Semantic
- Detect inheritance cycles (`A extends B extends A`).
- Resolve a field/method not found on B by walking up `parentName`.
- Type compatibility: a `B` is usable where an `A` is expected
  (Liskov substitution) — needed for arrays/params of the parent type.
- Optional: a `super is method(...)` form to call the parent's version.

### TAC / Codegen
- Field access is unchanged — inherited fields already sit at the right
  offsets because of the copy-parent-first rule.
- Statically-dispatched method calls just resolve up the chain to the
  right `Class_method` label.

**Milestone:** subclasses reuse and override parent code; offsets stable.

---

## Phase 3 — Polymorphism (vtables + dynamic dispatch)

Goal: `shape is draw()` calls `Circle.draw` or `Square.draw` depending on
the *runtime* type of `shape`, not its declared type.

### The mechanism
1. **Vtable per class.** Build a static table of method-label addresses,
   one slot per method (index assigned in Phase 1/2, inherited indices
   preserved so overrides land in the same slot).
2. **Vtable pointer per object.** Reserve slot 0 of every object for a
   pointer to its class's vtable. (Bump every field offset by 4; update
   `addStructField` offset math and `totalSize`.)
3. **`new` / constructor** stores the correct vtable address into slot 0.
4. **Dynamic call** `obj is m(args)`:
   - load vtable ptr from `obj[0]`
   - load method address from `vtable[index_of_m]`
   - `jalr` (jump-and-link to register) instead of `jal label`.

### What changes where
- `symtab`: finalize `vtableIndex` per method; emit a per-class vtable
  layout.
- `tac.h`: add `TAC_VCALL` (virtual call: result, vtable-slot, argcount)
  and `TAC_LOAD_VPTR`. Keep `TAC_CALL` for non-virtual/free functions.
- `codegen.c`:
  - Emit vtables into `.data`:
    ```asm
    Circle_vtable: .word func_Circle_area, func_Circle_draw, ...
    ```
  - `new Circle(...)`: allocate frame/heap slot, store
    `la $t0, Circle_vtable; sw $t0, 0($obj)`, then call `Circle_init`.
  - `TAC_VCALL`: `lw vptr,0(obj); lw target,(slot*4)(vptr); jalr target`.
- `semantic`: dispatch is now by declared (static) type for *resolution*
  (which slot), but the actual target is chosen at runtime — so checking
  only needs the method to exist on the static type.

**Milestone:** true runtime polymorphism. A `Shape[]` holding `Circle`s
and `Square`s dispatches correctly.

---

## Phase 4 — Object lifetime & memory (the real complication)

Your current structs live on the **stack** at fixed `$sp` offsets. That
breaks the moment objects must outlive their scope or be stored
polymorphically (e.g. returned from a function, or held in an array of
the parent type). To do OO properly you need **heap allocation**:

- Add a bump allocator or a `syscall 9` (`sbrk`) wrapper: `new` returns a
  *pointer*, not an inline stack block.
- Object variables become 4-byte pointers; field access becomes
  `lw base, 0(ptrslot); lw field, offset(base)`.
- This is the single biggest mechanical change. It touches every place
  that currently assumes `struct var == inline stack bytes`
  (`addStructVar`, `getVarStructType`, member load/store codegen).

Recommendation: do Phase 4 **before** Phase 3 in practice, since vtable
pointers and polymorphic storage assume reference semantics. The phases
are numbered by concept, not necessarily build order.

---

## Suggested build order

1. Phase 1 (methods + `self`) on the existing stack model — proves the
   dispatch plumbing end to end with minimal risk.
2. Phase 4 (heap + reference semantics) — the foundational refactor.
3. Phase 2 (inheritance / layout) — cheap once references exist.
4. Phase 3 (vtables / dynamic dispatch) — the payoff.

---

## Effort estimate (rough, per file)

| File | Phase 1 | Phase 2 | Phase 3 | Phase 4 |
|---|---|---|---|---|
| `scanner.l` | small | trivial | – | – |
| `parser.y` | small | small | – | small |
| `ast.{c,h}` | medium | small | small | small |
| `symtab.{c,h}` | medium | medium | medium | medium |
| `semantic.c` | medium | medium | small | small |
| `tac.{c,h}` | medium | – | medium | medium |
| `codegen.c` | medium | small | large | large |

"Large" = the heap model and `jalr`-based dispatch in codegen are where
the genuine difficulty lives. Everything upstream of codegen is mostly
mechanical extension of patterns already in the tree.

---

## Risks / sharp edges

- **Offset bump for the vtable pointer** must be applied consistently, or
  every field read/write silently corrupts. Centralize offset math in one
  helper before Phase 3.
- **Register `$a0` doubling as `self`** collides with your current 4-arg
  convention; methods effectively get 3 user args unless you spill to the
  stack. Decide the calling convention up front.
- **Constructor chaining** (`init` calling parent `init`) needs `super`.
- **No GC**: heap objects leak. Acceptable for a teaching compiler; worth
  a comment.
- **Type checking is currently string-based** (`"int"`, `"float"`).
  Subtype checks need a small "is-A" walk over `parentName`; build that
  as a single reusable predicate.

---

## TL;DR

You don't rewrite the compiler — you grow the struct system. Methods are
mangled functions taking a hidden `self`; inheritance is "copy parent
layout first"; polymorphism is a vtable pointer in slot 0 plus `jalr`.
The only deep change is moving objects from stack-inline to heap
references, and that's the prerequisite that makes the rest fall into
place.
