; OOMini Three-Address Code
; ----------------------------------------

func Animal_init:
    self .legs = l          ; member store
endfunc

func Animal_sound:
    return 0
endfunc

func Animal_describe:
    t0 = self .legs          ; member load
    print t0
    param self              ; self
    t1 = vcall self.sound [slot 1], 0  ; dynamic dispatch
    print t1
endfunc

func Dog_sound:
    return 111
endfunc

func Cat_sound:
    return 222
endfunc

func main:
    decl Animal a
    decl Dog d
    decl Cat c
    t2 = new Animal(8)        ; heap alloc + set vtable
    param t2              ; self
    param 0
    call Animal_init, 1
    a = t2
    t3 = new Dog(8)        ; heap alloc + set vtable
    param t3              ; self
    param 4
    call Dog_init, 1
    d = t3
    t4 = new Cat(8)        ; heap alloc + set vtable
    param t4              ; self
    param 4
    call Cat_init, 1
    c = t4
    param a              ; self
    t5 = vcall a.describe [slot -1], 0  ; dynamic dispatch
    param d              ; self
    t6 = vcall d.describe [slot -1], 0  ; dynamic dispatch
    param c              ; self
    t7 = vcall c.describe [slot -1], 0  ; dynamic dispatch
endfunc

