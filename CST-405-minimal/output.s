# Generated MIPS Assembly
# -------------------------------------

.data
arr: .space 20

.text
.globl main

main:
    # Allocate global stack frame
    addi $sp, $sp, -400

    # Array arr[5] at offset 0 (20 bytes)
    li $t0, 0
    li $t1, 10
    sll  $t2, $t0, 2
    sw   $t1, arr($t2)   # arr[i] = ...
    li $t0, 0
    sll  $t1, $t0, 2
    lw   $t2, arr($t1)   # arr[i]
    # Print integer
    move $a0, $t2
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
