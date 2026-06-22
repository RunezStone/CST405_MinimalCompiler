#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* ============================================================================
 * OOMini  —  Three-Address Code (intermediate representation)
 * Phase 4. This produces a readable TAC listing that shows how the OO
 * constructs lower into primitive operations *before* MIPS is emitted:
 *
 *   t = a + b                 arithmetic
 *   t = obj .field            member load   (field read)
 *   obj .field = t            member store  (field write)
 *   t = new Class(size)       heap allocation
 *   param x                   pass an argument
 *   t = call f, n             static call (free function / constructor)
 *   t = vcall obj.m [slot k]  virtual call (dynamic dispatch via vtable)
 *
 * The TAC here is for explanation/inspection; MIPS codegen reads the AST
 * directly (same architecture as the original CST-405 compiler).
 * ==========================================================================*/

void generateTAC(ASTNode* program, const char* filename);

#endif /* TAC_H */
