# OOMini — Writing Object-Oriented Code (Tutorial)

OOMini is the object-oriented successor to the CST-405 minimal language. It
keeps the same compiler phases (scanner → parser → semantic → TAC → MIPS code
generation) and adds the things that make a language object-oriented:

- **Classes** with fields and methods (encapsulation)
- **Constructors** (`init`) and heap-allocated objects (`new`)
- **Single inheritance** (`extends`)
- **Method overriding** and **runtime polymorphism** (dynamic dispatch via
  vtables)
- The **`self`** receiver inside methods

Source files use the `.oom` extension. Programs compile to MIPS assembly you
can run in **spim** or **MARS**.

---

## 1. Building the compiler

You need `flex`, `bison`, and `gcc`.

```
cd "NEW COMPILER"
make
```

This produces the compiler executable `oomini`.

## 2. Compiling and running a program

```
./oomini examples/shapes.oom shapes.s     # compile  .oom -> .s (MIPS)
spim -file shapes.s                        # run it
```

Useful flags:

```
./oomini prog.oom prog.s -tokens     # also print the token stream (phase 1)
./oomini prog.oom prog.s -ast        # also print the AST (phase 2)
```

Every run also writes `prog.oom.tac` — a human-readable three-address-code
listing that shows how your OO code lowers into primitive operations (member
loads/stores, `new`, and virtual calls) before MIPS is emitted.

---

## 3. Your first class

A program is a set of classes and functions, plus a mandatory entry point
`func void main()`.

```
class Counter {
    int n;                       // a field

    func void init() {           // constructor (optional, named "init")
        self.n = 0;
    }
    func void inc() {            // a method
        self.n = self.n + 1;
    }
    func int get() {             // a method that returns a value
        return self.n;
    }
}

func void main() {
    Counter c;                   // declare an object reference
    c = new Counter();           // allocate on the heap + run init()
    c.inc();
    c.inc();
    print(c.get());              // prints 2
}
```

Key ideas:

- **`self`** is the current object, available inside any method.
- **Fields** are accessed with a dot: `self.n`, `c.get()`.
- **`new Counter()`** allocates the object and calls its `init` constructor.
- **`print(expr)`** prints an integer followed by a newline.

---

## 4. Encapsulation: state + behavior together

A class bundles data (fields) with the operations on that data (methods). The
`bank.oom` example models an account whose balance can only change through its
methods:

```
class Account {
    int balance;

    func void init(int start)  { self.balance = start; }
    func void deposit(int amt) { self.balance = self.balance + amt; }
    func int  getBalance()     { return self.balance; }
}
```

```
Account a;
a = new Account(100);
a.deposit(50);
print(a.getBalance());     // 150
```

Constructors can take arguments: `new Account(100)` passes `100` to `init`.

---

## 5. Inheritance: `extends`

A subclass automatically gets all the fields and methods of its parent, and
may add its own. **A parent class must be defined before any class that
extends it.**

```
class Savings extends Account {
    int rate;                          // NEW field, added after inherited ones

    func void init(int start) {        // override the constructor
        self.balance = start;          // balance is inherited
        self.rate = 5;
    }
    func void addInterest() {          // NEW method
        self.balance = self.balance + self.balance * self.rate / 100;
    }
}
```

```
Savings s;
s = new Savings(200);
s.deposit(100);        // inherited from Account  -> 300
s.addInterest();       // 300 + 300*5/100         -> 315
print(s.getBalance()); // inherited from Account  -> 315
```

Inherited fields keep the same memory offset in the child as in the parent, so
inherited methods like `deposit` and `getBalance` work unchanged on a
`Savings` object.

---

## 6. Polymorphism: overriding + dynamic dispatch

This is the heart of OO. A subclass can **override** a method, and when you
call that method the version chosen depends on the object's **runtime** type —
not the declared type of the variable.

```
class Animal {
    int legs;
    func void init(int l)  { self.legs = l; }
    func int  sound()      { return 0; }          // base version
    func void describe() {
        print(self.legs);
        print(self.sound());                       // dispatches dynamically
    }
}

class Dog extends Animal { func int sound() { return 111; } }   // override
class Cat extends Animal { func int sound() { return 222; } }   // override

func void main() {
    Animal a;  Dog d;  Cat c;
    a = new Animal(0);
    d = new Dog(4);
    c = new Cat(4);
    a.describe();    // 0  0
    d.describe();    // 4  111   <- Dog.sound(), even though describe() lives in Animal
    c.describe();    // 4  222   <- Cat.sound()
}
```

`describe()` is defined once in `Animal`, but its call to `self.sound()`
resolves to `Dog.sound` or `Cat.sound` at runtime. That is polymorphism.

---

## 7. Language reference (quick)

**Types:** `int`, and any class name (an object reference). `void` is a method
return type only.

**Top level:** class definitions and function definitions, in any order
(parents before subclasses). Exactly one `func void main()` is required.

**Class body items:**
- Field: `int name;` or `ClassName name;`
- Method: `func <retType> name(<params>) { <body> }`
- Constructor: a method literally named `init`.

**Statements:**
| Form | Meaning |
|------|---------|
| `int x;` / `ClassName o;` | declaration |
| `x = expr;` | assignment |
| `o.field = expr;` | field assignment |
| `print(expr);` | print an integer + newline |
| `if (cond) { } else { }` | conditional (braces required; `else` optional) |
| `while (cond) { }` | loop (braces required) |
| `return expr;` / `return;` | return from function/method |
| `o.method(args);` / `f(args);` | call used as a statement |

**Expressions:** integer literals, variables, `self`, `obj.field`,
`obj.method(args)`, `f(args)`, `new Class(args)`, arithmetic `+ - * /`,
relational `< > <= >= == !=`, unary minus, and parentheses.

**Relational operators** yield `1` (true) or `0` (false), so use them as `if`
/ `while` conditions: `while (i < 5) { ... }`.

---

## 8. How it maps to MIPS (under the hood)

- **Objects live on the heap.** `new C(...)` calls `sbrk` (syscall 9) to
  allocate `4 + 4*fieldCount` bytes. Word 0 is a pointer to the class's
  **vtable**; the fields follow.
- **Inheritance = layout sharing.** A subclass copies the parent's field
  layout first, so an inherited field has the same offset everywhere.
- **Polymorphism = vtables.** Each class emits a `ClassName_vtable` in `.data`
  holding one method address per slot. Overrides replace the address in the
  inherited slot. A method call loads the vtable pointer from the object,
  loads the method address from its slot, and `jalr`s to it — that's dynamic
  dispatch.
- **Calling convention.** Arguments go in `$a0..$a3`; for a method, `$a0` is
  the implicit `self`. Return value in `$v0`. A frame pointer `$fp` anchors
  locals so expression evaluation can use the stack freely.

Open the generated `.s` file and the `.oom.tac` file side by side to see this
concretely.

---

## 9. Limits (by design, to stay "minimal")

- The only scalar type is `int`; objects are references to `int` fields.
- Methods take at most 3 explicit arguments (because `$a0` is `self`); free
  functions at most 4.
- Single inheritance only (no multiple inheritance, no interfaces).
- No garbage collection — heap objects are never freed (fine for short
  programs).
- All methods are virtual (Java-style); there is no `final`/non-virtual
  distinction.

---

## 10. The included examples

| File | Demonstrates | Expected output |
|------|--------------|-----------------|
| `examples/counter.oom` | objects, `while`, free functions | `5` then `25` |
| `examples/bank.oom` | encapsulation, constructors, inherited methods, new fields | `150` then `315` |
| `examples/shapes.oom` | overriding + polymorphism via dynamic dispatch | `0 0 4 111 4 222` |

Try them:

```
./oomini examples/shapes.oom shapes.s && spim -file shapes.s
```
