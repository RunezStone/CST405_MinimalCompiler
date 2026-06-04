# Three-Address Code (TAC) - Unoptimized
# ─────────────────────────────────────

 1: DECL float x
 2: DECL float y
 3: DECL float z
 4: DECL int a
 5: DECL int b
 6: FUNC_BEGIN add
 7: PARAM num1
 8: PARAM num2
 9: DECL int result
10: t0 = num1 + num2
11: result = t0
12: RETURN result
13: FUNC_END add
14: FUNC_BEGIN Program_Start
15: x = 3.14
16: y = 2.0
17: t1 = x + y
18: z = t1
19: arr[1] = y
20: PRINT z
21: t2 = arr[1]
22: PRINT t2
23: a = 4
24: b = 5
25: ARG a
26: ARG b
27: t3 = CALL add, 2
28: b = t3
29: PRINT b
30: FUNC_END Program_Start
