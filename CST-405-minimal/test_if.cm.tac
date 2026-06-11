# Three-Address Code (TAC) - Unoptimized
# ─────────────────────────────────────

 1: DECL int x
 2: DECL int y
 3: DECL int result
 4: DECL stats playerStats
 5: DECL int playhealth
 6: FUNC_BEGIN add
 7: PARAM a
 8: PARAM b
 9: DECL int x
10: DECL int result
11: x = 0
12: t0 = a + b
13: result = t0
14: x = 0
15: LABEL L0:
16: t1 = x < 10
17: IF_FALSE t1 GOTO L1
18: PRINT result
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
30: PRINT x
31: GOTO L2
32: LABEL L3:
33: RETURN result
34: FUNC_END add
35: FUNC_BEGIN attackPlayer
36: PARAM damage
37: t6 = playhealth - damage
38: playhealth = t6
39: t7 = playhealth <= 0
40: IF_FALSE t7 GOTO L4
41: RETURN 1
42: GOTO L5
43: LABEL L4:
44: RETURN 0
45: LABEL L5:
46: RETURN 0
47: FUNC_END attackPlayer
48: FUNC_BEGIN Program_Start
49: x = 5
50: y = 10
51: result = 0
52: t8 = playerStats.health
53: playhealth = t8
54: PRINT playhealth
55: ARG x
56: t9 = CALL attackPlayer, 1
57: result = t9
58: t10 = result == 0
59: IF_FALSE t10 GOTO L6
60: y = 202
61: PRINT y
62: GOTO L7
63: LABEL L6:
64: y = 101
65: PRINT y
66: LABEL L7:
67: PRINT playhealth
68: PRINT result
69: FUNC_END Program_Start
