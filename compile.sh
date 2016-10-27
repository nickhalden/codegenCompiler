#!/bin/bash
yacc -d FP.y;
flex FP.l;
g++ lex.yy.c y.tab.c -o outputc++ --std=c++11 2>/dev/null;
./outputc++ < $1

