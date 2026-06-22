#ifndef SYMTAB_H
#define SYMTAB_H

/* ============================================================================
 * OOMini  —  Symbol Table + Class / VTable Registry
 * ----------------------------------------------------------------------------
 * Two distinct stores:
 *
 *  1. SymbolTable  — per-function scope. Maps local variable / parameter /
 *     `self` names to a stack offset (relative to the frame pointer $fp).
 *     Reset with initScope() at the start of every function and method.
 *
 *  2. Class registry — GLOBAL, persists for the whole compilation. Holds the
 *     flattened object layout for every class: inherited fields first, then
 *     own fields (so a parent and child agree on every inherited field's
 *     offset). Also holds the vtable: one slot per method, inherited slots
 *     preserved, overrides replacing the label in the existing slot. This is
 *     exactly what makes single inheritance + dynamic dispatch work.
 *
 * Object memory layout (heap):
 *     offset 0 : vtable pointer
 *     offset 4 : first field
 *     offset 8 : second field ...
 * ==========================================================================*/

#define MAX_SYMBOLS       128
#define MAX_CLASSES        64
#define MAX_FIELDS         64
#define MAX_METHODS        64
#define MAX_FUNCS         128
#define WORD                4

/* ---- per-scope variable ---- */
typedef struct {
    char* name;
    char* type;     /* "int" or a class name */
    int   offset;   /* bytes from $fp */
} Symbol;

typedef struct {
    Symbol vars[MAX_SYMBOLS];
    int    count;
    int    nextOffset;
} SymbolTable;

extern SymbolTable scope;

void  initScope(void);                 /* reset locals for a new function   */
int   addLocal(char* name, char* type);/* returns assigned $fp offset       */
int   getOffset(char* name);           /* -1 if not found                   */
char* getVarType(char* name);          /* NULL if not found                 */
int   isLocal(char* name);

/* =====================  CLASS / VTABLE REGISTRY  ========================= */

typedef struct {
    char name[64];
    char type[64];   /* "int" or a class name */
    int  offset;     /* byte offset inside the object (>=4; 0 is vtable ptr) */
} FieldInfo;

typedef struct {
    char name[64];        /* method name, e.g. "speak"                       */
    char label[128];      /* MIPS label of the DEFINING class: "Dog_speak"   */
    char retType[64];     /* "int", "void", or class name                    */
    int  paramCount;      /* explicit params (excludes implicit self)        */
    int  slot;            /* vtable slot index                               */
} MethodInfo;

typedef struct ClassInfo {
    char       name[64];
    char       parent[64];                 /* "" if none                     */
    FieldInfo  fields[MAX_FIELDS];
    int        fieldCount;
    MethodInfo methods[MAX_METHODS];        /* the vtable (by slot)           */
    int        methodCount;                 /* == number of vtable slots      */
    int        objectSize;                  /* bytes: 4 + 4*fieldCount        */
} ClassInfo;

extern ClassInfo classes[MAX_CLASSES];
extern int       classCount;

void        initClasses(void);
ClassInfo*  findClass(const char* name);
/* Create a class, copying parent's fields & vtable first (parent must already
 * be registered). Returns the new class, or NULL on error (dup / bad parent).*/
ClassInfo*  registerClass(const char* name, const char* parent);

/* Add an own field after inherited ones. Returns the field, NULL on dup. */
FieldInfo*  addField(ClassInfo* c, const char* name, const char* type);
FieldInfo*  findField(ClassInfo* c, const char* name);   /* incl. inherited */

/* Register a method. If the name already exists in the (inherited) vtable it
 * OVERRIDES — same slot, label updated to definingClass_name. Otherwise it is
 * APPENDED as a new slot. Returns the MethodInfo. */
MethodInfo* addMethod(ClassInfo* c, const char* definingClass,
                      const char* name, const char* retType, int paramCount);
MethodInfo* findMethod(ClassInfo* c, const char* name);  /* incl. inherited */

/* =====================  FREE FUNCTION REGISTRY  ========================== */
typedef struct {
    char name[64];
    char retType[64];
    int  paramCount;
} FuncInfo;

extern FuncInfo funcs[MAX_FUNCS];
extern int      funcCount;

void      initFuncs(void);
FuncInfo* registerFunc(const char* name, const char* retType, int paramCount);
FuncInfo* findFunc(const char* name);

void printClassRegistry(void);   /* debug dump of layouts + vtables */

#endif /* SYMTAB_H */
