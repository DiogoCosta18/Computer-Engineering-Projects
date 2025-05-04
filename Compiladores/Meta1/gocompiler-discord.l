%{
    #include <ctype.h>
    #include <stdio.h>
    #include <string.h>

    #define YY_USER_ACTION \
        curcol += yyleng; \
        

    int curline = 1; 
    int curcol = 1;
    int add_semicolon = 0; 

    int ml_comment_start_line = 0;
    int ml_comment_start_col = 0;

    char str_buffer[4096];
    int str_buffer_index = 0;

    int str_error = 0;

    void add_str_buffer(char *add, int length) {
        strncpy(&str_buffer[str_buffer_index], add, length);
        str_buffer_index += length;
    }

    void reset_str_buffer() {
        str_buffer_index = 0;
        str_buffer[0] = '\0';
    }

%}

SEMICOLON                           ";"
COMMA                               ","
BLANKID                             "_"
ASSIGN                              "="
STAR                                "*"
DIV                                 "/"
MINUS                               "-"
PLUS                                "+"
EQ                                  "=="
GE                                  ">="
GT                                  ">"
LBRACE                              "{"
LE                                  "<="
LPAR                                "("
LSQ                                 "["
LT                                  "<"
MOD                                 "%"
NE                                  "!="
NOT                                 "!"
AND                                 "&&"
OR                                  "||"
RBRACE                              "}"
RPAR                                ")"
RSQ                                 "]"
PACKAGE                             "package"
RETURN                              "return"
ELSE                                "else"
FOR                                 "for"
IF                                  "if"
VAR                                 "var"
INT                                 "int"
FLOAT32                             "float32"
BOOL                                "bool"
STRING                              "string"
PRINT                               "fmt.Println"
PARSEINT                            "strconv.Atoi"
FUNC                                "func"
CMDARGS                             "os.Args"
RESERVED                            "++"|"--"|"break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"fallthrough"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"

IGNORE                              " "|"\t"
NEWLINE                             "\n"|"\r"|"\r\n"

LETTER                              [a-z]|[A-Z]|"_"
DECLIT                              [0-9]

OCTALPREFIX                         "0"
OCTAL                               {OCTALPREFIX}[0-7]+
INVALID_OCTAL                       {OCTALPREFIX}[0-9]+

HEXPREFIX                            "0x"|"0X"
HEX                                  {HEXPREFIX}[0-9a-fA-F]+

IDENTIFIER                          {LETTER}({DECLIT}|{LETTER})*
NATURAL                             {DECLIT}+

EXPONENT                            [eE][+-]?{DECLIT}+
DECIMAL                             ({DECLIT}+"."{DECLIT}*{EXPONENT}?)|("."{DECLIT}+{EXPONENT}?)|({DECLIT}+{EXPONENT})

ESCAPE_SEQ			                \\\\|\\n|\\f|\\r|\\t|\\\"

QUOTE                               \"

%X SINGLE_LINE_COMMENT
%X MULTI_LINE_COMMENT
%X STRING

%%



"//"                                { BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>{NEWLINE}      { BEGIN(INITIAL); if(add_semicolon) printf("SEMICOLON\n"); add_semicolon = 0; curline++; curcol = 1; }
<SINGLE_LINE_COMMENT>.              { ; }
<SINGLE_LINE_COMMENT><<EOF>>        { BEGIN(INITIAL); if(add_semicolon) printf("SEMICOLON\n"); add_semicolon = 0; return 0; }



"/*"                                { BEGIN(MULTI_LINE_COMMENT); ml_comment_start_line = curline; ml_comment_start_col = curcol - yyleng; }
<MULTI_LINE_COMMENT>"*/"            { BEGIN(INITIAL); }
<MULTI_LINE_COMMENT>.               { ; }
<MULTI_LINE_COMMENT>{NEWLINE}       { curline++; curcol = 1; }
<MULTI_LINE_COMMENT><<EOF>>         { printf("Line %d, column %d: unterminated comment\n", ml_comment_start_line, ml_comment_start_col); add_semicolon = 0; return 0; }



{QUOTE}                             { BEGIN(STRING); add_semicolon = 1; add_str_buffer(yytext, yyleng); str_error = 0; }
<STRING>{QUOTE}                     { 
                                        add_str_buffer(yytext, yyleng); 
                                        str_buffer[str_buffer_index] = '\0';
                                        
                                        if(!str_error){
                                            printf("STRLIT(%s)\n", str_buffer); 
                                            add_semicolon = 1; 
                                        }
                                        else{
                                            add_semicolon = 0;
                                        }

                                        reset_str_buffer();
                                        BEGIN(INITIAL); 
                                    }

<STRING>{ESCAPE_SEQ}                { add_str_buffer(yytext, yyleng); }

<STRING>((\\.)|(\\))                { printf("Line %d, column %d: invalid escape sequence (%s)\n", curline, curcol - yyleng, yytext); str_error = 1; str_buffer_index += yyleng; /*BEGIN(INITIAL); reset_str_buffer();*/ }
<STRING>{NEWLINE}                   { printf("Line %d, column %d: unterminated string literal\n", curline, curcol - str_buffer_index - yyleng); BEGIN(INITIAL); curline++; curcol = 1; reset_str_buffer(); add_semicolon = 0; }

<STRING>.                           { add_str_buffer(yytext, yyleng); }
<STRING><<EOF>>                     { printf("Line %d, column %d: unterminated string literal\n", curline, curcol - str_buffer_index); BEGIN(INITIAL); reset_str_buffer(); add_semicolon = 0; return 0; }



{SEMICOLON}                         { printf("SEMICOLON\n"); add_semicolon = 0; }
{COMMA}                             { printf("COMMA\n"); add_semicolon = 0; }
{ASSIGN}                            { printf("ASSIGN\n"); add_semicolon = 0; }
{STAR}                              { printf("STAR\n"); add_semicolon = 0; }
{DIV}                               { printf("DIV\n"); add_semicolon = 0; }
{MINUS}                             { printf("MINUS\n"); add_semicolon = 0; }
{PLUS}                              { printf("PLUS\n"); add_semicolon = 0; }
{EQ}                                { printf("EQ\n"); add_semicolon = 0; }
{GE}                                { printf("GE\n"); add_semicolon = 0; }
{GT}                                { printf("GT\n"); add_semicolon = 0; }
{LBRACE}                            { printf("LBRACE\n"); add_semicolon = 0; }
{LE}                                { printf("LE\n"); add_semicolon = 0; }
{LPAR}                              { printf("LPAR\n"); add_semicolon = 0; }
{LSQ}                               { printf("LSQ\n"); add_semicolon = 0; }
{LT}                                { printf("LT\n"); add_semicolon = 0; }
{MOD}                               { printf("MOD\n"); add_semicolon = 0; }
{NE}                                { printf("NE\n"); add_semicolon = 0; }
{NOT}                               { printf("NOT\n"); add_semicolon = 0; }
{AND}                               { printf("AND\n"); add_semicolon = 0; }
{OR}                                { printf("OR\n"); add_semicolon = 0; }
{PACKAGE}                           { printf("PACKAGE\n"); add_semicolon = 0; }
{ELSE}                              { printf("ELSE\n"); add_semicolon = 0; }
{FOR}                               { printf("FOR\n"); add_semicolon = 0; }
{IF}                                { printf("IF\n"); add_semicolon = 0; }
{VAR}                               { printf("VAR\n"); add_semicolon = 0; }
{INT}                               { printf("INT\n"); add_semicolon = 0; }
{FLOAT32}                           { printf("FLOAT32\n"); add_semicolon = 0; }
{BOOL}                              { printf("BOOL\n"); add_semicolon = 0; }
{STRING}                            { printf("STRING\n"); add_semicolon = 0; }
{PRINT}                             { printf("PRINT\n"); add_semicolon = 0; }
{PARSEINT}                          { printf("PARSEINT\n"); add_semicolon = 0; }
{FUNC}                              { printf("FUNC\n"); add_semicolon = 0; }
{CMDARGS}                           { printf("CMDARGS\n"); add_semicolon = 0; }
{IGNORE}                            { ; }

{BLANKID}                           { printf("BLANKID\n"); add_semicolon = 0; }
{RESERVED}                          { printf("RESERVED(%s)\n", yytext); add_semicolon = 0; }

{RBRACE}                            { printf("RBRACE\n"); add_semicolon = 1; }
{RPAR}                              { printf("RPAR\n"); add_semicolon = 1; }
{RSQ}                               { printf("RSQ\n"); add_semicolon = 1; }
{RETURN}                            { printf("RETURN\n"); add_semicolon = 1; }
{IDENTIFIER}                        { printf("IDENTIFIER(%s)\n", yytext); add_semicolon = 1; }


{OCTAL}                             { printf("NATURAL(%s)\n", yytext); add_semicolon = 1; }
{INVALID_OCTAL}                     { printf("Line %d, column %d: invalid octal constant (%s)\n", curline, curcol - yyleng, yytext); }
{NATURAL}                           { printf("NATURAL(%s)\n", yytext); add_semicolon = 1; }
{HEX}                               { printf("NATURAL(%s)\n", yytext); add_semicolon = 1; }

{DECIMAL}                           { printf("DECIMAL(%s)\n", yytext); add_semicolon = 1; }
{NEWLINE}                           { curline++; curcol = 1; if(add_semicolon) printf("SEMICOLON\n"); add_semicolon = 0; }

.                                   { printf("Line %d, column %d: illegal character (%s)\n", curline, curcol - yyleng, yytext); }

<<EOF>>                             { if(add_semicolon) printf("SEMICOLON\n"); return 0; }

%%

extern int yylex();
int main() {
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}
