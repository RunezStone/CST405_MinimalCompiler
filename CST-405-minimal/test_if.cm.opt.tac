# Three-Address Code (TAC) - Optimized
# Optimized Three-Address Code
# ----------------------------------
1: DECL int x
2: DECL int y
3: DECL int result
4: DECL stats playerStats
5: DECL int playhealth
6: FUNC_BEGIN add
7: PARAM (null)
8: PARAM (null)
9: DECL int x
10: DECL int result
11: x = 0
12: t0 = a + b
13: result = t0
14: x = 0
15: LABEL L0:
16: t1 = x < 10
17: IF_FALSE t1 GOTO L1
18: print result
19: t2 = result + x
20: result = t2
21: t3 = x + 1
22: x = t3
23: GOTO L0
24: LABEL L1:
25: LABEL L2:
26: t4 = x > 0
27: IF_FALSE t4 GOTO L3
28: t5 = x - 1
29: x = t5
30: print t5
31: GOTO L2
32: LABEL L3:
33: RETURN (null)
34: FUNC_END add
35: FUNC_BEGIN attackPlayer
36: PARAM (null)
37: t6 = playhealth - damage
38: playhealth = t6
39: t7 = t6 <= 0
40: IF_FALSE t7 GOTO L4
41: RETURN (null)
42: GOTO L5
43: LABEL L4:
44: RETURN (null)
45: LABEL L5:
46: RETURN (null)
47: FUNC_END attackPlayer
48: FUNC_BEGIN Program_Start
49: x = 5
50: result = 0
51: t8 = playerStats.health
52: playhealth = t8
53: print t8
54: ARG (null)
55: t9 = CALL attackPlayer, 1
56: result = t9
57: print "Hello world"
58: t10 = t9 == 0
59: IF_FALSE t10 GOTO L6
60: print 202
61: GOTO L7
62: LABEL L6:
63: print 101
64: LABEL L7:
65: print playhealth
66: print result
67: FUNC_END Program_Start
