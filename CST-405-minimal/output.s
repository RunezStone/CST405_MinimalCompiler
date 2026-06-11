# Generated MIPS Assembly
# -------------------------------------

.data

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

# -- Function: attackPlayer --
func_attackPlayer:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    sw   $a0, 0($sp)   # param damage
    lw $t0, 20($s7)   # global playhealth
    lw $t1, 0($sp)
    sub $t0, $t0, $t1
    sw   $t0, 20($s7)   # playhealth = ...
    lw $t0, 20($s7)   # global playhealth
    li $t1, 0
    sle $t0, $t0, $t1
    beqz $t0, Lelse2
    li   $v0, 1   # early return value
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra
    j Lend2
Lelse2:
    li   $v0, 0   # early return value
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra
Lend2:
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
    lw $t0, 0($sp)
    move $a0, $t0
    jal func_attackPlayer
    sw   $v0, 8($sp)   # result = call result
    lw $t0, 8($sp)
    li $t1, 0
    seq $t0, $t0, $t1
    beqz $t0, Lelse3
    li $t0, 202
    sw   $t0, 4($sp)   # y = ...
    lw $t0, 4($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    j Lend3
Lelse3:
    li $t0, 101
    sw   $t0, 4($sp)   # y = ...
    lw $t0, 4($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
Lend3:
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

    # Exit program
    addi $sp, $sp, 400
    li   $v0, 10
    syscall
