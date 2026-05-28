#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

/* MIPS CODE GENERATOR
 * Translates the AST directly into MIPS assembly.
 * Reads the symbol table (symtab.h) for variable offsets.
 *
 * Calling convention used:
 *   Arguments  : $a0–$a3 (max 4)
 *   Return val : $v0
 *   Saved $ra  : top of each function's stack frame
 *   Temporaries: $t0–$t7 (reset at each statement boundary)
 */

/* Top-level entry point — generates the full .s file */
void generateMIPS(ASTNode* root, const char* filename);

/* Statement-level generation (recursive) */
void genStmt(ASTNode* node);

/* Function call generation — evaluates args, moves to $a0-$a3, jal */
void genFuncCall(ASTNode* node);

#endif /* CODEGEN_H */