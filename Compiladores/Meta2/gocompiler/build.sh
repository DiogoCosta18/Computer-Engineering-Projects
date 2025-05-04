#!/bin/sh
rm -f gocompiler lex.yy.c y.tab.c y.tab.h
yacc -d -v -t -g --report=all gocompiler.y
lex gocompiler.l
clang  -g -o gocompiler lex.yy.c y.tab.c ast.c  -Wall -Wno-unused-function
