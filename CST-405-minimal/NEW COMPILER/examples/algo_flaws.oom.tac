; OOMini Three-Address Code
; ----------------------------------------

func sign:
    t0 = x > 0
    ifFalse t0 goto L0
    return 1
    goto L1
L0:
L1:
endfunc

func safeDivide:
    t1 = a / b
    return t1
endfunc

func scaleUp:
    decl int result
    decl int i
    result = 0
    i = 0
L2:
    t2 = i < factor
    ifFalse t2 goto L3
    t3 = result + x
    result = t3
    t4 = i + 1
    i = t4
    goto L2
L3:
    return result
endfunc

func compute:
    decl int i
    decl int sum
    decl int step
    i = 0
    sum = 0
L4:
    t5 = i < n
    ifFalse t5 goto L5
    t6 = a + b
    step = t6
    t7 = sum + step
    sum = t7
    t8 = i + 1
    i = t8
    goto L4
L5:
    return sum
endfunc

func countUp:
    decl int i
    decl int count
    i = 1
    count = 0
L6:
    t9 = i < n
    ifFalse t9 goto L7
    t10 = count + 1
    count = t10
    t11 = i + 1
    i = t11
    goto L6
L7:
    return count
endfunc

func main:
    param 3
    param 4
    t12 = call scaleUp, 2 args
    print t12
    param 2
    param 3
    param 5
    t13 = call compute, 3 args
    print t13
    param 5
    t14 = call countUp, 1 args
    print t14
endfunc

