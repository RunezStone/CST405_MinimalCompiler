# Three-Address Code (TAC) - Optimized
# Optimized Three-Address Code
# ----------------------------------
1: DECL int x
2: DECL int y
3: DECL int result
4: FUNC_BEGIN add
5: PARAM (null)
6: PARAM (null)
7: DECL int x
8: DECL int result
9: x = 0
10: t0 = a + b
11: result = t0
12: x = 0
13: LABEL L0:
14: t1 = x < 10
15: IF_FALSE t1 GOTO L1
16: print result
17: t2 = result + x
18: result = t2
19: t3 = x + 1
20: x = t3
21: GOTO L0
22: LABEL L1:
23: RETURN (null)
24: FUNC_END add
25: FUNC_BEGIN Program_Start
26: x = 5
27: y = 10
28: ARG (null)
29: ARG (null)
30: t4 = CALL add, 2
31: result = t4
32: result = 0
33: print 0
34: FUNC_END Program_Start
