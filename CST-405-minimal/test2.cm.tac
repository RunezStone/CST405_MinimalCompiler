# Three-Address Code (TAC) - Unoptimized
# ─────────────────────────────────────

 1: DECL int a
 2: DECL int b
 3: DECL int result
 4: FUNC_BEGIN add
 5: PARAM num1
 6: PARAM num2
 7: DECL int result
 8: t0 = num1 + num2
 9: result = t0
10: RETURN result
11: FUNC_END add
12: FUNC_BEGIN Program_Start
13: a = 10
14: b = 3
15: t1 = a + b
16: t3 = a - b
17: t2 = t1 * t3
18: t4 = t2 / 2
19: result = t4
20: PRINT result
21: a = 4
22: b = 5
23: ARG a
24: ARG b
25: t5 = CALL add, 2
26: b = t5
27: PRINT b
28: FUNC_END Program_Start
