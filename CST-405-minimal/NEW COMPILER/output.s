# ============================================
#  OOMini -> MIPS   (run with: spim -file output.s)
# ============================================

.data
MathUtil_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven
Exhibit_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Exhibit_compute, Exhibit_show
Factorial_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Factorial_compute, Exhibit_show
Fibonacci_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Fibonacci_compute, Exhibit_show
Triangular_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Triangular_compute, Exhibit_show
Prime_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Prime_compute, Exhibit_show
Isqrt_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Isqrt_compute, Exhibit_show
DigitSum_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, DigitSum_compute, Exhibit_show
Reverse_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Reverse_compute, Exhibit_show
Collatz_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Collatz_compute, Exhibit_show
Divisors_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Divisors_compute, Exhibit_show
Pairwise_vtable: .word MathUtil_init, MathUtil_mod, MathUtil_absVal, MathUtil_isEven, Pairwise_gcd, Pairwise_lcm, Pairwise_power

.text
.globl main

# ---- main ----
main:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    # decl Factorial fact
    li    $t0, 0
    sw    $t0, 0($fp)
    # decl Fibonacci fib
    li    $t0, 0
    sw    $t0, 4($fp)
    # decl Triangular tri
    li    $t0, 0
    sw    $t0, 8($fp)
    # decl Prime prime
    li    $t0, 0
    sw    $t0, 12($fp)
    # decl Isqrt root
    li    $t0, 0
    sw    $t0, 16($fp)
    # decl DigitSum dsum
    li    $t0, 0
    sw    $t0, 20($fp)
    # decl Reverse rev
    li    $t0, 0
    sw    $t0, 24($fp)
    # decl Collatz col
    li    $t0, 0
    sw    $t0, 28($fp)
    # decl Divisors div
    li    $t0, 0
    sw    $t0, 32($fp)
    # decl Pairwise pair
    li    $t0, 0
    sw    $t0, 36($fp)
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new Factorial
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, Factorial_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 0($fp)    # fact = ...
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new Fibonacci
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, Fibonacci_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 4($fp)    # fib = ...
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new Triangular
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, Triangular_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 8($fp)    # tri = ...
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new Prime
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, Prime_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 12($fp)    # prime = ...
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new Isqrt
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, Isqrt_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 16($fp)    # root = ...
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new DigitSum
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, DigitSum_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 20($fp)    # dsum = ...
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new Reverse
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, Reverse_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 24($fp)    # rev = ...
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new Collatz
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, Collatz_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 28($fp)    # col = ...
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new Divisors
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, Divisors_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 32($fp)    # div = ...
    li    $v0, 9          # sbrk: allocate object
    li    $a0, 4
    syscall
    move  $t0, $v0        # $t0 = new Pairwise
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    la    $t1, Pairwise_vtable
    sw    $t1, 0($t0)     # install vtable
    lw    $a0, 0($sp)    # self (new obj)
    addiu $sp, $sp, 0   # pop args, keep obj
    jal   MathUtil_init            # constructor
    lw    $t0, 0($sp)
    addiu $sp, $sp, 4
    sw    $t0, 36($fp)    # pair = ...
    lw    $t0, 0($fp)    # fact
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 5
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 4($fp)    # fib
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 10
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 8($fp)    # tri
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 10
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 12($fp)    # prime
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 17
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 12($fp)    # prime
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 15
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 16($fp)    # root
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 50
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 20($fp)    # dsum
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 12345
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 24($fp)    # rev
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1234
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 28($fp)    # col
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 6
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 32($fp)    # div
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 12
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = show
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t0, 36($fp)    # pair
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 48
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 36
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 16($t9)    # vtable[4] = gcd
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    move  $a0, $t0
    li    $v0, 1          # print int
    syscall
    li    $v0, 11         # print newline
    li    $a0, 10
    syscall
    lw    $t0, 36($fp)    # pair
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 4
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 6
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 20($t9)    # vtable[5] = lcm
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    move  $a0, $t0
    li    $v0, 1          # print int
    syscall
    li    $v0, 11         # print newline
    li    $a0, 10
    syscall
    lw    $t0, 36($fp)    # pair
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 2
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 10
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 24($t9)    # vtable[6] = power
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    move  $a0, $t0
    li    $v0, 1          # print int
    syscall
    li    $v0, 11         # print newline
    li    $a0, 10
    syscall
L_end_main:
    li    $v0, 10         # exit
    syscall

# ---- MathUtil_init ----
MathUtil_init:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    j     L_end_MathUtil_init
L_end_MathUtil_init:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- MathUtil_mod ----
MathUtil_mod:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    sw    $a2, 8($fp)    # param
    lw    $t0, 4($fp)    # a
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # a
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # b
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    div   $t1, $t0
    mflo  $t0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # b
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    mul   $t0, $t1, $t0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sub   $t0, $t1, $t0
    move  $v0, $t0
    j     L_end_MathUtil_mod
L_end_MathUtil_mod:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- MathUtil_absVal ----
MathUtil_absVal:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    lw    $t0, 4($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    slt   $t0, $t1, $t0
    beqz  $t0, Lelse0
    li    $t0, 0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # x
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sub   $t0, $t1, $t0
    move  $v0, $t0
    j     L_end_MathUtil_absVal
    j     Lendif1
Lelse0:
Lendif1:
    lw    $t0, 4($fp)    # x
    move  $v0, $t0
    j     L_end_MathUtil_absVal
L_end_MathUtil_absVal:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- MathUtil_isEven ----
MathUtil_isEven:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 2
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 4($t9)    # vtable[1] = mod
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    seq   $t0, $t1, $t0
    beqz  $t0, Lelse2
    li    $t0, 1
    move  $v0, $t0
    j     L_end_MathUtil_isEven
    j     Lendif3
Lelse2:
Lendif3:
    li    $t0, 0
    move  $v0, $t0
    j     L_end_MathUtil_isEven
L_end_MathUtil_isEven:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Exhibit_compute ----
Exhibit_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    li    $t0, 0
    move  $v0, $t0
    j     L_end_Exhibit_compute
L_end_Exhibit_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Exhibit_show ----
Exhibit_show:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 16($t9)    # vtable[4] = compute
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    move  $a0, $t0
    li    $v0, 1          # print int
    syscall
    li    $v0, 11         # print newline
    li    $a0, 10
    syscall
L_end_Exhibit_show:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Factorial_compute ----
Factorial_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    # decl int result
    li    $t0, 0
    sw    $t0, 8($fp)
    # decl int i
    li    $t0, 0
    sw    $t0, 12($fp)
    li    $t0, 1
    sw    $t0, 8($fp)    # result = ...
    li    $t0, 2
    sw    $t0, 12($fp)    # i = ...
Lwhile4:
    lw    $t0, 12($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sle   $t0, $t1, $t0
    beqz  $t0, Lendw5
    lw    $t0, 8($fp)    # result
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 12($fp)    # i
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    mul   $t0, $t1, $t0
    sw    $t0, 8($fp)    # result = ...
    lw    $t0, 12($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 12($fp)    # i = ...
    j     Lwhile4
Lendw5:
    lw    $t0, 8($fp)    # result
    move  $v0, $t0
    j     L_end_Factorial_compute
L_end_Factorial_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Fibonacci_compute ----
Fibonacci_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    # decl int a
    li    $t0, 0
    sw    $t0, 8($fp)
    # decl int b
    li    $t0, 0
    sw    $t0, 12($fp)
    # decl int t
    li    $t0, 0
    sw    $t0, 16($fp)
    # decl int i
    li    $t0, 0
    sw    $t0, 20($fp)
    li    $t0, 0
    sw    $t0, 8($fp)    # a = ...
    li    $t0, 1
    sw    $t0, 12($fp)    # b = ...
    li    $t0, 0
    sw    $t0, 20($fp)    # i = ...
Lwhile6:
    lw    $t0, 20($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    slt   $t0, $t1, $t0
    beqz  $t0, Lendw7
    lw    $t0, 8($fp)    # a
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 12($fp)    # b
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 16($fp)    # t = ...
    lw    $t0, 12($fp)    # b
    sw    $t0, 8($fp)    # a = ...
    lw    $t0, 16($fp)    # t
    sw    $t0, 12($fp)    # b = ...
    lw    $t0, 20($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 20($fp)    # i = ...
    j     Lwhile6
Lendw7:
    lw    $t0, 8($fp)    # a
    move  $v0, $t0
    j     L_end_Fibonacci_compute
L_end_Fibonacci_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Triangular_compute ----
Triangular_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    # decl int sum
    li    $t0, 0
    sw    $t0, 8($fp)
    # decl int i
    li    $t0, 0
    sw    $t0, 12($fp)
    li    $t0, 0
    sw    $t0, 8($fp)    # sum = ...
    li    $t0, 1
    sw    $t0, 12($fp)    # i = ...
Lwhile8:
    lw    $t0, 12($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sle   $t0, $t1, $t0
    beqz  $t0, Lendw9
    lw    $t0, 8($fp)    # sum
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 12($fp)    # i
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 8($fp)    # sum = ...
    lw    $t0, 12($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 12($fp)    # i = ...
    j     Lwhile8
Lendw9:
    lw    $t0, 8($fp)    # sum
    move  $v0, $t0
    j     L_end_Triangular_compute
L_end_Triangular_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Prime_compute ----
Prime_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    # decl int i
    li    $t0, 0
    sw    $t0, 8($fp)
    lw    $t0, 4($fp)    # n
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 2
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    slt   $t0, $t1, $t0
    beqz  $t0, Lelse10
    li    $t0, 0
    move  $v0, $t0
    j     L_end_Prime_compute
    j     Lendif11
Lelse10:
Lendif11:
    li    $t0, 2
    sw    $t0, 8($fp)    # i = ...
Lwhile12:
    lw    $t0, 8($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # i
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    mul   $t0, $t1, $t0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sle   $t0, $t1, $t0
    beqz  $t0, Lendw13
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 4($t9)    # vtable[1] = mod
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    seq   $t0, $t1, $t0
    beqz  $t0, Lelse14
    li    $t0, 0
    move  $v0, $t0
    j     L_end_Prime_compute
    j     Lendif15
Lelse14:
Lendif15:
    lw    $t0, 8($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 8($fp)    # i = ...
    j     Lwhile12
Lendw13:
    li    $t0, 1
    move  $v0, $t0
    j     L_end_Prime_compute
L_end_Prime_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Isqrt_compute ----
Isqrt_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    # decl int k
    li    $t0, 0
    sw    $t0, 8($fp)
    li    $t0, 0
    sw    $t0, 8($fp)    # k = ...
Lwhile16:
    lw    $t0, 8($fp)    # k
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # k
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    mul   $t0, $t1, $t0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sle   $t0, $t1, $t0
    beqz  $t0, Lendw17
    lw    $t0, 8($fp)    # k
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 8($fp)    # k = ...
    j     Lwhile16
Lendw17:
    lw    $t0, 8($fp)    # k
    move  $v0, $t0
    j     L_end_Isqrt_compute
L_end_Isqrt_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- DigitSum_compute ----
DigitSum_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    # decl int sum
    li    $t0, 0
    sw    $t0, 8($fp)
    # decl int x
    li    $t0, 0
    sw    $t0, 12($fp)
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 8($t9)    # vtable[2] = absVal
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    sw    $t0, 12($fp)    # x = ...
    li    $t0, 0
    sw    $t0, 8($fp)    # sum = ...
Lwhile18:
    lw    $t0, 12($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sgt   $t0, $t1, $t0
    beqz  $t0, Lendw19
    lw    $t0, 8($fp)    # sum
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 12($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 10
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 4($t9)    # vtable[1] = mod
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 8($fp)    # sum = ...
    lw    $t0, 12($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 10
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    div   $t1, $t0
    mflo  $t0
    sw    $t0, 12($fp)    # x = ...
    j     Lwhile18
Lendw19:
    lw    $t0, 8($fp)    # sum
    move  $v0, $t0
    j     L_end_DigitSum_compute
L_end_DigitSum_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Reverse_compute ----
Reverse_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    # decl int rev
    li    $t0, 0
    sw    $t0, 8($fp)
    # decl int x
    li    $t0, 0
    sw    $t0, 12($fp)
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 8($t9)    # vtable[2] = absVal
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    sw    $t0, 12($fp)    # x = ...
    li    $t0, 0
    sw    $t0, 8($fp)    # rev = ...
Lwhile20:
    lw    $t0, 12($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sgt   $t0, $t1, $t0
    beqz  $t0, Lendw21
    lw    $t0, 8($fp)    # rev
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 10
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    mul   $t0, $t1, $t0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 12($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 10
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 4($t9)    # vtable[1] = mod
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 8($fp)    # rev = ...
    lw    $t0, 12($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 10
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    div   $t1, $t0
    mflo  $t0
    sw    $t0, 12($fp)    # x = ...
    j     Lwhile20
Lendw21:
    lw    $t0, 8($fp)    # rev
    move  $v0, $t0
    j     L_end_Reverse_compute
L_end_Reverse_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Collatz_compute ----
Collatz_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    # decl int steps
    li    $t0, 0
    sw    $t0, 8($fp)
    # decl int x
    li    $t0, 0
    sw    $t0, 12($fp)
    lw    $t0, 4($fp)    # n
    sw    $t0, 12($fp)    # x = ...
    li    $t0, 0
    sw    $t0, 8($fp)    # steps = ...
Lwhile22:
    lw    $t0, 12($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sgt   $t0, $t1, $t0
    beqz  $t0, Lendw23
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 12($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 12($t9)    # vtable[3] = isEven
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    seq   $t0, $t1, $t0
    beqz  $t0, Lelse24
    lw    $t0, 12($fp)    # x
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 2
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    div   $t1, $t0
    mflo  $t0
    sw    $t0, 12($fp)    # x = ...
    j     Lendif25
Lelse24:
    li    $t0, 3
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 12($fp)    # x
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    mul   $t0, $t1, $t0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 12($fp)    # x = ...
Lendif25:
    lw    $t0, 8($fp)    # steps
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 8($fp)    # steps = ...
    j     Lwhile22
Lendw23:
    lw    $t0, 8($fp)    # steps
    move  $v0, $t0
    j     L_end_Collatz_compute
L_end_Collatz_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Divisors_compute ----
Divisors_compute:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    # decl int count
    li    $t0, 0
    sw    $t0, 8($fp)
    # decl int i
    li    $t0, 0
    sw    $t0, 12($fp)
    li    $t0, 0
    sw    $t0, 8($fp)    # count = ...
    li    $t0, 1
    sw    $t0, 12($fp)    # i = ...
Lwhile26:
    lw    $t0, 12($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sle   $t0, $t1, $t0
    beqz  $t0, Lendw27
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # n
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 12($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 4($t9)    # vtable[1] = mod
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    seq   $t0, $t1, $t0
    beqz  $t0, Lelse28
    lw    $t0, 8($fp)    # count
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 8($fp)    # count = ...
    j     Lendif29
Lelse28:
Lendif29:
    lw    $t0, 12($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 12($fp)    # i = ...
    j     Lwhile26
Lendw27:
    lw    $t0, 8($fp)    # count
    move  $v0, $t0
    j     L_end_Divisors_compute
L_end_Divisors_compute:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Pairwise_gcd ----
Pairwise_gcd:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    sw    $a2, 8($fp)    # param
    # decl int t
    li    $t0, 0
    sw    $t0, 12($fp)
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # a
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 8($t9)    # vtable[2] = absVal
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    sw    $t0, 4($fp)    # a = ...
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # b
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 4($sp)    # self
    lw    $a1, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 8($t9)    # vtable[2] = absVal
    addiu $sp, $sp, 8
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    sw    $t0, 8($fp)    # b = ...
Lwhile30:
    lw    $t0, 8($fp)    # b
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    sne   $t0, $t1, $t0
    beqz  $t0, Lendw31
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # a
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # b
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 4($t9)    # vtable[1] = mod
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    sw    $t0, 12($fp)    # t = ...
    lw    $t0, 8($fp)    # b
    sw    $t0, 4($fp)    # a = ...
    lw    $t0, 12($fp)    # t
    sw    $t0, 8($fp)    # b = ...
    j     Lwhile30
Lendw31:
    lw    $t0, 4($fp)    # a
    move  $v0, $t0
    j     L_end_Pairwise_gcd
L_end_Pairwise_gcd:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Pairwise_lcm ----
Pairwise_lcm:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    sw    $a2, 8($fp)    # param
    lw    $t0, 4($fp)    # a
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 0($fp)    # self
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # a
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # b
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $a0, 8($sp)    # self
    lw    $a1, 4($sp)
    lw    $a2, 0($sp)
    lw    $t9, 0($a0)     # vtable ptr
    lw    $t9, 16($t9)    # vtable[4] = gcd
    addiu $sp, $sp, 12
    jalr  $t9            # dynamic dispatch
    move  $t0, $v0
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    div   $t1, $t0
    mflo  $t0
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # b
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    mul   $t0, $t1, $t0
    move  $v0, $t0
    j     L_end_Pairwise_lcm
L_end_Pairwise_lcm:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra

# ---- Pairwise_power ----
Pairwise_power:
    addiu $sp, $sp, -1024
    sw    $ra, 1020($sp)
    sw    $fp, 1016($sp)
    move  $fp, $sp
    sw    $a0, 0($fp)    # self
    sw    $a1, 4($fp)    # param
    sw    $a2, 8($fp)    # param
    # decl int result
    li    $t0, 0
    sw    $t0, 12($fp)
    # decl int i
    li    $t0, 0
    sw    $t0, 16($fp)
    li    $t0, 1
    sw    $t0, 12($fp)    # result = ...
    li    $t0, 0
    sw    $t0, 16($fp)    # i = ...
Lwhile32:
    lw    $t0, 16($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 8($fp)    # exp
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    slt   $t0, $t1, $t0
    beqz  $t0, Lendw33
    lw    $t0, 12($fp)    # result
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    lw    $t0, 4($fp)    # base
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    mul   $t0, $t1, $t0
    sw    $t0, 12($fp)    # result = ...
    lw    $t0, 16($fp)    # i
    addiu $sp, $sp, -4
    sw    $t0, 0($sp)
    li    $t0, 1
    lw    $t1, 0($sp)
    addiu $sp, $sp, 4
    add   $t0, $t1, $t0
    sw    $t0, 16($fp)    # i = ...
    j     Lwhile32
Lendw33:
    lw    $t0, 12($fp)    # result
    move  $v0, $t0
    j     L_end_Pairwise_power
L_end_Pairwise_power:
    move  $sp, $fp
    lw    $ra, 1020($sp)
    lw    $fp, 1016($sp)
    addiu $sp, $sp, 1024
    jr    $ra
