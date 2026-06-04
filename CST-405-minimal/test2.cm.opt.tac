# Three-Address Code (TAC) - Optimized
# Optimized Three-Address Code
# ----------------------------------
1: DECL int a
2: DECL int b
3: DECL int result
4: FUNC_BEGIN add
5: PARAM (null)
6: PARAM (null)
7: DECL int result
8: t0 = num1 + num2
9: result = t0
10: RETURN (null)
11: FUNC_END add
12: FUNC_BEGIN Program_Start
13: a = 10
14: b = 3
15: result = 45
16: print 45
17: a = 4
18: b = 5
19: ARG (null)
20: ARG (null)
21: t5 = CALL add, 2
22: b = t5
23: print t5
24: FUNC_END Program_Start
