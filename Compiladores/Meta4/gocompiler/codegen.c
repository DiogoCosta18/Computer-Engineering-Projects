#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"
#include "codegen.h"

int temporary;
int flag_return;

extern struct symbol_list *symbol_table;


const char* tipo_codificado(enum type type){
    switch (type){
    case int_type:
        return "i32";
    case bool_type:
        return "i1";
    case float32_type:
        return "double";
    case string_type:
        return "i8*";
    default:
        return "void";
    }
} 

const char* tipo_inicial(enum type type){
    switch (type){
    case int_type:
        return "0";
    case bool_type:
        return "0"; //inicializado a falso
    case float32_type:
        return "0.0";
   // case string_type:  --> nao sei fazer
        //return "";
    default:
        return "void";
    }
}

char* escape_sequences(const char* str, int* tamanho_final) {
    //DISCLAIMER: Funcao gerada pelo ChatGPT
    int tamanho_str = strlen(str);
    char* nova_str = malloc(tamanho_str * 2); //duplicar pq cada caracter das escape sequences vai ser codificado com dois caracteres
    int j = 0; //indice da nova string
    int novo_tamanho = 0; //contador tamanho final para a string
    
    for(int i = 0; i < tamanho_str; i++) {
        if(str[i] == '\\') {
            i++;
            switch(str[i]) {
                case 'n':
                    nova_str[j++] = '\\';
                    nova_str[j++] = '0';
                    nova_str[j++] = 'A';
                    novo_tamanho++;
                    break;
                case 'r':
                    nova_str[j++] = '\\';
                    nova_str[j++] = '0';
                    nova_str[j++] = 'D';
                    novo_tamanho++;
                    break;
                case '\\':
                    nova_str[j++] = '\\';
                    nova_str[j++] = '5';
                    nova_str[j++] = 'C';
                    novo_tamanho++;
                    break;
                case 't':
                    nova_str[j++] = '\\';
                    nova_str[j++] = '0';
                    nova_str[j++] = '9';
                    novo_tamanho++;
                    break;
                case '"':
                    nova_str[j++] = '\\';
                    nova_str[j++] = '2';
                    nova_str[j++] = '2';
                    novo_tamanho++;
                    break;
                case 'f':
                    nova_str[j++] = '\\';
                    nova_str[j++] = '0';
                    nova_str[j++] = 'C';
                    novo_tamanho++;
                    break;
                default:
                    nova_str[j++] = str[i];
                    novo_tamanho++;
            }
        } else {
            nova_str[j++] = str[i];
            novo_tamanho++;
        }
    }
    nova_str[j] = '\0';
    *tamanho_final = novo_tamanho;
    return nova_str;
}

void codegen_program(struct node *program, int flag_n_recursao) {

    if (program==NULL){
        return;
    }
    if(flag_n_recursao==1){
        //funcoes de print
        //DISCLAIMER: estas funcoes de print foram geradas pelo ChatGPT
        printf(
            "@.str_int = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n"
            "@.str_float = private unnamed_addr constant [7 x i8] c\"%%.08F\\0A\\00\"\n"
            "@.str_true = private unnamed_addr constant [6 x i8] c\"true\\0A\\00\"\n"
            "@.str_false = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\"\n"
            "@.str_string = private unnamed_addr constant [4 x i8] c\"%%s\\0A\\00\"\n"
            "@.empty_str = private unnamed_addr constant [1 x i8] c\"\\00\"\n\n"
            "declare i32 @atoi(i8*)\n"
            "declare i32 @printf(i8*, ...)\n"
            "@logic_result = global i1 false\n\n"
            "\n\n"
        );
    }
    
    // generate the code for each function
    struct node_list *child = program->children;
    while((child = child->next) != NULL){
        if(child->node->category==VarDecl){
            codegen_varDecl(child->node);
        }else if(child->node->category==FuncDecl){
            codegen_funcDecl(child->node);
        }else if(child->node->category==aux){
            codegen_program(child->node,0);
        }
    }

    if(flag_n_recursao==1){
        print_main();
    }
 

}

void print_main(){
    struct symbol_list *entry = search_symbol(symbol_table, "main");
    if(entry != NULL && entry->node->category == FuncDecl){

        struct node *funcHeader = getchild(entry->node,0);
        enum type type = category_type(getchild(funcHeader,1)->category);

        //printf("define i32 @main() {\n");
        printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");

        if(type==no_type){//void
            //falta ver para casos em que main tenha parametros de entrada
            //printf("  call void @_main()\n");
            printf("  call void @_main(i32 %%argc, i8** %%argv)\n");
            printf("  ret i32 0\n"); // Retorna 0 como sucesso
        }else{
            printf("  %%1 = call %s @_main(i32 %%argc, i8** %%argv)\n", tipo_codificado(type));
            printf("  ret %s %%1\n",  tipo_codificado(type));
        }
        printf("}\n");

    }
}


void codegen_varDecl(struct node *varspec){
    struct node *id = getchild(varspec, 1);
    enum type type = category_type(getchild(varspec,0)->category);
    if(id->token==NULL){ 
        id = getchild(varspec, 2);
        type = category_type(getchild(varspec,1)->category);
    }
    if (search_symbol(symbol_table,id->token)!=NULL) {
        // Variável global
        printf("@%s = global %s %s\n", id->token, tipo_codificado(type),tipo_inicial(type));
    } else {
        // Variável local
        printf("  %%%s = alloca %s\n", id->token, tipo_codificado(type));
        //printf("  store %s 0, %s* %%%s\n",tipo_codificado(type),tipo_codificado(type), id->token);
    }
}


void codegen_funcDecl(struct node *funcdecl) {
    struct node *funcHeader = getchild(funcdecl,0);
    struct node *funcBody = getchild(funcdecl,1);
    struct node *id = getchild(funcHeader, 0);
    enum type type = category_type(getchild(funcHeader,1)->category);
    temporary = 1;
    flag_return = 0;//nao tem no return

    if(strcmp(id->token,"main")==0){
        printf("define void @_main(i32 %%argc, i8** %%argv");
    }else{
        printf("define %s @_%s(", tipo_codificado(type), id->token);
    }
    
    if(type==no_type){
        codegen_funcParams(getchild(funcHeader,1));
        printf(") {\n");
        codegen_funcBody(funcBody);
        if(flag_return==0){
            printf("  ret void\n");
        }
    }else{
        codegen_funcParams(getchild(funcHeader,2));
        printf(") {\n");
        codegen_funcBody(funcBody);
        if(flag_return==0){
            printf("  ret %s %s\n", tipo_codificado(type),tipo_inicial(type)); 
        }
    }
    printf("}\n\n");
}

void codegen_funcParams(struct node *funcParams) {
    struct node_list *paramDecl= funcParams->children;
    while((paramDecl=paramDecl->next)!=NULL){
        struct node *paramDecl_node = paramDecl->node;
        if(paramDecl_node->category==aux){
            codegen_funcParams(paramDecl_node);
        } else{
            struct node *id = getchild(paramDecl_node,1);
            enum type type = category_type(getchild(paramDecl_node,0)->category);
            printf("%s %%%s",tipo_codificado(type), id->token);
        }

        if (paramDecl->next != NULL) {
            printf(", ");
        }
    }

}

void codegen_funcBody(struct node *funcBody){
    struct node_list *child = funcBody->children;
    while ((child=child->next) != NULL) {
        struct node *child_node = child->node;
        //Nos aux
        if(child_node->category==aux){
            codegen_funcBody(child_node);
        }
        // varDecl
        else if (child_node->category == VarDecl) {
            codegen_varDecl(child_node); 
        }
        //Statements
        else{
            codegen_statements(child_node);
        }   
    }
}

void codegen_statements(struct node *statement){
    struct node *id = (struct node *) malloc(sizeof(struct node));
    struct node *expr = (struct node *) malloc(sizeof(struct node));
    struct node *aux = (struct node *) malloc(sizeof(struct node));
    struct node_list *child = (struct node_list *) malloc(sizeof(struct node_list));
    struct node *child_node = (struct node *) malloc(sizeof(struct node));
    int label_id=0;
    switch(statement->category){
        case Assign:
        //verificar se e global ou local, tratar ambas com load mas uma com @ e outra com %%
            id = getchild(statement,0);
            expr = getchild(statement,1);
            int tmp=codegen_expr(expr);
            
            if(search_symbol(symbol_table,id->token)!=NULL){ //global
                printf("  store %s %%%d, %s* @%s\n",tipo_codificado(expr->type),tmp,tipo_codificado(id->type), id->token);
            }else{
                printf("  store %s %%%d, %s* %%%s\n",tipo_codificado(expr->type),tmp,tipo_codificado(id->type), id->token);
            }
            
            //printf("%d",search_symbol(symbol_table,id->token)->node->is_param);
            //printf("  store %s %%%d, %s* %%%s\n",tipo_codificado(expr->type),tmp,tipo_codificado(id->type), id->token);
            break;
        case If:
            label_id=temporary++;
            printf("  %%%d = alloca i32\n", label_id);
            id = getchild(statement,0);
            int e = codegen_expr(id);
            printf("  %%%d = icmp ne %s %%%d, 0\n", temporary,tipo_codificado(id->type), e);
            printf("  br i1 %%%d, label %%L%dthen, label %%L%delse\n", temporary++, label_id, label_id);


            printf("L%dthen:\n", label_id);
            codegen_statements(getchild(statement,1)); //primeiro block
            printf("  br label %%L%dend\n", label_id);


            printf("L%delse:\n", label_id);
            codegen_statements(getchild(statement,2)); //segundo block
            printf("  br label %%L%dend\n", label_id);  
            printf("L%dend:\n", label_id);
            printf("  %%%d = load i32, i32* %%%d\n", temporary, label_id);
            temporary++;
            break;
        case For:
            expr=getchild(statement,0);
            label_id=temporary++;
            
            printf("  %%%d = alloca i32\n", label_id);
            printf("  store i32 0, i32* %%%d\n", label_id); //contador do loop para saber qnd parar colocado a 0
            printf("  br label %%L%dfor_cond\n", label_id);

            //loop enqt a expressao n for falsa --> label de loop
            printf("L%dfor_cond:\n", label_id);
            
            if (expr->category==Block){
                //n tem expr de cond ent vai diretamente para o label do body
                printf("  br label %%L%dbody\n", label_id);
                printf("L%dbody:\n", label_id);
                codegen_statements(expr);
                printf("  br label %%L%dfor_cond\n", label_id);
            }else{
               
                //label de condicao
                int e = codegen_expr(expr);
                printf("  %%%d = icmp ne %s %%%d, 0\n", temporary,tipo_codificado(expr->type), e);
                printf("  br i1 %%%d, label %%L%dbody, label %%L%dend\n", temporary++, label_id, label_id);

                //label body
                printf("L%dbody:\n", label_id);
                codegen_statements(getchild(statement,1));
                printf("  br label %%L%dfor_cond\n", label_id); 

            }


            printf("L%dend:\n", label_id);
            printf("  %%%d = load i32, i32* %%%d\n", temporary, label_id);
            temporary++;
            break;
        case Block:
            if (getchild(statement,0)!=NULL){
                aux=getchild(statement,0);
                child = aux->children; //aux pode ter mais do que um filho expr
                while ((child=child->next) != NULL) {
                    child_node = child->node;
                    codegen_statements(child_node);  
                }
            }
            break;
        case Return:
            flag_return=1; //tem return
            expr=getchild(statement,0);
            if (expr != NULL) {
                int result = codegen_expr(expr);
                printf("  ret %s %%%d\n", tipo_codificado(expr->type) ,result);
            } else {
                printf("  ret void\n");
            }
            break;
        case Call:
            codegen_expr(statement);
            break;
        case ParseArgs:
            id=getchild(statement,0);
            expr=getchild(statement,1);

            //n preciso de fzr codegen do id
            int expr_tmp=codegen_expr(expr);

            //valor do CMDARGS
            int args_tmp = temporary++;
            printf("  %%%d = getelementptr i8*, i8** %%argv, i32 %%%d\n", args_tmp, expr_tmp);
            int loaded_arg = temporary++;
            printf("  %%%d = load i8*, i8** %%%d\n", loaded_arg, args_tmp);
            
            
            //temos de converter para int
            printf("  %%%d = call i32 @atoi(i8* %%%d)\n", temporary, loaded_arg);
            
            //guarda o resultado no id
            if(search_symbol(symbol_table,id->token)!=NULL){ //global
                printf("  store i32 %%%d, i32* @%s\n",temporary, id->token);
            }else{
                printf("  store i32 %%%d, i32* %%%s\n",temporary, id->token);
            }
            temporary++;
            break;
        case Print:
            expr=getchild(statement,0);
            if (expr->category==StrLit){
                //Imprimir apenas a partir do len+1 e ate ao len-2 pq as aspas n sao para imprimir
                //tenho de lidar com as escape sequences n faz sentido imprimir \n 
                
                //
                char *str = strdup(expr->token + 1);
                str[strlen(str) - 1] = '\0';
                
                //troca as escape sequences pelo seu valor hexadeciaml e altera o length da string
                int tamanho_string;
                char *nova_str = escape_sequences(str, &tamanho_string);
                tamanho_string++;

                //guarda a string
                printf("  %%%d = alloca [%d x i8]\n",temporary, tamanho_string);
                printf("  store [%d x i8] c\"%s\\00\", [%d x i8]* %%%d\n",tamanho_string, nova_str, tamanho_string, temporary);
                int e2=temporary++;

                //imprime string
                printf("  %%ptr%d = getelementptr inbounds [%d x i8], [%d x i8]* %%%d, i32 0, i32 0\n",temporary, tamanho_string, tamanho_string, e2);
                printf("  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %%ptr%d)\n",temporary);
                temporary++;
                
            }else{
                int e1=codegen_expr(expr);
                diferentes_prints(expr->type,e1);
            }
            break;
        default:
            break;
    }
}

void diferentes_prints(enum type type, int tmp){
    switch(type){
        case int_type:
            printf("  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_int, i32 0, i32 0), i32 %%%d)\n", tmp);
            temporary++;
            break;
        case float32_type:
            printf("  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str_float, i32 0, i32 0), double %%%d)\n",tmp);
            temporary++;
            break;
        case bool_type:
            printf(
                "  br i1 %%%d, label %%L%dtrue, label %%L%dfalse\n"
                "L%dtrue:\n"
                "  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str_true, i32 0, i32 0))\n"
                "  br label %%L%dend\n"
                "L%dfalse:\n"
                "  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str_false, i32 0, i32 0))\n"
                "  br label %%L%dend\n"
                "L%dend:\n",
                tmp, temporary, temporary, temporary, temporary, temporary, temporary, temporary
                );
            temporary += 2;
            break;
        case string_type:
            //este apenas imprime as variaveis de tipo string
            printf("  call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str_string, i32 0, i32 0), i8* %%%d)\n",tmp);
            temporary++;
            break;
        default:
            break;
    }
}

int codegen_expr(struct node *expr){
    int tmp=-1;
    switch(expr->category){
        case Identifier: 
        //verificar se e global ou local, tratar ambas com load mas uma com @ e outra com %%
        //Tem erro quando o id e um parametro da funcao
            if(search_symbol(symbol_table,expr->token)!=NULL){ //global
                printf("  %%%d = load %s, %s* @%s\n", temporary, tipo_codificado(expr->type), tipo_codificado(expr->type), expr->token);
            }else{
                //printf("  %%%d = add %s %%%s, 0\n", temporary, tipo_codificado(expr->type), expr->token);
                printf("  %%%d = load %s, %s* %%%s\n", temporary, tipo_codificado(expr->type), tipo_codificado(expr->type), expr->token);
            }
            return temporary++;
        case Natural:
            printf("  %%%d = add i32 %s, 0\n", temporary, expr->token);
            tmp = temporary++;
            return tmp;
        case Decimal:
            printf("  %%%d = fadd double %s, 0.0\n", temporary, expr->token);
            tmp = temporary++;
            return tmp;
        case Or:
            return codegen_operation(expr,"or");
        case And:
            return codegen_operation(expr,"and");
        case Le:
            return codegen_operation2(expr,"icmp sle","fcmp ole");
        case Ge:
            return codegen_operation2(expr,"icmp sge","fcmp oge");
        case Lt:
            return codegen_operation2(expr,"icmp slt","fcmp olt");
        case Gt:
            return codegen_operation2(expr,"icmp sgt","fcmp ogt");
        case Eq:
            return codegen_operation2(expr,"icmp eq","fmcp oeq");
        case Ne:
            return codegen_operation2(expr,"icmp ne","fmcp one");
        case Add:
            return codegen_operation2(expr,"add","fadd");
        case Sub:
            return codegen_operation2(expr,"sub","fsub");
        case Mul:
            return codegen_operation2(expr,"mul","fmul");
        case Div:
            return codegen_operation2(expr,"sdiv","fdiv");
        case Mod:
            return codegen_operation(expr,"srem");
        case Not:
            return codegen_not(expr); 
        case Minus:
            return codegen_minus(expr);;
        case Plus:
            return codegen_plus(expr);
        case Call:
            return codegen_call(expr);
        default:
            return -1;
    }
    
}

int codegen_operation(struct node *expr, const char *op) {
    struct node *expr1=getchild(expr,0);
    struct node *expr2=getchild(expr,1);
    int left = codegen_expr(expr1);
    int right = codegen_expr(expr2);
    
    printf("  %%%d = %s %s %%%d, %%%d\n", temporary,op,tipo_codificado(expr1->type), left, right);
    return temporary++;
}

int codegen_operation2(struct node *expr, const char *op,const char *op2) {
    struct node *expr1=getchild(expr,0);
    struct node *expr2=getchild(expr,1);
    int left = codegen_expr(expr1);
    int right = codegen_expr(expr2);

    if(expr1->type==float32_type){
        printf("  %%%d = %s %s %%%d, %%%d\n", temporary,op2,tipo_codificado(expr1->type), left, right);
    }else{
        printf("  %%%d = %s %s %%%d, %%%d\n", temporary,op,tipo_codificado(expr1->type), left, right);
    }
    return temporary++;
}

int codegen_not(struct node *expr) {
    struct node *expr1=getchild(expr,0);
    int right = codegen_expr(expr1);
    printf("  %%%d = xor i1 %%%d, 1\n", temporary, right);
    return temporary++;
}

int codegen_minus(struct node *expr) {
    struct node *expr1=getchild(expr,0);
    int right = codegen_expr(expr1);
    if(expr1->type==float32_type){
        printf("  %%%d = fsub double -0.0, %%%d\n", temporary, right);
    }else{
        printf("  %%%d = sub i32 0, %%%d\n", temporary, right);
    }
    
    return temporary++;
}

int codegen_plus(struct node *expr) {
    struct node *expr1=getchild(expr,0);
    int right = codegen_expr(expr1);
    printf("  %%%d = add %s %%%d, 0\n", temporary, tipo_codificado(expr->type), right);
    return temporary++;
}

int codegen_call(struct node *expr){
    struct node *id=getchild(expr,0); 
    struct node *aux = (struct node *) malloc(sizeof(struct node));
    struct node_list *child = (struct node_list *) malloc(sizeof(struct node_list));
    struct node *child_node = (struct node *) malloc(sizeof(struct node));
    char *lista_types_call = (char *)malloc(4096);
    

    //Cria um string com tds o tipos passados no call
    if (getchild(expr,1)!=NULL){ //verifica o primeiro expr
        int tmp=codegen_expr(getchild(expr,1));
        char *str_aux = (char *)malloc(4096);
        sprintf(str_aux,"%s %%%d", tipo_codificado(getchild(expr,1)->type), tmp);
        strcat(lista_types_call, str_aux);
        if (getchild(expr,2)!=NULL){
            aux=getchild(expr,2);
            child = aux->children; //aux pode ter mais do que um filho expr
            while ((child=child->next) != NULL) {
                child_node = child->node;
                int tmp2=codegen_expr(child_node);
                char *str_aux2 = (char *)malloc(4096);
                strcat(lista_types_call, ",");
                sprintf(str_aux2,"%s %%%d", tipo_codificado(child_node->type), tmp2);
                strcat(lista_types_call, str_aux2);
            }
        }
    }

    if(search_symbol(symbol_table,id->token)->type==no_type){ //funcao do tipo void
        printf("  call %s @_%s(%s)\n",tipo_codificado(search_symbol(symbol_table,id->token)->type), id->token, lista_types_call);
    }else{
        printf("  %%%d = call %s @_%s(%s)\n",temporary, tipo_codificado(search_symbol(symbol_table,id->token)->type), id->token, lista_types_call);
    }



    return temporary++;
}