#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

/* ============================================================================
 * OOMini  —  MIPS Code Generator
 * Phase 5. Translates the AST directly into MIPS assembly (runnable in spim
 * or MARS). Reads the class registry (symtab.h) for object layouts & vtables.
 *
 * Runtime model
 * -------------
 *  - Frame pointer $fp anchors locals/params, so expressions can freely use
 *    the $sp stack as a scratch evaluation stack without disturbing them.
 *  - Objects live on the heap (allocated with syscall 9 / sbrk). An object is:
 *        word 0 : pointer to its class vtable
 *        word 1+: fields (inherited first, then own)
 *  - Calling convention: $a0..$a3 carry args; for methods $a0 is the implicit
 *    `self`. Return value in $v0.
 *  - Dynamic dispatch: load vtable ptr from obj[0], load method address from
 *    vtable[slot], jalr. This is what makes overridden methods polymorphic.
 * ==========================================================================*/

void generateMIPS(ASTNode* program, const char* filename);

#endif /* CODEGEN_H */
