; OOMini Three-Address Code
; ----------------------------------------

func MathUtil_init:
    return
endfunc

func MathUtil_mod:
    t0 = a / b
    t1 = t0 * b
    t2 = a - t1
    return t2
endfunc

func MathUtil_absVal:
    t3 = x < 0
    ifFalse t3 goto L0
    t4 = 0 - x
    return t4
    goto L1
L0:
L1:
    return x
endfunc

func MathUtil_isEven:
    param self              ; self
    param x
    param 2
    t5 = vcall self.mod [slot 1], 2 args  ; dynamic dispatch
    t6 = t5 == 0
    ifFalse t6 goto L2
    return 1
    goto L3
L2:
L3:
    return 0
endfunc

func Exhibit_compute:
    return 0
endfunc

func Exhibit_show:
    param self              ; self
    param n
    t7 = vcall self.compute [slot 4], 1 args  ; dynamic dispatch
    print t7
endfunc

func Factorial_compute:
    decl int result
    decl int i
    result = 1
    i = 2
L4:
    t8 = i <= n
    ifFalse t8 goto L5
    t9 = result * i
    result = t9
    t10 = i + 1
    i = t10
    goto L4
L5:
    return result
endfunc

func Fibonacci_compute:
    decl int a
    decl int b
    decl int t
    decl int i
    a = 0
    b = 1
    i = 0
L6:
    t11 = i < n
    ifFalse t11 goto L7
    t12 = a + b
    t = t12
    a = b
    b = t
    t13 = i + 1
    i = t13
    goto L6
L7:
    return a
endfunc

func Triangular_compute:
    decl int sum
    decl int i
    sum = 0
    i = 1
L8:
    t14 = i <= n
    ifFalse t14 goto L9
    t15 = sum + i
    sum = t15
    t16 = i + 1
    i = t16
    goto L8
L9:
    return sum
endfunc

func Prime_compute:
    decl int i
    t17 = n < 2
    ifFalse t17 goto L10
    return 0
    goto L11
L10:
L11:
    i = 2
L12:
    t18 = i * i
    t19 = t18 <= n
    ifFalse t19 goto L13
    param self              ; self
    param n
    param i
    t20 = vcall self.mod [slot 1], 2 args  ; dynamic dispatch
    t21 = t20 == 0
    ifFalse t21 goto L14
    return 0
    goto L15
L14:
L15:
    t22 = i + 1
    i = t22
    goto L12
L13:
    return 1
endfunc

func Isqrt_compute:
    decl int k
    k = 0
L16:
    t23 = k + 1
    t24 = k + 1
    t25 = t23 * t24
    t26 = t25 <= n
    ifFalse t26 goto L17
    t27 = k + 1
    k = t27
    goto L16
L17:
    return k
endfunc

func DigitSum_compute:
    decl int sum
    decl int x
    param self              ; self
    param n
    t28 = vcall self.absVal [slot 2], 1 args  ; dynamic dispatch
    x = t28
    sum = 0
L18:
    t29 = x > 0
    ifFalse t29 goto L19
    param self              ; self
    param x
    param 10
    t30 = vcall self.mod [slot 1], 2 args  ; dynamic dispatch
    t31 = sum + t30
    sum = t31
    t32 = x / 10
    x = t32
    goto L18
L19:
    return sum
endfunc

func Reverse_compute:
    decl int rev
    decl int x
    param self              ; self
    param n
    t33 = vcall self.absVal [slot 2], 1 args  ; dynamic dispatch
    x = t33
    rev = 0
L20:
    t34 = x > 0
    ifFalse t34 goto L21
    t35 = rev * 10
    param self              ; self
    param x
    param 10
    t36 = vcall self.mod [slot 1], 2 args  ; dynamic dispatch
    t37 = t35 + t36
    rev = t37
    t38 = x / 10
    x = t38
    goto L20
L21:
    return rev
endfunc

func Collatz_compute:
    decl int steps
    decl int x
    x = n
    steps = 0
L22:
    t39 = x > 1
    ifFalse t39 goto L23
    param self              ; self
    param x
    t40 = vcall self.isEven [slot 3], 1 args  ; dynamic dispatch
    t41 = t40 == 1
    ifFalse t41 goto L24
    t42 = x / 2
    x = t42
    goto L25
L24:
    t43 = 3 * x
    t44 = t43 + 1
    x = t44
L25:
    t45 = steps + 1
    steps = t45
    goto L22
L23:
    return steps
endfunc

func Divisors_compute:
    decl int count
    decl int i
    count = 0
    i = 1
L26:
    t46 = i <= n
    ifFalse t46 goto L27
    param self              ; self
    param n
    param i
    t47 = vcall self.mod [slot 1], 2 args  ; dynamic dispatch
    t48 = t47 == 0
    ifFalse t48 goto L28
    t49 = count + 1
    count = t49
    goto L29
L28:
L29:
    t50 = i + 1
    i = t50
    goto L26
L27:
    return count
endfunc

func Pairwise_gcd:
    decl int t
    param self              ; self
    param a
    t51 = vcall self.absVal [slot 2], 1 args  ; dynamic dispatch
    a = t51
    param self              ; self
    param b
    t52 = vcall self.absVal [slot 2], 1 args  ; dynamic dispatch
    b = t52
L30:
    t53 = b != 0
    ifFalse t53 goto L31
    param self              ; self
    param a
    param b
    t54 = vcall self.mod [slot 1], 2 args  ; dynamic dispatch
    t = t54
    a = b
    b = t
    goto L30
L31:
    return a
endfunc

func Pairwise_lcm:
    param self              ; self
    param a
    param b
    t55 = vcall self.gcd [slot 4], 2 args  ; dynamic dispatch
    t56 = a / t55
    t57 = t56 * b
    return t57
endfunc

func Pairwise_power:
    decl int result
    decl int i
    result = 1
    i = 0
L32:
    t58 = i < exp
    ifFalse t58 goto L33
    t59 = result * base
    result = t59
    t60 = i + 1
    i = t60
    goto L32
L33:
    return result
endfunc

func main:
    decl Factorial fact
    decl Fibonacci fib
    decl Triangular tri
    decl Prime prime
    decl Isqrt root
    decl DigitSum dsum
    decl Reverse rev
    decl Collatz col
    decl Divisors div
    decl Pairwise pair
    t61 = new Factorial(4)        ; heap alloc + set vtable
    param t61              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    fact = t61
    t62 = new Fibonacci(4)        ; heap alloc + set vtable
    param t62              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    fib = t62
    t63 = new Triangular(4)        ; heap alloc + set vtable
    param t63              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    tri = t63
    t64 = new Prime(4)        ; heap alloc + set vtable
    param t64              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    prime = t64
    t65 = new Isqrt(4)        ; heap alloc + set vtable
    param t65              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    root = t65
    t66 = new DigitSum(4)        ; heap alloc + set vtable
    param t66              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    dsum = t66
    t67 = new Reverse(4)        ; heap alloc + set vtable
    param t67              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    rev = t67
    t68 = new Collatz(4)        ; heap alloc + set vtable
    param t68              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    col = t68
    t69 = new Divisors(4)        ; heap alloc + set vtable
    param t69              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    div = t69
    t70 = new Pairwise(4)        ; heap alloc + set vtable
    param t70              ; self
    call MathUtil_init, 0 args      ; constructor (resolved)
    pair = t70
    param fact              ; self
    param 5
    t71 = vcall fact.show [slot 5], 1 args  ; dynamic dispatch
    param fib              ; self
    param 10
    t72 = vcall fib.show [slot 5], 1 args  ; dynamic dispatch
    param tri              ; self
    param 10
    t73 = vcall tri.show [slot 5], 1 args  ; dynamic dispatch
    param prime              ; self
    param 17
    t74 = vcall prime.show [slot 5], 1 args  ; dynamic dispatch
    param prime              ; self
    param 15
    t75 = vcall prime.show [slot 5], 1 args  ; dynamic dispatch
    param root              ; self
    param 50
    t76 = vcall root.show [slot 5], 1 args  ; dynamic dispatch
    param dsum              ; self
    param 12345
    t77 = vcall dsum.show [slot 5], 1 args  ; dynamic dispatch
    param rev              ; self
    param 1234
    t78 = vcall rev.show [slot 5], 1 args  ; dynamic dispatch
    param col              ; self
    param 6
    t79 = vcall col.show [slot 5], 1 args  ; dynamic dispatch
    param div              ; self
    param 12
    t80 = vcall div.show [slot 5], 1 args  ; dynamic dispatch
    param pair              ; self
    param 48
    param 36
    t81 = vcall pair.gcd [slot 4], 2 args  ; dynamic dispatch
    print t81
    param pair              ; self
    param 4
    param 6
    t82 = vcall pair.lcm [slot 5], 2 args  ; dynamic dispatch
    print t82
    param pair              ; self
    param 2
    param 10
    t83 = vcall pair.power [slot 6], 2 args  ; dynamic dispatch
    print t83
endfunc

