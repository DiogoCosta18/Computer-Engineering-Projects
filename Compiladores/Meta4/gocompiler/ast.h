#ifndef _AST_H
#define _AST_H

enum category { aux,Program, VarDecl, FuncDecl, FuncHeader, FuncParams, FuncBody, ParamDecl, Statements, Block, If, For, Return, Call, Print, ParseArgs, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Assign, Int, Float32, Bool, String, Natural, Decimal, Identifier, StrLit };
#define names { "aux","Program", "VarDecl", "FuncDecl", "FuncHeader", "FuncParams", "FuncBody", "ParamDecl", "Statements", "Block", "If", "For", "Return", "Call", "Print", "ParseArgs", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Assign", "Int", "Float32", "Bool", "String", "Natural", "Decimal", "Identifier", "StrLit" }

enum type {int_type,float32_type,bool_type,string_type,no_type,undef};
#define type_name(type) (type == int_type ? "int" : (type == float32_type ? "float32" : (type == bool_type ? "bool" : (type == string_type ? "string" : (type == no_type ? "none" : "undef")))))
#define category_type(category) (category == Int ? int_type : (category == Float32 ? float32_type : (category == Bool ? bool_type : (category == String ? string_type : no_type))))

#define operator_category(category)(category == Or ? "||" : (category == And ? "&&" : (category == Eq ? "==" : (category == Ne ? "!=" : (category == Lt ? "<" : (category == Gt ? ">" : (category == Le ? "<=" : (category == Ge ? ">=" : (category == Add ? "+" : (category == Sub ? "-" : (category == Mul ? "*" : (category == Div ? "/" : (category == Mod ? "%%" : (category == Not ? "!" : (category == Minus ? "-" : (category == Plus ? "+" : ""))))))))))))))))


struct node {
    enum category category;
    char *token;
    int token_line, token_column; //para guardar onde ouve erro semantico
    enum type type;
    struct node_list *children; //aponta para a lista de filhos
    int is_param;                  //flag para verificar se e um parametro de uma funcao
    int is_expr;                    //flag para imprimir na ast
    int is_func;                    //para imprimir quando chamamos uma funcao, o seu tipo entre parenteses
    int is_used;
    char* lista_tipos;               //guardar os tipos chamdos na funcao para dar o printf
};

struct node_list {
    struct node *node; //aponta para o nó filho do pai atual
    struct node_list *next; //aponta para o nó filho seguinte
};

struct node *newnode(enum category category, char *token);
void addchild(struct node *parent, struct node *child);
void addType(struct node *parent, struct node *child);
void show(struct node *root, int depth);
void show_anotated(struct node *root, int depth);
struct node *getchild(struct node *parent, int position);
int countchildren(struct node *node);
void deallocate(struct node *root);
void free_ast (struct node * cur_node);
int countblocks(struct node *node);

#endif
