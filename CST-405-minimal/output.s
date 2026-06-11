# Generated MIPS Assembly
# -------------------------------------

.data
__str0: .asciiz "Hello"

.text
.globl main

# -- Function: add --
func_add:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    sw   $a0, 0($sp)   # param a
    sw   $a1, 4($sp)   # param b
    # Declare int x at offset 8
    # Declare int result at offset 12
    li $t0, 0
    sw   $t0, 8($sp)   # x = ...
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw   $t0, 12($sp)   # result = ...
    li $t0, 0
    sw   $t0, 8($sp)   # x = ...
Lstart0:
    lw $t0, 8($sp)
    li $t1, 10
    slt $t0, $t0, $t1
    beqz $t0, Lend0
    lw $t0, 12($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    add $t0, $t0, $t1
    sw   $t0, 12($sp)   # result = ...
    lw $t0, 8($sp)
    li $t1, 1
    add $t0, $t0, $t1
    sw   $t0, 8($sp)   # x = ...
    j Lstart0
Lend0:
Lstart1:
    lw $t0, 8($sp)
    li $t1, 0
    sgt $t0, $t0, $t1
    beqz $t0, Lend1
    lw $t0, 8($sp)
    li $t1, 1
    sub $t0, $t0, $t1
    sw   $t0, 8($sp)   # x = ...
    lw $t0, 8($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lstart1
Lend1:
    lw   $v0, 12($sp)   # return result
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

main:
    # Allocate global stack frame
    addi $sp, $sp, -400
    move $s7, $sp   # global frame pointer

    # Declare int x at offset 0
    # Declare int y at offset 4
    # Declare int result at offset 8
    # Declare stats playerStats at offset 12
    li $t0, 10
    sw $t0, 12($sp)   # playerStats.health = 10 (default)
    # Declare int playhealth at offset 20
    li $t0, 5
    sw   $t0, 0($sp)   # x = ...
    li $t0, 10
    sw   $t0, 4($sp)   # y = ...
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    move $a0, $t0
    move $a1, $t1
    jal func_add
    sw   $v0, 8($sp)   # result = call result
    li $t0, 0
    sw   $t0, 8($sp)   # result = ...
    lw $t0, 12($sp)   # playerStats is health
    sw   $t0, 20($sp)   # playhealth = ...
    lw $t0, 20($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 8($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    # Declare int score at offset 24
    li $t0, 100
    sw   $t0, 24($sp)   # score = ...
    # Declare char grade at offset 28
    la   $t0, __str0
    # Print string
    move $a0, $t0
    li   $v0, 4
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    lw $t0, 24($sp)
    li $t1, 10
    div $t0, $t1
    mflo $t0
    li $t1, 10
    beq $t0, $t1, Lcase2_0
    li $t2, 9
    beq $t0, $t2, Lcase2_1
    li $t3, 8
    beq $t0, $t3, Lcase2_2
    li $t4, 7
    beq $t0, $t4, Lcase2_3
    li $t5, 6
    beq $t0, $t5, Lcase2_4
    j Ldefault2
Lcase2_0:
Lcase2_1:
    li $t0, 65
    sw   $t0, 28($sp)   # grade = ...
    j Lend2
Lcase2_2:
    li $t0, 66
    sw   $t0, 28($sp)   # grade = ...
    j Lend2
Lcase2_3:
    li $t0, 67
    sw   $t0, 28($sp)   # grade = ...
    j Lend2
Lcase2_4:
    li $t0, 68
    sw   $t0, 28($sp)   # grade = ...
    j Lend2
Ldefault2:
    li $t0, 70
    sw   $t0, 28($sp)   # grade = ...
    j Lend2
Lend2:
    lw $t0, 28($sp)
    # Print char
    move $a0, $t0
    li   $v0, 11
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall

    # Exit program
    addi $sp, $sp, 400
    li   $v0, 10
    syscall
