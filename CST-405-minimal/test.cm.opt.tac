# Three-Address Code (TAC) - Optimized
# Optimizations: Constant folding, Copy propagation, DCE
# ─────────────────────────────────────

 1: DECL int x
 2: DECL int y
 3: DECL int z
 4: FUNC_BEGIN add
 5: PARAM a
 6: PARAM b
 7: DECL int result
 8: t0 = a + b
 9: result = t0
10: RETURN result
11: FUNC_END add
12: FUNC_BEGIN Program_Start
13: x = 1
14: y = 2
15: ARG x
16: ARG y
17: t1 = CALL add, 2
18: PRINT t1
19: FUNC_END Program_Start
