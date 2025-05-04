%{
    /* Andre Miguel Martinho de Melo 2022213285 */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    #include "ast.h"

    int yyparse(void);
    void yyerror(char *);
    extern struct node *program;

    #define YY_USER_ACTION {syn_line =  linha; syn_column =  coluna; coluna+=yyleng;} 
    #define PASS_TOKEN() yylval.lexeme = strdup(yytext);

    int linha = 1;
    int coluna = 1;
    int linha_coluna[2]; 
    int syn_line = -1;
    int syn_column = -1;
    int errors=0;

    int flag = 0; //0 - imprime so erros , 1 - imprimi tudo (so acontece se for corrido com a flag -l)
    int flag_string=0; //para quando da erro a meio na string nao a imprimir
    int last_token=0; //flag para as semicolon
    

    char str_buffer[4096];
    int str_buffer_index = 0;

    void add_str_buffer(char *add, int length) {
        strncpy(&str_buffer[str_buffer_index], add, length);
        str_buffer_index += length;
    }

    void reset_str_buffer() {
        str_buffer_index = 0;
        str_buffer[0] = '\0';
    }

%}
%X COMMENT_BARRAS STRLIT2 COMMENT_ASTERISCO


newline                 \n|\r|\r\n
ignore                  "\f"|"\t"|" "

letra                   [a-z]|[A-Z]|"_"
digito                  [0-9]

octal_prefixo           "0"
octal                   {octal_prefixo}[0-7]+
invalid_octal           {octal_prefixo}[0-9]+

hex_prefixo             "0x"|"0X"
hex                     {hex_prefixo}[0-9a-fA-F]+

identifier              {letra}({digito}|{letra})*
natural                 {digito}+

expoente                [eE][+-]?{digito}+
decimal                 ({digito}+"."{digito}*{expoente}?)|("."{digito}+{expoente}?)|({digito}+{expoente})

escape_seq              \\\\|\\n|\\f|\\r|\\t|\\\"




semicolon               ";"
comma                   ","
blankid                 "_"
assign                  "="
star                    "*"
div                     "/"
minus                   "-"
plus                    "+"
eq                      "=="
ge                      ">="
gt                      ">"
lbrace                  "{"
le                      "<="
lpar                    "("
lsq                     "["
lt                      "<"
mod                     "%"
ne                      "!="
not                     "!"
and                     "&&"
or                      "||"
rbrace                  "}"
rpar                    ")"
rsq                     "]"
package                 "package"
return                  "return"
else                    "else"
for                     "for"
if                      "if"
var                     "var"
int                     "int"
float32                 "float32"
bool                    "bool"
string                  "string"
print                   "fmt.Println"
parseint                "strconv.Atoi"
func                    "func"
cmdargs                 "os.Args"
reserved                "++"|"--"|"break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"fallthrough"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"




%%

"//"                                    {BEGIN(COMMENT_BARRAS);}
<COMMENT_BARRAS>{newline}               {BEGIN(INITIAL);coluna=1;linha++;if(last_token==1)printf("SEMICOLON\n");last_token=0;}
<COMMENT_BARRAS>.                       {}


"/*"                                    {BEGIN(COMMENT_ASTERISCO);linha_coluna[0]=linha;linha_coluna[1]=coluna-yyleng;}
<COMMENT_ASTERISCO>"*/"                 {BEGIN(INITIAL);}
<COMMENT_ASTERISCO>.                    {}
<COMMENT_ASTERISCO>{newline}            {coluna=1,linha++;}
<COMMENT_ASTERISCO><<EOF>>              {printf("Line %d, column %d: unterminated comment\n",linha_coluna[0],linha_coluna[1]);last_token=0;return 1;}


\"                                      {BEGIN(STRLIT2); flag_string=1;reset_str_buffer();add_str_buffer(yytext, yyleng); linha_coluna[0]=linha; linha_coluna[1]=coluna-yyleng;}
<STRLIT2>\"                              {add_str_buffer(yytext, yyleng);BEGIN(INITIAL);if(flag_string==1){if(flag==1){printf("STRLIT(%s)\n",str_buffer);}last_token=1;yylval.lexeme = strdup(str_buffer);return STRLIT;}}
<STRLIT2>{escape_seq}                    {add_str_buffer(yytext, yyleng);}
<STRLIT2>((\\.)|(\\))                    {printf("Line %d, column %zu: invalid escape sequence (%s)\n",linha,coluna-yyleng,yytext);flag_string=0;str_buffer_index+=yyleng;}
<STRLIT2>{newline}                       {linha++; coluna= 1; printf("Line %d, column %d: unterminated string literal\n",linha_coluna[0],linha_coluna[1]);reset_str_buffer();BEGIN(INITIAL);}
<STRLIT2>.                               {add_str_buffer(yytext, yyleng);}
<STRLIT2><<EOF>>                         {printf("Line %d, column %d: unterminated string literal\n",linha_coluna[0],linha_coluna[1]);reset_str_buffer(); BEGIN(INITIAL);return 0;}




{semicolon}                             {if(flag == 1)printf("SEMICOLON\n");last_token=0;return SEMICOLON;}
{comma}                                 {if(flag == 1)printf("COMMA\n");last_token=0;return COMMA;}
{blankid}                               {if(flag == 1)printf("BLANKID\n");last_token=0;return BLANKID;}
{assign}                                {if(flag == 1)printf("ASSIGN\n");last_token=0;return ASSIGN;}
{star}                                  {if(flag == 1)printf("STAR\n");last_token=0;return STAR;}
{div}                                   {if(flag == 1)printf("DIV\n");last_token=0;return DIV;}
{minus}                                 {if(flag == 1)printf("MINUS\n");last_token=0;return MINUS;}
{plus}                                  {if(flag == 1)printf("PLUS\n");last_token=0;return PLUS;}
{eq}                                    {if(flag == 1)printf("EQ\n");last_token=0;return EQ;}
{ge}                                    {if(flag == 1)printf("GE\n");last_token=0;return GE;}
{gt}                                    {if(flag == 1)printf("GT\n");last_token=0;return GT;}
{lbrace}                                {if(flag == 1)printf("LBRACE\n");last_token=0;return LBRACE;} 
{le}                                    {if(flag == 1)printf("LE\n");last_token=0;return LE;}
{lpar}                                  {if(flag == 1)printf("LPAR\n");last_token=0;return LPAR;}
{lsq}                                   {if(flag == 1)printf("LSQ\n");last_token=0;return LSQ;}
{lt}                                    {if(flag == 1)printf("LT\n");last_token=0;return LT;}
{mod}                                   {if(flag == 1)printf("MOD\n");last_token=0;return MOD;}
{ne}                                    {if(flag == 1)printf("NE\n");last_token=0;return NE;}
{not}                                   {if(flag == 1)printf("NOT\n");last_token=0;return NOT;}
{and}                                   {if(flag == 1)printf("AND\n");last_token=0;return AND;}
{or}                                    {if(flag == 1)printf("OR\n");last_token=0;return OR;}
{rbrace}                                {if(flag == 1)printf("RBRACE\n");last_token=1;return RBRACE;}
{rpar}                                  {if(flag == 1)printf("RPAR\n");last_token=1;return RPAR;}
{rsq}                                   {if(flag == 1)printf("RSQ\n");last_token=1;return RSQ;}
{package}                               {if(flag == 1)printf("PACKAGE\n");last_token=0;return PACKAGE;}
{return}                                {if(flag == 1)printf("RETURN\n");last_token=1;return RETURN;}
{else}                                  {if(flag == 1)printf("ELSE\n");last_token=0;return ELSE;}
{for}                                   {if(flag == 1)printf("FOR\n");last_token=0;return FOR;}
{if}                                    {if(flag == 1)printf("IF\n");last_token=0;return IF;}
{var}                                   {if(flag == 1)printf("VAR\n");last_token=0;return VAR;}
{int}                                   {if(flag == 1)printf("INT\n");last_token=0;return INT;}
{float32}                               {if(flag == 1)printf("FLOAT32\n");last_token=0;return FLOAT32;}
{bool}                                  {if(flag == 1)printf("BOOL\n");last_token=0;return BOOL;}
{string}                                {if(flag == 1)printf("STRING\n");last_token=0;return STRING;}
{print}                                 {if(flag == 1)printf("PRINT\n");last_token=0;return PRINT;}
{parseint}                              {if(flag == 1)printf("PARSEINT\n");last_token=0;return PARSEINT;}
{func}                                  {if(flag == 1)printf("FUNC\n");last_token=0;return FUNC;}
{cmdargs}                               {if(flag == 1)printf("CMDARGS\n");last_token=0;return CMDARGS;}
{ignore}                                {}

{reserved}                              {if(flag == 1)printf("RESERVED(%s)\n",yytext);last_token=0;return RESERVED;}


{identifier}                            {if(flag == 1)printf("IDENTIFIER(%s)\n",yytext);last_token=1;PASS_TOKEN();return IDENTIFIER;}

{octal}                                 {if(flag == 1)printf("NATURAL(%s)\n",yytext);last_token=1;PASS_TOKEN();return NATURAL;}
{invalid_octal}                         { printf("Line %d, column %zu: invalid octal constant (%s)\n", linha,coluna - yyleng,yytext); } //o erro e para ser dado no primeiro digito
{natural}                               {if(flag == 1)printf("NATURAL(%s)\n",yytext);last_token=1;PASS_TOKEN();return NATURAL;}
{hex}                                   {if(flag == 1)printf("NATURAL(%s)\n",yytext);last_token=1;PASS_TOKEN();return NATURAL;}
{decimal}                               {if(flag == 1)printf("DECIMAL(%s)\n",yytext);last_token=1;PASS_TOKEN();return DECIMAL;}

{newline}                               {linha++;coluna = 1;
                                            if(last_token==1){
                                                if(flag==1){
                                                    printf("SEMICOLON\n"); 
                                                }
                                                last_token=0;
                                                return SEMICOLON;
                                            }
                                        }



.                                       { yyerror("unrecognized character"); }

<<EOF>>                                 {
                                            if(flag==1 && last_token==1){
                                                printf("SEMICOLON\n");
                                                return 0;
                                            }
                                            if (last_token==1){
                                                last_token=0;
                                                return SEMICOLON;
                                            }
                                        last_token=0; return 0;}

%%



extern int yylex();
int main(int argc, char *argv[]){
    if (argc > 1 && strcmp(argv[1],"-l") == 0) {
            flag = 1;
            while(yylex()); //sem o while so imprime o primeiro e acaba o progrma
            return 0;
    }
    else if(argc >= 2 && strcmp(argv[1], "-t") == 0 && errors == 0) {  
        yyparse();
        show(program, 0);
        return 0;
    }else{
        yylex();
        yyparse();
        return 0;
    }
    
    
    
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}
void yyerror(char *error) {
    errors++;
    printf("Found %s '%s' (%d,%d)\n", error, yytext, syn_line, syn_column);
}

