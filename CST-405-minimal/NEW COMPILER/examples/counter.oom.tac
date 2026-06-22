; OOMini Three-Address Code
; ----------------------------------------

func Counter_init:
    self .n = 0          ; member store
endfunc

func Counter_inc:
    t0 = self .n          ; member load
    t1 = t0 + 1
    self .n = t1          ; member store
endfunc

func Counter_get:
    t2 = self .n          ; member load
    return t2
endfunc

func square:
    t3 = x * x
    return t3
endfunc

func main:
    decl Counter c
    decl int i
    t4 = new Counter(8)        ; heap alloc + set vtable
    param t4              ; self
    call Counter_init, 0 args      ; constructor (resolved)
    c = t4
    i = 0
L0:
    t5 = i < 5
    ifFalse t5 goto L1
    param c              ; self
    t6 = vcall c.inc [slot 1], 0 args  ; dynamic dispatch
    t7 = i + 1
    i = t7
    goto L0
L1:
    param c              ; self
    t8 = vcall c.get [slot 2], 0 args  ; dynamic dispatch
    print t8
    param c              ; self
    t9 = vcall c.get [slot 2], 0 args  ; dynamic dispatch
    param t9
    t10 = call square, 1 args
    print t10
endfunc

