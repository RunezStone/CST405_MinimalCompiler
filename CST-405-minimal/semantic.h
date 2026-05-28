#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

/* SEMANTIC ANALYZER
 * Performs semantic checks on the AST after parsing, before code generation.
 *
 * Checks enforced:
 *   ✓ No duplicate variable declarations in the same scope
 *   ✓ No use of undeclared variables
 *   ✓ No duplicate function definitions
 *   ✓ Function calls reference defined functions
 *   ✓ Argument count matches parameter count
 *   ✓ "end <var>;" — the return variable must be declared in the function
 *   ✓ Array sizes must be positive
 *   ✓ No duplicate array declarations
 *
 * Architecture — two passes:
 *   Pass 1: Register all function signatures (enables forward calls)
 *   Pass 2: Check global declarations, function bodies, Program_Start body
 */

/* ─────────────────────────────────────────────────────────────────────────
 * RESULT TYPE
 * ───────────────────────────────────────────────────────────────────────── */
typedef struct {
    int errorCount;    /* Total semantic errors found   */
    int warningCount;  /* Total semantic warnings found */
} SemanticInfo;

/* ─────────────────────────────────────────────────────────────────────────
 * PUBLIC API
 * ───────────────────────────────────────────────────────────────────────── */

/* Initialize the semantic analyzer — must be called before analysis.
 * Resets all state and registers the built-in print() function.      */
void initSemantic(void);

/* Run both semantic passes over the AST.
 * Returns  0 if no errors were found.
 * Returns -1 if one or more semantic errors were found.              */
int performSemanticAnalysis(ASTNode* root);

/* Print a human-readable summary of errors/warnings after analysis.  */
void printSemanticSummary(void);

#endif /* SEMANTIC_H */