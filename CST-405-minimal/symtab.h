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
    char* name;       /* Variable identifier                        */
    char* type;       /* Type string, e.g. "int"                    */
    int   offset;     /* Stack offset in bytes from $sp             */
    int   isArray;    /* 1 if this is an array, 0 for scalar        */
    int   arrSize;    /* Number of elements (0 for scalars)         */
    char* structType; /* Struct type name, or NULL if not a struct  */
} Symbol;

/* ─────────────────────────────────────────────────────────────────────────
 * STRUCT TYPE REGISTRY
 * Stores the layout (fields + byte offsets) of every "struct Name { .. }"
 * definition seen in the program. This registry is GLOBAL — unlike the
 * per-function SymbolTable, struct type definitions persist across the
 * whole compilation (structs cannot be declared inside functions).
 * Each scalar field occupies 4 bytes; field i sits at offset i*4 from
 * the struct variable's base stack offset.
 * ───────────────────────────────────────────────────────────────────────── */

#define MAX_STRUCT_TYPES  20
#define MAX_STRUCT_FIELDS 32

/* One field within a struct type */
typedef struct {
    char  name[64];   /* Field name                               */
    char  type[16];   /* Field type: "int" or "float"             */
    int   offset;     /* Byte offset within the struct (i * 4)    */
    int   isArray;    /* 1 if this field is an array              */
    int   arrSize;    /* Element count (0 for scalar fields)      */
    int   hasDefault;      /* 1 if a default value was assigned in
                              the struct body, e.g. "health = 10;" */
    int   defaultIsFloat;  /* 1 if the default literal was a float */
    int   defaultIntVal;   /* default value for int fields         */
    float defaultFloatVal; /* default value for float fields       */
} StructField;

/* One registered struct type, e.g. "struct stats { ... }" */
typedef struct {
    char        name[64];               /* Struct type name            */
    StructField fields[MAX_STRUCT_FIELDS];
    int         fieldCount;             /* Number of fields registered */
    int         totalSize;              /* Total size in bytes         */
} StructTypeInfo;

extern StructTypeInfo structTypes[MAX_STRUCT_TYPES];
extern int            structTypeCount;

/* -- Struct registry API -- */
void            initStructTypes(void);
StructTypeInfo* findStructType(const char* name);
StructTypeInfo* registerStructType(const char* name);
int             addStructField(StructTypeInfo* st, const char* fieldName,
                               const char* fieldType, int isArray, int arrSize);
StructField*    findStructField(StructTypeInfo* st, const char* fieldName);

/* Record a default value for an already-declared field, e.g. the
 * "health = 10;" line inside "struct stats { int health; ... }".
 * isFloat selects which of intVal/floatVal is meaningful.
 * Returns 1 on success, 0 if the field doesn't exist. */
int             setStructFieldDefault(StructTypeInfo* st, const char* fieldName,
                                      int isFloat, int intVal, float floatVal);

/* -- Struct variable helpers (operate on the per-scope SymbolTable) -- */
int   addStructVar(char* name, char* structTypeName); /* returns base offset, or -1 */
char* getVarStructType(char* name);                   /* NULL if not a struct var   */

/* The symbol table itself */
typedef struct {
    Symbol vars[MAX_SYMBOLS];
    int    count;       /* Number of entries currently stored       */
    int    nextOffset;  /* Next available byte offset on the stack  */
} SymbolTable;

extern SymbolTable symtab;

/* -- Public API -- */
void initSymTab(void);              /* Reset table -- call at program start and each func */
int  addVar(char* name, char* type);/* Add scalar var; returns offset or -1 on duplicate */
int  addArray(char* name, int size);/* Add array;     returns base offset or -1          */
int   getVarOffset(char* name);     /* Look up offset; returns -1 if not found           */
char* getVarType(char* name);       /* Look up type; returns NULL if not found           */
int   isVarDeclared(char* name);    /* 1 if declared, 0 otherwise                        */
int  getFrameSize(void);            /* Total bytes needed for current frame (incl. $ra)  */
void printSymTab(void);

#endif /* SYMTAB_H */
