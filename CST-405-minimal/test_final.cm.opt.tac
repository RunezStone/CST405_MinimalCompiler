# Three-Address Code (TAC) - Optimized
# Optimized Three-Address Code
# ----------------------------------
1: DECL int gCount
2: DECL int gSize
3: FUNC_BEGIN greet
4: print 999
5: FUNC_END greet
6: FUNC_BEGIN getAnswer
7: DECL int ans
8: ans = 42
9: RETURN (null)
10: FUNC_END getAnswer
11: FUNC_BEGIN square
12: PARAM (null)
13: DECL int result
14: t0 = n * n
15: result = t0
16: RETURN (null)
17: FUNC_END square
18: FUNC_BEGIN average
19: PARAM (null)
20: PARAM (null)
21: DECL int r
22: t1 = a / b
23: r = t1
24: RETURN (null)
25: FUNC_END average
26: FUNC_BEGIN increment
27: t2 = gCount + 1
28: gCount = t2
29: FUNC_END increment
30: FUNC_BEGIN factorial
31: PARAM (null)
32: DECL int result
33: DECL int i
34: result = 1
35: i = 1
36: LABEL L0:
37: t3 = i <= n
38: IF_FALSE t3 GOTO L1
39: t4 = result * i
40: result = t4
41: t5 = i + 1
42: i = t5
43: GOTO L0
44: LABEL L1:
45: RETURN (null)
46: FUNC_END factorial
47: FUNC_BEGIN sumArray
48: PARAM (null)
49: DECL int total
50: DECL int idx
51: total = 0
52: idx = 0
53: LABEL L2:
54: t6 = idx < size
55: IF_FALSE t6 GOTO L3
56: t8 = gArr[idx]
57: t7 = total + t8
58: total = t7
59: t9 = idx + 1
60: idx = t9
61: GOTO L2
62: LABEL L3:
63: RETURN (null)
64: FUNC_END sumArray
65: FUNC_BEGIN isEven
66: PARAM (null)
67: DECL int half
68: t10 = n / 2
69: t11 = t10 * 2
70: t12 = n == t11
71: IF_FALSE t12 GOTO L4
72: RETURN (null)
73: LABEL L4:
74: RETURN (null)
75: FUNC_END isEven
76: FUNC_BEGIN fibFunc
77: PARAM (null)
78: DECL int a
79: DECL int b
80: DECL int next
81: DECL int k
82: a = 0
83: b = 1
84: k = 0
85: LABEL L5:
86: t13 = k < n
87: IF_FALSE t13 GOTO L6
88: t14 = a + b
89: a = b
90: b = t14
91: t15 = k + 1
92: k = t15
93: GOTO L5
94: LABEL L6:
95: RETURN (null)
96: FUNC_END fibFunc
97: FUNC_BEGIN Program_Start
98: DECL int a
99: DECL int b
100: DECL int c
101: a = 42
102: b = 8
103: print 42
104: print 8
105: print 34
106: DECL int flag
107: DECL int done
108: print 1
109: print 0
110: DECL char grade
111: DECL char init
112: print 65
113: print 90
114: print "Alice"
115: print "Hello"
116: nums[0] = 10
117: nums[1] = 20
118: nums[2] = 30
119: nums[3] = 40
120: nums[4] = 50
121: nums[5] = 60
122: t17 = nums[0]
123: print t17
124: t18 = nums[3]
125: print t18
126: t19 = nums[5]
127: print t19
128: DECL int dummy
129: t20 = CALL greet, 0
130: DECL int magic
131: t21 = CALL getAnswer, 0
132: print t21
133: DECL int sq
134: ARG (null)
135: t22 = CALL square, 1
136: print t22
137: DECL int avg
138: ARG (null)
139: ARG (null)
140: t23 = CALL average, 2
141: print t23
142: gCount = 0
143: t24 = CALL increment, 0
144: t25 = CALL increment, 0
145: t26 = CALL increment, 0
146: print 0
147: DECL int fact
148: ARG (null)
149: t27 = CALL factorial, 1
150: print t27
151: gArr[0] = 1
152: gArr[1] = 2
153: gArr[2] = 3
154: gArr[3] = 4
155: gArr[4] = 5
156: DECL int s
157: ARG (null)
158: t28 = CALL sumArray, 1
159: print t28
160: DECL int even
161: ARG (null)
162: t29 = CALL isEven, 1
163: print t29
164: ARG (null)
165: t30 = CALL isEven, 1
166: print t30
167: DECL int i
168: DECL int total
169: i = 1
170: total = 0
171: LABEL L7:
172: t31 = i <= 10
173: IF_FALSE t31 GOTO L8
174: t32 = total + i
175: total = t32
176: t33 = i + 1
177: i = t33
178: GOTO L7
179: LABEL L8:
180: print total
181: DECL int j
182: DECL int fsum
183: fsum = 0
184: j = 1
185: LABEL L9:
186: t34 = j <= 5
187: IF_FALSE t34 GOTO L10
188: t35 = fsum + j
189: fsum = t35
190: t36 = j + 1
191: j = t36
192: GOTO L9
193: LABEL L10:
194: print fsum
195: j = 0
196: LABEL L11:
197: t37 = j < 5
198: IF_FALSE t37 GOTO L12
199: data[j] = t38
200: t39 = j + 1
201: j = t39
202: GOTO L11
203: LABEL L12:
204: j = 0
205: LABEL L13:
206: t40 = j < 5
207: IF_FALSE t40 GOTO L14
208: t41 = data[j]
209: print t41
210: t42 = j + 1
211: j = t42
212: GOTO L13
213: LABEL L14:
214: DECL int row
215: DECL int col
216: DECL int product
217: row = 1
218: LABEL L15:
219: t43 = row <= 2
220: IF_FALSE t43 GOTO L16
221: col = 1
222: LABEL L17:
223: t44 = col <= 3
224: IF_FALSE t44 GOTO L18
225: t45 = row * col
226: print t45
227: t46 = col + 1
228: col = t46
229: GOTO L17
230: LABEL L18:
231: t47 = row + 1
232: row = t47
233: GOTO L15
234: LABEL L16:
235: DECL int kk
236: DECL int acc
237: j = 1
238: LABEL L19:
239: t48 = j <= 3
240: IF_FALSE t48 GOTO L20
241: kk = 0
242: acc = 0
243: LABEL L21:
244: t49 = kk < j
245: IF_FALSE t49 GOTO L22
246: t50 = acc + 1
247: acc = t50
248: t51 = kk + 1
249: kk = t51
250: GOTO L21
251: LABEL L22:
252: print acc
253: t52 = j + 1
254: j = t52
255: GOTO L19
256: LABEL L20:
257: DECL int val
258: val = 10
259: IF_FALSE 1 GOTO L23
260: print 100
261: LABEL L23:
262: val = 3
263: IF_FALSE 0 GOTO L24
264: print 200
265: GOTO L25
266: LABEL L24:
267: print 201
268: LABEL L25:
269: val = 75
270: IF_FALSE 0 GOTO L26
271: print 300
272: GOTO L27
273: LABEL L26:
274: t56 = val >= 80
275: IF_FALSE t56 GOTO L28
276: print 301
277: GOTO L29
278: LABEL L28:
279: t57 = val >= 70
280: IF_FALSE t57 GOTO L30
281: print 302
282: GOTO L31
283: LABEL L30:
284: print 303
285: LABEL L31:
286: LABEL L29:
287: LABEL L27:
288: DECL int p
289: DECL int q
290: IF_FALSE 1 GOTO L32
291: IF_FALSE 1 GOTO L34
292: print 400
293: GOTO L35
294: LABEL L34:
295: print 401
296: LABEL L35:
297: GOTO L33
298: LABEL L32:
299: print 402
300: LABEL L33:
301: DECL int day
302: DECL int __sw36
303: __sw36 = 3
304: IF_FALSE 0 GOTO L37
305: GOTO L36
306: LABEL L37:
307: t61 = __sw36 == 2
308: IF_FALSE t61 GOTO L39
309: GOTO L38
310: LABEL L39:
311: t62 = __sw36 == 3
312: IF_FALSE t62 GOTO L41
313: GOTO L40
314: LABEL L41:
315: GOTO L42
316: LABEL L36:
317: print 501
318: GOTO L43
319: LABEL L38:
320: print 502
321: GOTO L43
322: LABEL L40:
323: print 503
324: GOTO L43
325: LABEL L42:
326: print 500
327: GOTO L43
328: LABEL L43:
329: DECL int season
330: DECL int __sw44
331: __sw44 = 2
332: IF_FALSE 0 GOTO L45
333: GOTO L44
334: LABEL L45:
335: t64 = __sw44 == 2
336: IF_FALSE t64 GOTO L47
337: GOTO L46
338: LABEL L47:
339: t65 = __sw44 == 3
340: IF_FALSE t65 GOTO L49
341: GOTO L48
342: LABEL L49:
343: t66 = __sw44 == 4
344: IF_FALSE t66 GOTO L51
345: GOTO L50
346: LABEL L51:
347: GOTO L52
348: LABEL L44:
349: LABEL L46:
350: LABEL L48:
351: print 510
352: GOTO L53
353: LABEL L50:
354: print 511
355: GOTO L53
356: LABEL L52:
357: print 512
358: GOTO L53
359: LABEL L53:
360: DECL int code
361: DECL int __sw54
362: __sw54 = 99
363: IF_FALSE 0 GOTO L55
364: GOTO L54
365: LABEL L55:
366: t68 = __sw54 == 2
367: IF_FALSE t68 GOTO L57
368: GOTO L56
369: LABEL L57:
370: GOTO L58
371: LABEL L54:
372: print 520
373: GOTO L59
374: LABEL L56:
375: print 521
376: GOTO L59
377: LABEL L58:
378: print 522
379: GOTO L59
380: LABEL L59:
381: DECL int outer
382: DECL int inner
383: inner = 1
384: DECL int __sw60
385: __sw60 = 2
386: IF_FALSE 0 GOTO L61
387: GOTO L60
388: LABEL L61:
389: t70 = __sw60 == 2
390: IF_FALSE t70 GOTO L63
391: GOTO L62
392: LABEL L63:
393: GOTO L64
394: LABEL L60:
395: DECL int __sw66
396: t71 = inner == 1
397: IF_FALSE t71 GOTO L67
398: GOTO L66
399: LABEL L67:
400: GOTO L68
401: LABEL L66:
402: print 531
403: GOTO L69
404: LABEL L68:
405: print 530
406: GOTO L69
407: LABEL L69:
408: GOTO L65
409: LABEL L62:
410: DECL int __sw70
411: t72 = inner == 1
412: IF_FALSE t72 GOTO L71
413: GOTO L70
414: LABEL L71:
415: GOTO L72
416: LABEL L70:
417: print 532
418: GOTO L73
419: LABEL L72:
420: print 530
421: GOTO L73
422: LABEL L73:
423: GOTO L65
424: LABEL L64:
425: print 530
426: GOTO L65
427: LABEL L65:
428: DECL int fibA
429: DECL int fibB
430: DECL int fibNext
431: DECL int n
432: fibA = 0
433: fibB = 1
434: print 0
435: print 1
436: n = 2
437: LABEL L74:
438: t73 = n < 7
439: IF_FALSE t73 GOTO L75
440: t74 = fibA + fibB
441: print t74
442: fibA = fibB
443: fibB = t74
444: t75 = n + 1
445: n = t75
446: GOTO L74
447: LABEL L75:
448: DECL int fibR
449: ARG (null)
450: t76 = CALL fibFunc, 1
451: print t76
452: DECL int perf
453: print 25
454: DECL int limit
455: DECL int lcount
456: limit = 100
457: lcount = 0
458: i = 0
459: LABEL L76:
460: t81 = i < limit
461: IF_FALSE t81 GOTO L77
462: t82 = lcount + 1
463: lcount = t82
464: t83 = i + 1
465: i = t83
466: GOTO L76
467: LABEL L77:
468: print lcount
469: DECL int dc
470: IF_FALSE 1 GOTO L78
471: print 601
472: GOTO L79
473: LABEL L78:
474: print 602
475: LABEL L79:
476: FUNC_END Program_Start
