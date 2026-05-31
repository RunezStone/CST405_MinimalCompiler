/* SYMBOL TABLE IMPLEMENTATION
 * Manages variable declarations and memory offsets.
 * Used by both semantic analysis and code generation.
 *
 * initSymTab() is called once at program start AND once at the
 * beginning of every function (TAC_FUNC_BEGIN) so each function
 * gets its own isolated set of stack offsets.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* Global symbol table instance */
SymbolTable symtab;

/* Initialize (or re-initialize) an empty symbol table.
 * Call once before generating globals, and again at every
 * FUNC_BEGIN so each function frame starts at offset 0.     */
void initSymTab() {
    /* Free any previously strdup'd strings to avoid leaks */
    for (int i = 0; i < symtab.count; i++) {
        free(symtab.vars[i].name);
        free(symtab.vars[i].type);
        symtab.vars[i].name = NULL;
        symtab.vars[i].type = NULL;
    }
    symtab.count      = 0;
    symtab.nextOffset = 0;
    printf("SYMBOL TABLE: Initialized\n");
    printSymTab();
}

/* Add a scalar variable.
 * Returns the stack offset on success, -1 on duplicate.     */
int addVar(char* name, char* type) {
    if (isVarDeclared(name)) {
        printf("SYMBOL TABLE: Failed to add '%s' - already declared\n", name);
        return -1;
    }
    if (symtab.count >= MAX_SYMBOLS) {
        fprintf(stderr, "SYMBOL TABLE: Full — cannot add '%s'\n", name);
        return -1;
    }

    symtab.vars[symtab.count].name     = strdup(name);
    symtab.vars[symtab.count].type     = strdup(type);
    symtab.vars[symtab.count].offset   = symtab.nextOffset;
    symtab.vars[symtab.count].isArray  = 0;
    symtab.vars[symtab.count].arrSize  = 0;

    int offset = symtab.nextOffset;
    symtab.nextOffset += 4;   /* one int = 4 bytes */
    symtab.count++;

    printf("SYMBOL TABLE: Added '%s' (type: %s) at offset %d\n",
           name, type, offset);
    printSymTab();
    return offset;
}

/* Add an array variable.
 * Returns the base stack offset on success, -1 on duplicate. */
int addArray(char* name, int size) {
    if (isVarDeclared(name)) {
        printf("SYMBOL TABLE: Failed to add array '%s' - already declared\n",
               name);
        return -1;
    }
    if (symtab.count >= MAX_SYMBOLS) {
        fprintf(stderr, "SYMBOL TABLE: Full — cannot add array '%s'\n", name);
        return -1;
    }

    symtab.vars[symtab.count].name     = strdup(name);
    symtab.vars[symtab.count].type     = strdup("int");
    symtab.vars[symtab.count].offset   = symtab.nextOffset;
    symtab.vars[symtab.count].isArray  = 1;
    symtab.vars[symtab.count].arrSize  = size;

    int offset = symtab.nextOffset;
    symtab.nextOffset += size * 4;   /* size × 4 bytes */
    symtab.count++;

    printf("SYMBOL TABLE: Added array '%s[%d]' at offset %d\n",
           name, size, offset);
    printSymTab();
    return offset;
}

/* Look up a variable's stack offset.
 * Returns the offset, or -1 if not found.                   */
int getVarOffset(char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0) {
            printf("SYMBOL TABLE: Found '%s' at offset %d\n",
                   name, symtab.vars[i].offset);
            return symtab.vars[i].offset;
        }
    }
    printf("SYMBOL TABLE: Variable '%s' not found\n", name);
    return -1;
}

/* Returns the type string of a declared variable, or NULL if not found. */
char* getVarType(char* name) {
    for (int i = 0; i < symtab.count; i++)
        if (strcmp(symtab.vars[i].name, name) == 0)
            return symtab.vars[i].type;
    return NULL;
}

/* Returns 1 if the variable has been declared, 0 otherwise. */
int isVarDeclared(char* name) {
    for (int i = 0; i < symtab.count; i++)
        if (strcmp(symtab.vars[i].name, name) == 0) return 1;
    return 0;
}

/* Returns the total bytes currently allocated on the stack.
 * Useful for the code generator to size the stack frame.    */
int getFrameSize() {
    /* Round up to a multiple of 8 for alignment, minimum 8  */
    int size = symtab.nextOffset + 4;  /* +4 for saved $ra  */
    return (size + 7) & ~7;            /* align to 8 bytes  */
}

/* Print current symbol table for debugging */
void printSymTab() {
    printf("\n=== SYMBOL TABLE STATE ===\n");
    printf("Count: %d, Next Offset: %d\n", symtab.count, symtab.nextOffset);
    if (symtab.count == 0) {
        printf("(empty)\n");
    } else {
        printf("  %-4s %-16s %-8s %-8s %s\n",
               "Idx", "Name", "Type", "Offset", "Array?");
        printf("  ────────────────────────────────────────\n");
        for (int i = 0; i < symtab.count; i++) {
            if (symtab.vars[i].isArray) {
                printf("  [%d]  %-16s %-8s %-8d\n",
                       i,
                       symtab.vars[i].name,
                       symtab.vars[i].type,
                       symtab.vars[i].offset);
            }
        }
    }
    printf("\n");
}
