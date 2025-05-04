#!/bin/sh
rm -f gocompiler lex.yy.c y.tab.c y.tab.h
yacc -d -v -t -g --report=all gocompiler.y
lex gocompiler.l
clang -o gocompiler lex.yy.c y.tab.c ast.c semantics.c -Wall -Wno-unused-function
