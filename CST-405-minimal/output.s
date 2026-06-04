# Generated MIPS Assembly
# -------------------------------------

.data

.text
.globl main

# -- Function: add --
func_add:
    addi $sp, $sp, -128
    sw   $ra, 124($sp)
    sw   $a0, 0($sp)   # param num1
    sw   $a1, 4($sp)   # param num2
    # Declare int result at offset 8
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    sw   $t0, 8($sp)   # result = ...
    lw   $v0, 8($sp)   # return result
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

main:
    # Allocate global stack frame
    addi $sp, $sp, -400

    # Declare int a at offset 0
    # Declare int b at offset 4
    # Declare int result at offset 8
    li $t0, 10
    sw   $t0, 0($sp)   # a = ...
    li $t0, 3
    sw   $t0, 4($sp)   # b = ...
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t0, $t0, $t1
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    sub $t1, $t1, $t2
    mul $t0, $t0, $t1
    li $t1, 2
    div $t0, $t1
    mflo $t0
    sw   $t0, 8($sp)   # result = ...
    lw $t0, 8($sp)
    # Print integer
    move $a0, $t0
    li   $v0, 1
    syscall
    # Print newline
    li   $v0, 11
    li   $a0, 10
    syscall
    li $t0, 4
    sw   $t0, 0($sp)   # a = ...
    li $t0, 5
    sw   $t0, 4($sp)   # b = ...
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    move $a0, $t0
    move $a1, $t1
    jal func_add
    sw   $v0, 4($sp)   # b = call result
    lw $t0, 4($sp)
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
