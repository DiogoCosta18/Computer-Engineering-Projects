#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"


int semantic_errors = 0;

struct symbol_list *symbol_table;


void check_varDecl(struct node *varspec, struct symbol_list *tabela){
    struct node *id = getchild(varspec, 1);
    enum type type = category_type(getchild(varspec,0)->category);

    if(id->token==NULL){ 
        //para corrigir o problema de multiplas vardecl 
        //ao fzr o addtype o id esta como terceiro filho e nao como segundo
        //e o type nao esta como primeiro mas sim como segundo
        id = getchild(varspec, 2);
        type = category_type(getchild(varspec,1)->category);
    }

    //Verificar se ja esxite na tabela local
    if(search_symbol(tabela, id->token) != NULL) {
        semantic_errors++;
        printf("Line %d, column %d: Symbol %s already defined\n", id->token_line, id->token_column,id->token);
        return;
    }

    
    //Se nao existe ainda,  inserre na tabela local
    insert_symbol(tabela, id->token, type, varspec,0,NULL,id,0);

}

void check_expr(struct node *expr,struct symbol_list *scope){
    struct node *expr1 = (struct node *) malloc(sizeof(struct node));
    struct node *expr2 = (struct node *) malloc(sizeof(struct node));
    struct node *id = (struct node *) malloc(sizeof(struct node));
    struct node *aux = (struct node *) malloc(sizeof(struct node));
    struct node_list *child = (struct node_list *) malloc(sizeof(struct node_list));
    struct node *child_node = (struct node *) malloc(sizeof(struct node));
    switch(expr->category){
        case Identifier:
            if((search_symbol(scope, expr->token) == NULL && search_symbol(symbol_table, expr->token) == NULL) ||(search_symbol(scope, expr->token) == NULL && (search_symbol(symbol_table, expr->token) != NULL && search_symbol(symbol_table, expr->token)->is_func==1 ))){
                //caso nao esteja declarado na tabela local nem na global 
                //caso esteja na global mas seja uma funcao
                semantic_errors++;
                printf("Line %d, column %d: Cannot find symbol %s\n", expr->token_line, expr->token_column, expr->token);
                expr->type=undef; //tem de ter este tipo por causa dos prints
            }else{
                //necessario verificar na local e na global antes de atribuir o type
                if(search_symbol(scope, expr->token)!=NULL){
                    expr->type = search_symbol(scope, expr->token)->type;
                    search_symbol(scope, expr->token)->is_used=1;
                }else if(search_symbol(symbol_table, expr->token)!=NULL){
                    expr->type = search_symbol(symbol_table, expr->token)->type;
                    search_symbol(symbol_table, expr->token)->is_used=1;
                } 
                expr->is_expr=1;
            }
            break;

        case Natural:
            expr->type=int_type;
            expr->is_expr=1;
            break;

        case Decimal:
            expr->type=float32_type;
            expr->is_expr=1;
            break;

        case Or:
        case And:
            expr1=getchild(expr,0);
            expr2=getchild(expr,1);
            check_expr(expr1,scope);
            check_expr(expr2,scope);

            if(expr1->type!=bool_type || expr2->type!=bool_type){
                semantic_errors++;
                printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n",expr->token_line, expr->token_column,operator_category(expr->category),type_name(expr1->type),type_name(expr2->type));
            }
            expr->type=bool_type;
            expr->is_expr=1;
            expr1->is_expr=1;
            expr2->is_expr=1;
            break;
        case Le:
        case Ge:
        case Lt: 
        case Gt:
            expr1=getchild(expr,0);
            expr2=getchild(expr,1);
            check_expr(expr1,scope);
            check_expr(expr2,scope);
            if(expr1->type!=expr2->type || !(expr1->type==int_type||expr1->type==float32_type)){
                semantic_errors++;
                printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n",expr->token_line, expr->token_column,operator_category(expr->category),type_name(expr1->type),type_name(expr2->type));
            }
            expr->type=bool_type;
            expr->is_expr=1;
            expr1->is_expr=1;
            expr2->is_expr=1;
            break;
        case Eq:
        case Ne:
            expr1=getchild(expr,0);
            expr2=getchild(expr,1);
            check_expr(expr1,scope);
            check_expr(expr2,scope);
            if(expr1->type!=expr2->type||expr1->type==no_type ||expr1->type==undef ){
                semantic_errors++;
                printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n",expr->token_line, expr->token_column,operator_category(expr->category),type_name(expr1->type),type_name(expr2->type));
            }
            expr->type=bool_type;
            expr->is_expr=1;
            expr1->is_expr=1;
            expr2->is_expr=1;
            
            break;
        case Add:
        case Sub:
        case Mul:
        case Div:
        case Mod:
            expr1=getchild(expr,0);
            expr2=getchild(expr,1);
            check_expr(expr1,scope);
            check_expr(expr2,scope);
            if((expr1->type!=expr2->type) || !(expr1->type==int_type||expr1->type==float32_type)){
                semantic_errors++;
                printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n",expr->token_line, expr->token_column,operator_category(expr->category),type_name(expr1->type),type_name(expr2->type));
                expr->type=undef;
            }else{
                expr->type=expr1->type;
                expr->is_expr=1;
                expr1->is_expr=1;
                expr2->is_expr=1;
            }
            break;
        case Not:
            expr1=getchild(expr,0);
            check_expr(expr1,scope);
            if(expr1->type!=bool_type){
                semantic_errors++;
                printf("Line %d, column %d: Operator ! cannot be applied to type %s\n",expr->token_line, expr->token_column,type_name(expr1->type));
            }
            expr->type=bool_type;
            expr->is_expr=1;
            expr1->is_expr=1;

            break;

        case Minus:
        case Plus:
            expr1=getchild(expr,0);
            check_expr(expr1,scope);
            if(expr1->type!=int_type && expr1->type!=float32_type){
                semantic_errors++;
                printf("Line %d, column %d: Operator %s cannot be applied to type %s\n",expr->token_line, expr->token_column,operator_category(expr->category),type_name(expr1->type));
                expr->type=undef;
                
            }else{
                expr->type=expr1->type;
                expr->is_expr=1;
                expr1->is_expr=1;
            }
            break;

        case Call:
            id=getchild(expr,0); 
            //char lista_types_call[256]="";
            char *lista_types_call = (char *)malloc(4096);
            

            //Cria um string com tds o stipos passados no call
            if (getchild(expr,1)!=NULL){ //verifica o primeiro expr
                check_expr(getchild(expr,1),scope);
                strcat(lista_types_call, type_name(getchild(expr,1)->type));
                if (getchild(expr,2)!=NULL){
                    aux=getchild(expr,2);
                    child = aux->children; //aux pode ter mais do que um filho expr
                    while ((child=child->next) != NULL) {
                        child_node = child->node;
                        check_expr(child_node,scope);
                        strcat(lista_types_call, ",");
                        strcat(lista_types_call, type_name(child_node->type));
                    }
                }
            }
    
            //Verifica se a funcao existe
            if(search_symbol(symbol_table, id->token) == NULL){
                semantic_errors++;
                printf("Line %d, column %d: Cannot find symbol %s(%s)\n", id->token_line, id->token_column, id->token,lista_types_call);
                expr->type=undef;
                id->type=undef;
            }else{ 
                //lista de tipos dos argumentos da funcao --> original
                char *lista_types=search_symbol(symbol_table, id->token)->lista_params;

                //Compara a string de tipos do Call com a original da funcao
                if(strcmp(lista_types_call,lista_types)!=0){
                    semantic_errors++;
                    printf("Line %d, column %d: Cannot find symbol %s(%s)\n", id->token_line, id->token_column, id->token,lista_types_call);
                    expr->type=undef;
                    id->type=undef;
                }else{
                    id->lista_tipos = malloc(strlen(lista_types_call) + 1);
                    if (id->lista_tipos != NULL) {
                        strcpy(id->lista_tipos, lista_types_call);
                    }
                    expr->type=search_symbol(symbol_table, id->token)->type;
                    expr->is_expr=1;
                    id->is_func=1;
                }
            }

            break;
              
        default:
            break;
    }   

}    

void check_statements(struct node *statement,struct symbol_list *scope){
    struct node *id = (struct node *) malloc(sizeof(struct node));
    struct node *expr = (struct node *) malloc(sizeof(struct node));
    struct node *aux = (struct node *) malloc(sizeof(struct node));
    struct node_list *child = (struct node_list *) malloc(sizeof(struct node_list));
    struct node *child_node = (struct node *) malloc(sizeof(struct node));

    switch(statement->category){
        case Assign:
            //TENHO DE REVER ESTE
            id = getchild(statement,0);
            expr = getchild(statement,1);

            check_expr(id,scope);
            check_expr(expr,scope);
       
            if((expr->type!=id->type) || (expr->type == undef) || (id->type == undef) || (id->type == no_type) || (expr->type == no_type)  ){
                semantic_errors++;
                printf("Line %d, column %d: Operator = cannot be applied to types %s, %s\n",statement->token_line, statement->token_column,type_name(id->type),type_name(expr->type));
            }
            statement->type=id->type;
            statement->is_expr=1;
            
            break;

        case If:
            id = getchild(statement,0);
            check_expr(id,scope);
            if(id->type!=bool_type){
                semantic_errors++;
                printf("Line %d, column %d: Incompatible type %s in if statement\n", id->token_line, id->token_column, type_name(expr->type));
            }
            check_statements(getchild(statement,1),scope); //primeiro block
            check_statements(getchild(statement,2),scope); //segundo block
            break;

        case For:
            if (getchild(statement,0)->category==Block){
                check_statements(getchild(statement,0),scope);
            }else{
                expr=getchild(statement,0);
                check_expr(expr,scope);
                if((expr->type!=bool_type && expr->type!=no_type)|| expr->type==undef){
                    semantic_errors++;
                    printf("Line %d, column %d: Incompatible type %s in for statement\n", expr->token_line, expr->token_column, type_name(expr->type));
                }
                check_statements(getchild(statement,1),scope);
            }
            break;

        case Block:
            if (getchild(statement,0)!=NULL){
                aux=getchild(statement,0);
                child = aux->children; //aux pode ter mais do que um filho expr
                while ((child=child->next) != NULL) {
                    child_node = child->node;
                    check_statements(child_node,scope);   
                }
            }
            break;
        case Return:
            expr=getchild(statement,0);
            if (expr!=NULL){
                check_expr(expr,scope);
                //verificar se o tipo da expressao e igual ao da funcao
                //ir ao no da funcao e tirar o type
                //scope->identifier --> vai buscar o no com este nome e dps a partir dele tiro o tipo
                if(search_symbol(scope, "return")->type != expr->type){
                    semantic_errors++;
                    printf("Line %d, column %d: Incompatible type %s in return statement\n",statement->token_line, expr->token_column,type_name(expr->type));
                }
            }else{ //pode nao ter expr por isso o type tem de ser no_type
                if(search_symbol(scope, "return")->type != no_type){
                    semantic_errors++;
                    printf("Line %d, column %d: Incompatible type void in return statement\n",statement->token_line, statement->token_column);
                }
            }
            break;

        case Call:
            check_expr(statement,scope);
            break;

        case ParseArgs:
            //IMPORTANTE: id tem de ser int e expr tem de ser int ou string
            id=getchild(statement,0);
            expr=getchild(statement,1);
            check_expr(id,scope);
            check_expr(expr,scope);
            if((id->type!=int_type)||(expr->type!=int_type && expr->type!=string_type)){
                if(expr->type==no_type){expr->type=undef;}
                semantic_errors++;
                printf("Line %d, column %d: Operator strconv.Atoi cannot be applied to types %s, %s\n",statement->token_line, statement->token_column,type_name(id->type),type_name(expr->type));
            }else{
                statement->type=expr->type;
                statement->is_expr=1;
            }
            break;

        case Print:
            //print nao precisa de imprimir o tipo
            if (getchild(statement,0)->category==StrLit){
                getchild(statement,0)->type=string_type;
            }else{
                expr=getchild(statement,0);
                check_expr(expr,scope);
                if((expr->type==no_type) || (expr->type==undef)){
                    semantic_errors++;
                    printf("Line %d, column %d: Incompatible type undef in fmt.Println statement\n",expr->token_line, expr->token_column);      
                }
                statement->is_expr=1;
            }
            
            break;

        default:
            break;
    }
}


void check_funcBody(struct node *funcBody,struct symbol_list *scope){
    struct node_list *child = funcBody->children;
    while ((child=child->next) != NULL) {
        struct node *child_node = child->node;
        //Nos aux
        if(child_node->category==aux){
            check_funcBody(child_node,scope);
        }
        // varDecl
        else if (child_node->category == VarDecl) {
            check_varDecl(child_node, scope); 
        }
        //Statements
        else{
            check_statements(child_node,scope);
        }   
    }
}






void check_funcParams(struct node *funcParams,struct symbol_list *scope,char *string_params){
    //FuncParams e o parameters da gramatica so podem ser chamadis pelo funcHeader
    //tem de ser guardados na tabela global os types 
    // na tabela da funcao tem de ficar os ids e os types

    //vai buscar todos os types dos parametros e junta-os numa string
    //vai ao funcParams e dentro dele percorre todos os nos ParamDecl para tirar o type
    
    struct node_list *paramDecl= funcParams->children;
    while((paramDecl=paramDecl->next)!=NULL){
        struct node *paramDecl_node = paramDecl->node;

        if(paramDecl_node->category==aux){
            check_funcParams(paramDecl_node,scope,string_params);
        } else{
            struct node *id = getchild(paramDecl_node,1);
            enum type type = category_type(getchild(paramDecl_node,0)->category);
            strcat(string_params, type_name(type));

            if(search_symbol(scope, id->token) == NULL ){
                insert_symbol(scope, id->token, type, paramDecl_node,0,NULL,NULL,1);
                paramDecl_node->is_param=1;
            } else {
                semantic_errors++;
                printf("Line %d, column %d: Symbol %s already defined\n", id->token_line, id->token_column,id->token);
            }
        }

        if (paramDecl->next != NULL) {
            strcat(string_params, ",");
        }
    }

}



void check_funcDecl(struct node *funcdecl){
    struct node *funcHeader = getchild(funcdecl,0);
    struct node *funcBody = getchild(funcdecl,1);

    struct node *id = getchild(funcHeader, 0);
    enum type type = category_type(getchild(funcHeader,1)->category);

    //Verifica se ja existe alguma funcao com o mesmo nome
    if(search_symbol(symbol_table, id->token) != NULL) {
        semantic_errors++;
        printf("Line %d, column %d: Symbol %s already defined\n", id->token_line, id->token_column,id->token);
        return;
    }

    //Cria uma nova tabela para a funcao e adiciona como filha da global
    struct symbol_list *scope = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    scope->identifier = strdup(id->token);
    scope->next = NULL;
    scope->children = NULL;
    scope->is_func = 1;
    scope->lista_params = NULL;
    scope->FuncBody=funcBody;
    scope->not_used_id=id;
    scope->is_used=1;


    insert_symbol(scope,"return",type,funcdecl,0,NULL,NULL,1); //martelar o return para cada tabela de cada funcao


    //verificar o funcParams
    //char string_params[256]="";
    char *string_params = (char *)malloc(4096);
    if(type==no_type){ //tive de adicionar isto pq quando nao ha type na funcao o nº do child muda
        check_funcParams(getchild(funcHeader,1),scope,string_params);
    }else{
        check_funcParams(getchild(funcHeader,2),scope,string_params);
    }
    
    scope->lista_params = strdup(string_params);


    //Insere a funcao na tabela global
    insert_symbol(symbol_table, id->token, type, funcdecl,1,string_params,NULL,1);




    if(symbol_table->children == NULL) {
        symbol_table->children = scope;
    } else {
        struct symbol_list *child = symbol_table->children;
        while(child->children != NULL){
            child = child->children;
        }
        child->children = scope;
    }
    

}



// semantic analysis begins here, with the AST root node
int check_program(struct node *program, int flag_n_recursao) {
    if(symbol_table==NULL){
        symbol_table = (struct symbol_list *) malloc(sizeof(struct symbol_list));
        symbol_table->next = NULL;
        symbol_table->identifier=strdup("Global");
        symbol_table->is_func=1;
        symbol_table->lista_params=NULL;
        symbol_table->children=NULL;
        symbol_table->FuncBody=NULL;
        symbol_table->node=program;
        symbol_table->not_used_id=NULL;
    }

    //Percorrer a AST da primeira vez 
    struct node_list *child = program->children;
    while((child = child->next) != NULL){
        if(child->node->category==VarDecl){
            check_varDecl(child->node,symbol_table);
        }else if(child->node->category==FuncDecl){
            check_funcDecl(child->node);
        }else if(child->node->category==aux){
            check_program(child->node,0);
        }
    }
    //Percorrer a AST para o funcBody
    if (flag_n_recursao==1) {
        check_program3(symbol_table);
        check_simbolos_usados(symbol_table);
    }
    
    

    return semantic_errors;
}


void check_program3(struct symbol_list *tabela){
    if(tabela->is_func==1 && tabela->FuncBody!=NULL){
       //printf("CHECK: %s\n",tabela->identifier);
        //printf("%s:%s\n",tabela->identifier,tabela->FuncBody->token);
        check_funcBody(tabela->FuncBody,tabela);
    }
    struct symbol_list *scope=tabela->children;
    while(scope != NULL) {
        check_program3(scope);
        scope = scope->next;
    }

}


// insert a new symbol in the list, unless it is already there
struct symbol_list *insert_symbol(struct symbol_list *table, char *identifier, enum type type, struct node *node,int is_func,char *lista_params,struct node *id,int is_used) {
    struct symbol_list *new = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    new->identifier = strdup(identifier);
    new->type = type;
    new->node = node;
    new->next = NULL;
    new->is_func=is_func;
    new->children=NULL;
    new->not_used_id=id;
    new->is_used=is_used;
    if (lista_params == NULL) {
        new->lista_params = strdup("");
    } else {
        new->lista_params = strdup(lista_params);
    }
    struct symbol_list *symbol = table;
    while(symbol != NULL) {
        if(symbol->next == NULL) {
            symbol->next = new;    /* insert new symbol at the tail of the list */
            break;
        } else if(strcmp(symbol->next->identifier, identifier) == 0) {
            free(new);
            return NULL;           /* return NULL if symbol is already inserted */
        }
        symbol = symbol->next;
    }
    return new;
}

// look up a symbol by its identifier
struct symbol_list *search_symbol(struct symbol_list *table, char *identifier) {
    struct symbol_list *symbol;
    for(symbol = table->next; symbol != NULL; symbol = symbol->next)
        if(strcmp(symbol->identifier, identifier) == 0)
            return symbol;
    return NULL;
}

void show_symbol_table(struct symbol_list *tabela) {
    if(tabela->is_func==1){
        if(strcmp(tabela->identifier,"Global")==0){
            printf("===== %s Symbol Table =====\n",tabela->identifier);
        } else{
            printf("===== Function %s(%s) Symbol Table =====\n",tabela->identifier,tabela->lista_params);
        }

        struct symbol_list *symbol;
        for(symbol = tabela->next; symbol != NULL; symbol = symbol->next){
            if (symbol->is_func) {
                printf("%s\t(%s)\t%s\n", symbol->identifier, symbol->lista_params, type_name(symbol->type));
            }else if(symbol->node->is_param==1){
                printf("%s\t%s\t%s\tparam\n", symbol->identifier, symbol->lista_params,type_name(symbol->type));
            } else {
                printf("%s\t%s\t%s\n", symbol->identifier, symbol->lista_params,type_name(symbol->type));
            }
        }
        printf("\n");
    }
    struct symbol_list *child = tabela->children;
    while(child != NULL) {
        show_symbol_table(child);
        child = child->next;
    }

}


void check_simbolos_usados(struct symbol_list *tabela){
    //Variaveis globais podem nao ser usadas
    if(tabela->is_func==1 && strcmp(tabela->identifier,"Global")!=0){
        struct symbol_list *symbol;
        for(symbol = tabela->next; symbol != NULL; symbol = symbol->next){
            if(symbol->is_used==0 && symbol->node->is_param==0){ 
                struct node *id= symbol->not_used_id;
                if(id!=NULL){
                    semantic_errors++;
                    printf("Line %d, column %d: Symbol %s declared but never used\n",id->token_line, id->token_column, id->token);
                    symbol->is_used=1;
                }
            }
        }

    }
    
    struct symbol_list *child = tabela->children;
    while(child != NULL) {
        check_simbolos_usados(child);
        child = child->next;
    }


}




