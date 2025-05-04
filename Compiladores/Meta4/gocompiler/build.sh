#!/bin/sh

# Remove old files
rm -f gocompiler lex.yy.c y.tab.c y.tab.h

# Generate parser files
yacc -d -v -t gocompiler.y

# Generate lexer file
lex gocompiler.l

# Compile the program
gcc -g -o gocompiler lex.yy.c y.tab.c ast.c semantics.c codegen.c -Wall -Wno-unused-function