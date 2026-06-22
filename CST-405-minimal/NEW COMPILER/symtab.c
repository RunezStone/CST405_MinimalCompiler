/* ============================================================================
 * OOMini  —  Symbol Table + Class / VTable Registry (implementation)
 * ==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* ----------------------------------------------------------------------------
 * Per-scope variable table
 * --------------------------------------------------------------------------*/
SymbolTable scope;

void initScope(void) {
    scope.count = 0;
    scope.nextOffset = 0;
}

int addLocal(char* name, char* type) {
    for (int i = 0; i < scope.count; i++)
        if (strcmp(scope.vars[i].name, name) == 0)
            return scope.vars[i].offset;          /* already declared: reuse */
    if (scope.count >= MAX_SYMBOLS) {
        fprintf(stderr, "symbol table overflow\n");
        exit(1);
    }
    int off = scope.nextOffset;
    scope.vars[scope.count].name   = strdup(name);
    scope.vars[scope.count].type   = strdup(type);
    scope.vars[scope.count].offset = off;
    scope.count++;
    scope.nextOffset += WORD;     /* int and object-reference are both 4 bytes */
    return off;
}

int getOffset(char* name) {
    for (int i = 0; i < scope.count; i++)
        if (strcmp(scope.vars[i].name, name) == 0)
            return scope.vars[i].offset;
    return -1;
}

char* getVarType(char* name) {
    for (int i = 0; i < scope.count; i++)
        if (strcmp(scope.vars[i].name, name) == 0)
            return scope.vars[i].type;
    return NULL;
}

int isLocal(char* name) { return getOffset(name) != -1; }

/* ----------------------------------------------------------------------------
 * Class registry
 * --------------------------------------------------------------------------*/
ClassInfo classes[MAX_CLASSES];
int       classCount;

void initClasses(void) { classCount = 0; }

ClassInfo* findClass(const char* name) {
    if (!name) return NULL;
    for (int i = 0; i < classCount; i++)
        if (strcmp(classes[i].name, name) == 0)
            return &classes[i];
    return NULL;
}

ClassInfo* registerClass(const char* name, const char* parent) {
    if (findClass(name)) return NULL;                 /* duplicate */
    if (classCount >= MAX_CLASSES) { fprintf(stderr, "too many classes\n"); exit(1); }

    ClassInfo* c = &classes[classCount++];
    memset(c, 0, sizeof(*c));
    strncpy(c->name, name, 63);

    if (parent && parent[0]) {
        ClassInfo* p = findClass(parent);
        if (!p) { classCount--; return NULL; }        /* unknown parent */
        strncpy(c->parent, parent, 63);

        /* Inherit fields FIRST — guarantees identical offsets in parent/child */
        for (int i = 0; i < p->fieldCount; i++)
            c->fields[c->fieldCount++] = p->fields[i];

        /* Inherit the vtable — same slots, same labels (overridden later) */
        for (int i = 0; i < p->methodCount; i++)
            c->methods[c->methodCount++] = p->methods[i];
    }

    /* objectSize is recomputed as fields are added */
    c->objectSize = WORD + WORD * c->fieldCount;       /* vtable ptr + fields */
    return c;
}

FieldInfo* findField(ClassInfo* c, const char* name) {
    if (!c) return NULL;
    for (int i = 0; i < c->fieldCount; i++)
        if (strcmp(c->fields[i].name, name) == 0)
            return &c->fields[i];
    return NULL;
}

FieldInfo* addField(ClassInfo* c, const char* name, const char* type) {
    if (findField(c, name)) return NULL;               /* duplicate field */
    if (c->fieldCount >= MAX_FIELDS) { fprintf(stderr, "too many fields\n"); exit(1); }
    FieldInfo* f = &c->fields[c->fieldCount];
    strncpy(f->name, name, 63);
    strncpy(f->type, type, 63);
    f->offset = WORD + WORD * c->fieldCount;            /* skip vtable ptr */
    c->fieldCount++;
    c->objectSize = WORD + WORD * c->fieldCount;
    return f;
}

MethodInfo* findMethod(ClassInfo* c, const char* name) {
    if (!c) return NULL;
    for (int i = 0; i < c->methodCount; i++)
        if (strcmp(c->methods[i].name, name) == 0)
            return &c->methods[i];
    return NULL;
}

MethodInfo* addMethod(ClassInfo* c, const char* definingClass,
                      const char* name, const char* retType, int paramCount) {
    MethodInfo* existing = findMethod(c, name);
    if (existing) {
        /* OVERRIDE: keep the slot, repoint the label to this class's version */
        snprintf(existing->label, sizeof(existing->label), "%s_%s",
                 definingClass, name);
        strncpy(existing->retType, retType, 63);
        existing->paramCount = paramCount;
        return existing;
    }
    if (c->methodCount >= MAX_METHODS) { fprintf(stderr, "too many methods\n"); exit(1); }
    MethodInfo* m = &c->methods[c->methodCount];
    strncpy(m->name, name, 63);
    snprintf(m->label, sizeof(m->label), "%s_%s", definingClass, name);
    strncpy(m->retType, retType, 63);
    m->paramCount = paramCount;
    m->slot = c->methodCount;                           /* append new slot */
    c->methodCount++;
    return m;
}

/* ----------------------------------------------------------------------------
 * Free function registry
 * --------------------------------------------------------------------------*/
FuncInfo funcs[MAX_FUNCS];
int      funcCount;

void initFuncs(void) { funcCount = 0; }

FuncInfo* findFunc(const char* name) {
    for (int i = 0; i < funcCount; i++)
        if (strcmp(funcs[i].name, name) == 0)
            return &funcs[i];
    return NULL;
}

FuncInfo* registerFunc(const char* name, const char* retType, int paramCount) {
    if (findFunc(name)) return NULL;
    if (funcCount >= MAX_FUNCS) { fprintf(stderr, "too many functions\n"); exit(1); }
    FuncInfo* f = &funcs[funcCount++];
    strncpy(f->name, name, 63);
    strncpy(f->retType, retType, 63);
    f->paramCount = paramCount;
    return f;
}

/* ----------------------------------------------------------------------------
 * Debug dump
 * --------------------------------------------------------------------------*/
void printClassRegistry(void) {
    printf("\n===== CLASS REGISTRY =====\n");
    for (int i = 0; i < classCount; i++) {
        ClassInfo* c = &classes[i];
        printf("class %s", c->name);
        if (c->parent[0]) printf(" extends %s", c->parent);
        printf("   (objectSize=%d bytes)\n", c->objectSize);

        printf("  fields:\n");
        for (int j = 0; j < c->fieldCount; j++)
            printf("    [+%2d] %s %s\n", c->fields[j].offset,
                   c->fields[j].type, c->fields[j].name);

        printf("  vtable:\n");
        for (int j = 0; j < c->methodCount; j++)
            printf("    slot %d -> %s  (%s, %d params)\n",
                   c->methods[j].slot, c->methods[j].label,
                   c->methods[j].retType, c->methods[j].paramCount);
    }
    printf("==========================\n\n");
}
