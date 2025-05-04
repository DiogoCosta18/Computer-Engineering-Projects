#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "ast.h"


void codegen_program(struct node *program, int flag_n_recursao);
void codegen_funcDecl(struct node *funcdecl);
void codegen_funcParams(struct node *funcParams);

const char* tipo_codificado(enum type type);
void print_main();
const char* tipo_inicial(enum type type);
void codegen_funcBody(struct node *funcBody);
void codegen_varDecl(struct node *varspec);
void codegen_statements(struct node *statement);
int codegen_expr(struct node *expr);
int codegen_operation(struct node *expr, const char *op);
int codegen_not(struct node *expr);
int codegen_minus(struct node *expr);
int codegen_plus(struct node *expr);
int codegen_call(struct node *expr);
void diferentes_prints(enum type type, int tmp);
int codegen_operation2(struct node *expr, const char *op,const char *op2);

char* escape_sequences(const char* input, int* final_len);
#endif