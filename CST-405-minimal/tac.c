#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

// Two global lists; the unoptimized TAC_List and the updated optimized list
TACList tacList;
TACList optimizedList;

/* ─────────────────────────────────────────────────────────────
 * REGISTER ALLOCATOR
 * Maps TAC temporaries (t0, t1, ...) to real MIPS registers
 * ($t0–$t7, 8 available). When all registers are full, the
 * least-recently-used (LRU) one is spilled to the stack so its
 * register can be reused (reallocation / spilling).
 * ───────────────────────────────────────────────────────────── */

#define NUM_REGS 8          /* MIPS $t0–$t7 */
#define MAX_SPILLS 64       /* Max spill slots on the stack    */

/* One entry in the register file */
typedef struct {
    char  name[32];   /* Which temporary occupies this register ("" = free) */
    int   lastUsed;   /* Logical clock tick of last access – used for LRU   */
    int   spilled;    /* 1 if a current copy also lives on the stack         */
} RegEntry;

/* One entry in the spill table */
typedef struct {
    char name[32];    /* Temporary name that was spilled   */
    int  stackSlot;   /* Stack slot index (slot * 4 = byte offset from $sp) */
} SpillEntry;

/* **TEST TO SEE IF IT IS NOT NEEDED**
typedef struct {
    char* var;
    char* value;
} VarValue;
*/
static RegEntry  regFile[NUM_REGS];
static SpillEntry spillTable[MAX_SPILLS];
static int       spillCount  = 0;
static int       clock_tick  = 0;   /* Incremented on every allocation */

/* NEW FUNCTION: Initialise the register EIGHT file ($t0 - $t7)– call once before allocating */
void initRegAlloc() {
    for (int i = 0; i < NUM_REGS; i++) {
        regFile[i].name[0] = '\0';
        regFile[i].lastUsed = 0;
        regFile[i].spilled  = 0;
    }
    spillCount = 0;
    clock_tick = 0;
    printf("\n┌──────────────────────────────────────────────────────────┐\n");
    printf("│ REGISTER ALLOCATOR: Initialized ($t0–$t7, LRU spilling) │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
}

/* Return the register index already holding 'name', or -1 */
static int findReg(const char* name) {
    for (int i = 0; i < NUM_REGS; i++)
        if (regFile[i].name[0] && strcmp(regFile[i].name, name) == 0)
            return i;
    return -1;
}

/* Return the index of the free register, or -1 if all are occupied */
static int findFreeReg() {
    for (int i = 0; i < NUM_REGS; i++)
        if (regFile[i].name[0] == '\0')
            return i;
    return -1;
}

/* Return the LRU register index (the one with the smallest lastUsed) */
static int lruReg() {
    int lru = 0;
    for (int i = 1; i < NUM_REGS; i++)
        if (regFile[i].lastUsed < regFile[lru].lastUsed)
            lru = i;
    return lru;
}

/* Spill register 'reg' to the stack and record it in the spill table */
static void spillReg(int reg) {
    if (spillCount >= MAX_SPILLS) {
        fprintf(stderr, "❌ Register Allocator Error: spill table full\n");
        return;
    }
    strncpy(spillTable[spillCount].name, regFile[reg].name, 31);
    spillTable[spillCount].stackSlot = spillCount;
    printf("  ⬇ SPILL:  $t%d (%s) → stack slot %d  (sw $t%d, %d($sp))\n",
           reg, regFile[reg].name, spillCount, reg, spillCount * 4);
    spillCount++;
    regFile[reg].spilled = 1;
}

/* Reload a previously-spilled temporary into register 'reg' */
static void reloadReg(int reg, const char* name) {
    for (int i = 0; i < spillCount; i++) {
        if (strcmp(spillTable[i].name, name) == 0) {
            printf("  ⬆ RELOAD: stack slot %d → $t%d (%s)  (lw $t%d, %d($sp))\n",
                   spillTable[i].stackSlot, reg, name, reg, spillTable[i].stackSlot * 4);
            return;
        }
    }
}

/*
 * allocReg(name) – the main entry point.
 *
 * Given a temporary name (e.g. "t0", "x", "5"):
 *   • If it is already in a register, return that register (hit).
 *   • If a free register exists, put it there (fresh allocation).
 *   • Otherwise, spill the LRU register and reuse it (reallocation).
 *
 * Returns the register index (0–7) and prints a trace line.
 */
int allocReg(const char* name) {
    clock_tick++;

    /* 1. Already in a register? – just update LRU and return */
    int reg = findReg(name);
    if (reg != -1) {
        regFile[reg].lastUsed = clock_tick;
        printf("  ✓ HIT:    '%s' already in $t%d\n", name, reg);
        return reg;
    }

    /* 2. Free register available? */
    reg = findFreeReg();
    if (reg != -1) {
        /* Check if it needs to be reloaded from a previous spill */
        int wasSpilled = 0;
        for (int i = 0; i < spillCount; i++) {
            if (strcmp(spillTable[i].name, name) == 0) {
                wasSpilled = 1;
                reloadReg(reg, name);
                break;
            }
        }
        if (!wasSpilled)
            printf("  + ALLOC:  '%s' → $t%d  (free register)\n", name, reg);

        strncpy(regFile[reg].name, name, 31);
        regFile[reg].lastUsed = clock_tick;
        regFile[reg].spilled  = 0;
        return reg;
    }

    /* 3. No free register – spill LRU and reuse it (reallocation) */
    reg = lruReg();
    printf("  ! REALLOC: all registers full – evicting $t%d (%s)\n",
           reg, regFile[reg].name);
    spillReg(reg);

    /* Check if new value was previously spilled */
    int wasSpilled = 0;
    for (int i = 0; i < spillCount; i++) {
        if (strcmp(spillTable[i].name, name) == 0) {
            wasSpilled = 1;
            reloadReg(reg, name);
            break;
        }
    }
    if (!wasSpilled)
        printf("  + ALLOC:  '%s' → $t%d  (after eviction)\n", name, reg);

    strncpy(regFile[reg].name, name, 31);
    regFile[reg].lastUsed = clock_tick;
    regFile[reg].spilled  = 0;
    return reg;
}

/* Free a register when its value is no longer needed */
void freeReg(const char* name) {
    int reg = findReg(name);
    if (reg != -1) {
        printf("  - FREE:   $t%d (%s) released\n", reg, name);
        regFile[reg].name[0] = '\0';
        regFile[reg].spilled  = 0;
    }
}

/* Print the current state of all registers */
void printRegState() {
    printf("\n  Register file state:\n");
    printf("  ┌──────┬──────────────┬──────────┐\n");
    printf("  │ Reg  │ Holds        │ Spilled? │\n");
    printf("  ├──────┼──────────────┼──────────┤\n");
    for (int i = 0; i < NUM_REGS; i++) {
        printf("  │ $t%-2d │ %-12s │ %-8s │\n",
               i,
               regFile[i].name[0] ? regFile[i].name : "(free)",
               regFile[i].spilled ? "yes" : "no");
    }
    printf("  └──────┴──────────────┴──────────┘\n");
}

/*
 * allocateRegistersForTAC()
 *
 * Walk the optimised TAC list and call allocReg/freeReg for every
 * operand and result, simulating what a real back-end would do.
 * Temporaries are freed as soon as their result has been assigned
 * to a named variable (they are no longer live after that point).
 */
void allocateRegistersForTAC() {
    printf("\n┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE: REGISTER ALLOCATION                               │\n");
    printf("│  Mapping temporaries to $t0–$t7 with LRU spill policy   │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");

    initRegAlloc();

    TACInstr* curr = optimizedList.head;
    int lineNum = 1;
    while (curr) {
        printf("\n  [Line %d] ", lineNum++);
        switch (curr->op) {
            case TAC_DECL:
                printf("DECL %s  →  allocate storage\n", curr->result);
                allocReg(curr->result);
                break;

            case TAC_ASSIGN:
                printf("%s = %s\n", curr->result, curr->arg1);
                /* Allocate source (may already be in a register) */
                if (curr->arg1 && !isdigit((unsigned char)curr->arg1[0]))
                    allocReg(curr->arg1);
                /* Allocate destination */
                allocReg(curr->result);
                /* Free any temporary used as source */
                if (curr->arg1 && curr->arg1[0] == 't')
                    freeReg(curr->arg1);
                break;

            case TAC_ADD:
                printf("%s = %s + %s\n", curr->result, curr->arg1, curr->arg2);
                if (curr->arg1 && !isdigit((unsigned char)curr->arg1[0]))
                    allocReg(curr->arg1);
                if (curr->arg2 && !isdigit((unsigned char)curr->arg2[0]))
                    allocReg(curr->arg2);
                allocReg(curr->result);
                /* Free operand temporaries after use */
                if (curr->arg1 && curr->arg1[0] == 't') freeReg(curr->arg1);
                if (curr->arg2 && curr->arg2[0] == 't') freeReg(curr->arg2);
                break;

            case TAC_PRINT:
                printf("PRINT %s\n", curr->arg1);
                if (curr->arg1 && !isdigit((unsigned char)curr->arg1[0]))
                    allocReg(curr->arg1);
                break;

            default:
                break;
        }
        curr = curr->next;
    }

    printf("\n  ── Final register state after allocation ──");
    printRegState();

    if (spillCount > 0) {
        printf("\n  ── Spill summary: %d variable(s) spilled to stack ──\n", spillCount);
        for (int i = 0; i < spillCount; i++)
            printf("     slot %d: '%s'  (at %d($sp))\n",
                   i, spillTable[i].name, i * 4);
    } else {
        printf("\n  ✓ No spills needed – all temporaries fit in registers\n");
    }
}

void initTAC() {
    tacList.head = NULL;
    tacList.tail = NULL;
    tacList.tempCount = 0;
    optimizedList.head = NULL;
    optimizedList.tail = NULL;
}

char* newTemp() {
    char* temp = malloc(10);
    sprintf(temp, "t%d", tacList.tempCount++);
    return temp;
}

TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = malloc(sizeof(TACInstr));
    instr->op = op;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->next = NULL;
    return instr;
}

void appendTAC(TACInstr* instr) {
    if (!tacList.head) {
        tacList.head = tacList.tail = instr;
    } else {
        tacList.tail->next = instr;
        tacList.tail = instr;
    }
}

void appendOptimizedTAC(TACInstr* instr) {
    if (!optimizedList.head) {
        optimizedList.head = optimizedList.tail = instr;
    } else {
        optimizedList.tail->next = instr;
        optimizedList.tail = instr;
    }
}

char* generateTACExpr(ASTNode* node) {
    if (!node) return NULL;
    
    switch(node->type) {
        case NODE_NUM: {
            char* temp = malloc(20);
            sprintf(temp, "%d", node->data.num);
            return temp;
        }
        
        case NODE_VAR:
            return strdup(node->data.name);
        
        case NODE_BINOP: {
            char* left = generateTACExpr(node->data.binop.left);
            char* right = generateTACExpr(node->data.binop.right);
            char* temp = newTemp();
            
            if (node->data.binop.op == '+') {
                appendTAC(createTAC(TAC_ADD, left, right, temp));
            }
            
            return temp;
        }
        
        default:
            return NULL;
    }
}

void generateTAC(ASTNode* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_DECL:
            appendTAC(createTAC(TAC_DECL, node->data.decl.varType, NULL, node->data.decl.name));
            break;
            
        case NODE_ASSIGN: {
            char* expr = generateTACExpr(node->data.assign.value);
            appendTAC(createTAC(TAC_ASSIGN, expr, NULL, node->data.assign.var));
            break;
        }
        
        case NODE_PRINT: {
            char* expr = generateTACExpr(node->data.expr);
            appendTAC(createTAC(TAC_PRINT, expr, NULL, NULL));
            break;
        }
        
        case NODE_STMT_LIST:
            generateTAC(node->data.stmtlist.stmt);
            generateTAC(node->data.stmtlist.next);
            break;
            
        default:
            break;
    }
}

void printTAC() {
    printf("Unoptimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = tacList.head;
    int lineNum = 1;
    while (curr) {
        printf("%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                printf("DECL %s %s", curr->arg1 ? curr->arg1 : "", curr->result);
                printf("       // Declare variable '%s' (type: %s)\n", curr->result, curr->arg1 ? curr->arg1 : "unknown");
                break;
            case TAC_ADD:
                printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Add: store result in %s\n", curr->result);
                break;
            case TAC_ASSIGN:
                printf("%s = %s", curr->result, curr->arg1);
                printf("           // Assign value to %s\n", curr->result);
                break;
            case TAC_PRINT:
                printf("PRINT %s", curr->arg1);
                printf("          // Output value of %s\n", curr->arg1);
                break;
            default:
                break;
        }
        curr = curr->next;
    }
}

// Simple optimization: constant folding and copy propagation
void optimizeTAC() {
    // Seed the optimized list from the original TAC
    // (first pass reads from tacList, subsequent passes re-process optimizedList)
    TACInstr* curr = tacList.head;
    while (curr) {
        appendOptimizedTAC(createTAC(curr->op, curr->arg1,
                                     curr->arg2, curr->result));
        curr = curr->next;
    }

    //**TEST TO SEE IF IT IS NOT NEEDED**
    //typedef struct { char* var; char* value; } VarValue;
    VarValue values[100];
    int valueCount = 0;

    int pass = 1;
    int changed;

    printf("\n── Multi-pass optimization ──\n");
    do {
        printf("  Pass %d...\n", pass++);
        changed = optimizeTACPass(values, &valueCount);
    } while (changed);

    printf("  Converged after %d pass(es).\n", pass - 1);
    
    eliminateDeadCode();   
}


// ADDED: A multi pass
int optimizeTACPass(VarValue* values, int* valueCount) {
    int changed = 0;
    TACInstr* curr = optimizedList.head;

    // Clear the optimized list for this pass
    optimizedList.head = NULL;
    optimizedList.tail = NULL;
    *valueCount = 0;

    while (curr) {
        TACInstr* newInstr = NULL;

        switch (curr->op) {
            case TAC_ADD: {
                char* left  = curr->arg1;
                char* right = curr->arg2;

                // Copy propagation lookups (same as before)
                for (int i = *valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, left)  == 0) { left  = values[i].value; break; }
                for (int i = *valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, right) == 0) { right = values[i].value; break; }

                if (isdigit(left[0]) && isdigit(right[0])) {
                    int result = atoi(left) + atoi(right);
                    char* resultStr = malloc(20);
                    sprintf(resultStr, "%d", result);

                    values[*valueCount].var   = strdup(curr->result);
                    values[*valueCount].value = resultStr;
                    (*valueCount)++;

                    newInstr = createTAC(TAC_ASSIGN, resultStr, NULL, curr->result);
                    changed = 1;   // ← Constant fold fired
                } else {
                    newInstr = createTAC(TAC_ADD, left, right, curr->result);
                    // Flag change if propagation substituted an operand
                    if (strcmp(left, curr->arg1) != 0 || strcmp(right, curr->arg2) != 0)
                        changed = 1;
                }
                break;
            }

            case TAC_ASSIGN: {
                char* value = curr->arg1;
                for (int i = *valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, value) == 0) { value = values[i].value; break; }

                if (strcmp(value, curr->arg1) != 0)
                    changed = 1;   // ← Copy propagation fired

                values[*valueCount].var   = strdup(curr->result);
                values[*valueCount].value = strdup(value);
                (*valueCount)++;

                newInstr = createTAC(TAC_ASSIGN, value, NULL, curr->result);
                break;
            }

            case TAC_PRINT: {
                char* value = curr->arg1;
                for (int i = *valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, value) == 0) { value = values[i].value; break; }

                if (strcmp(value, curr->arg1) != 0)
                    changed = 1;

                newInstr = createTAC(TAC_PRINT, value, NULL, NULL);
                break;
            }

            case TAC_DECL:
                newInstr = createTAC(TAC_DECL, NULL, NULL, curr->result);
                break;
        }

        if (newInstr)
            appendOptimizedTAC(newInstr);

        curr = curr->next;
    }

    return changed;
}

//added: dead code elimination (DCE) pass that runs after constant folding and copy propagation
void eliminateDeadCode() {
    // --- Pass 1: collect every variable that is READ ---
    char used[100][32];
    int usedCount = 0;

    TACInstr* curr = optimizedList.head;
    while (curr) {
        // arg1 and arg2 are "read" operands
        if (curr->arg1 && !isdigit((unsigned char)curr->arg1[0]))
            strncpy(used[usedCount++], curr->arg1, 31);
        if (curr->arg2 && !isdigit((unsigned char)curr->arg2[0]))
            strncpy(used[usedCount++], curr->arg2, 31);
        // PRINT reads its argument too
        curr = curr->next;
    }

    // --- Pass 2: drop instructions whose result is never read ---
    TACInstr* prev = NULL;
    curr = optimizedList.head;
    while (curr) {
        int isUsed = 0;

        // DECL / PRINT are always "live" (side-effectful)
        if (curr->op == TAC_DECL || curr->op == TAC_PRINT) {
            isUsed = 1;
        } else if (curr->result) {
            for (int i = 0; i < usedCount; i++) {
                if (strcmp(used[i], curr->result) == 0) {
                    isUsed = 1;
                    break;
                }
            }
        }

        if (!isUsed) {
            printf("  ✂ DCE: removing dead instruction '%s = ...'\n",
                   curr->result);
            TACInstr* dead = curr;
            if (prev) prev->next = curr->next;
            else       optimizedList.head = curr->next;
            if (optimizedList.tail == dead)
                optimizedList.tail = prev;
            curr = curr->next;
            // free dead->arg1, arg2, result, dead itself
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void printOptimizedTAC() {
    printf("Optimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = optimizedList.head;
    int lineNum = 1;
    while (curr) {
        printf("%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                printf("DECL %s\n", curr->result);
                break;
            case TAC_ADD:
                printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Runtime addition needed\n");
                break;
            case TAC_ASSIGN:
                printf("%s = %s", curr->result, curr->arg1);
                // Check if it's a constant
                if (curr->arg1[0] >= '0' && curr->arg1[0] <= '9') {
                    printf("           // Constant value: %s\n", curr->arg1);
                } else {
                    printf("           // Copy value\n");
                }
                break;
            case TAC_PRINT:
                printf("PRINT %s", curr->arg1);
                // Check if it's a constant
                if (curr->arg1[0] >= '0' && curr->arg1[0] <= '9') {
                    printf("          // Print constant: %s\n", curr->arg1);
                } else {
                    printf("          // Print variable\n");
                }
                break;
            default:
                break;
        }
        curr = curr->next;
    }
}

void saveTACToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s' for writing\n", filename);
        return;
    }

    fprintf(file, "# Three-Address Code (TAC) - Unoptimized\n");
    fprintf(file, "# Generated by Minimal C Compiler\n");
    fprintf(file, "# ─────────────────────────────────────\n\n");

    TACInstr* curr = tacList.head;
    int lineNum = 1;
    while (curr) {
        fprintf(file, "%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                fprintf(file, "DECL %s\n", curr->result);
                break;
            case TAC_ADD:
                fprintf(file, "%s = %s + %s\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_ASSIGN:
                fprintf(file, "%s = %s\n", curr->result, curr->arg1);
                break;
            case TAC_PRINT:
                fprintf(file, "PRINT %s\n", curr->arg1);
                break;
            default:
                break;
        }
        curr = curr->next;
    }

    fclose(file);
}

void saveOptimizedTACToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s' for writing\n", filename);
        return;
    }

    fprintf(file, "# Three-Address Code (TAC) - Optimized\n");
    fprintf(file, "# Generated by Minimal C Compiler\n");
    fprintf(file, "# Optimizations applied: Constant folding, Copy propagation\n");
    fprintf(file, "# ─────────────────────────────────────\n\n");

    TACInstr* curr = optimizedList.head;
    int lineNum = 1;
    while (curr) {
        fprintf(file, "%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                fprintf(file, "DECL %s\n", curr->result);
                break;
            case TAC_ADD:
                fprintf(file, "%s = %s + %s\n", curr->result, curr->arg1, curr->arg2);
                break;
            case TAC_ASSIGN:
                fprintf(file, "%s = %s\n", curr->result, curr->arg1);
                break;
            case TAC_PRINT:
                fprintf(file, "PRINT %s\n", curr->arg1);
                break;
            default:
                break;
        }
        curr = curr->next;
    }

    fclose(file);
}