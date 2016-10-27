
%{
#include<stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "symbolNode.h"
//#include <string.h>
//#include<iostream>
//#include <map>
//#include <string>


int size=0;
int printC;
//using namespace std;


void operations();
void Insert(char *);
void Display();
void Delete();
int Search(char lab[]);
void Modify();

// symbol table operations
 int initialisetable(char *,int);
//extern struct table st;
int lookup(char*);
int initialiseConstant(char *,char *);//initialise the constant value when you find it in yacc reduction
int printSymbolTable();
int offset=0;

//global symbol table structure 

extern struct table
{
        char name[20];
        int occurance;
        int size;
        int offsetinfo;
        char value[50];
        char *fargs[50];
        int firstAddress;
        int nextline;
        char caller[20];
        char type[20];
        int elementNumber;

}st[100];



%}

%%
[\t \n]							;
"if"							{strcpy(yylval.val,yytext);/*yylval.val=(char *)yytext*/return IF;}
"then"							{strcpy(yylval.val,yytext);return THEN;}
"else"							{strcpy(yylval.val,yytext);return ELSE;}	
"while"							{strcpy(yylval.val,yytext);return WHILE;}
"CONSTANTS"						{strcpy(yylval.val,yytext); return CONSTANTS;}
"FUNCTIONS"						{strcpy(yylval.val,yytext);return FUNCTIONS;}
"return"						{strcpy(yylval.val,yytext);return RETURN;}
"MAIN"							{strcpy(yylval.val,yytext);return MAIN;}
"print"							{strcpy(yylval.val,yytext);return PRINT;}
"read"							{strcpy(yylval.val,yytext);return READ;}
"loop"							{strcpy(yylval.val,yytext);return LOOP;}
"{"                            			  	{strcpy(yylval.val,yytext);return OB;}
"}"                              		         {strcpy(yylval.val,yytext); return CB;}
"T"|"F"                                                  { strcpy(yylval.val,yytext);return BOOLEAN;}
"=="|">"|"<"|">="|"<="|"!="                              {strcpy(yylval.val,yytext);return CMP;}
"%"							{strcpy(yylval.val,yytext);return MOD;}
"/"|"-"                                              {strcpy(yylval.val,yytext);return TWOPDF;}
"+"|"*"                                                  {strcpy(yylval.val,yytext);;return PDF;}
"print"                               			 {strcpy(yylval.val,yytext);return PRINT;}
=                               			 {strcpy(yylval.val,yytext);return EQUALS;}
0                                                    	 {strcpy(yylval.val,yytext);return INTEGER;}
[-]?[ ]+?[1-9][0-9]?[0-9]?[0-9]?[0-9]?[0-9]?             { /*strcpy(yylval.val,&yytext[0]);*/strcpy(yylval.val,yytext); return INTEGER;} 
[-]?[ ]+?[1-9][0-9][0-9][0-9][0-9][0-9][0-9]+            {exit(0);}
[ ]+?(0)"."(0)+					         {strcpy(yylval.val,yytext);return FLOAT;} 
(-)?[ ]+?(0)(".")[0]+[1-9]+[0-9]*                        {strcpy(yylval.val,yytext);return FLOAT;}
(-)?[ ]+?(0)(".")[1-9]+[0-9]*			       	 {strcpy(yylval.val,yytext);return FLOAT;} 
(-)?[ ]+?([1-9])([0-9]*)"."([0-9]+)                	 {strcpy(yylval.val,yytext);return FLOAT;}
[a-z][a-z]*	                                	 {strcpy(yylval.val,yytext);initialisetable(yytext,offset);return IDENTIFIER;}
-[ ]*/-|"-"                                              {return PDF;}
\([a-z,A-Z,0-9, ,\\.]+\)                                   {strcpy(yylval.val,yytext);return STRING;}
<<EOF>>							 return -1;
.							 printf("unrecognised string: %s\n",yytext);
%%


int initialisetable(char* identifier,int off){
        st[0].offsetinfo=0;
        if (lookup(identifier)==-100000){ //this means symbol is found on -1 being returned so nothing executed
	   offset=offset+1;
           strcpy(st[offset].name,identifier);
           st[offset].offsetinfo=offset;
           st[offset].occurance=1;
        }
}
int lookup(char *id){
        int ret=-100000;
        for(int i=1;i<=offset;i++){
                if (!strcmp(st[i].name,id)){
                        st[i].occurance=st[i].occurance+1;
            		ret=st[i].offsetinfo;
			return ret;
            }
        }
        return ret;
}


int printSymbolTable(){
        int printTill=offset;
        printf("idetifier \t occurance \t  \t offset \t value \t returnAddress \t  lvars\n");
        for(int element=1;element<=offset;element++){
        	printf(" %s  \t\t  %d     ",st[element].name,st[element].occurance);
			printf("\t\t offset= %d",st[element].offsetinfo);
			printf("\t %s \t",st[element].value);
			if (st[element].nextline>0){
				printf("%d",st[element].nextline);
			}
			printf("\t");
			if (strcmp(st[element].type,"f")==0){
			//printf("inside the cmp %d",st[element].elementNumber);
			int lc=st[element].elementNumber;
			//printf(" oo %s \t",st[3].fargs[0]);
                        for (int i=0;i<lc;i++){
                                 printf("%s ",st[element].fargs[i]);
                        }
			}
			printf("\n");
        }

}


int yywrap(void){
return 1;
}




