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
23: LABEL L2:
24: t4 = x > 0
25: IF_FALSE t4 GOTO L3
26: t5 = x - 1
27: x = t5
28: print t5
29: GOTO L2
30: LABEL L3:
31: RETURN (null)
32: FUNC_END add
33: FUNC_BEGIN Program_Start
34: DECL stats playerStats
35: DECL int playhealth
36: x = 5
37: y = 10
38: ARG (null)
39: ARG (null)
40: t6 = CALL add, 2
41: result = t6
42: result = 0
43: t7 = playerStats.health
44: print t7
45: print 0
46: FUNC_END Program_Start
