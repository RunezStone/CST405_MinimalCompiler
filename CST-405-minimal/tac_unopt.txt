# Three-Address Code (TAC) - Unoptimized
# ─────────────────────────────────────

 1: DECL int gCount
 2: DECL int gSize
 3: FUNC_BEGIN greet
 4: PRINT 999
 5: FUNC_END greet
 6: FUNC_BEGIN getAnswer
 7: DECL int ans
 8: ans = 42
 9: RETURN ans
10: FUNC_END getAnswer
11: FUNC_BEGIN square
12: PARAM n
13: DECL int result
14: t0 = n * n
15: result = t0
16: RETURN result
17: FUNC_END square
18: FUNC_BEGIN average
19: PARAM a
20: PARAM b
21: DECL int r
22: t1 = a / b
23: r = t1
24: RETURN r
25: FUNC_END average
26: FUNC_BEGIN increment
27: t2 = gCount + 1
28: gCount = t2
29: FUNC_END increment
30: FUNC_BEGIN factorial
31: PARAM n
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
45: RETURN result
46: FUNC_END factorial
47: FUNC_BEGIN sumArray
48: PARAM size
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
63: RETURN total
64: FUNC_END sumArray
65: FUNC_BEGIN isEven
66: PARAM n
67: DECL int half
68: t10 = n / 2
69: t11 = t10 * 2
70: half = t11
71: t12 = n == half
72: IF_FALSE t12 GOTO L4
73: RETURN 1
74: LABEL L4:
75: RETURN 0
76: FUNC_END isEven
77: FUNC_BEGIN fibFunc
78: PARAM n
79: DECL int a
80: DECL int b
81: DECL int next
82: DECL int k
83: a = 0
84: b = 1
85: k = 0
86: LABEL L5:
87: t13 = k < n
88: IF_FALSE t13 GOTO L6
89: t14 = a + b
90: next = t14
91: a = b
92: b = next
93: t15 = k + 1
94: k = t15
95: GOTO L5
96: LABEL L6:
97: RETURN a
98: FUNC_END fibFunc
99: FUNC_BEGIN Program_Start
100: DECL int a
101: DECL int b
102: DECL int c
103: a = 42
104: b = 8
105: t16 = a - b
106: c = t16
107: PRINT a
108: PRINT b
109: PRINT c
110: DECL int flag
111: DECL int done
112: flag = 1
113: done = 0
114: PRINT flag
115: PRINT done
116: DECL char grade
117: DECL char init
118: grade = 65
119: init = 90
120: PRINT grade
121: PRINT init
122: PRINT "Alice"
123: PRINT "Hello"
124: nums[0] = 10
125: nums[1] = 20
126: nums[2] = 30
127: nums[3] = 40
128: nums[4] = 50
129: nums[5] = 60
130: t17 = nums[0]
131: PRINT t17
132: t18 = nums[3]
133: PRINT t18
134: t19 = nums[5]
135: PRINT t19
136: DECL int dummy
137: t20 = CALL greet, 0
138: dummy = t20
139: DECL int magic
140: t21 = CALL getAnswer, 0
141: magic = t21
142: PRINT magic
143: DECL int sq
144: ARG 7
145: t22 = CALL square, 1
146: sq = t22
147: PRINT sq
148: DECL int avg
149: ARG 10
150: ARG 3
151: t23 = CALL average, 2
152: avg = t23
153: PRINT avg
154: gCount = 0
155: t24 = CALL increment, 0
156: dummy = t24
157: t25 = CALL increment, 0
158: dummy = t25
159: t26 = CALL increment, 0
160: dummy = t26
161: PRINT gCount
162: DECL int fact
163: ARG 5
164: t27 = CALL factorial, 1
165: fact = t27
166: PRINT fact
167: gArr[0] = 1
168: gArr[1] = 2
169: gArr[2] = 3
170: gArr[3] = 4
171: gArr[4] = 5
172: DECL int s
173: ARG 5
174: t28 = CALL sumArray, 1
175: s = t28
176: PRINT s
177: DECL int even
178: ARG 4
179: t29 = CALL isEven, 1
180: even = t29
181: PRINT even
182: ARG 7
183: t30 = CALL isEven, 1
184: even = t30
185: PRINT even
186: DECL int i
187: DECL int total
188: i = 1
189: total = 0
190: LABEL L7:
191: t31 = i <= 10
192: IF_FALSE t31 GOTO L8
193: t32 = total + i
194: total = t32
195: t33 = i + 1
196: i = t33
197: GOTO L7
198: LABEL L8:
199: PRINT total
200: DECL int j
201: DECL int fsum
202: fsum = 0
203: j = 1
204: LABEL L9:
205: t34 = j <= 5
206: IF_FALSE t34 GOTO L10
207: t35 = fsum + j
208: fsum = t35
209: t36 = j + 1
210: j = t36
211: GOTO L9
212: LABEL L10:
213: PRINT fsum
214: j = 0
215: LABEL L11:
216: t37 = j < 5
217: IF_FALSE t37 GOTO L12
218: t38 = j * j
219: data[j] = t38
220: t39 = j + 1
221: j = t39
222: GOTO L11
223: LABEL L12:
224: j = 0
225: LABEL L13:
226: t40 = j < 5
227: IF_FALSE t40 GOTO L14
228: t41 = data[j]
229: PRINT t41
230: t42 = j + 1
231: j = t42
232: GOTO L13
233: LABEL L14:
234: DECL int row
235: DECL int col
236: DECL int product
237: row = 1
238: LABEL L15:
239: t43 = row <= 2
240: IF_FALSE t43 GOTO L16
241: col = 1
242: LABEL L17:
243: t44 = col <= 3
244: IF_FALSE t44 GOTO L18
245: t45 = row * col
246: product = t45
247: PRINT product
248: t46 = col + 1
249: col = t46
250: GOTO L17
251: LABEL L18:
252: t47 = row + 1
253: row = t47
254: GOTO L15
255: LABEL L16:
256: DECL int kk
257: DECL int acc
258: j = 1
259: LABEL L19:
260: t48 = j <= 3
261: IF_FALSE t48 GOTO L20
262: kk = 0
263: acc = 0
264: LABEL L21:
265: t49 = kk < j
266: IF_FALSE t49 GOTO L22
267: t50 = acc + 1
268: acc = t50
269: t51 = kk + 1
270: kk = t51
271: GOTO L21
272: LABEL L22:
273: PRINT acc
274: t52 = j + 1
275: j = t52
276: GOTO L19
277: LABEL L20:
278: DECL int val
279: val = 10
280: t53 = val > 5
281: IF_FALSE t53 GOTO L23
282: PRINT 100
283: LABEL L23:
284: val = 3
285: t54 = val > 5
286: IF_FALSE t54 GOTO L24
287: PRINT 200
288: GOTO L25
289: LABEL L24:
290: PRINT 201
291: LABEL L25:
292: val = 75
293: t55 = val >= 90
294: IF_FALSE t55 GOTO L26
295: PRINT 300
296: GOTO L27
297: LABEL L26:
298: t56 = val >= 80
299: IF_FALSE t56 GOTO L28
300: PRINT 301
301: GOTO L29
302: LABEL L28:
303: t57 = val >= 70
304: IF_FALSE t57 GOTO L30
305: PRINT 302
306: GOTO L31
307: LABEL L30:
308: PRINT 303
309: LABEL L31:
310: LABEL L29:
311: LABEL L27:
312: DECL int p
313: DECL int q
314: p = 5
315: q = 10
316: t58 = p < q
317: IF_FALSE t58 GOTO L32
318: t59 = p > 0
319: IF_FALSE t59 GOTO L34
320: PRINT 400
321: GOTO L35
322: LABEL L34:
323: PRINT 401
324: LABEL L35:
325: GOTO L33
326: LABEL L32:
327: PRINT 402
328: LABEL L33:
329: DECL int day
330: day = 3
331: DECL int __sw36
332: __sw36 = day
333: t60 = __sw36 == 1
334: IF_FALSE t60 GOTO L37
335: GOTO L36
336: LABEL L37:
337: t61 = __sw36 == 2
338: IF_FALSE t61 GOTO L39
339: GOTO L38
340: LABEL L39:
341: t62 = __sw36 == 3
342: IF_FALSE t62 GOTO L41
343: GOTO L40
344: LABEL L41:
345: GOTO L42
346: LABEL L36:
347: PRINT 501
348: GOTO L43
349: LABEL L38:
350: PRINT 502
351: GOTO L43
352: LABEL L40:
353: PRINT 503
354: GOTO L43
355: LABEL L42:
356: PRINT 500
357: GOTO L43
358: LABEL L43:
359: DECL int season
360: season = 2
361: DECL int __sw44
362: __sw44 = season
363: t63 = __sw44 == 1
364: IF_FALSE t63 GOTO L45
365: GOTO L44
366: LABEL L45:
367: t64 = __sw44 == 2
368: IF_FALSE t64 GOTO L47
369: GOTO L46
370: LABEL L47:
371: t65 = __sw44 == 3
372: IF_FALSE t65 GOTO L49
373: GOTO L48
374: LABEL L49:
375: t66 = __sw44 == 4
376: IF_FALSE t66 GOTO L51
377: GOTO L50
378: LABEL L51:
379: GOTO L52
380: LABEL L44:
381: LABEL L46:
382: LABEL L48:
383: PRINT 510
384: GOTO L53
385: LABEL L50:
386: PRINT 511
387: GOTO L53
388: LABEL L52:
389: PRINT 512
390: GOTO L53
391: LABEL L53:
392: DECL int code
393: code = 99
394: DECL int __sw54
395: __sw54 = code
396: t67 = __sw54 == 1
397: IF_FALSE t67 GOTO L55
398: GOTO L54
399: LABEL L55:
400: t68 = __sw54 == 2
401: IF_FALSE t68 GOTO L57
402: GOTO L56
403: LABEL L57:
404: GOTO L58
405: LABEL L54:
406: PRINT 520
407: GOTO L59
408: LABEL L56:
409: PRINT 521
410: GOTO L59
411: LABEL L58:
412: PRINT 522
413: GOTO L59
414: LABEL L59:
415: DECL int outer
416: DECL int inner
417: outer = 2
418: inner = 1
419: DECL int __sw60
420: __sw60 = outer
421: t69 = __sw60 == 1
422: IF_FALSE t69 GOTO L61
423: GOTO L60
424: LABEL L61:
425: t70 = __sw60 == 2
426: IF_FALSE t70 GOTO L63
427: GOTO L62
428: LABEL L63:
429: GOTO L64
430: LABEL L60:
431: DECL int __sw66
432: __sw66 = inner
433: t71 = __sw66 == 1
434: IF_FALSE t71 GOTO L67
435: GOTO L66
436: LABEL L67:
437: GOTO L68
438: LABEL L66:
439: PRINT 531
440: GOTO L69
441: LABEL L68:
442: PRINT 530
443: GOTO L69
444: LABEL L69:
445: GOTO L65
446: LABEL L62:
447: DECL int __sw70
448: __sw70 = inner
449: t72 = __sw70 == 1
450: IF_FALSE t72 GOTO L71
451: GOTO L70
452: LABEL L71:
453: GOTO L72
454: LABEL L70:
455: PRINT 532
456: GOTO L73
457: LABEL L72:
458: PRINT 530
459: GOTO L73
460: LABEL L73:
461: GOTO L65
462: LABEL L64:
463: PRINT 530
464: GOTO L65
465: LABEL L65:
466: DECL int fibA
467: DECL int fibB
468: DECL int fibNext
469: DECL int n
470: fibA = 0
471: fibB = 1
472: PRINT fibA
473: PRINT fibB
474: n = 2
475: LABEL L74:
476: t73 = n < 7
477: IF_FALSE t73 GOTO L75
478: t74 = fibA + fibB
479: fibNext = t74
480: PRINT fibNext
481: fibA = fibB
482: fibB = fibNext
483: t75 = n + 1
484: n = t75
485: GOTO L74
486: LABEL L75:
487: DECL int fibR
488: ARG 6
489: t76 = CALL fibFunc, 1
490: fibR = t76
491: PRINT fibR
492: DECL int perf
493: t77 = 2 * 3
494: t79 = 4 * 5
495: t78 = t77 + t79
496: t80 = t78 - 1
497: perf = t80
498: PRINT perf
499: DECL int limit
500: DECL int lcount
501: limit = 100
502: lcount = 0
503: i = 0
504: LABEL L76:
505: t81 = i < limit
506: IF_FALSE t81 GOTO L77
507: t82 = lcount + 1
508: lcount = t82
509: t83 = i + 1
510: i = t83
511: GOTO L76
512: LABEL L77:
513: PRINT lcount
514: DECL int dc
515: dc = 1
516: t84 = dc == 1
517: IF_FALSE t84 GOTO L78
518: PRINT 601
519: GOTO L79
520: LABEL L78:
521: PRINT 602
522: LABEL L79:
523: FUNC_END Program_Start
