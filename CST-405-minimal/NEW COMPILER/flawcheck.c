/* ============================================================================
 * OOMini  —  Phase 6: Logical Flaw Detection & Self-Correction
 * ==========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flawcheck.h"

static int gFlaws = 0;
static int gFixed = 0;

/* ============================================================================
 * Reporting
 * ==========================================================================*/

static void report(int line, const char* kind, const char* msg) {
    printf("  [%s] Line %d: %s\n", kind, line, msg);
    gFlaws++;
}

/* ============================================================================
 * Expression traversal helpers
 * ==========================================================================*/

/* Returns 1 if expression tree 'e' contains a read of 'varName'. */
static int exprUsesVar(ASTNode* e, const char* varName) {
    if (!e) return 0;
    if (e->type == NODE_VAR && strcmp(e->name, varName) == 0) return 1;
    if (exprUsesVar(e->left,  varName)) return 1;
    if (exprUsesVar(e->right, varName)) return 1;
    if (exprUsesVar(e->base,  varName)) return 1;
    if (exprUsesVar(e->value, varName)) return 1;
    if (exprUsesVar(e->cond,  varName)) return 1;
    for (ASTNode* a = e->args; a; a = a->next)
        if (exprUsesVar(a, varName)) return 1;
    return 0;
}

/* Walk expression tree reporting division by literal zero. */
static void scanDivByZero(ASTNode* e) {
    if (!e) return;
    if (e->type == NODE_BINOP && e->op == '/') {
        if (e->right && e->right->type == NODE_NUM && e->right->ival == 0) {
            report(e->lineno, "WARN", "division by literal zero");
            printf("         Suggestion: replace the zero divisor with a non-zero value\n");
        }
    }
    scanDivByZero(e->left);
    scanDivByZero(e->right);
    scanDivByZero(e->base);
    scanDivByZero(e->value);
    scanDivByZero(e->cond);
    for (ASTNode* a = e->args; a; a = a->next)
        scanDivByZero(a);
}

/* ============================================================================
 * Variable-use queries over statement lists
 * ==========================================================================*/

static int stmtListUsesVarAsRVal(ASTNode* s, const char* varName);
static int stmtListAssignsVar   (ASTNode* s, const char* varName);

/* Returns 1 if statement 's' reads 'varName' as a value. */
static int stmtUsesVarAsRVal(ASTNode* s, const char* varName) {
    if (!s) return 0;
    switch (s->type) {
        case NODE_ASSIGN:
            /* LHS plain-variable name is a write, not a read; check RHS and
               field-LHS expressions (obj.field = …  uses obj as a read). */
            if (s->lhsField)
                return exprUsesVar(s->lhsField, varName)
                    || exprUsesVar(s->value,    varName);
            return exprUsesVar(s->value, varName);

        case NODE_PRINT:
        case NODE_RETURN:
        case NODE_EXPR_STMT:
            return exprUsesVar(s->value, varName);

        case NODE_IF:
            return exprUsesVar(s->cond, varName)
                || stmtListUsesVarAsRVal(s->body,     varName)
                || stmtListUsesVarAsRVal(s->elseBody, varName);

        case NODE_WHILE:
            return exprUsesVar(s->cond, varName)
                || stmtListUsesVarAsRVal(s->body, varName);

        default:
            return 0;
    }
}

static int stmtListUsesVarAsRVal(ASTNode* s, const char* varName) {
    for (; s; s = s->next)
        if (stmtUsesVarAsRVal(s, varName)) return 1;
    return 0;
}

/* Returns 1 if 'varName' appears as the plain-variable LHS of any assignment
   anywhere in the statement list (including inside if/while bodies). */
static int stmtListAssignsVar(ASTNode* s, const char* varName) {
    for (; s; s = s->next) {
        if (s->type == NODE_ASSIGN && !s->lhsField
            && s->name && strcmp(s->name, varName) == 0)
            return 1;
        if (s->type == NODE_IF) {
            if (stmtListAssignsVar(s->body,     varName)) return 1;
            if (stmtListAssignsVar(s->elseBody, varName)) return 1;
        }
        if (s->type == NODE_WHILE) {
            if (stmtListAssignsVar(s->body, varName)) return 1;
        }
    }
    return 0;
}

/* ============================================================================
 * Core flaw-fixing pass  (structural fixes, modifies AST in-place)
 * ==========================================================================*/

static ASTNode* fixStmtList(ASTNode* head);    /* forward decl for recursion */

static ASTNode* fixStmtList(ASTNode* head) {
    /* Use a sentinel so we can splice/remove nodes without a special-case for
       the list head. */
    ASTNode sentinel;
    memset(&sentinel, 0, sizeof(sentinel));
    sentinel.next = head;
    ASTNode* prev = &sentinel;

    while (prev->next) {
        ASTNode* s = prev->next;

        switch (s->type) {

        /* ------------------------------------------------------------------ */
        case NODE_RETURN:
            /* Dead code after return */
            if (s->next) {
                int count = 0;
                for (ASTNode* d = s->next; d; d = d->next) count++;
                char buf[200];
                snprintf(buf, sizeof(buf),
                    "dead code after 'return' — %d unreachable statement(s) removed", count);
                report(s->next->lineno, "FIX", buf);
                s->next = NULL;
                gFixed++;
            }
            prev = s;
            break;

        /* ------------------------------------------------------------------ */
        case NODE_ASSIGN:
            /* Self-assignment:  x = x */
            if (!s->lhsField && s->value && s->value->type == NODE_VAR
                && s->name && strcmp(s->name, s->value->name) == 0) {
                char buf[200];
                snprintf(buf, sizeof(buf),
                    "self-assignment '%s = %s' has no effect — statement removed",
                    s->name, s->name);
                report(s->lineno, "FIX", buf);
                prev->next = s->next;   /* unlink; don't advance prev */
                gFixed++;
            } else {
                if (s->value) scanDivByZero(s->value);
                prev = s;
            }
            break;

        /* ------------------------------------------------------------------ */
        case NODE_IF: {
            if (s->cond && s->cond->type == NODE_NUM) {
                /* Compile-time constant condition */
                int cv = s->cond->ival;
                char buf[200];

                if (cv == 0) {
                    /* Then-branch is dead; inline else-branch (may be NULL). */
                    snprintf(buf, sizeof(buf),
                        "if-condition is always false (0) — "
                        "then-branch is dead, inlining else-branch");
                    report(s->lineno, "FIX", buf);

                    ASTNode* replacement = fixStmtList(s->elseBody);
                    if (replacement) {
                        ASTNode* tail = replacement;
                        while (tail->next) tail = tail->next;
                        tail->next = s->next;
                        prev->next = replacement;
                        /* don't advance prev — loop will process inlined stmts */
                    } else {
                        prev->next = s->next;
                    }
                } else {
                    /* Else-branch is dead; inline then-branch (may be NULL). */
                    snprintf(buf, sizeof(buf),
                        "if-condition is always true (%d) — "
                        "else-branch is dead, inlining then-branch", cv);
                    report(s->lineno, "FIX", buf);

                    ASTNode* replacement = fixStmtList(s->body);
                    if (replacement) {
                        ASTNode* tail = replacement;
                        while (tail->next) tail = tail->next;
                        tail->next = s->next;
                        prev->next = replacement;
                    } else {
                        prev->next = s->next;
                    }
                }
                gFixed++;
                /* don't advance prev — re-scan the freshly inlined nodes */

            } else {
                /* Non-constant condition: recurse into both branches. */
                s->body     = fixStmtList(s->body);
                s->elseBody = fixStmtList(s->elseBody);
                if (s->cond) scanDivByZero(s->cond);
                prev = s;
            }
            break;
        }

        /* ------------------------------------------------------------------ */
        case NODE_WHILE: {
            /* Warn about while(constant_nonzero) — potential infinite loop. */
            if (s->cond && s->cond->type == NODE_NUM && s->cond->ival != 0) {
                char buf[200];
                snprintf(buf, sizeof(buf),
                    "while-condition is always true (%d) — potential infinite loop",
                    s->cond->ival);
                report(s->lineno, "WARN", buf);
                printf("         Suggestion: ensure the loop body modifies the condition variable\n");
            } else if (s->cond) {
                scanDivByZero(s->cond);
            }
            s->body = fixStmtList(s->body);
            prev = s;
            break;
        }

        /* ------------------------------------------------------------------ */
        default:
            /* Scan any sub-expressions for div/0. */
            if (s->value) scanDivByZero(s->value);
            prev = s;
            break;
        }
    }

    return sentinel.next;
}

/* ============================================================================
 * Second pass: unused / write-only variable declarations
 * ==========================================================================*/

static ASTNode* checkDecls(ASTNode* head) {
    ASTNode sentinel;
    memset(&sentinel, 0, sizeof(sentinel));
    sentinel.next = head;
    ASTNode* prev = &sentinel;

    while (prev->next) {
        ASTNode* s = prev->next;

        if (s->type == NODE_DECL) {
            const char* name = s->name;
            ASTNode*    rest = s->next;

            int rval   = stmtListUsesVarAsRVal(rest, name);
            int assign = stmtListAssignsVar(rest, name);

            if (!rval && !assign) {
                /* Completely unreferenced — safe to drop the declaration. */
                char buf[200];
                snprintf(buf, sizeof(buf),
                    "'%s' (%s) declared but never referenced — declaration removed",
                    name, s->typeName);
                report(s->lineno, "FIX", buf);
                prev->next = s->next;
                gFixed++;
                /* don't advance prev; re-read prev->next next iteration */
                continue;

            } else if (!rval && assign) {
                /* Assigned but its value is never consumed. */
                char buf[200];
                snprintf(buf, sizeof(buf),
                    "'%s' is assigned but its value is never read (write-only variable)",
                    name);
                report(s->lineno, "WARN", buf);
                printf("         Suggestion: remove the variable and its assignments "
                       "if the result is not needed\n");
                prev = s;

            } else {
                prev = s;
            }

        } else if (s->type == NODE_IF) {
            /* Recurse into branches so nested declarations are also checked. */
            s->body     = checkDecls(s->body);
            s->elseBody = checkDecls(s->elseBody);
            prev = s;

        } else if (s->type == NODE_WHILE) {
            s->body = checkDecls(s->body);
            prev = s;

        } else {
            prev = s;
        }
    }

    return sentinel.next;
}

/* ============================================================================
 * Per-function entry point (structural pass)
 * ==========================================================================*/

static void checkBody(ASTNode* fn) {
    fn->body = fixStmtList(fn->body);
    fn->body = checkDecls(fn->body);
}

/* ============================================================================
 * ALGORITHMIC ANALYSIS
 * These checks detect logic design flaws: missing case coverage, wasteful
 * algorithms, and incorrect iteration bounds.  They do NOT auto-fix the AST
 * because the correct replacement requires programmer judgement.
 * Labels used:
 *   [ALGO]  — algorithm design: better approach exists
 *   [PERF]  — performance: unnecessary repeated computation
 *   [LOGIC] — correctness: code may behave wrong in some inputs
 * ==========================================================================*/

#define MAX_VARS 48

/* ---- Generic helpers ---------------------------------------------------- */

/* Collect names of every variable ASSIGNED anywhere in a statement list
   (recurses into if/while bodies). */
static void collectModifiedVars(ASTNode* s, char** out, int* count) {
    for (; s; s = s->next) {
        if (s->type == NODE_ASSIGN && !s->lhsField && s->name) {
            int found = 0;
            for (int i = 0; i < *count; i++)
                if (strcmp(out[i], s->name) == 0) { found = 1; break; }
            if (!found && *count < MAX_VARS)
                out[(*count)++] = s->name;
        }
        if (s->type == NODE_IF) {
            collectModifiedVars(s->body,     out, count);
            collectModifiedVars(s->elseBody, out, count);
        }
        if (s->type == NODE_WHILE)
            collectModifiedVars(s->body, out, count);
    }
}

/* Returns 1 if expression 'e' uses any variable in the set 'vars[0..count)'. */
static int exprUsesAnyOf(ASTNode* e, char** vars, int count) {
    if (!e) return 0;
    if (e->type == NODE_VAR) {
        for (int i = 0; i < count; i++)
            if (strcmp(e->name, vars[i]) == 0) return 1;
        return 0;
    }
    if (exprUsesAnyOf(e->left,  vars, count)) return 1;
    if (exprUsesAnyOf(e->right, vars, count)) return 1;
    if (exprUsesAnyOf(e->base,  vars, count)) return 1;
    if (exprUsesAnyOf(e->value, vars, count)) return 1;
    for (ASTNode* a = e->args; a; a = a->next)
        if (exprUsesAnyOf(a, vars, count)) return 1;
    return 0;
}

/* Returns 1 if expression contains any function/method call (side effects). */
static int exprHasCall(ASTNode* e) {
    if (!e) return 0;
    if (e->type == NODE_FUNC_CALL || e->type == NODE_METHOD_CALL) return 1;
    if (exprHasCall(e->left))  return 1;
    if (exprHasCall(e->right)) return 1;
    if (exprHasCall(e->base))  return 1;
    if (exprHasCall(e->value)) return 1;
    for (ASTNode* a = e->args; a; a = a->next)
        if (exprHasCall(a)) return 1;
    return 0;
}

/* Returns the last assignment to 'varName' that appears before 'stop' in 'head'. */
static ASTNode* findPrecedingAssign(ASTNode* head, ASTNode* stop,
                                    const char* varName) {
    ASTNode* last = NULL;
    for (ASTNode* s = head; s && s != stop; s = s->next)
        if (s->type == NODE_ASSIGN && !s->lhsField
            && s->name && strcmp(s->name, varName) == 0)
            last = s;
    return last;
}

/* ---- Check: repeated addition simulating multiplication ----------------- */
/*
 * Matches:  acc = 0;
 *           while (i < n) { acc = acc + x;  i = i + 1; }
 * where x does not reference i or acc.
 * Suggests: acc = x * n   (O(1) instead of O(n))
 */
static void checkRepeatedAddition(ASTNode* whileNode, ASTNode* contextHead) {
    ASTNode* cond = whileNode->cond;
    if (!cond || cond->type != NODE_BINOP) return;
    if (cond->op != '<' && cond->op != 'l') return;   /* < or <= only */
    if (!cond->left || cond->left->type != NODE_VAR)   return;

    const char* counterVar = cond->left->name;
    const char* accVar     = NULL;
    ASTNode*    addend     = NULL;
    int         hasInc     = 0;
    int         extra      = 0;

    for (ASTNode* s = whileNode->body; s; s = s->next) {
        if (s->type != NODE_ASSIGN || s->lhsField || !s->name || !s->value) {
            extra++; continue;
        }
        ASTNode* rhs = s->value;

        /* Counter increment:  counter = counter + 1 */
        if (strcmp(s->name, counterVar) == 0
            && rhs->type == NODE_BINOP && rhs->op == '+'
            && rhs->left  && rhs->left->type  == NODE_VAR
            && strcmp(rhs->left->name, counterVar) == 0
            && rhs->right && rhs->right->type == NODE_NUM
            && rhs->right->ival == 1) {
            hasInc = 1; continue;
        }

        /* Accumulation:  acc = acc + addend  (or addend + acc) */
        if (rhs->type == NODE_BINOP && rhs->op == '+') {
            ASTNode* cand = NULL;
            if (rhs->left && rhs->left->type == NODE_VAR
                && strcmp(rhs->left->name, s->name) == 0)
                cand = rhs->right;
            else if (rhs->right && rhs->right->type == NODE_VAR
                     && strcmp(rhs->right->name, s->name) == 0)
                cand = rhs->left;
            if (cand && !accVar) { accVar = s->name; addend = cand; continue; }
        }
        extra++;
    }

    if (!accVar || !hasInc || extra > 0) return;
    if (exprUsesVar(addend, counterVar) || exprUsesVar(addend, accVar)) return;

    /* acc must have been initialised to 0 before the loop */
    ASTNode* init = findPrecedingAssign(contextHead, whileNode, accVar);
    if (!init || !init->value || init->value->type != NODE_NUM
        || init->value->ival != 0) return;

    const char* bound_str  = "n";
    char        nbuf[32];
    if (cond->right) {
        if (cond->right->type == NODE_VAR)
            bound_str = cond->right->name;
        else if (cond->right->type == NODE_NUM) {
            snprintf(nbuf, sizeof(nbuf), "%d", cond->right->ival);
            bound_str = nbuf;
        }
    }
    static char add_nbuf[32];
    const char* add_str;
    if      (addend && addend->type == NODE_VAR) add_str = addend->name;
    else if (addend && addend->type == NODE_NUM) {
        snprintf(add_nbuf, sizeof(add_nbuf), "%d", addend->ival);
        add_str = add_nbuf;
    } else add_str = "expr";

    char buf[300];
    snprintf(buf, sizeof(buf),
        "loop adds '%s' to '%s' on every iteration (O(n) repeated addition) — "
        "replace with: %s = %s * %s",
        add_str, accVar, accVar, add_str, bound_str);
    report(whileNode->lineno, "ALGO", buf);
    printf("         Repeated addition is O(n); the direct multiplication '%s = %s * %s' is O(1)\n",
           accVar, add_str, bound_str);
}

/* ---- Check: loop-invariant computation ---------------------------------- */
/*
 * If an assignment inside a loop body has an RHS that does not depend on any
 * variable modified in the loop, it is computed identically every iteration.
 */
static void checkLoopInvariant(ASTNode* whileNode) {
    char* modified[MAX_VARS];
    int   nMod = 0;
    collectModifiedVars(whileNode->body, modified, &nMod);

    for (ASTNode* s = whileNode->body; s; s = s->next) {
        if (s->type != NODE_ASSIGN || s->lhsField || !s->value) continue;
        /* Evolving assignments (x = x + ...) are intentional, skip them. */
        if (exprUsesVar(s->value, s->name)) continue;
        /* Skip calls — side effects make hoisting unsafe. */
        if (exprHasCall(s->value)) continue;
        /* If RHS touches no loop-modified variable, it never changes. */
        if (!exprUsesAnyOf(s->value, modified, nMod)) {
            char buf[300];
            snprintf(buf, sizeof(buf),
                "'%s = ...' produces the same result every iteration (loop-invariant) — "
                "move this assignment to before the loop",
                s->name);
            report(s->lineno, "PERF", buf);
            printf("         Hoisting this out of the loop eliminates the repeated computation\n");
        }
    }
}

/* ---- Check: off-by-one suspicion ---------------------------------------- */
/*
 * while (i <= n) with i initialised to 0  ->  iterates n+1 times
 * while (i <  n) with i initialised to 1  ->  iterates n-1 times
 */
static void checkOffByOne(ASTNode* whileNode, ASTNode* contextHead) {
    ASTNode* cond = whileNode->cond;
    if (!cond || cond->type != NODE_BINOP) return;
    if (cond->op != '<' && cond->op != 'l') return;
    if (!cond->left || cond->left->type != NODE_VAR) return;

    const char* cv    = cond->left->name;
    ASTNode*    init  = findPrecedingAssign(contextHead, whileNode, cv);
    if (!init || !init->value || init->value->type != NODE_NUM) return;

    int  iv = init->value->ival;
    char op = cond->op;
    char buf[300];

    if (iv == 0 && op == 'l' /* <= */) {
        snprintf(buf, sizeof(buf),
            "'%s' starts at 0 with condition '%s <= bound': "
            "loop runs (bound+1) times — did you mean '%s < bound'?",
            cv, cv, cv);
        report(whileNode->lineno, "LOGIC", buf);
        printf("         'i <= n' starting from 0 iterates n+1 times (0..n). "
               "Use 'i < n' for exactly n iterations.\n");
    } else if (iv == 1 && op == '<') {
        snprintf(buf, sizeof(buf),
            "'%s' starts at 1 with condition '%s < bound': "
            "loop runs (bound-1) times — did you mean '%s <= bound'?",
            cv, cv, cv);
        report(whileNode->lineno, "LOGIC", buf);
        printf("         'i < n' starting from 1 iterates n-1 times (1..n-1). "
               "Use 'i <= n' for exactly n iterations.\n");
    }
}

/* ---- Check: division by variable without zero guard --------------------- */
/*
 * Finds every  a / varName  in the function body and checks whether
 * the function contains an if-condition that tests varName == 0 or varName != 0.
 * Missing guard -> the caller can trigger a divide-by-zero at runtime.
 */
static void collectVarDivisors(ASTNode* e, char** vars, int* count) {
    if (!e) return;
    if (e->type == NODE_BINOP && e->op == '/') {
        if (e->right && e->right->type == NODE_VAR) {
            const char* nm = e->right->name;
            int found = 0;
            for (int i = 0; i < *count; i++)
                if (strcmp(vars[i], nm) == 0) { found = 1; break; }
            if (!found && *count < MAX_VARS)
                vars[(*count)++] = (char*)nm;
        }
    }
    collectVarDivisors(e->left,  vars, count);
    collectVarDivisors(e->right, vars, count);
    collectVarDivisors(e->base,  vars, count);
    collectVarDivisors(e->value, vars, count);
    for (ASTNode* a = e->args; a; a = a->next)
        collectVarDivisors(a, vars, count);
}

static void scanDivisors(ASTNode* s, char** vars, int* count) {
    for (; s; s = s->next) {
        switch (s->type) {
            case NODE_ASSIGN:
                collectVarDivisors(s->value, vars, count);
                if (s->lhsField) collectVarDivisors(s->lhsField, vars, count);
                break;
            case NODE_PRINT: case NODE_RETURN: case NODE_EXPR_STMT:
                collectVarDivisors(s->value, vars, count);
                break;
            case NODE_IF:
                collectVarDivisors(s->cond, vars, count);
                scanDivisors(s->body,     vars, count);
                scanDivisors(s->elseBody, vars, count);
                break;
            case NODE_WHILE:
                collectVarDivisors(s->cond, vars, count);
                scanDivisors(s->body, vars, count);
                break;
            default: break;
        }
    }
}

/* Collect variables that appear in a  var == 0  or  var != 0  if-condition. */
static void collectZeroGuards(ASTNode* s, char** vars, int* count) {
    for (; s; s = s->next) {
        if (s->type == NODE_IF) {
            ASTNode* c = s->cond;
            if (c && c->type == NODE_BINOP
                && (c->op == 'e' || c->op == 'n')) {   /* == or != */
                ASTNode* vn = NULL;
                if (c->left  && c->left->type  == NODE_VAR
                    && c->right && c->right->type == NODE_NUM && c->right->ival == 0)
                    vn = c->left;
                else if (c->right && c->right->type == NODE_VAR
                         && c->left  && c->left->type  == NODE_NUM && c->left->ival == 0)
                    vn = c->right;
                if (vn) {
                    int found = 0;
                    for (int i = 0; i < *count; i++)
                        if (strcmp(vars[i], vn->name) == 0) { found = 1; break; }
                    if (!found && *count < MAX_VARS)
                        vars[(*count)++] = (char*)vn->name;
                }
            }
            collectZeroGuards(s->body,     vars, count);
            collectZeroGuards(s->elseBody, vars, count);
        }
        if (s->type == NODE_WHILE)
            collectZeroGuards(s->body, vars, count);
    }
}

static void checkDivisionGuards(ASTNode* fn) {
    char* divisors[MAX_VARS]; int nDiv = 0;
    char* guarded [MAX_VARS]; int nGrd = 0;

    scanDivisors(fn->body,     divisors, &nDiv);
    collectZeroGuards(fn->body, guarded, &nGrd);

    for (int i = 0; i < nDiv; i++) {
        int ok = 0;
        for (int j = 0; j < nGrd; j++)
            if (strcmp(divisors[i], guarded[j]) == 0) { ok = 1; break; }
        if (!ok) {
            char buf[300];
            snprintf(buf, sizeof(buf),
                "'%s' is used as a divisor but is never checked for zero — "
                "a caller can trigger a crash by passing %s == 0",
                divisors[i], divisors[i]);
            report(fn->lineno, "LOGIC", buf);
            printf("         Add a guard before the division: "
                   "if (%s == 0) { /* handle zero denominator */ }\n",
                   divisors[i]);
        }
    }
}

/* ---- Check: non-void function with missing return paths ----------------- */
/*
 * A function that returns int but doesn't return in every branch silently
 * returns garbage (or crashes).  This is a common beginner oversight.
 */
static int stmtListAlwaysReturns(ASTNode* s) {
    if (!s) return 0;
    ASTNode* last = s;
    while (last->next) last = last->next;
    if (last->type == NODE_RETURN) return 1;
    if (last->type == NODE_IF)
        return stmtListAlwaysReturns(last->body)
            && stmtListAlwaysReturns(last->elseBody);
    return 0;
}

static void checkReturnPaths(ASTNode* fn) {
    if (!fn->typeName || strcmp(fn->typeName, "void") == 0) return;
    if (!stmtListAlwaysReturns(fn->body)) {
        char buf[300];
        snprintf(buf, sizeof(buf),
            "non-void '%s' (returns %s) may not return a value in all code paths",
            fn->name, fn->typeName);
        report(fn->lineno, "LOGIC", buf);
        printf("         Every branch must return a '%s' value, "
               "or add a fallback return at the end of the function\n",
               fn->typeName);
    }
}

/* ---- Dispatcher: walk statement list looking for algorithmic patterns --- */

static void algCheckStmtList(ASTNode* head) {
    for (ASTNode* s = head; s; s = s->next) {
        if (s->type == NODE_WHILE) {
            checkRepeatedAddition(s, head);
            checkLoopInvariant(s);
            checkOffByOne(s, head);
            algCheckStmtList(s->body);
        } else if (s->type == NODE_IF) {
            algCheckStmtList(s->body);
            algCheckStmtList(s->elseBody);
        }
    }
}

static void algCheckFunc(ASTNode* fn) {
    checkReturnPaths(fn);
    checkDivisionGuards(fn);
    algCheckStmtList(fn->body);
}

/* ============================================================================
 * Public API
 * ==========================================================================*/

int flawCheck(ASTNode* program) {
    gFlaws = 0;
    gFixed = 0;

    for (ASTNode* it = program; it; it = it->next) {
        if (it->type == NODE_FUNC_DEF) {
            checkBody(it);
            algCheckFunc(it);
        } else if (it->type == NODE_CLASS_DEF) {
            for (ASTNode* m = it->members; m; m = m->next)
                if (m->type == NODE_METHOD_DEF) {
                    checkBody(m);
                    algCheckFunc(m);
                }
        }
    }

    if (gFlaws == 0) {
        printf("  No logical flaws detected.\n");
    } else {
        printf("\n  Summary: %d flaw(s) found", gFlaws);
        if (gFixed > 0)
            printf(", %d auto-corrected", gFixed);
        printf(".\n");
    }

    return gFlaws;
}

int flawsWereFixed(void) {
    return gFixed > 0;
}
