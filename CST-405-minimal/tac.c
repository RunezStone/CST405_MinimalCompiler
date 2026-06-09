#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

/* Two global lists: unoptimized and optimized */
TACList tacList;
TACList optimizedList;

/* ─────────────────────────────────────────────────────────────────────────
 * REGISTER ALLOCATOR
 * Maps TAC temporaries (t0, t1, ...) to real MIPS registers ($t0–$t7).
 * When all registers are full, the least-recently-used (LRU) one is
 * spilled to the stack so its register can be reused.
 * ───────────────────────────────────────────────────────────────────────── */

#define NUM_REGS   8    /* MIPS $t0–$t7              */
#define MAX_SPILLS 64   /* Max spill slots on stack  */

typedef struct {
    char name[32];  /* Which temporary is here ("" = free) */
    int  lastUsed;  /* Logical clock tick — used for LRU   */
    int  spilled;   /* 1 if a copy also lives on the stack */
} RegEntry;

typedef struct {
    char name[32];  /* Temporary that was spilled          */
    int  stackSlot; /* Slot index (slot * 4 = byte offset) */
} SpillEntry;

static RegEntry   regFile[NUM_REGS];
static SpillEntry spillTable[MAX_SPILLS];
static int        spillCount = 0;
static int        clock_tick = 0;

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

static int findReg(const char* name) {
    for (int i = 0; i < NUM_REGS; i++)
        if (regFile[i].name[0] && strcmp(regFile[i].name, name) == 0)
            return i;
    return -1;
}

static int findFreeReg() {
    for (int i = 0; i < NUM_REGS; i++)
        if (regFile[i].name[0] == '\0')
            return i;
    return -1;
}

static int lruReg() {
    int lru = 0;
    for (int i = 1; i < NUM_REGS; i++)
        if (regFile[i].lastUsed < regFile[lru].lastUsed)
            lru = i;
    return lru;
}

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

static void reloadReg(int reg, const char* name) {
    for (int i = 0; i < spillCount; i++) {
        if (strcmp(spillTable[i].name, name) == 0) {
            printf("  ⬆ RELOAD: stack slot %d → $t%d (%s)  (lw $t%d, %d($sp))\n",
                   spillTable[i].stackSlot, reg, name, reg,
                   spillTable[i].stackSlot * 4);
            return;
        }
    }
}

int allocReg(const char* name) {
    clock_tick++;

    int reg = findReg(name);
    if (reg != -1) {
        regFile[reg].lastUsed = clock_tick;
        printf("  ✓ HIT:    '%s' already in $t%d\n", name, reg);
        return reg;
    }

    reg = findFreeReg();
    if (reg != -1) {
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

    reg = lruReg();
    printf("  ! REALLOC: all registers full – evicting $t%d (%s)\n",
           reg, regFile[reg].name);
    spillReg(reg);

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

void freeReg(const char* name) {
    int reg = findReg(name);
    if (reg != -1) {
        printf("  - FREE:   $t%d (%s) released\n", reg, name);
        regFile[reg].name[0] = '\0';
        regFile[reg].spilled  = 0;
    }
}

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
                if (curr->arg1 && !isdigit((unsigned char)curr->arg1[0]))
                    allocReg(curr->arg1);
                allocReg(curr->result);
                if (curr->arg1 && curr->arg1[0] == 't')
                    freeReg(curr->arg1);
                break;

            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV: {
                const char* opstr = (curr->op==TAC_ADD)?"+":
                                    (curr->op==TAC_SUB)?"-":
                                    (curr->op==TAC_MUL)?"*":"/";
                printf("%s = %s %s %s\n", curr->result, curr->arg1, opstr, curr->arg2);
                if (curr->arg1 && !isdigit((unsigned char)curr->arg1[0]))
                    allocReg(curr->arg1);
                if (curr->arg2 && !isdigit((unsigned char)curr->arg2[0]))
                    allocReg(curr->arg2);
                allocReg(curr->result);
                if (curr->arg1 && curr->arg1[0] == 't') freeReg(curr->arg1);
                if (curr->arg2 && curr->arg2[0] == 't') freeReg(curr->arg2);
                break;
            }
            case TAC_NEG:
                printf("%s = -%s\n", curr->result, curr->arg1);
                if (curr->arg1 && !isdigit((unsigned char)curr->arg1[0]))
                    allocReg(curr->arg1);
                allocReg(curr->result);
                if (curr->arg1 && curr->arg1[0] == 't') freeReg(curr->arg1);
                break;

            case TAC_PRINT:
                printf("PRINT %s\n", curr->arg1);
                if (curr->arg1 && !isdigit((unsigned char)curr->arg1[0]))
                    allocReg(curr->arg1);
                break;

            /* ── NEW: function opcodes in register allocator ── */
            case TAC_FUNC_BEGIN:
                printf("FUNC_BEGIN %s  →  reset frame\n", curr->result);
                /* Each function gets a fresh register context */
                initRegAlloc();
                break;

            case TAC_FUNC_END:
                printf("FUNC_END %s\n", curr->result);
                break;

            case TAC_PARAM:
                printf("PARAM %s  →  allocate for parameter\n", curr->result);
                allocReg(curr->result);
                break;

            case TAC_ARG:
                printf("ARG %s  →  load argument\n", curr->result);
                if (curr->result && !isdigit((unsigned char)curr->result[0]))
                    allocReg(curr->result);
                break;

            case TAC_CALL:
                printf("%s = CALL %s, %s\n", curr->result, curr->arg1, curr->arg2);
                /* Result lands in $v0 in MIPS; map to a temp register here */
                allocReg(curr->result);
                break;

            case TAC_RETURN:
                printf("RETURN %s\n", curr->result);
                if (curr->result && !isdigit((unsigned char)curr->result[0]))
                    allocReg(curr->result);
                break;

            default:
                break;
        }
        curr = curr->next;
    }

    printf("\n  ── Final register state after allocation ──");
    printRegState();

    if (spillCount > 0) {
        printf("\n  ── Spill summary: %d variable(s) spilled to stack ──\n",
               spillCount);
        for (int i = 0; i < spillCount; i++)
            printf("     slot %d: '%s'  (at %d($sp))\n",
                   i, spillTable[i].name, i * 4);
    } else {
        printf("\n  ✓ No spills needed – all temporaries fit in registers\n");
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * CORE TAC INFRASTRUCTURE
 * ───────────────────────────────────────────────────────────────────────── */

/* Counter for generated labels (L0, L1, ...) — used by while-loop TAC */
static int labelCount = 0;

void initTAC() {
    tacList.head      = NULL;
    tacList.tail      = NULL;
    tacList.tempCount = 0;
    optimizedList.head = NULL;
    optimizedList.tail = NULL;
    labelCount         = 0;
}

char* newTemp() {
    char* temp = malloc(10);
    sprintf(temp, "t%d", tacList.tempCount++);
    return temp;
}

/* Generate a fresh, unique label name (L0, L1, ...) for control flow */
char* newLabel() {
    char* label = malloc(12);
    sprintf(label, "L%d", labelCount++);
    return label;
}

TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = malloc(sizeof(TACInstr));
    instr->op     = op;
    instr->arg1   = arg1   ? strdup(arg1)   : NULL;
    instr->arg2   = arg2   ? strdup(arg2)   : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->next   = NULL;
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

/* ─────────────────────────────────────────────────────────────────────────
 * EXPRESSION GENERATION
 * ───────────────────────────────────────────────────────────────────────── */

char* generateTACExpr(ASTNode* node) {
    if (!node) return NULL;

    switch (node->type) {
        case NODE_NUM: {
            char* temp = malloc(20);
            sprintf(temp, "%d", node->data.num);
            return temp;
        }

        case NODE_FLOAT: {
            char* temp = malloc(32);
            sprintf(temp, "%g", node->data.fval);
            /* Ensure it contains a decimal point so it's distinguishable
             * from an integer constant in later phases */
            if (!strchr(temp, '.') && !strchr(temp, 'e'))
                strcat(temp, ".0");
            return temp;
        }

        case NODE_VAR:
            return strdup(node->data.name);

        case NODE_BINOP: {
            char* left  = generateTACExpr(node->data.binop.left);
            char* temp  = newTemp();
            char  op    = node->data.binop.op;
            if (op == 'u') {
                /* Unary minus: right is NULL, negate left */
                appendTAC(createTAC(TAC_NEG, left, NULL, temp));
            } else {
                char* right = generateTACExpr(node->data.binop.right);
                TACOp tacOp;
                switch (op) {
                    case '+': tacOp = TAC_ADD; break;
                    case '-': tacOp = TAC_SUB; break;
                    case '*': tacOp = TAC_MUL; break;
                    case '/': tacOp = TAC_DIV; break;
                    /* Relational operators (used in while/if conditions):
                     * '<' '>' '<' literal, plus 'l'(<=) 'g'(>=) 'e'(==) 'n'(!=) */
                    case '<': tacOp = TAC_LT; break;
                    case '>': tacOp = TAC_GT; break;
                    case 'l': tacOp = TAC_LE; break;
                    case 'g': tacOp = TAC_GE; break;
                    case 'e': tacOp = TAC_EQ; break;
                    case 'n': tacOp = TAC_NE; break;
                    default:  tacOp = TAC_ADD; break;
                }
                appendTAC(createTAC(tacOp, left, right, temp));
            }
            return temp;
        }

        /* ── NEW: function call as an expression (RHS of assignment) ── */
        case NODE_FUNC_CALL:
            return generateTACFuncCall(node);

        case NODE_ARRAY_INDEX: {
            char* index = generateTACExpr(node->data.array_index.index);
            char* temp  = newTemp();
            appendTAC(createTAC(TAC_ARRAY_LOAD,
                                node->data.array_index.name,
                                index, temp));
            return temp;
        }

        case NODE_STRUCT_ACCESS: {
            /* "base is field"  →  temp = base.field   (TAC_MEMBER_LOAD)
             * The base is always a simple struct-variable reference
             * (semantic analysis guarantees this); codegen resolves
             * 'field' to a byte offset via the struct-type registry. */
            ASTNode* base = node->data.struct_access.base;
            char* baseName = (base && base->type == NODE_VAR)
                                 ? strdup(base->data.name)
                                 : generateTACExpr(base);
            char* temp = newTemp();
            appendTAC(createTAC(TAC_MEMBER_LOAD,
                                baseName,
                                strdup(node->data.struct_access.field),
                                temp));
            return temp;
        }

        default:
            return NULL;
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * NEW: FUNCTION CALL GENERATION
 * Emits ARG instructions for each argument, then a CALL instruction.
 * Returns the temporary that holds the return value.
 * ───────────────────────────────────────────────────────────────────────── */
char* generateTACFuncCall(ASTNode* node) {
    if (!node || node->type != NODE_FUNC_CALL) return NULL;

    /* Emit ARG for each argument (left to right) */
    int argCount = 0;
    ASTNode* arg = node->data.func_call.args;
    while (arg) {
        if (arg->type == NODE_ARG_LIST) {
            char* argVal = generateTACExpr(arg->data.arg_list.expr);
            appendTAC(createTAC(TAC_ARG, NULL, NULL, argVal));
            argCount++;
            arg = arg->data.arg_list.next;
        } else {
            /* Single expression not wrapped in ARG_LIST */
            char* argVal = generateTACExpr(arg);
            appendTAC(createTAC(TAC_ARG, NULL, NULL, argVal));
            argCount++;
            break;
        }
    }

    /* t0 = CALL funcName, argCount */
    char* resultTemp = newTemp();
    char  countStr[16];
    snprintf(countStr, sizeof(countStr), "%d", argCount);
    appendTAC(createTAC(TAC_CALL, node->data.func_call.name, countStr, resultTemp));

    return resultTemp;
}

/* ─────────────────────────────────────────────────────────────────────────
 * NEW: FUNCTION DECLARATION GENERATION
 * Emits FUNC_BEGIN, PARAM instructions, body TAC, optional RETURN,
 * and FUNC_END.
 * ───────────────────────────────────────────────────────────────────────── */
void generateTACFuncDecl(ASTNode* node) {
    if (!node || node->type != NODE_FUNC_DEF) return;

    /* FUNC_BEGIN funcName */
    appendTAC(createTAC(TAC_FUNC_BEGIN, NULL, NULL,
                        node->data.func_def.name));

    /* PARAM for each parameter — walk the param list */
    ASTNode* p = node->data.func_def.params;
    while (p) {
        if (p->type == NODE_PARAM) {
            appendTAC(createTAC(TAC_PARAM, NULL, NULL,
                                p->data.param.name));
            break;
        } else if (p->type == NODE_PARAM_LIST) {
            ASTNode* param = p->data.param_list.param;
            if (param) {
                if (param->type == NODE_PARAM)
                    appendTAC(createTAC(TAC_PARAM, NULL, NULL,
                                        param->data.param.name));
                else if (param->type == NODE_ARRAY_DECL)
                    appendTAC(createTAC(TAC_PARAM, NULL, NULL,
                                        param->data.array_decl.name));
            }
            p = p->data.param_list.next;
        } else {
            break;
        }
    }

    /* Generate TAC for the body */
    generateTAC(node->data.func_def.body);

    /* RETURN — read from end_clause node */
    ASTNode* ec = node->data.func_def.end_clause;
    if (ec && ec->data.name != NULL) {
        /* "end result;" — return the named variable */
        appendTAC(createTAC(TAC_RETURN, NULL, NULL, ec->data.name));
    }
    /* "end null;" — void, no RETURN instruction needed */

    /* FUNC_END funcName */
    appendTAC(createTAC(TAC_FUNC_END, NULL, NULL,
                        node->data.func_def.name));
}

/* ─────────────────────────────────────────────────────────────────────────
 * NEW: WALK A STMT_LIST OF FUNCTION DEFINITIONS
 * ───────────────────────────────────────────────────────────────────────── */
void generateTACFuncList(ASTNode* node) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        generateTACFuncList(node->data.stmtlist.stmt);
        generateTACFuncList(node->data.stmtlist.next);
    } else if (node->type == NODE_FUNC_DEF) {
        generateTACFuncDecl(node);
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * NEW: PROGRAM_START GENERATION
 * Wraps the entry body in FUNC_BEGIN/FUNC_END like any other function.
 * ───────────────────────────────────────────────────────────────────────── */
void generateTACProgramStart(ASTNode* node) {
    if (!node || node->type != NODE_PROGRAM_START) return;

    appendTAC(createTAC(TAC_FUNC_BEGIN, NULL, NULL, "Program_Start"));
    generateTAC(node->data.block.stmt_list);
    appendTAC(createTAC(TAC_FUNC_END,   NULL, NULL, "Program_Start"));
}

/* ─────────────────────────────────────────────────────────────────────────
 * TOP-LEVEL TAC GENERATION
 * Handles NODE_PROGRAM root as well as all existing node types.
 * ───────────────────────────────────────────────────────────────────────── */
void generateTAC(ASTNode* node) {
    if (!node) return;

    switch (node->type) {

        /* ── NEW: root program node ── */
        case NODE_PROGRAM:
            /* 1. Global declarations */
            generateTAC(node->data.program.globals);
            /* 2. Function definitions */
            generateTACFuncList(node->data.program.funcs);
            /* 3. Program_Start entry block */
            generateTACProgramStart(node->data.program.start);
            break;

        case NODE_DECL:
            appendTAC(createTAC(TAC_DECL,
                                node->data.decl.varType,
                                NULL,
                                node->data.decl.name));
            break;

case NODE_ASSIGN: {
    if (node->data.assign.arrayLHS) {               /* ← ADD THIS BRANCH */
        char* index = generateTACExpr(
            node->data.assign.arrayLHS->data.array_index.index);
        char* val   = generateTACExpr(node->data.assign.value);
        appendTAC(createTAC(TAC_ARRAY_STORE,
                            node->data.assign.arrayLHS->data.array_index.name,
                            index, val));
    } else if (node->data.assign.structLHS) {
        /* "base is field = expr;"  →  base.field = expr  (TAC_MEMBER_STORE) */
        ASTNode* base = node->data.assign.structLHS->data.struct_access.base;
        char* baseName = (base && base->type == NODE_VAR)
                             ? strdup(base->data.name)
                             : generateTACExpr(base);
        char* val = generateTACExpr(node->data.assign.value);
        appendTAC(createTAC(TAC_MEMBER_STORE,
                            baseName,
                            strdup(node->data.assign.structLHS->data.struct_access.field),
                            val));
    } else {
        /* existing scalar assignment logic — unchanged */
        char* expr;
        if (node->data.assign.value &&
            node->data.assign.value->type == NODE_FUNC_CALL) {
            expr = generateTACFuncCall(node->data.assign.value);
        } else {
            expr = generateTACExpr(node->data.assign.value);
        }
        appendTAC(createTAC(TAC_ASSIGN, expr, NULL,
                            node->data.assign.var));
    }
    break;
}
        case NODE_PRINT: {
            char* expr = generateTACExpr(node->data.expr);
            appendTAC(createTAC(TAC_PRINT, expr, NULL, NULL));
            break;
        }

        /* ── NEW: standalone function call statement ── */
        case NODE_FUNC_CALL:
            generateTACFuncCall(node);   /* result temp is discarded */
            break;

        /* ── NEW: while loop ──
         * LABEL Lstart
         *   t = <condition>
         *   IF_FALSE t GOTO Lend
         *   <body>
         *   GOTO Lstart
         * LABEL Lend                                                  */
        case NODE_WHILE: {
            char* startLabel = newLabel();
            char* endLabel   = newLabel();

            appendTAC(createTAC(TAC_LABEL, NULL, NULL, startLabel));
            char* condTemp = generateTACExpr(node->data.while_stmt.condition);
            appendTAC(createTAC(TAC_IF_FALSE, condTemp, NULL, endLabel));
            generateTAC(node->data.while_stmt.body);
            appendTAC(createTAC(TAC_GOTO, NULL, NULL, startLabel));
            appendTAC(createTAC(TAC_LABEL, NULL, NULL, endLabel));

            free(startLabel);
            free(endLabel);
            free(condTemp);
            break;
        }

        /* ── NEW: C-style while loop ──
         * <init>
         * LABEL Lstart
         *   t = <condition>
         *   IF_FALSE t GOTO Lend
         *   <body>
         *   <update>
         *   GOTO Lstart
         * LABEL Lend                                                  */
        case NODE_FOR_WHILE: {
            generateTAC(node->data.for_while.init);

            char* startLabel = newLabel();
            char* endLabel   = newLabel();

            appendTAC(createTAC(TAC_LABEL, NULL, NULL, startLabel));
            char* condTemp = generateTACExpr(node->data.for_while.condition);
            appendTAC(createTAC(TAC_IF_FALSE, condTemp, NULL, endLabel));
            generateTAC(node->data.for_while.body);
            generateTAC(node->data.for_while.update);
            appendTAC(createTAC(TAC_GOTO, NULL, NULL, startLabel));
            appendTAC(createTAC(TAC_LABEL, NULL, NULL, endLabel));

            free(startLabel);
            free(endLabel);
            free(condTemp);
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

/* ─────────────────────────────────────────────────────────────────────────
 * PRINT / DISPLAY
 * ───────────────────────────────────────────────────────────────────────── */

/* Helper: print one instruction to a FILE* (stdout or file) */
static void printOneInstr(FILE* out, TACInstr* curr, int lineNum) {
    fprintf(out, "%2d: ", lineNum);
    switch (curr->op) {
        case TAC_DECL:
            fprintf(out, "DECL %s %s\n",
                    curr->arg1 ? curr->arg1 : "",
                    curr->result ? curr->result : "");
            break;
        case TAC_ASSIGN:
            fprintf(out, "%s = %s\n",
                    curr->result, curr->arg1);
            break;
        case TAC_ADD:
            fprintf(out, "%s = %s + %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_SUB:
            fprintf(out, "%s = %s - %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_MUL:
            fprintf(out, "%s = %s * %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_DIV:
            fprintf(out, "%s = %s / %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_NEG:
            fprintf(out, "%s = -%s\n", curr->result, curr->arg1);
            break;
        case TAC_PRINT:
            fprintf(out, "PRINT %s\n", curr->arg1);
            break;
        /* ── function opcodes ── */
        case TAC_FUNC_BEGIN:
            fprintf(out, "FUNC_BEGIN %s\n", curr->result);
            break;
        case TAC_FUNC_END:
            fprintf(out, "FUNC_END %s\n", curr->result);
            break;
        case TAC_PARAM:
            fprintf(out, "PARAM %s\n", curr->result);
            break;
        case TAC_ARG:
            fprintf(out, "ARG %s\n", curr->result);
            break;
        case TAC_CALL:
            fprintf(out, "%s = CALL %s, %s\n",
                    curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_RETURN:
            fprintf(out, "RETURN %s\n", curr->result);
            break;
        case TAC_ARRAY_LOAD:                              
            fprintf(out, "%s = %s[%s]\n",
            curr->result, curr->arg1, curr->arg2);
        break;
        case TAC_ARRAY_STORE:
            fprintf(out, "%s[%s] = %s\n",
            curr->arg1, curr->arg2, curr->result);
        break;
        case TAC_MEMBER_LOAD:
            fprintf(out, "%s = %s.%s\n",
            curr->result, curr->arg1, curr->arg2);
        break;
        case TAC_MEMBER_STORE:
            fprintf(out, "%s.%s = %s\n",
            curr->arg1, curr->arg2, curr->result);
        break;
        /* ── relational opcodes ── */
        case TAC_LT:
            fprintf(out, "%s = %s < %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_LE:
            fprintf(out, "%s = %s <= %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_GT:
            fprintf(out, "%s = %s > %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_GE:
            fprintf(out, "%s = %s >= %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_EQ:
            fprintf(out, "%s = %s == %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case TAC_NE:
            fprintf(out, "%s = %s != %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        /* ── control-flow opcodes ── */
        case TAC_LABEL:
            fprintf(out, "LABEL %s:\n", curr->result);
            break;
        case TAC_GOTO:
            fprintf(out, "GOTO %s\n", curr->result);
            break;
        case TAC_IF_FALSE:
            fprintf(out, "IF_FALSE %s GOTO %s\n", curr->arg1, curr->result);
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
        printOneInstr(stdout, curr, lineNum++);
        curr = curr->next;
    }
}

void printOptimizedTAC() {
    printf("Optimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = optimizedList.head;
    int lineNum = 1;
    while (curr) {
        printOneInstr(stdout, curr, lineNum++);
        curr = curr->next;
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * OPTIMIZATION
 * ───────────────────────────────────────────────────────────────────────── */

void optimizeTAC() {
    /* Seed optimized list from the original */
    TACInstr* curr = tacList.head;
    while (curr) {
        appendOptimizedTAC(createTAC(curr->op, curr->arg1,
                                     curr->arg2, curr->result));
        curr = curr->next;
    }

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

int optimizeTACPass(VarValue* values, int* valueCount) {
    int changed = 0;
    TACInstr* curr = optimizedList.head;

    optimizedList.head = NULL;
    optimizedList.tail = NULL;
    *valueCount = 0;

    while (curr) {
        TACInstr* newInstr = NULL;

        switch (curr->op) {
            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV:
            case TAC_LT:
            case TAC_LE:
            case TAC_GT:
            case TAC_GE:
            case TAC_EQ:
            case TAC_NE: {
                char* left  = curr->arg1;
                char* right = curr->arg2;

                for (int i = *valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, left)  == 0) { left  = values[i].value; break; }
                for (int i = *valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, right) == 0) { right = values[i].value; break; }

                /* Constant folding for integer operands */
                int leftIsConst  = isdigit((unsigned char)left[0])  || (left[0]=='-'  && isdigit((unsigned char)left[1]));
                int rightIsConst = isdigit((unsigned char)right[0]) || (right[0]=='-' && isdigit((unsigned char)right[1]));
                if (leftIsConst && rightIsConst &&
                    !(curr->op == TAC_DIV && atoi(right) == 0)) {
                    int lv = atoi(left), rv = atoi(right), res = 0;
                    if      (curr->op == TAC_ADD) res = lv + rv;
                    else if (curr->op == TAC_SUB) res = lv - rv;
                    else if (curr->op == TAC_MUL) res = lv * rv;
                    else if (curr->op == TAC_DIV) res = lv / rv;
                    else if (curr->op == TAC_LT)  res = (lv <  rv);
                    else if (curr->op == TAC_LE)  res = (lv <= rv);
                    else if (curr->op == TAC_GT)  res = (lv >  rv);
                    else if (curr->op == TAC_GE)  res = (lv >= rv);
                    else if (curr->op == TAC_EQ)  res = (lv == rv);
                    else                          res = (lv != rv);
                    char* resultStr = malloc(24);
                    sprintf(resultStr, "%d", res);
                    values[*valueCount].var   = strdup(curr->result);
                    values[*valueCount].value = resultStr;
                    (*valueCount)++;
                    newInstr = createTAC(TAC_ASSIGN, resultStr, NULL, curr->result);
                    changed = 1;
                } else {
                    newInstr = createTAC(curr->op, left, right, curr->result);
                    if (strcmp(left,  curr->arg1) != 0 ||
                        strcmp(right, curr->arg2) != 0)
                        changed = 1;
                }
                break;
            }
            case TAC_NEG: {
                char* operand = curr->arg1;
                for (int i = *valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, operand) == 0) { operand = values[i].value; break; }
                newInstr = createTAC(TAC_NEG, operand, NULL, curr->result);
                if (strcmp(operand, curr->arg1) != 0) changed = 1;
                break;
            }

            case TAC_ASSIGN: {
                char* value = curr->arg1;
                for (int i = *valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, value) == 0) { value = values[i].value; break; }
                if (strcmp(value, curr->arg1) != 0) changed = 1;
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
                if (strcmp(value, curr->arg1) != 0) changed = 1;
                newInstr = createTAC(TAC_PRINT, value, NULL, NULL);
                break;
            }

            case TAC_DECL:
                newInstr = createTAC(TAC_DECL, curr->arg1, NULL, curr->result);
                break;

            /* ── NEW: pass function opcodes through unchanged ──
             * These are never folded or propagated — they are structural
             * markers that the code generator depends on.              */
            case TAC_FUNC_BEGIN:
                /* Each new function boundary invalidates known values */
                *valueCount = 0;
                newInstr = createTAC(TAC_FUNC_BEGIN, NULL, NULL, curr->result);
                break;
            case TAC_FUNC_END:
                newInstr = createTAC(TAC_FUNC_END, NULL, NULL, curr->result);
                break;
            case TAC_PARAM:
                newInstr = createTAC(TAC_PARAM, NULL, NULL, curr->result);
                break;
            case TAC_ARG:
                newInstr = createTAC(TAC_ARG, NULL, NULL, curr->result);
                break;
            case TAC_CALL:
                /* Result of a call is unknown at compile time — don't fold */
                newInstr = createTAC(TAC_CALL, curr->arg1, curr->arg2, curr->result);
                break;
            case TAC_RETURN:
                newInstr = createTAC(TAC_RETURN, NULL, NULL, curr->result);
                break;
            case TAC_ARRAY_LOAD:                              /* ← ADD THIS */
            /* Don't propagate through array accesses —
            * the index may alias a modified variable   */
                newInstr = createTAC(TAC_ARRAY_LOAD,
                         curr->arg1, curr->arg2, curr->result);
                break;

            case TAC_ARRAY_STORE:                             /* ← ADD THIS */
            /* Flush the propagation table — a store may change
            * a value that a live variable was propagated from */
                 *valueCount = 0;
                newInstr = createTAC(TAC_ARRAY_STORE,
                         curr->arg1, curr->arg2, curr->result);
                break;

            case TAC_MEMBER_LOAD:
            /* Don't propagate through struct-field loads — the field's
             * value may have been changed via a different alias        */
                newInstr = createTAC(TAC_MEMBER_LOAD,
                         curr->arg1, curr->arg2, curr->result);
                break;

            case TAC_MEMBER_STORE:
            /* Flush the propagation table — a store may change a value
             * that a live variable was propagated from                 */
                 *valueCount = 0;
                newInstr = createTAC(TAC_MEMBER_STORE,
                         curr->arg1, curr->arg2, curr->result);
                break;

            /* ── NEW: control-flow opcodes ──
             * LABEL marks a merge point reachable from multiple paths
             * (e.g. loop back-edges), so any propagated constant values
             * may no longer be valid there — flush the table.          */
            case TAC_LABEL:
                *valueCount = 0;
                newInstr = createTAC(TAC_LABEL, NULL, NULL, curr->result);
                break;
            case TAC_GOTO:
                newInstr = createTAC(TAC_GOTO, NULL, NULL, curr->result);
                break;
            case TAC_IF_FALSE: {
                char* cond = curr->arg1;
                for (int i = *valueCount - 1; i >= 0; i--)
                    if (strcmp(values[i].var, cond) == 0) { cond = values[i].value; break; }
                if (strcmp(cond, curr->arg1) != 0) changed = 1;
                newInstr = createTAC(TAC_IF_FALSE, cond, NULL, curr->result);
                break;
            }

            default:
                break;
        }

        if (newInstr)
            appendOptimizedTAC(newInstr);

        curr = curr->next;
    }

    return changed;
}

void eliminateDeadCode() {
    /* Pass 1: collect every variable that is READ */
    char used[100][32];
    int  usedCount = 0;

    TACInstr* curr = optimizedList.head;
    while (curr) {
        if (curr->arg1 && !isdigit((unsigned char)curr->arg1[0]))
            strncpy(used[usedCount++], curr->arg1, 31);
        if (curr->arg2 && !isdigit((unsigned char)curr->arg2[0]))
            strncpy(used[usedCount++], curr->arg2, 31);
        /* TAC_ARG reads result; TAC_RETURN reads result */
        if ((curr->op == TAC_ARG || curr->op == TAC_RETURN) &&
             curr->result && !isdigit((unsigned char)curr->result[0]))
            strncpy(used[usedCount++], curr->result, 31);
        curr = curr->next;
    }

    /* Pass 2: drop instructions whose result is never read */
    TACInstr* prev = NULL;
    curr = optimizedList.head;
    while (curr) {
        int isUsed = 0;

        /* These are always live — structural or have side effects */
        if (curr->op == TAC_DECL       ||
            curr->op == TAC_PRINT      ||
            curr->op == TAC_FUNC_BEGIN ||
            curr->op == TAC_FUNC_END   ||
            curr->op == TAC_PARAM      ||
            curr->op == TAC_ARG        ||
            curr->op == TAC_CALL       ||
            curr->op == TAC_RETURN     ||
            curr->op == TAC_ARRAY_STORE||
            curr->op == TAC_MEMBER_STORE||
            curr->op == TAC_LABEL      ||
            curr->op == TAC_GOTO       ||
            curr->op == TAC_IF_FALSE) {      /* control-flow is structural */
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
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

/* ─────────────────────────────────────────────────────────────────────────
 * FILE OUTPUT
 * ───────────────────────────────────────────────────────────────────────── */

void saveTACToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot open '%s' for writing\n", filename);
        return;
    }
    fprintf(file, "# Three-Address Code (TAC) - Unoptimized\n");
    fprintf(file, "# ─────────────────────────────────────\n\n");
    TACInstr* curr = tacList.head;
    int lineNum = 1;
    while (curr) {
        printOneInstr(file, curr, lineNum++);
        curr = curr->next;
    }
    fclose(file);
}

void saveOptimizedTACToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot open '%s' for writing\n", filename);
        return;
    }
    fprintf(file, "# Three-Address Code (TAC) - Optimized\n");
    fprintf(file, "# Optimized Three-Address Code\n");
    fprintf(file, "# ----------------------------------\n");
    TACInstr* curr = optimizedList.head;
    int lineNum = 1;
    while (curr) {
        switch (curr->op) {
            case TAC_DECL:   fprintf(file, "%d: DECL %s %s\n",   lineNum, curr->arg1, curr->result); break;
            case TAC_ASSIGN: fprintf(file, "%d: %s = %s\n",      lineNum, curr->result, curr->arg1); break;
            case TAC_ADD:    fprintf(file, "%d: %s = %s + %s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_SUB:    fprintf(file, "%d: %s = %s - %s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_MUL:    fprintf(file, "%d: %s = %s * %s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_DIV:    fprintf(file, "%d: %s = %s / %s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_NEG:    fprintf(file, "%d: %s = -%s\n",     lineNum, curr->result, curr->arg1); break;
            case TAC_PRINT:  fprintf(file, "%d: print %s\n",     lineNum, curr->arg1); break;
            case TAC_FUNC_BEGIN: fprintf(file, "%d: FUNC_BEGIN %s\n", lineNum, curr->result); break;
            case TAC_FUNC_END:   fprintf(file, "%d: FUNC_END %s\n",   lineNum, curr->result); break;
            case TAC_PARAM:  fprintf(file, "%d: PARAM %s\n",   lineNum, curr->arg1); break;
            case TAC_ARG:    fprintf(file, "%d: ARG %s\n",     lineNum, curr->arg1); break;
            case TAC_CALL:   fprintf(file, "%d: %s = CALL %s, %s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_RETURN: fprintf(file, "%d: RETURN %s\n", lineNum, curr->arg1); break;
            case TAC_ARRAY_LOAD:  fprintf(file, "%d: %s = %s[%s]\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_ARRAY_STORE: fprintf(file, "%d: %s[%s] = %s\n", lineNum, curr->arg1, curr->arg2, curr->result); break;
            case TAC_MEMBER_LOAD:  fprintf(file, "%d: %s = %s.%s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_MEMBER_STORE: fprintf(file, "%d: %s.%s = %s\n", lineNum, curr->arg1, curr->arg2, curr->result); break;
            case TAC_LT: fprintf(file, "%d: %s = %s < %s\n",  lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_LE: fprintf(file, "%d: %s = %s <= %s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_GT: fprintf(file, "%d: %s = %s > %s\n",  lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_GE: fprintf(file, "%d: %s = %s >= %s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_EQ: fprintf(file, "%d: %s = %s == %s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_NE: fprintf(file, "%d: %s = %s != %s\n", lineNum, curr->result, curr->arg1, curr->arg2); break;
            case TAC_LABEL:    fprintf(file, "%d: LABEL %s:\n",            lineNum, curr->result); break;
            case TAC_GOTO:     fprintf(file, "%d: GOTO %s\n",              lineNum, curr->result); break;
            case TAC_IF_FALSE: fprintf(file, "%d: IF_FALSE %s GOTO %s\n",  lineNum, curr->arg1, curr->result); break;
            default: break;
        }
        curr = curr->next;
        lineNum++;
    }
    fclose(file);
}
