#ifndef FLAWCHECK_H
#define FLAWCHECK_H

#include "ast.h"

/* ============================================================================
 * OOMini  —  Phase 6: Logical Flaw Detection & Self-Correction
 * ----------------------------------------------------------------------------
 * Walks every function and method body AFTER code generation, identifies
 * logical flaws that pass semantic analysis, and auto-corrects those that
 * are safe to fix without altering intended program semantics.
 *
 * Auto-corrected  [FIX]:
 *   - Dead code after a return statement         (trailing stmts removed)
 *   - Self-assignment  x = x                     (statement removed)
 *   - if-condition is a compile-time constant    (live branch inlined)
 *   - Variable declared but never referenced     (declaration removed)
 *
 * Warned only  [WARN]:
 *   - while-condition is a compile-time non-zero (potential infinite loop)
 *   - Division by literal zero                   (division is flagged)
 *   - Variable assigned but its value never read (write-only variable)
 *
 * Returns the total number of flaws found (fixed + warned).
 * Call flawsWereFixed() afterwards to determine whether re-codegen is needed.
 * ==========================================================================*/
int flawCheck(ASTNode* program);

/* Non-zero if the last flawCheck() call modified the AST. */
int flawsWereFixed(void);

#endif /* FLAWCHECK_H */
