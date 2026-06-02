# Video Script — Functions & Types of Operations
### ~2 Minutes | CST-405 Mini-Compiler

---

**[0:00 – 0:15] — HOOK**

> "If you've ever written a function in any programming language, you've relied on your compiler to do a lot of invisible work. Let me show you exactly what that work is — and why it has to happen the way it does — inside this mini-compiler."

---

**[0:15 – 0:45] — FUNCTIONS: WHY THEY'RE HARD**

> "When the compiler sees a function declaration like this —"

*(show on screen: `func add(int a, int b) ... end result;`)*

> "— it can't just read it and move on. It has to do three things at once:
> manage the function's own memory space, figure out how values get passed in, and figure out how to return a result back to whoever called it.
>
> The reason this is hard is that MIPS — the assembly language this compiler targets — has only eight temporary registers. Once a function is running, it can call another function, which would overwrite those registers. So the compiler does something called a **stack frame**: it carves out 128 bytes on the stack, saves the return address in $ra, stores each parameter immediately — before anything else can clobber them — and only then runs the function body.
>
> Without saving $ra, the program would lose track of where to go after the function finishes. That's the whole reason for the prologue and epilogue in the assembly output."

---

**[0:45 – 1:15] — OPERATIONS: HOW THE COMPILER BREAKS THEM DOWN**

> "Now let's talk about operations. This compiler supports addition, subtraction, multiplication, division, and negation. The interesting one is division.
>
> MIPS division works differently from the others — it produces two results at once: the quotient and the remainder. It stores them in special registers called HI and LO. The compiler always emits a `div` instruction immediately followed by `mflo` — 'move from LO' — to grab the quotient."

*(show on screen: `div $t0, $t1` → `mflo $t0`)*

> "Why not just use a single instruction like addition does? Because the hardware was designed to capture both results in one shot, and the architecture requires you to retrieve them from HI/LO. The compiler has to know this — it's not a quirk, it's a fundamental property of the ISA."

---

**[1:15 – 1:45] — EXPRESSION TREES & PARENTHESES**

> "Here's where it comes together. Take this expression from the test file:"

*(show: `result = (a + b) * (a - b) / 2;`)*

> "Parentheses in the source code control which sub-expressions get built first in the Abstract Syntax Tree. The grammar rule is literally just `'(' expr ')'` — it returns the inner expression unchanged. No new node. No extra step. The parentheses disappear after parsing.
>
> Then the compiler linearises that tree into Three-Address Code — one operation per line — by recursively processing each subtree. Left side first, right side second, then combine. The result is five simple instructions. That's why you always break complex expressions into temporaries: the optimizer can then inspect each step individually and fold constants at compile time."

*(show TAC on screen: `t0 = a + b`, `t2 = a - b`, `t1 = t0 * t2`, `t3 = t1 / 2`, `result = t3`)*

---

**[1:45 – 2:00] — CLOSER**

> "So functions and operations aren't just language features — they each expose a specific constraint of the underlying hardware. The compiler's job is to know those constraints and translate around them correctly, every time. That's what this compiler does."

---

*[END]*
