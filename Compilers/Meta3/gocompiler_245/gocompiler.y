/* START definitions section -- C code delimited by %{ ... %} and token declarations */

%{
#include "ast.h"

int yylex(void);
void yyerror(char *);


struct node *program;
//int yydebug=1;


%}

%token SEMICOLON COMMA BLANKID ASSIGN STAR DIV MINUS PLUS EQ GE GT LBRACE LE LPAR LSQ LT MOD NE NOT AND OR RBRACE RPAR RSQ PACKAGE RETURN ELSE FOR IF VAR INT FLOAT32 BOOL STRING PRINT PARSEINT FUNC CMDARGS RESERVED 


%token<lexeme> IDENTIFIER NATURAL DECIMAL STRLIT
%type<node> program  declarations vardeclaration  varspec varspec2 type funcdeclaration parameters parameters2 funcbody  varsandstatements  statement statement2  parseargs funcinvocation funcinvocation2 expr 

%debug

%nonassoc IF ELSE FOR
%left COMMA
%right ASSIGN
%left OR
%left AND
%left GE LE LT GT EQ NE
%left PLUS MINUS
%left STAR DIV MOD
%left LPAR RPAR LBRACE RBRACE 
%right NOT MINUS_SOZINHO PLUS_SOZINHO


%union{
    char *lexeme;
    struct node *node;
}

%locations
%{
#define LOCATE(node, line, column) { node->token_line = line; node->token_column = column; }
%}

/* START grammar rules section -- BNF grammar */

%%

program: PACKAGE IDENTIFIER SEMICOLON declarations              {   
                                                                    $$=program=newnode(Program,NULL);
                                                                    if($4!=NULL){addchild($$,$4);}
                                                                }
    ;


declarations: declarations vardeclaration SEMICOLON             { 
                                                                    if ($1 == NULL) {
                                                                        $$ = newnode(aux, NULL);
                                                                    } else {
                                                                        $$ = $1;
                                                                    }
                                                                    struct node* vardeclaration = newnode(aux,NULL);
                                                                    addchild(vardeclaration,$2);
                                                                    addchild($$,vardeclaration);
                                                                }
    | declarations funcdeclaration SEMICOLON                    {                      
                                                                    if ($1 == NULL) {
                                                                        $$ = newnode(aux, NULL);
                                                                    } else {
                                                                        $$ = $1;
                                                                    }
                                                                    if ($2 != NULL) {
                                                                        addchild($$, $2);
                                                                    }
                                                                }
    | /*vazio*/                                                 {$$=NULL;}
    ;


vardeclaration: VAR varspec                                     {$$=$2;}
    | VAR LPAR varspec SEMICOLON RPAR                           {$$=$3;}
    ;

varspec: IDENTIFIER varspec2 type                               {
                                                                    $$=newnode(aux,NULL);
                                                                    struct node* vardecl=newnode(VarDecl,NULL);
                                                                    addchild(vardecl,$3);
                                                                    addchild(vardecl,newnode(Identifier,$1));
                                                                    addchild($$,vardecl);
                                                                    if($2!=NULL){
                                                                        addchild($$,$2);
                                                                        addType($2,$3);
                                                                    }
                                                                    LOCATE(getchild(vardecl, 1), @1.first_line, @1.first_column); 
                                                                }                                  
    ;

varspec2: varspec2 COMMA IDENTIFIER                             {   
                                                                    if ($1 == NULL) {
                                                                        $$ = newnode(aux, NULL);
                                                                    } else {
                                                                        $$ = $1;
                                                                    }
                                                                    struct node* vardecl=newnode(VarDecl,NULL);
                                                                    addchild(vardecl, newnode(Identifier, $3));
                                                                    addchild($$,vardecl);
                                                                    LOCATE(getchild(vardecl, 0), @3.first_line, @3.first_column);

                                                                }                                                                    
    | /*vazio*/                                                 {$$=NULL;}
    ;

type: INT                                                       {$$=newnode(Int,NULL);;}
    | FLOAT32                                                   {$$=newnode(Float32,NULL);}
    | BOOL                                                      {$$=newnode(Bool,NULL);}
    | STRING                                                    {$$=newnode(String,NULL);}
    ;


funcdeclaration: FUNC IDENTIFIER LPAR parameters RPAR type funcbody             {
                                                                                    $$=newnode(FuncDecl,NULL);

                                                                                    struct node *funcHeader = newnode(FuncHeader, NULL);
                                                                                    addchild(funcHeader,newnode(Identifier,$2));
                                                                                    addchild(funcHeader,$6);
                                                                                    addchild(funcHeader,$4);

                                                                                    addchild($$,funcHeader);
                                                                                    addchild($$,$7);
                                                                                    LOCATE(getchild(funcHeader, 0), @2.first_line, @2.first_column);
                                                                                }
    | FUNC IDENTIFIER LPAR parameters RPAR funcbody                             {
                                                                                    $$=newnode(FuncDecl,NULL);

                                                                                    struct node *funcHeader = newnode(FuncHeader, NULL);
                                                                                    addchild(funcHeader,newnode(Identifier,$2));
                                                                                    addchild(funcHeader,$4);

                                                                                    addchild($$,funcHeader);
                                                                                    addchild($$,$6);
                                                                                    LOCATE(getchild(funcHeader, 0), @2.first_line, @2.first_column);
                                                                                }
    ;

parameters: IDENTIFIER type parameters2                                         {
                                                                                    $$=newnode(FuncParams,NULL);

                                                                                    struct node *paramDecl = newnode(ParamDecl, NULL);
                                                                                    addchild(paramDecl,$2);
                                                                                    addchild(paramDecl,newnode(Identifier,$1));

                                                                                    addchild($$,paramDecl);

                                                                                    if($3!=NULL){
                                                                                        addchild($$,$3);
                                                                                    }
                                                                                    LOCATE(getchild(paramDecl, 1), @1.first_line, @1.first_column);
                                                                                }

    | /*vazio*/                                                                 {$$=newnode(FuncParams,NULL);}
    ;

parameters2: parameters2 COMMA IDENTIFIER type                                  {
                                                                                    if ($1 == NULL) {
                                                                                        $$ = newnode(aux, NULL);
                                                                                    } else {
                                                                                        $$ = $1;
                                                                                    }
                                                                                    struct node *paramDecl = newnode(ParamDecl, NULL);
                                                                                    addchild(paramDecl,$4);
                                                                                    addchild(paramDecl,newnode(Identifier,$3));
                                                                                    addchild($$,paramDecl);
                                                                                    LOCATE(getchild(paramDecl, 1), @3.first_line, @3.first_column);
                                                                                }
    | /*vazio*/                                                                 {$$=NULL;}
    ;

funcbody: LBRACE varsandstatements RBRACE                                       {
                                                                                    if($2==NULL){
                                                                                        $$=newnode(FuncBody,NULL);
                                                                                    }else{
                                                                                        $$=$2;
                                                                                    }
                                                                                }

    ;

varsandstatements: varsandstatements SEMICOLON                                  {$$=$1;}
    | varsandstatements vardeclaration SEMICOLON                                {
                                                                                    if($1==NULL){
                                                                                        $$=newnode(FuncBody,NULL);
                                                                                    }else{
                                                                                        $$=$1;
                                                                                    }
                                                                                    addchild($$,$2);
                                                                                }
    | varsandstatements statement SEMICOLON                                     {
                                                                                    if($1==NULL){
                                                                                        $$=newnode(FuncBody,NULL);
                                                                                    }else{
                                                                                        $$=$1;
                                                                                    }
                                                                                    if($2!=NULL){
                                                                                        addchild($$,$2);
                                                                                    }
                                                                                }                               
    | /* vazio*/                                                                {$$=NULL;}
    ;


statement: IDENTIFIER ASSIGN expr                                               {   
                                                                                    $$=newnode(Assign,NULL);
                                                                                    addchild($$,newnode(Identifier,$1));
                                                                                    addchild($$,$3);
                                                                                    LOCATE(getchild($$, 0), @1.first_line, @1.first_column);
                                                                                    LOCATE($$, @2.first_line, @2.first_column);
                                                                                }
    | LBRACE statement2 RBRACE                                                  {
                                                                                    if($2!=NULL){
                                                                                        if (countblocks($2) > 1){
                                                                                            $$=newnode(Block,NULL);
                                                                                            addchild($$,$2);
                                                                                        }else{
                                                                                            $$=$2;
                                                                                        }
                                                                                    }else{
                                                                                        $$=NULL;
                                                                                    }
                                                                                }
    | IF expr LBRACE statement2 RBRACE ELSE LBRACE statement2 RBRACE            {
                                                                                    $$=newnode(If,NULL);
                                                                                    addchild($$,$2);
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if($4!=NULL){
                                                                                        addchild(block,$4);
                                                                                    }
                                                                                    addchild($$,block);
                                                                                    struct node *block2 = newnode(Block, NULL);
                                                                                    if($8!=NULL){
                                                                                        addchild(block2,$8);
                                                                                    }
                                                                                    addchild($$,block2);
                                                                                }
    | IF expr LBRACE statement2 RBRACE                                          {
                                                                                    $$=newnode(If,NULL);
                                                                                    addchild($$,$2);
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if($4!=NULL){
                                                                                        addchild(block,$4);
                                                                                    }
                                                                                    addchild($$,block);
                                                                                    addchild($$,newnode(Block,NULL));
                                                                                }                                                                                
    | FOR expr LBRACE statement2 RBRACE                                         {
                                                                                    $$=newnode(For,NULL);
                                                                                    addchild($$,$2);
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if($4!=NULL){
                                                                                        addchild(block,$4);
                                                                                    }
                                                                                    addchild($$,block);
                                                                                }

    | FOR  LBRACE statement2 RBRACE                                             {
                                                                                    $$=newnode(For,NULL);
                                                                                    struct node *block = newnode(Block, NULL);
                                                                                    if($3!=NULL){
                                                                                        addchild(block,$3);
                                                                                    }
                                                                                    addchild($$,block);
                                                                                }
    | RETURN expr                                                               {
                                                                                    $$=newnode(Return,NULL);
                                                                                    addchild($$,$2);
                                                                                    LOCATE($$, @1.first_line, @1.first_column);
                                                                                }

    | RETURN                                                                    {   $$=newnode(Return,NULL);
                                                                                    LOCATE($$, @1.first_line, @1.first_column);
                                                                                }

    | funcinvocation                                                            {$$=$1;}
    | parseargs                                                                 {$$=$1;}
    | PRINT LPAR expr RPAR                                                      {
                                                                                    $$=newnode(Print,NULL);
                                                                                    addchild($$,$3);
                                                                                }
    | PRINT LPAR STRLIT RPAR                                                    {
                                                                                    $$=newnode(Print,NULL);
                                                                                    addchild($$,newnode(StrLit,$3));
                                                                                }
    | error                                                                     {$$=NULL;}

statement2: statement2 statement SEMICOLON                                      {
                                                                                    if ($1 == NULL) {
                                                                                        $$ = newnode(aux, NULL); 
                                                                                    } else {
                                                                                        $$ = $1; 
                                                                                    }
                                                                                    if($2!=NULL){addchild($$, $2);} 
                                                                                }
    |/*vazio*/                                                                  {$$=NULL;}
    ;





parseargs: IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ expr RSQ RPAR      {
                                                                                            $$=newnode(ParseArgs,NULL);
                                                                                            addchild($$,newnode(Identifier,$1));
                                                                                            addchild($$,$9);
                                                                                            LOCATE($$, @5.first_line, @5.first_column);
                                                                                        }
    | IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                          {$$=NULL;}
    ;

funcinvocation: IDENTIFIER LPAR expr funcinvocation2 RPAR                               {
                                                                                            $$=newnode(Call,NULL);
                                                                                            addchild($$,newnode(Identifier,$1));
                                                                                            addchild($$,$3);
                                                                                            if($4!=NULL){
                                                                                                addchild($$,$4);
                                                                                            }
                                                                                            LOCATE(getchild($$, 0), @1.first_line, @1.first_column);
                                                                                        }
    | IDENTIFIER LPAR RPAR                                                              {
                                                                                            $$=newnode(Call,NULL);
                                                                                            addchild($$,newnode(Identifier,$1));
                                                                                            LOCATE(getchild($$, 0), @1.first_line, @1.first_column);
                                                                                        }
    | IDENTIFIER LPAR error RPAR                                                        {$$=NULL;}
    ;

funcinvocation2: funcinvocation2 COMMA expr                                             {
                                                                                            if ($1 == NULL) {
                                                                                                $$ = newnode(aux, NULL); 
                                                                                            } else {
                                                                                                $$ = $1; 
                                                                                            }addchild($$, $3);                                                     
                                                                                        }
    |/*vazio*/                                                                          {$$=NULL;}
    ;

expr: expr OR expr                                                                     {
                                                                                            $$=newnode(Or,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr AND expr                                                                    {    $$=newnode(And,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr LT expr                                                                      {   $$=newnode(Lt,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr GT expr                                                                      {   $$=newnode(Gt,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr EQ expr                                                                      {   $$=newnode(Eq,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr NE expr                                                                      {   $$=newnode(Ne,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr LE expr                                                                      {   $$=newnode(Le,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr GE expr                                                                      {   $$=newnode(Ge,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr PLUS expr                                                                    {   $$=newnode(Add,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr MINUS expr                                                                   {   $$=newnode(Sub,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr STAR expr                                                                    {   $$=newnode(Mul,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr DIV expr                                                                     {   $$=newnode(Div,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | expr MOD expr                                                                     {   $$=newnode(Mod,NULL);
                                                                                            addchild($$, $1);
                                                                                            addchild($$, $3);
                                                                                            LOCATE($$, @2.first_line, @2.first_column);
                                                                                        }
    | NOT expr         %prec  NOT                                                       {   $$=newnode(Not,NULL);
                                                                                            addchild($$, $2);
                                                                                            LOCATE($$, @1.first_line, @1.first_column);
                                                                                        }
    | MINUS expr      %prec MINUS_SOZINHO                                               {   $$=newnode(Minus,NULL);
                                                                                            addchild($$, $2);
                                                                                            LOCATE($$, @1.first_line, @1.first_column);
                                                                                        }
    | PLUS expr         %prec PLUS_SOZINHO                                              {   $$=newnode(Plus,NULL);
                                                                                            addchild($$, $2);
                                                                                            LOCATE($$, @1.first_line, @1.first_column);
                                                                                        }
    | NATURAL                                                                           {$$ = newnode(Natural, $1);
                                                                                            LOCATE($$, @1.first_line, @1.first_column);}
    | DECIMAL                                                                           {$$ = newnode(Decimal, $1);
                                                                                            LOCATE($$, @1.first_line, @1.first_column);}
    | IDENTIFIER                                                                        {$$ = newnode(Identifier, $1);
                                                                                            LOCATE($$, @1.first_line, @1.first_column);}
    | funcinvocation                                                                    {$$ = $1;
                                                                                            LOCATE($$, @1.first_line, @1.first_column);}
    | LPAR expr RPAR                                                                    {$$ = $2;}
    | LPAR error RPAR                                                                   {$$ = NULL;}





%%

/* START subroutines section */

// all needed functions are collected in the .l and ast.* files