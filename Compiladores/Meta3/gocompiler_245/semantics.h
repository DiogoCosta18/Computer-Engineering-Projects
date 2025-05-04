#ifndef _SEMANTICS_H
#define _SEMANTICS_H

#include "ast.h"


struct symbol_list {
	char *identifier;				//nome da variavel ou funcao
	enum type type;
	struct node *node;
	struct symbol_list *next;
	struct symbol_list *children;	//lista de tabelas de cada funcao declarada, ficam todas como filhas da global
	int is_func;				//flag para verificar se e uma funcao para depois dar um print diferente
	char *lista_params;				//guarda os tipos dos parametros da funcao
	int is_used;					//flagf para saber se um simbolo foi usado
	struct node *FuncBody;
	struct node *not_used_id;
	

};


struct symbol_list *search_symbol(struct symbol_list *symbol_table, char *identifier);
void show_symbol_table(struct symbol_list *tabela);

int check_program(struct node *program,int flag_n_recursao);
void check_funcDecl(struct node *funcdecl);
void check_funcParams(struct node *funcParams,struct symbol_list *scope,char *string_params);
void check_funcBody(struct node *funcBody,struct symbol_list *scope);
void check_expr(struct node *expr,struct symbol_list *scope);
void check_statements(struct node *statement,struct symbol_list *scope);
void check_varDecl(struct node *varspec, struct symbol_list *tabela);
void check_program3(struct symbol_list *tabela);
void check_simbolos_usados(struct symbol_list *tabela);

struct symbol_list *insert_symbol(struct symbol_list *table, char *identifier, enum type type, struct node *node,int is_func,char *lista_params,struct node *id,int is_used);



#endif
