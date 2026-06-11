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
46: DECL int score
47: DECL char grade
48: print "Hello"
49: DECL int __sw4
50: __sw4 = 10
51: IF_FALSE 1 GOTO L5
52: GOTO L4
53: LABEL L5:
54: t10 = __sw4 == 9
55: IF_FALSE t10 GOTO L7
56: GOTO L6
57: LABEL L7:
58: t11 = __sw4 == 8
59: IF_FALSE t11 GOTO L9
60: GOTO L8
61: LABEL L9:
62: t12 = __sw4 == 7
63: IF_FALSE t12 GOTO L11
64: GOTO L10
65: LABEL L11:
66: t13 = __sw4 == 6
67: IF_FALSE t13 GOTO L13
68: GOTO L12
69: LABEL L13:
70: GOTO L14
71: LABEL L4:
72: LABEL L6:
73: grade = 65
74: GOTO L15
75: LABEL L8:
76: grade = 66
77: GOTO L15
78: LABEL L10:
79: grade = 67
80: GOTO L15
81: LABEL L12:
82: grade = 68
83: GOTO L15
84: LABEL L14:
85: grade = 70
86: GOTO L15
87: LABEL L15:
88: print grade
89: FUNC_END Program_Start
