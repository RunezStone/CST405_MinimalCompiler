; OOMini Three-Address Code
; ----------------------------------------

func Account_init:
    self .balance = start          ; member store
endfunc

func Account_deposit:
    t0 = self .balance          ; member load
    t1 = t0 + amt
    self .balance = t1          ; member store
endfunc

func Account_getBalance:
    t2 = self .balance          ; member load
    return t2
endfunc

func Savings_init:
    self .balance = start          ; member store
    self .rate = 5          ; member store
endfunc

func Savings_addInterest:
    t3 = self .balance          ; member load
    t4 = self .balance          ; member load
    t5 = self .rate          ; member load
    t6 = t4 * t5
    t7 = t6 / 100
    t8 = t3 + t7
    self .balance = t8          ; member store
endfunc

func main:
    decl Account a
    decl Savings s
    t9 = new Account(8)        ; heap alloc + set vtable
    param t9              ; self
    param 100
    call Account_init, 1 args      ; constructor (resolved)
    a = t9
    param a              ; self
    param 50
    t10 = vcall a.deposit [slot 1], 1 args  ; dynamic dispatch
    param a              ; self
    t11 = vcall a.getBalance [slot 2], 0 args  ; dynamic dispatch
    print t11
    t12 = new Savings(12)        ; heap alloc + set vtable
    param t12              ; self
    param 200
    call Savings_init, 1 args      ; constructor (resolved)
    s = t12
    param s              ; self
    param 100
    t13 = vcall s.deposit [slot 1], 1 args  ; dynamic dispatch
    param s              ; self
    t14 = vcall s.addInterest [slot 3], 0 args  ; dynamic dispatch
    param s              ; self
    t15 = vcall s.getBalance [slot 2], 0 args  ; dynamic dispatch
    print t15
endfunc

