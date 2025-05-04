#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"


// create a node of a given category with a given lexical symbol
struct node *newnode(enum category category, char *token) {
    struct node *new = malloc(sizeof(struct node));
    new->category = category;
    new->token = token;
    new->type = no_type;
    new->children = malloc(sizeof(struct node_list));
    new->children->node = NULL;
    new->children->next = NULL;
    return new;
}

// append a node to the list of children of the parent node
void addchild(struct node *parent, struct node *child) {
    struct node_list *new = malloc(sizeof(struct node_list));
    new->node = child;
    new->next = NULL;
    struct node_list *children = parent->children;
    while(children->next != NULL)
        children = children->next;
    children->next = new;
}


// get a pointer to a specific child, numbered 0, 1, 2, ...
struct node *getchild(struct node *parent, int position) {
    struct node_list *children = parent->children;
    while((children = children->next) != NULL)
        if(position-- == 0)
            return children->node;
    return NULL;
}

// count the children of a node
int countchildren(struct node *node) {
    int i = 0;
    while(getchild(node, i) != NULL)
        i++;
    return i;
}

int countblocks(struct node *node) {
    int count = 0;
    struct node_list *child = node->children;
    while((child = child->next) != NULL){
        if(child->node->category != aux){
            count++;
        }
        else{//quando o no e aux temos de contar os filhos dele
            count += countblocks(child->node);
        }
    }
    return count;
}


//o objetivo e percorrer tds os nos vardecl q sao filhos de aux, adicionar-lhes o type e meter o tipo antes do id
// cria-se um novo no type com a categoria do $3
// vai-se buscara o token do id 
//cria-se um novo no id com esse token
// troca-se a categoria do primeiro no id para aux que assim ja n e impresso e cm se tivesse sido eliminado
void addType(struct node *parent, struct node *child){ 
    struct node_list *var_decl = parent->children->next;
    while(var_decl != NULL){
        struct node *new_type_node = newnode(child->category,NULL); 

        struct node *current_id_node = var_decl->node->children->next->node;
        struct node *new_id_node = newnode(Identifier,current_id_node->token);

        //Tenho de passar o numero da linha para a meta 3 
        new_id_node->token_line=current_id_node->token_line;
        new_id_node->token_column=current_id_node->token_column;

        addchild(var_decl->node,new_type_node);
        addchild(var_decl->node,new_id_node);

        var_decl->node->children->next->node->category=aux;

        var_decl = var_decl->next;
    }

}

char *category_name[] = names;//ver .h
//funcao para mostrar a AST

void show(struct node *node, int depth) {
    int i;
    if(strcmp(category_name[node->category], "aux") == 0){
        depth --; //se nao tirar vai imprimir como o umero errado de tracos
    }else{
        for(i = 0; i < depth; i++)
            printf("..");
        if(node->token == NULL)
            printf("%s\n", category_name[node->category]);
        else
            printf("%s(%s)\n", category_name[node->category], node->token);
    }
    
    struct node_list *child = node->children;
    while((child = child->next) != NULL)
        show(child->node, depth+1);
}

void show_anotated(struct node *node, int depth) {
    int i;
    if(strcmp(category_name[node->category], "aux") == 0){
        depth --; //se nao tirar vai imprimir como o umero errado de tracos
    }else{
        for(i = 0; i < depth; i++)
            printf("..");
        if(node->token == NULL)
            printf("%s", category_name[node->category]);
        else
            printf("%s(%s)", category_name[node->category], node->token);


        if(node->type!=no_type){
            if(node->is_expr){
                if (node->is_func ) {
                    printf(" - (%s)", node->lista_tipos); 
                }else{
                    printf(" - %s", type_name(node->type));
                }
            }else if(node->is_func) {
                printf(" - (%s)", node->lista_tipos); 
            }
        }else if (node->is_func ) {
                printf(" - (%s)", node->lista_tipos); 
        }
        if(!node->is_expr && !node->is_expr && node->type!=no_type){
            printf(" - %s", type_name(node->type));
        }
        

        printf("\n");
    }
    
    struct node_list *child = node->children;
    while((child = child->next) != NULL)
        show_anotated(child->node, depth+1);
}



void free_ast (struct node * cur_node){
    if(cur_node == NULL){
        return;
    }

    struct node_list *child = cur_node->children;
    while(child != NULL){
        struct node_list *next = child->next;
        
        if(child->node != NULL){
            free_ast(child->node);
        }
        free(child);
        child = next;
    }
    if(cur_node->token != NULL){
        free(cur_node->token);
        cur_node->token = NULL;
    }
    free(cur_node);
}

void deallocate(struct node *node) {
    if(node != NULL) {
        struct node_list *child = node->children;
        while(child != NULL) {
            deallocate(child->node);
            struct node_list *tmp = child;
            child = child->next;
            free(tmp);
        }
        if(node->token != NULL)
            free(node->token);
        free(node);
    }
}

