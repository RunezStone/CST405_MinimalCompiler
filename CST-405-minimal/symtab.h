#ifndef SYMTAB_H
#define SYMTAB_H

/* SYMBOL TABLE
 * Tracks variable names, types, and stack offsets.
 * initSymTab() must be called once before globals are processed,
 * and again at every function boundary (TAC_FUNC_BEGIN / NODE_FUNC_DEF)
 * so each function gets its own isolated stack frame layout.
 */

#define MAX_SYMBOLS 200

/* One entry in the symbol table */
typedef struct {
    char* name;      /* Variable identifier                        */
    char* type;      /* Type string, e.g. "int"                    */
    int   offset;    /* Stack offset in bytes from $sp             */
    int   isArray;   /* 1 if this is an array, 0 for scalar        */
    int   arrSize;   /* Number of elements (0 for scalars)         */
} Symbol;

/* The symbol table itself */
typedef struct {
    Symbol vars[MAX_SYMBOLS];
    int    count;       /* Number of entries currently stored       */
    int    nextOffset;  /* Next available byte offset on the stack  */
} SymbolTable;

extern SymbolTable symtab;

/* ── Public API ── */
void initSymTab(void);              /* Reset table — call at program start and each func */
int  addVar(char* name, char* type);/* Add scalar var; returns offset or -1 on duplicate */
int  addArray(char* name, int size);/* Add array;     returns base offset or -1          */
int  getVarOffset(char* name);      /* Look up offset; returns -1 if not found           */
int  isVarDeclared(char* name);     /* 1 if declared, 0 otherwise                        */
int  getFrameSize(void);            /* Total bytes needed for current frame (incl. $ra)  */
void printSymTab(void);             /* Debug print                                       */

#endif /* SYMTAB_H */