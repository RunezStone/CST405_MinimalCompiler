/* MINIMAL C COMPILER - EDUCATIONAL VERSION
 * Demonstrates all phases of compilation with a simple language
 * Supports: int variables, addition, assignment, print, functions
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"
#include "tac.h"
#include "semantic.h"

extern int yyparse();
extern FILE* yyin;
extern ASTNode* root;

/* Global flag to enable token display in lexer */
int displayTokens = 1;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input.c> <output.s>\n", argv[0]);
        printf("Example: ./minicompiler test.c output.s\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", argv[1]);
        return 1;
    }

    clock_t _tStart = clock();   /* whole-compilation timer */

    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║          MINIMAL C COMPILER - EDUCATIONAL VERSION          ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");

    /* ── PHASE 1: Lexical and Syntax Analysis ── */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 1: LEXICAL & SYNTAX ANALYSIS                       │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ • Reading source file: %-35s│\n", argv[1]);
    printf("│ • Tokenizing input (scanner.l)                           │\n");
    printf("│ • Parsing grammar rules (parser.y)                       │\n");
    printf("│ • Building Abstract Syntax Tree                          │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    printf("\nTokens recognized:\n");

    if (yyparse() != 0) {
        printf("\n✗ Parse failed - check your syntax!\n");
        printf("Common errors:\n");
        printf("  • Missing semicolons after statements\n");
        printf("  • Missing 'end null;' or 'end <var>;' at end of func/Program_Start\n");
        printf("  • Undeclared variables\n");
        printf("  • Functions must be declared before Program_Start()\n");
        fclose(yyin);
        return 1;
    }

    printf("\n✓ Parse successful - program is syntactically correct!\n\n");

    /* ── PHASE 2: AST Display ── */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 2: ABSTRACT SYNTAX TREE (AST)                      │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Tree structure representing the program hierarchy:        │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    printAST(root, 0);
    printf("\n");

    /* ── PHASE 3: Semantic Analysis ── */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 3: SEMANTIC ANALYSIS                               │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Checking semantic correctness:                           │\n");
    printf("│ • Variables declared before use                          │\n");
    printf("│ • No duplicate declarations                              │\n");
    printf("│ • Functions defined before Program_Start()               │\n");
    printf("│ • Argument counts match parameter counts                 │\n");
    printf("│ • Return variables declared inside their function        │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");

    initSemantic();
    /* UPDATED: was analyzeProgram(root) — now performSemanticAnalysis(root) */
    if (performSemanticAnalysis(root) != 0) {
        printSemanticSummary();
        printf("\n✗ Compilation failed due to semantic errors!\n");
        fclose(yyin);
        return 1;
    }
    printSemanticSummary();
    printf("\n");

    /* ── PHASE 4: Intermediate Code Generation ── */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 4: INTERMEDIATE CODE GENERATION                    │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Three-Address Code (TAC) - simplified instructions:       │\n");
    printf("│ • Each instruction has at most 3 operands                │\n");
    printf("│ • Temporary variables (t0, t1, ...) for expressions      │\n");
    printf("│ • FUNC_BEGIN/END, PARAM, ARG, CALL, RETURN for functions │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");

    initTAC();
    generateTAC(root);
    printTAC();

    char tacFile[256];
    sprintf(tacFile, "%s.tac", argv[1]);
    saveTACToFile(tacFile);
    saveTACToFile("tac_unopt.txt");   /* handout-named deliverable */
    printf("✓ TAC saved to: %s (and tac_unopt.txt)\n\n", tacFile);

    /* ── PHASE 5: Optimization ── */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 5: CODE OPTIMIZATION                               │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Applying optimizations:                                  │\n");
    printf("│ • Constant folding (evaluate compile-time expressions)   │\n");
    printf("│ • Copy propagation (replace variables with values)       │\n");
    printf("│ • Dead code elimination                                  │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");

    clock_t _tOptStart = clock();
    optimizeTAC();
    clock_t _tOptEnd = clock();
    printOptimizedTAC();
    allocateRegistersForTAC();

    char optTacFile[256];
    sprintf(optTacFile, "%s.opt.tac", argv[1]);
    saveOptimizedTACToFile(optTacFile);
    saveOptimizedTACToFile("tac_opt.txt");   /* handout-named deliverable */
    printf("✓ Optimized TAC saved to: %s (and tac_opt.txt)\n\n", optTacFile);

    /* ── PHASE 6: MIPS Code Generation ── */
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 6: MIPS CODE GENERATION                            │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ Translating to MIPS assembly:                            │\n");
    printf("│ • Variables stored on stack per function frame           │\n");
    printf("│ • Using $t0-$t7 for temporary values                     │\n");
    printf("│ • $a0-$a3 for function arguments, $v0 for return value   │\n");
    printf("│ • System calls for print operations                      │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");

    generateMIPS(root, argv[2]);
    printf("✓ MIPS assembly generated: %s\n\n", argv[2]);

    /* ── Count real MIPS instructions in the generated .s ──
     * Skip blank lines, comments (#), directives (.), and labels (ending ':') */
    int mipsCount = 0;
    FILE* sf = fopen(argv[2], "r");
    if (sf) {
        char line[512];
        while (fgets(line, sizeof(line), sf)) {
            char* p = line;
            while (*p == ' ' || *p == '\t') p++;
            if (*p == '\0' || *p == '\n' || *p == '#' || *p == '.') continue;
            /* label line? (single token ending in ':') */
            char* colon = strchr(p, ':');
            char* space = strpbrk(p, " \t");
            if (colon && (!space || colon < space)) continue;
            mipsCount++;
        }
        fclose(sf);
    }

    /* ── PHASE 7: Performance Report ── */
    double optMs   = ((double)(_tOptEnd  - _tOptStart) / CLOCKS_PER_SEC) * 1000.0;
    double totalMs = ((double)(clock()   - _tStart)    / CLOCKS_PER_SEC) * 1000.0;
    double unoptMs = totalMs - optMs;          /* time without the optimizer */
    if (unoptMs < 0) unoptMs = 0;
    generatePerformanceReport(argv[1], mipsCount, unoptMs, totalMs);

    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                  COMPILATION SUCCESSFUL!                   ║\n");
    printf("║         Run the output file in a MIPS simulator           ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");

    fclose(yyin);
    return 0;
}