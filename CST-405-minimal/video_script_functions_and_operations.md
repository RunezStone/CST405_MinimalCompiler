# Video Script — Functions & Types of Operations
### ~2 Minutes | CST-405 Mini-Compiler

---

**[0:00 – 0:12] — INTRO**

> "I want to talk about two specific design choices I made in this compiler — how I ended functions, and how I handled operators — and why I made those choices."

---

**[0:12 – 1:05] — DESIGN CHOICE 1: THE `end` KEYWORD**

> "Most languages end a function with a closing curly brace. I didn't do that. I designed a dedicated keyword — `end` — that every single function has to finish with."

*(show on screen:)*
```
func add(int a, int b)
    int result;
    result = a + b;
end result;
```

> "The reason I made this choice is about the lexer. When the lexer scans through the file, it needs to know when a function is over. A closing brace is ambiguous — it could close an if-block, a loop, or a function. The lexer can't tell the difference without a lot of extra context.

> With `end`, there's no ambiguity. The lexer sees END and it knows: a function boundary is here. That's an identifiable token that belongs exclusively to function endings.

> But I took it one step further. After `end`, you either write the name of the variable you're returning, or you write `null`. So the return value is part of the closing syntax itself — not a separate return statement somewhere inside the body.

*(show: `end result;` vs `end null;`)*

> "This matters because the lexer emits `END` as one token and then immediately either an ID token — the return variable — or the `NULLTOK` token for void. The parser can always see, right at the function boundary, exactly what's being returned. There's no searching backward through the body. The information is right there, attached to the closing token, every time."

---

**[1:05 – 1:50] — DESIGN CHOICE 2: HOW OPERATORS ARE IMPLEMENTED**

> "For operators, I made a different kind of design choice. I didn't create separate named tokens for plus, minus, multiply, and divide. Instead, the lexer returns the character itself directly."

*(show scanner.l rules:)*
```
"+"  { return '+'; }
"-"  { return '-'; }
"*"  { return '*'; }
"/"  { return '/'; }
```

> "The reason is simplicity of the pipeline. Because the lexer passes the raw character through, the parser can match it directly in the grammar rule. And when the AST node is created, the operator gets stored as a single char — one field, no mapping, no enum conversion needed at that stage.

*(show: `$$ = createBinOp('+', $1, $3);`)*

> "Then later, when TAC is generated, that char is matched in a switch statement to produce the right TAC opcode — TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV. And when MIPS assembly is generated, the same char drives another switch that emits `add`, `sub`, `mul`, or the special-case `div` plus `mflo`.

*(show the switch in tac.c:)*
```
case '+': tacOp = TAC_ADD; break;
case '-': tacOp = TAC_SUB; break;
case '*': tacOp = TAC_MUL; break;
case '/': tacOp = TAC_DIV; break;
```

> "So the operator character flows cleanly through every phase — lexer, parser, AST, TAC, code gen — without ever needing to be re-encoded. That's why I kept it as a raw character rather than creating a separate token type."

---

**[1:50 – 2:00] — CLOSER**

> "Both of these choices were about making each phase of the compiler's job as unambiguous as possible. `end` gives the lexer a guaranteed function boundary. Raw operator characters give the pipeline a single representation that carries through without translation."

---

*[END]*
