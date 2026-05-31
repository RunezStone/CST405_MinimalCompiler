#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* THREE-ADDRESS CODE (TAC)
 * Intermediate representation between AST and machine code.
 * Each instruction has at most 3 operands: result = arg1 op arg2
 *
 * Instruction layout by opcode:
 *
 *  Opcode          result          arg1            arg2
 *  ─────────────────────────────────────────────────────
 *  TAC_DECL        var name        type ("int")    —
 *  TAC_ASSIGN      dest var        source/const    —
 *  TAC_ADD         temp            left operand    right operand
 *  TAC_PRINT       —               value/var       —
 *  TAC_FUNC_BEGIN  func name       —               —
 *  TAC_FUNC_END    func name       —               —
 *  TAC_PARAM       param name      —               —
 *  TAC_ARG         value/var       —               —
 *  TAC_CALL        dest temp       func name       arg count (str)
 *  TAC_RETURN      value/var       —               —
 */

/* ─────────────────────────────────────────────────────────────────────────
 * OPCODE ENUM
 * ───────────────────────────────────────────────────────────────────────── */
typedef enum {
    /* Arithmetic opcodes */
    TAC_ADD,        /* result = arg1 + arg2                    */
    TAC_SUB,        /* result = arg1 - arg2                    */
    TAC_MUL,        /* result = arg1 * arg2                    */
    TAC_DIV,        /* result = arg1 / arg2                    */
    TAC_NEG,        /* result = -arg1  (unary minus)           */
    TAC_ASSIGN,     /* result = arg1                           */
    TAC_PRINT,      /* print(arg1)                             */
    TAC_DECL,       /* declare variable 'result' of type arg1  */

    /* Function opcodes */
    TAC_FUNC_BEGIN, /* start of function:  FUNC_BEGIN funcName */
    TAC_FUNC_END,   /* end of function:    FUNC_END   funcName */
    TAC_PARAM,      /* formal parameter:   PARAM      name     */
    TAC_ARG,        /* call argument:      ARG        value    */
    TAC_CALL,       /* call:               result = CALL arg1, arg2 (count) */
    TAC_RETURN,     /* return value:       RETURN     value    */
    TAC_ARRAY_LOAD, /* t0 = arr[i]                             */
    TAC_ARRAY_STORE /* arr[i] = t0                             */
} TACOp;

/* ─────────────────────────────────────────────────────────────────────────
 * INSTRUCTION STRUCTURE
 * ───────────────────────────────────────────────────────────────────────── */
typedef struct TACInstr {
    TACOp  op;              /* Operation type                  */
    char*  arg1;            /* First operand (if needed)       */
    char*  arg2;            /* Second operand (binary ops)     */
    char*  result;          /* Result / destination            */
    struct TACInstr* next;  /* Linked list pointer             */
} TACInstr;

/* ─────────────────────────────────────────────────────────────────────────
 * LIST MANAGEMENT
 * ───────────────────────────────────────────────────────────────────────── */
typedef struct {
    TACInstr* head;     /* First instruction                   */
    TACInstr* tail;     /* Last instruction (fast append)      */
    int       tempCount;/* Counter for temporaries t0, t1, ... */
} TACList;

/* ─────────────────────────────────────────────────────────────────────────
 * OPTIMIZATION HELPER TYPE
 * ───────────────────────────────────────────────────────────────────────── */
typedef struct {
    char* var;    /* Variable or temporary name  */
    char* value;  /* Constant value it holds     */
} VarValue;

/* ─────────────────────────────────────────────────────────────────────────
 * PUBLIC API
 * ───────────────────────────────────────────────────────────────────────── */

/* Initialization */
void      initTAC(void);
char*     newTemp(void);

/* Instruction creation and appending */
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result);
void      appendTAC(TACInstr* instr);
void      appendOptimizedTAC(TACInstr* instr);

/* TAC generation from AST */
void      generateTAC(ASTNode* node);          /* Top-level entry point   */
char*     generateTACExpr(ASTNode* node);      /* Expression → temp/value */

/* Function-specific generation */
void      generateTACFuncDecl(ASTNode* node);       /* func f(...) ... end x; */
void      generateTACFuncList(ASTNode* node);        /* walk STMT_LIST of funcs */
void      generateTACProgramStart(ASTNode* node);    /* Program_Start() block  */
char*     generateTACFuncCall(ASTNode* node);        /* call → returns result temp */

/* Optimization */
void      optimizeTAC(void);
int       optimizeTACPass(VarValue* values, int* valueCount);
void      eliminateDeadCode(void);

/* Output and saving */
void      printTAC(void);
void      printOptimizedTAC(void);
void      saveTACToFile(const char* filename);
void      saveOptimizedTACToFile(const char* filename);

/* Register allocation */
void      initRegAlloc(void);
int       allocReg(const char* name);
void      freeReg(const char* name);
void      printRegState(void);
void      allocateRegistersForTAC(void);

#endif /* TAC_H */