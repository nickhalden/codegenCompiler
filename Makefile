all:
	yacc -d FP.y;flex FP.l;g++ lex.yy.c y.tab.c operations.cpp -o outputc++ --std=c++11;
	./outputc++ < sample.fp
	 

