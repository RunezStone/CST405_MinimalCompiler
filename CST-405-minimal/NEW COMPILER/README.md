# OOMini — An Object-Oriented Compiler (MIPS target)

OOMini is an object-oriented language and compiler built as the successor to
the CST-405 minimal compiler. It is a **separate, standalone compiler** (the
original compiler in the parent folder is untouched) and follows the **same
five compilation phases**, extended for OO.

> New to the language? Read **`TUTORIAL.md`** for a hands-on guide to writing
> object-oriented code in OOMini.

## What it supports

- Classes with fields and methods (encapsulation)
- Constructors (`init`) and heap-allocated objects (`new`)
- Single inheritance (`extends`) with shared field layout
- Method overriding and **runtime polymorphism** via per-class vtables
- The `self` receiver, free functions, `if/else`, `while`, integer arithmetic
- Output is MIPS assembly that runs in **spim** / **MARS**

## Build & run

```
make
./oomini examples/shapes.oom shapes.s    # compile
spim -file shapes.s                       # run
```

## Compiler phases (and the file that implements each)

| Phase | Responsibility | Files |
|-------|----------------|-------|
| 1. Lexical analysis | source text → tokens | `scanner.l` |
| 2. Syntax analysis | tokens → AST | `parser.y`, `ast.c/.h` |
| 3. Semantic analysis | class/vtable registry, inheritance flattening, type & scope checks | `semantic.c/.h`, `symtab.c/.h` |
| 4. Intermediate code | three-address-code listing (incl. `new`, member ops, virtual calls) | `tac.c/.h` |
| 5. Code generation | MIPS assembly (heap objects, vtable dispatch) | `codegen.c/.h` |
| Driver | runs all phases | `main.c` |

This mirrors the original CST-405 compiler's structure
(scanner / parser / AST / symbol table / semantic / TAC / codegen), so the
phase-by-phase mapping between the two compilers is direct.

## The object model in one picture

```
Heap object:                Class vtable (.data):
+--------------+            Dog_vtable: .word Animal_init,   (slot 0)
| vtable ptr   | --------->             Dog_sound,           (slot 1, overridden)
+--------------+                        Animal_describe       (slot 2, inherited)
| field 0      |
| field 1      |   A method call loads the vtable ptr from the object,
| ...          |   loads the method address from its slot, and jalrs to it.
+--------------+   That indirection is what makes overrides polymorphic.
```

## Examples

See `examples/` — `counter.oom`, `bank.oom`, `shapes.oom`. Expected outputs are
documented in `TUTORIAL.md`.

## Design notes

The full design rationale (why structs were the natural starting point, how
each OO feature maps onto compiler infrastructure, and the build-order
reasoning) is in `../OO_TRANSFORMATION_PLAN.md`.
