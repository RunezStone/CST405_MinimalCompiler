# Three-Address Code (TAC) - Unoptimized
# ─────────────────────────────────────

 1: DECL int x
 2: DECL int y
 3: DECL int result
 4: FUNC_BEGIN add
 5: PARAM a
 6: PARAM b
 7: DECL int x
 8: DECL int result
 9: x = 0
10: t0 = a + b
11: result = t0
12: x = 0
13: LABEL L0:
14: t1 = x < 10
15: IF_FALSE t1 GOTO L1
16: PRINT result
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
28: PRINT x
29: GOTO L2
30: LABEL L3:
31: RETURN result
32: FUNC_END add
33: FUNC_BEGIN Program_Start
34: DECL stats playerStats
35: DECL int playhealth
36: x = 5
37: y = 10
38: ARG x
39: ARG y
40: t6 = CALL add, 2
41: result = t6
42: result = 0
43: t7 = playerStats.health
44: playhealth = t7
45: PRINT playhealth
46: PRINT result
47: DECL int score
48: score = 100
49: DECL char grade
50: PRINT "Hello"
51: DECL int __sw4
52: t8 = score / 10
53: __sw4 = t8
54: t9 = __sw4 == 10
55: IF_FALSE t9 GOTO L5
56: GOTO L4
57: LABEL L5:
58: t10 = __sw4 == 9
59: IF_FALSE t10 GOTO L7
60: GOTO L6
61: LABEL L7:
62: t11 = __sw4 == 8
63: IF_FALSE t11 GOTO L9
64: GOTO L8
65: LABEL L9:
66: t12 = __sw4 == 7
67: IF_FALSE t12 GOTO L11
68: GOTO L10
69: LABEL L11:
70: t13 = __sw4 == 6
71: IF_FALSE t13 GOTO L13
72: GOTO L12
73: LABEL L13:
74: GOTO L14
75: LABEL L4:
76: LABEL L6:
77: grade = 65
78: GOTO L15
79: LABEL L8:
80: grade = 66
81: GOTO L15
82: LABEL L10:
83: grade = 67
84: GOTO L15
85: LABEL L12:
86: grade = 68
87: GOTO L15
88: LABEL L14:
89: grade = 70
90: GOTO L15
91: LABEL L15:
92: PRINT grade
93: FUNC_END Program_Start
