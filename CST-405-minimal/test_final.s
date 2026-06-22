# Generated MIPS Assembly
# -------------------------------------

.data
__str0: .asciiz "Alice"
__str1: .asciiz "Hello"

.text
.globl main

# -- Function: greet --
func_greet:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    li $t0, 999
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

# -- Function: getAnswer --
func_getAnswer:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    # Declare int ans at offset 0
    li $t0, 42
    sw   $t0, 0($sp)   # ans = ...
    lw   $v0, 0($sp)   # return ans
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

# -- Function: square --
func_square:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    sw   $a0, 0($sp)   # param n
    # Declare int result at offset 4
    lw $t0, 0($sp)
    lw $t1, 0($sp)
    mul $t0, $t0, $t1
    sw   $t0, 4($sp)   # result = ...
    lw   $v0, 4($sp)   # return result
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

# -- Function: average --
func_average:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    sw   $a0, 0($sp)   # param a
    sw   $a1, 4($sp)   # param b
    # Declare int r at offset 8
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    div $t0, $t1
    mflo $t0
    sw   $t0, 8($sp)   # r = ...
    lw   $v0, 8($sp)   # return r
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

# -- Function: increment --
func_increment:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    lw $t0, 0($s7)   # global gCount
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 0($s7)   # gCount = ...
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

# -- Function: factorial --
func_factorial:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    sw   $a0, 0($sp)   # param n
    # Declare int result at offset 4
    # Declare int i at offset 8
    li $t0, 1
    sw   $t0, 4($sp)   # result = ...
    li $t0, 1
    sw   $t0, 8($sp)   # i = ...
Lstart0:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    sle $t0, $t0, $t1
    beqz $t0, Lend0
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    mul $t0, $t0, $t1
    sw   $t0, 4($sp)   # result = ...
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 8($sp)   # i = ...
    j Lstart0
Lend0:
    lw   $v0, 4($sp)   # return result
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

# -- Function: sumArray --
func_sumArray:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    sw   $a0, 0($sp)   # param size
    # Declare int total at offset 4
    # Declare int idx at offset 8
    li $t0, 0
    sw   $t0, 4($sp)   # total = ...
    li $t0, 0
    sw   $t0, 8($sp)   # idx = ...
Lstart1:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    slt $t0, $t0, $t1
    beqz $t0, Lend1
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    sll $t1, $t1, 2   # gArr index * 4
    add $t2, $t1, $s7   # &gArr[i]
    lw $t3, 4($t2)   # gArr[i]
    add $t0, $t0, $t3
    sw   $t0, 4($sp)   # total = ...
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 8($sp)   # idx = ...
    j Lstart1
Lend1:
    lw   $v0, 4($sp)   # return total
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

# -- Function: isEven --
func_isEven:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    sw   $a0, 0($sp)   # param n
    # Declare int half at offset 4
    lw $t0, 0($sp)
    li $t1, 2
    div $t0, $t1
    mflo $t0
    li $t1, 2
    mul $t0, $t0, $t1
    sw   $t0, 4($sp)   # half = ...
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    seq $t0, $t0, $t1
    beqz $t0, Lend2
    li   $v0, 1   # early return value
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra
Lend2:
    li   $v0, 0   # return literal
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

# -- Function: fibFunc --
func_fibFunc:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    sw   $a0, 0($sp)   # param n
    # Declare int a at offset 4
    # Declare int b at offset 8
    # Declare int next at offset 12
    # Declare int k at offset 16
    li $t0, 0
    sw   $t0, 4($sp)   # a = ...
    li $t0, 1
    sw   $t0, 8($sp)   # b = ...
    li $t0, 0
    sw   $t0, 16($sp)   # k = ...
Lstart3:
    lw $t0, 16($sp)
    lw $t1, 0($sp)
    slt $t0, $t0, $t1
    beqz $t0, Lend3
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw   $t0, 12($sp)   # next = ...
    lw $t0, 8($sp)
    sw   $t0, 4($sp)   # a = ...
    lw $t0, 12($sp)
    sw   $t0, 8($sp)   # b = ...
    lw $t0, 16($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 16($sp)   # k = ...
    j Lstart3
Lend3:
    lw   $v0, 4($sp)   # return a
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

main:
    # Allocate global stack frame
    addi $sp, $sp, -400
    move $s7, $sp   # global frame pointer

    # Declare int gCount at offset 0
    # Declare array gArr[5] at offset 4
    # Declare int gSize at offset 24
    # Declare int a at offset 28
    # Declare int b at offset 32
    # Declare int c at offset 36
    li $t0, 42
    sw   $t0, 28($sp)   # a = ...
    li $t0, 8
    sw   $t0, 32($sp)   # b = ...
    lw $t0, 28($sp)
    lw $t1, 32($sp)
    sub $t0, $t0, $t1
    sw   $t0, 36($sp)   # c = ...
    lw $t0, 28($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 32($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 36($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int flag at offset 40
    # Declare int done at offset 44
    li $t0, 1
    sw   $t0, 40($sp)   # flag = ...
    li $t0, 0
    sw   $t0, 44($sp)   # done = ...
    lw $t0, 40($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 44($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare char grade at offset 48
    # Declare char init at offset 52
    li $t0, 65
    sw   $t0, 48($sp)   # grade = ...
    li $t0, 90
    sw   $t0, 52($sp)   # init = ...
    lw $t0, 48($sp)
    # Print char
    move $a0, $t0
    li   $v0, 11
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 52($sp)
    # Print char
    move $a0, $t0
    li   $v0, 11
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    la   $t0, __str0
    # Print string
    move $a0, $t0
    li   $v0, 4
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    la   $t0, __str1
    # Print string
    move $a0, $t0
    li   $v0, 4
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare array nums[6] at offset 56
    li $t0, 10
    li $t1, 0
    sll $t1, $t1, 2   # nums index * 4
    add $t2, $t1, $sp   # &nums[i]
    sw $t0, 56($t2)   # nums[i] = ...
    li $t0, 20
    li $t1, 1
    sll $t1, $t1, 2   # nums index * 4
    add $t2, $t1, $sp   # &nums[i]
    sw $t0, 56($t2)   # nums[i] = ...
    li $t0, 30
    li $t1, 2
    sll $t1, $t1, 2   # nums index * 4
    add $t2, $t1, $sp   # &nums[i]
    sw $t0, 56($t2)   # nums[i] = ...
    li $t0, 40
    li $t1, 3
    sll $t1, $t1, 2   # nums index * 4
    add $t2, $t1, $sp   # &nums[i]
    sw $t0, 56($t2)   # nums[i] = ...
    li $t0, 50
    li $t1, 4
    sll $t1, $t1, 2   # nums index * 4
    add $t2, $t1, $sp   # &nums[i]
    sw $t0, 56($t2)   # nums[i] = ...
    li $t0, 60
    li $t1, 5
    sll $t1, $t1, 2   # nums index * 4
    add $t2, $t1, $sp   # &nums[i]
    sw $t0, 56($t2)   # nums[i] = ...
    li $t0, 0
    sll $t0, $t0, 2   # nums index * 4
    add $t1, $t0, $sp   # &nums[i]
    lw $t2, 56($t1)   # nums[i]
    # Print integer
    move $a0, $t2
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 3
    sll $t0, $t0, 2   # nums index * 4
    add $t1, $t0, $sp   # &nums[i]
    lw $t2, 56($t1)   # nums[i]
    # Print integer
    move $a0, $t2
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 5
    sll $t0, $t0, 2   # nums index * 4
    add $t1, $t0, $sp   # &nums[i]
    lw $t2, 56($t1)   # nums[i]
    # Print integer
    move $a0, $t2
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int dummy at offset 80
    jal func_greet
    sw   $v0, 80($sp)   # dummy = call result
    # Declare int magic at offset 84
    jal func_getAnswer
    sw   $v0, 84($sp)   # magic = call result
    lw $t0, 84($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int sq at offset 88
    li $t0, 7
    move $a0, $t0
    jal func_square
    sw   $v0, 88($sp)   # sq = call result
    lw $t0, 88($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int avg at offset 92
    li $t0, 10
    li $t1, 3
    move $a0, $t0
    move $a1, $t1
    jal func_average
    sw   $v0, 92($sp)   # avg = call result
    lw $t0, 92($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 0
    sw   $t0, 0($sp)   # gCount = ...
    jal func_increment
    sw   $v0, 80($sp)   # dummy = call result
    jal func_increment
    sw   $v0, 80($sp)   # dummy = call result
    jal func_increment
    sw   $v0, 80($sp)   # dummy = call result
    lw $t0, 0($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int fact at offset 96
    li $t0, 5
    move $a0, $t0
    jal func_factorial
    sw   $v0, 96($sp)   # fact = call result
    lw $t0, 96($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 1
    li $t1, 0
    sll $t1, $t1, 2   # gArr index * 4
    add $t2, $t1, $sp   # &gArr[i]
    sw $t0, 4($t2)   # gArr[i] = ...
    li $t0, 2
    li $t1, 1
    sll $t1, $t1, 2   # gArr index * 4
    add $t2, $t1, $sp   # &gArr[i]
    sw $t0, 4($t2)   # gArr[i] = ...
    li $t0, 3
    li $t1, 2
    sll $t1, $t1, 2   # gArr index * 4
    add $t2, $t1, $sp   # &gArr[i]
    sw $t0, 4($t2)   # gArr[i] = ...
    li $t0, 4
    li $t1, 3
    sll $t1, $t1, 2   # gArr index * 4
    add $t2, $t1, $sp   # &gArr[i]
    sw $t0, 4($t2)   # gArr[i] = ...
    li $t0, 5
    li $t1, 4
    sll $t1, $t1, 2   # gArr index * 4
    add $t2, $t1, $sp   # &gArr[i]
    sw $t0, 4($t2)   # gArr[i] = ...
    # Declare int s at offset 100
    li $t0, 5
    move $a0, $t0
    jal func_sumArray
    sw   $v0, 100($sp)   # s = call result
    lw $t0, 100($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int even at offset 104
    li $t0, 4
    move $a0, $t0
    jal func_isEven
    sw   $v0, 104($sp)   # even = call result
    lw $t0, 104($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 7
    move $a0, $t0
    jal func_isEven
    sw   $v0, 104($sp)   # even = call result
    lw $t0, 104($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int i at offset 108
    # Declare int total at offset 112
    li $t0, 1
    sw   $t0, 108($sp)   # i = ...
    li $t0, 0
    sw   $t0, 112($sp)   # total = ...
Lstart4:
    lw $t0, 108($sp)
    li $t1, 10
    sle $t0, $t0, $t1
    beqz $t0, Lend4
    lw $t0, 112($sp)
    lw $t1, 108($sp)
    add $t0, $t0, $t1
    sw   $t0, 112($sp)   # total = ...
    lw $t0, 108($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 108($sp)   # i = ...
    j Lstart4
Lend4:
    lw $t0, 112($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int j at offset 116
    # Declare int fsum at offset 120
    li $t0, 0
    sw   $t0, 120($sp)   # fsum = ...
    li $t0, 1
    sw   $t0, 116($sp)   # j = ...
Lstart5:
    lw $t0, 116($sp)
    li $t1, 5
    sle $t0, $t0, $t1
    beqz $t0, Lend5
    lw $t0, 120($sp)
    lw $t1, 116($sp)
    add $t0, $t0, $t1
    sw   $t0, 120($sp)   # fsum = ...
    lw $t0, 116($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 116($sp)   # j = ...
    j Lstart5
Lend5:
    lw $t0, 120($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare array data[5] at offset 124
    li $t0, 0
    sw   $t0, 116($sp)   # j = ...
Lstart6:
    lw $t0, 116($sp)
    li $t1, 5
    slt $t0, $t0, $t1
    beqz $t0, Lend6
    lw $t0, 116($sp)
    lw $t1, 116($sp)
    mul $t0, $t0, $t1
    lw $t1, 116($sp)
    sll $t1, $t1, 2   # data index * 4
    add $t2, $t1, $sp   # &data[i]
    sw $t0, 124($t2)   # data[i] = ...
    lw $t0, 116($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 116($sp)   # j = ...
    j Lstart6
Lend6:
    li $t0, 0
    sw   $t0, 116($sp)   # j = ...
Lstart7:
    lw $t0, 116($sp)
    li $t1, 5
    slt $t0, $t0, $t1
    beqz $t0, Lend7
    lw $t0, 116($sp)
    sll $t0, $t0, 2   # data index * 4
    add $t1, $t0, $sp   # &data[i]
    lw $t2, 124($t1)   # data[i]
    # Print integer
    move $a0, $t2
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 116($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 116($sp)   # j = ...
    j Lstart7
Lend7:
    # Declare int row at offset 144
    # Declare int col at offset 148
    # Declare int product at offset 152
    li $t0, 1
    sw   $t0, 144($sp)   # row = ...
Lstart8:
    lw $t0, 144($sp)
    li $t1, 2
    sle $t0, $t0, $t1
    beqz $t0, Lend8
    li $t0, 1
    sw   $t0, 148($sp)   # col = ...
Lstart9:
    lw $t0, 148($sp)
    li $t1, 3
    sle $t0, $t0, $t1
    beqz $t0, Lend9
    lw $t0, 144($sp)
    lw $t1, 148($sp)
    mul $t0, $t0, $t1
    sw   $t0, 152($sp)   # product = ...
    lw $t0, 152($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 148($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 148($sp)   # col = ...
    j Lstart9
Lend9:
    lw $t0, 144($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 144($sp)   # row = ...
    j Lstart8
Lend8:
    # Declare int kk at offset 156
    # Declare int acc at offset 160
    li $t0, 1
    sw   $t0, 116($sp)   # j = ...
Lstart10:
    lw $t0, 116($sp)
    li $t1, 3
    sle $t0, $t0, $t1
    beqz $t0, Lend10
    li $t0, 0
    sw   $t0, 156($sp)   # kk = ...
    li $t0, 0
    sw   $t0, 160($sp)   # acc = ...
Lstart11:
    lw $t0, 156($sp)
    lw $t1, 116($sp)
    slt $t0, $t0, $t1
    beqz $t0, Lend11
    lw $t0, 160($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 160($sp)   # acc = ...
    lw $t0, 156($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 156($sp)   # kk = ...
    j Lstart11
Lend11:
    lw $t0, 160($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 116($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 116($sp)   # j = ...
    j Lstart10
Lend10:
    # Declare int val at offset 164
    li $t0, 10
    sw   $t0, 164($sp)   # val = ...
    lw $t0, 164($sp)
    li $t1, 5
    sgt $t0, $t0, $t1
    beqz $t0, Lend12
    li $t0, 100
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
Lend12:
    li $t0, 3
    sw   $t0, 164($sp)   # val = ...
    lw $t0, 164($sp)
    li $t1, 5
    sgt $t0, $t0, $t1
    beqz $t0, Lelse13
    li $t0, 200
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend13
Lelse13:
    li $t0, 201
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
Lend13:
    li $t0, 75
    sw   $t0, 164($sp)   # val = ...
    lw $t0, 164($sp)
    li $t1, 90
    sge $t0, $t0, $t1
    beqz $t0, Lelse14
    li $t0, 300
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend14
Lelse14:
    lw $t0, 164($sp)
    li $t1, 80
    sge $t0, $t0, $t1
    beqz $t0, Lelse15
    li $t0, 301
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend15
Lelse15:
    lw $t0, 164($sp)
    li $t1, 70
    sge $t0, $t0, $t1
    beqz $t0, Lelse16
    li $t0, 302
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend16
Lelse16:
    li $t0, 303
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
Lend16:
Lend15:
Lend14:
    # Declare int p at offset 168
    # Declare int q at offset 172
    li $t0, 5
    sw   $t0, 168($sp)   # p = ...
    li $t0, 10
    sw   $t0, 172($sp)   # q = ...
    lw $t0, 168($sp)
    lw $t1, 172($sp)
    slt $t0, $t0, $t1
    beqz $t0, Lelse17
    lw $t0, 168($sp)
    li $t1, 0
    sgt $t0, $t0, $t1
    beqz $t0, Lelse18
    li $t0, 400
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend18
Lelse18:
    li $t0, 401
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
Lend18:
    j Lend17
Lelse17:
    li $t0, 402
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
Lend17:
    # Declare int day at offset 176
    li $t0, 3
    sw   $t0, 176($sp)   # day = ...
    lw $t0, 176($sp)
    li $t1, 1
    beq $t0, $t1, Lcase19_0
    li $t2, 2
    beq $t0, $t2, Lcase19_1
    li $t3, 3
    beq $t0, $t3, Lcase19_2
    j Ldefault19
Lcase19_0:
    li $t0, 501
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend19
Lcase19_1:
    li $t0, 502
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend19
Lcase19_2:
    li $t0, 503
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend19
Ldefault19:
    li $t0, 500
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend19
Lend19:
    # Declare int season at offset 180
    li $t0, 2
    sw   $t0, 180($sp)   # season = ...
    lw $t0, 180($sp)
    li $t1, 1
    beq $t0, $t1, Lcase20_0
    li $t2, 2
    beq $t0, $t2, Lcase20_1
    li $t3, 3
    beq $t0, $t3, Lcase20_2
    li $t4, 4
    beq $t0, $t4, Lcase20_3
    j Ldefault20
Lcase20_0:
Lcase20_1:
Lcase20_2:
    li $t0, 510
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend20
Lcase20_3:
    li $t0, 511
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend20
Ldefault20:
    li $t0, 512
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend20
Lend20:
    # Declare int code at offset 184
    li $t0, 99
    sw   $t0, 184($sp)   # code = ...
    lw $t0, 184($sp)
    li $t1, 1
    beq $t0, $t1, Lcase21_0
    li $t2, 2
    beq $t0, $t2, Lcase21_1
    j Ldefault21
Lcase21_0:
    li $t0, 520
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend21
Lcase21_1:
    li $t0, 521
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend21
Ldefault21:
    li $t0, 522
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend21
Lend21:
    # Declare int outer at offset 188
    # Declare int inner at offset 192
    li $t0, 2
    sw   $t0, 188($sp)   # outer = ...
    li $t0, 1
    sw   $t0, 192($sp)   # inner = ...
    lw $t0, 188($sp)
    li $t1, 1
    beq $t0, $t1, Lcase22_0
    li $t2, 2
    beq $t0, $t2, Lcase22_1
    j Ldefault22
Lcase22_0:
    lw $t0, 192($sp)
    li $t1, 1
    beq $t0, $t1, Lcase23_0
    j Ldefault23
Lcase23_0:
    li $t0, 531
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend23
Ldefault23:
    li $t0, 530
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend23
Lend23:
    j Lend22
Lcase22_1:
    lw $t0, 192($sp)
    li $t1, 1
    beq $t0, $t1, Lcase24_0
    j Ldefault24
Lcase24_0:
    li $t0, 532
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend24
Ldefault24:
    li $t0, 530
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend24
Lend24:
    j Lend22
Ldefault22:
    li $t0, 530
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend22
Lend22:
    # Declare int fibA at offset 196
    # Declare int fibB at offset 200
    # Declare int fibNext at offset 204
    # Declare int n at offset 208
    li $t0, 0
    sw   $t0, 196($sp)   # fibA = ...
    li $t0, 1
    sw   $t0, 200($sp)   # fibB = ...
    lw $t0, 196($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 200($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 2
    sw   $t0, 208($sp)   # n = ...
Lstart25:
    lw $t0, 208($sp)
    li $t1, 7
    slt $t0, $t0, $t1
    beqz $t0, Lend25
    lw $t0, 196($sp)
    lw $t1, 200($sp)
    add $t0, $t0, $t1
    sw   $t0, 204($sp)   # fibNext = ...
    lw $t0, 204($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 200($sp)
    sw   $t0, 196($sp)   # fibA = ...
    lw $t0, 204($sp)
    sw   $t0, 200($sp)   # fibB = ...
    lw $t0, 208($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 208($sp)   # n = ...
    j Lstart25
Lend25:
    # Declare int fibR at offset 212
    li $t0, 6
    move $a0, $t0
    jal func_fibFunc
    sw   $v0, 212($sp)   # fibR = call result
    lw $t0, 212($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int perf at offset 216
    li $t0, 2
    li $t1, 3
    mul $t0, $t0, $t1
    li $t1, 4
    li $t2, 5
    mul $t1, $t1, $t2
    add $t0, $t0, $t1
    li $t1, 1
    sub $t0, $t0, $t1
    sw   $t0, 216($sp)   # perf = ...
    lw $t0, 216($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int limit at offset 220
    # Declare int lcount at offset 224
    li $t0, 100
    sw   $t0, 220($sp)   # limit = ...
    li $t0, 0
    sw   $t0, 224($sp)   # lcount = ...
    li $t0, 0
    sw   $t0, 108($sp)   # i = ...
Lstart26:
    lw $t0, 108($sp)
    lw $t1, 220($sp)
    slt $t0, $t0, $t1
    beqz $t0, Lend26
    lw $t0, 224($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 224($sp)   # lcount = ...
    lw $t0, 108($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 108($sp)   # i = ...
    j Lstart26
Lend26:
    lw $t0, 224($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int dc at offset 228
    li $t0, 1
    sw   $t0, 228($sp)   # dc = ...
    lw $t0, 228($sp)
    li $t1, 1
    seq $t0, $t0, $t1
    beqz $t0, Lelse27
    li $t0, 601
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend27
Lelse27:
    li $t0, 602
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
Lend27:

    # Exit program
    addi $sp, $sp, 400
    li   $v0, 10
    syscall
