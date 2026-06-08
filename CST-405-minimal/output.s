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
    lw   $v0, 12($sp)   # return result
    lw   $ra, 124($sp)
    addi $sp, $sp, 128
    jr   $ra

main:
    # Allocate global stack frame
    addi $sp, $sp, -400

    # Declare int x at offset 0
    # Declare int y at offset 4
    # Declare int result at offset 8
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
