# Three-Address Code (TAC) - Optimized
# Optimized Three-Address Code
# ----------------------------------
1: DECL float x
2: DECL float y
3: DECL float z
4: DECL int a
5: DECL int b
6: FUNC_BEGIN add
7: PARAM (null)
8: PARAM (null)
9: DECL int result
10: t0 = num1 + num2
11: result = t0
12: RETURN (null)
13: FUNC_END add
14: FUNC_BEGIN Program_Start
15: z = 5
16: arr[1] = y
17: print z
18: t2 = arr[1]
19: print t2
20: a = 4
21: b = 5
22: ARG (null)
23: ARG (null)
24: t3 = CALL add, 2
25: b = t3
26: print t3
27: FUNC_END Program_Start
