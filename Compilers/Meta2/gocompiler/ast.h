#ifndef _AST_H
#define _AST_H

enum category { aux,Program, VarDecl, FuncDecl, FuncHeader, FuncParams, FuncBody, ParamDecl, Statements, Block, If, For, Return, Call, Print, ParseArgs, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Assign, Int, Float32, Bool, String, Natural, Decimal, Identifier, StrLit };

#define names { "aux","Program", "VarDecl", "FuncDecl", "FuncHeader", "FuncParams", "FuncBody", "ParamDecl", "Statements", "Block", "If", "For", "Return", "Call", "Print", "ParseArgs", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Assign", "Int", "Float32", "Bool", "String", "Natural", "Decimal", "Identifier", "StrLit" }



struct node {
    enum category category;
    char *token;
    struct node_list *children; //aponta para a lista de filhos
};

struct node_list {
    struct node *node; //aponta para o nó filho do pai atual
    struct node_list *next; //aponta para o nó filho seguinte
};

struct node *newnode(enum category category, char *token);
void addchild(struct node *parent, struct node *child);
void addType(struct node *parent, struct node *child);
void show(struct node *root, int depth);
struct node *getchild(struct node *parent, int position);
int countchildren(struct node *node);
void deallocate(struct node *root);
void free_ast (struct node * cur_node);
int countblocks(struct node *node);

#endif
