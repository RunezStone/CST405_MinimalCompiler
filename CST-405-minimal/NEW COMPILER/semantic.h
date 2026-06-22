#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

/* ============================================================================
 * OOMini  —  Semantic Analyzer
 * Phase 3. Two passes:
 *   Pass 1  registers every class (flattening inherited fields + vtables) and
 *           every free function, so forward references work.
 *   Pass 2  walks each function/method body: declaration & scope checks,
 *           undeclared-variable checks, field/method existence on the
 *           receiver's static type, argument-count checks, `self` validity,
 *           and `new` target validity.
 *
 * Returns 0 if clean, non-zero if any error was found.
 * ==========================================================================*/
int analyze(ASTNode* program);

/* Expose the static-type resolver so codegen can reuse the same logic. */
const char* exprType(ASTNode* e);

/* Codegen sets this so exprType / checks know the enclosing class (or NULL). */
extern const char* currentClassName;

#endif /* SEMANTIC_H */
