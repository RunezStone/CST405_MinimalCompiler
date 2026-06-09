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

/* Global struct type registry — persists across the whole compilation */
StructTypeInfo structTypes[MAX_STRUCT_TYPES];
int            structTypeCount = 0;

/* Initialize (or re-initialize) an empty symbol table.
 * Call once before generating globals, and again at every
 * FUNC_BEGIN so each function frame starts at offset 0.     */
void initSymTab() {
    /* Free any previously strdup'd strings to avoid leaks */
    for (int i = 0; i < symtab.count; i++) {
        free(symtab.vars[i].name);
        free(symtab.vars[i].type);
        if (symtab.vars[i].structType) free(symtab.vars[i].structType);
        symtab.vars[i].name       = NULL;
        symtab.vars[i].type       = NULL;
        symtab.vars[i].structType = NULL;
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
    symtab.vars[symtab.count].offset     = symtab.nextOffset;
    symtab.vars[symtab.count].isArray    = 0;
    symtab.vars[symtab.count].arrSize    = 0;
    symtab.vars[symtab.count].structType = NULL;

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
    symtab.vars[symtab.count].offset     = symtab.nextOffset;
    symtab.vars[symtab.count].isArray    = 1;
    symtab.vars[symtab.count].arrSize    = size;
    symtab.vars[symtab.count].structType = NULL;

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

/* ─────────────────────────────────────────────────────────────────────────
 * STRUCT TYPE REGISTRY
 * Global across the whole program — struct types are defined only at
 * the top level, so this table is initialized once (not per function).
 * ───────────────────────────────────────────────────────────────────────── */

/* Reset the struct type registry. Call once before semantic analysis. */
void initStructTypes(void) {
    structTypeCount = 0;
    for (int i = 0; i < MAX_STRUCT_TYPES; i++) {
        structTypes[i].name[0]   = '\0';
        structTypes[i].fieldCount = 0;
        structTypes[i].totalSize  = 0;
    }
    printf("STRUCT REGISTRY: Initialized\n");
}

/* Look up a struct type by name. Returns NULL if not registered. */
StructTypeInfo* findStructType(const char* name) {
    for (int i = 0; i < structTypeCount; i++) {
        if (strcmp(structTypes[i].name, name) == 0)
            return &structTypes[i];
    }
    return NULL;
}

/* Register a new struct type. Returns the new entry, or NULL on
 * duplicate name / table-full.                                       */
StructTypeInfo* registerStructType(const char* name) {
    if (findStructType(name) != NULL) {
        printf("STRUCT REGISTRY: Failed to register '%s' - already defined\n", name);
        return NULL;
    }
    if (structTypeCount >= MAX_STRUCT_TYPES) {
        fprintf(stderr, "STRUCT REGISTRY: Full — cannot register '%s'\n", name);
        return NULL;
    }

    StructTypeInfo* st = &structTypes[structTypeCount++];
    strncpy(st->name, name, sizeof(st->name) - 1);
    st->name[sizeof(st->name) - 1] = '\0';
    st->fieldCount = 0;
    st->totalSize  = 0;

    printf("STRUCT REGISTRY: Registered struct type '%s'\n", name);
    return st;
}

/* Add a field to a struct type. Each scalar field is 4 bytes; arrays
 * occupy arrSize * 4 bytes. Fields are laid out contiguously, so the
 * new field's offset is simply the type's current totalSize.
 * Returns the field's byte offset, or -1 on duplicate / table-full.  */
int addStructField(StructTypeInfo* st, const char* fieldName,
                   const char* fieldType, int isArray, int arrSize) {
    if (st == NULL) return -1;

    if (findStructField(st, fieldName) != NULL) {
        printf("STRUCT REGISTRY: Failed to add field '%s' to '%s' - duplicate\n",
               fieldName, st->name);
        return -1;
    }
    if (st->fieldCount >= MAX_STRUCT_FIELDS) {
        fprintf(stderr, "STRUCT REGISTRY: '%s' has too many fields — cannot add '%s'\n",
                st->name, fieldName);
        return -1;
    }

    StructField* f = &st->fields[st->fieldCount++];
    strncpy(f->name, fieldName, sizeof(f->name) - 1);
    f->name[sizeof(f->name) - 1] = '\0';
    strncpy(f->type, fieldType, sizeof(f->type) - 1);
    f->type[sizeof(f->type) - 1] = '\0';
    f->offset  = st->totalSize;
    f->isArray = isArray;
    f->arrSize = arrSize;
    f->hasDefault      = 0;
    f->defaultIsFloat  = 0;
    f->defaultIntVal   = 0;
    f->defaultFloatVal = 0.0f;

    int size = isArray ? (arrSize * 4) : 4;
    st->totalSize += size;

    printf("STRUCT REGISTRY: Added field '%s.%s' (type: %s) at offset %d\n",
           st->name, fieldName, fieldType, f->offset);
    return f->offset;
}

/* Record a default value for a field declared earlier in the struct,
 * e.g. "health = 10;" sets stats.health's default to the int 10.     */
int setStructFieldDefault(StructTypeInfo* st, const char* fieldName,
                          int isFloat, int intVal, float floatVal) {
    StructField* f = findStructField(st, fieldName);
    if (f == NULL) return 0;

    f->hasDefault     = 1;
    f->defaultIsFloat = isFloat;
    if (isFloat) {
        f->defaultFloatVal = floatVal;
        printf("STRUCT REGISTRY: Field '%s.%s' default value = %g\n",
               st->name, fieldName, floatVal);
    } else {
        f->defaultIntVal = intVal;
        printf("STRUCT REGISTRY: Field '%s.%s' default value = %d\n",
               st->name, fieldName, intVal);
    }
    return 1;
}

/* Look up a field within a struct type. Returns NULL if not found. */
StructField* findStructField(StructTypeInfo* st, const char* fieldName) {
    if (st == NULL) return NULL;
    for (int i = 0; i < st->fieldCount; i++) {
        if (strcmp(st->fields[i].name, fieldName) == 0)
            return &st->fields[i];
    }
    return NULL;
}

/* ─────────────────────────────────────────────────────────────────────────
 * STRUCT VARIABLES
 * A struct-typed variable reserves totalSize bytes (contiguous, so each
 * field i lives at baseOffset + field[i].offset).
 * ───────────────────────────────────────────────────────────────────────── */

/* Add a struct-typed variable to the current scope's symbol table.
 * Returns the variable's base stack offset, or -1 on failure.        */
int addStructVar(char* name, char* structTypeName) {
    if (isVarDeclared(name)) {
        printf("SYMBOL TABLE: Failed to add struct var '%s' - already declared\n", name);
        return -1;
    }
    if (symtab.count >= MAX_SYMBOLS) {
        fprintf(stderr, "SYMBOL TABLE: Full — cannot add struct var '%s'\n", name);
        return -1;
    }

    StructTypeInfo* st = findStructType(structTypeName);
    int size = (st != NULL) ? st->totalSize : 4;
    if (size <= 0) size = 4;

    symtab.vars[symtab.count].name       = strdup(name);
    symtab.vars[symtab.count].type       = strdup(structTypeName);
    symtab.vars[symtab.count].offset     = symtab.nextOffset;
    symtab.vars[symtab.count].isArray    = 0;
    symtab.vars[symtab.count].arrSize    = 0;
    symtab.vars[symtab.count].structType = strdup(structTypeName);

    int offset = symtab.nextOffset;
    symtab.nextOffset += size;
    symtab.count++;

    printf("SYMBOL TABLE: Added struct var '%s' (type: %s, size: %d) at offset %d\n",
           name, structTypeName, size, offset);
    printSymTab();
    return offset;
}

/* Returns the struct type name of a struct-typed variable, or NULL
 * if 'name' is not declared or is not a struct.                      */
char* getVarStructType(char* name) {
    for (int i = 0; i < symtab.count; i++)
        if (strcmp(symtab.vars[i].name, name) == 0)
            return symtab.vars[i].structType;
    return NULL;
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
