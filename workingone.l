%{

#include<stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "symbolNode.h"
int size=0;
int printC;
void operations();
void Insert(char *);
void Display();
void Delete();
int Search(char lab[]);void Modify();

struct SymbTab
{
char label[10],symbol[10];
int addr;
struct SymbTab *next;
};

struct SymbTab *first,*last;


int initialisetable(char *,int);

int looksymbol(char *symbol);
int lookup(char *);
int updateSymbolVal(char *symbol,float val);
int printSymbolTable();
int offset=1;

//int repeat=1; // look up the symbol table using id and repeat++;


//extern symbolNode book1;
//#include "FP.h"


/* Functions for adding and displaying symbol table */
//void show_table();
//int find_symbol(char[]);

/*struct node {
        char identifier[20];
	char type[10];
	int offsetinfo;
        symbolnode* address;
	int repeat;
        int off;
};*/

struct node
{
        int var;
        char value[15];
        char type[15];
        char dtype[15];
        struct node *child;
        struct node *sib;
        int offsetinfo;
};
struct table
{
	char name[20];
	//char **address=NULL;
	int size;
        //table node[] ;
	struct node elements[100];
}st[100];

int createnode(char);
/*struct node
{
	char value[15];
	char type[15];
	char dtype[15];
	struct node *child;
	struct node *sib;
};*/



//int jmaxut[20]={0}; /* max no. of usage types of each symbol */
//int maxcr[10]={0};
//int maxce[10]={0};
/*

*/
%}

%%
[\n \t]					;
"if"							{yylval.ptr=(char *)yytext;return IF;}
"then"							{yylval.ptr=(char *)yytext;return THEN;}
"else"							{yylval.ptr=(char *)yytext;return ELSE;}	
"while"							{yylval.ptr=(char *)yytext;return WHILE;}
"CONSTANTS"						{yylval.ptr=(char *)yytext; return CONSTANTS;}
"FUNCTIONS"						{yylval.ptr=(char *)yytext;return FUNCTIONS;}
"return"						{yylval.ptr=(char *)yytext;return RETURN;}
"MAIN"							{yylval.ptr=(char *)yytext;return MAIN;}
"print"							{yylval.ptr=(char *)yytext;return PRINT;}
"read"							{yylval.ptr=(char *)yytext;return READ;}
"loop"							{yylval.ptr=(char *)yytext;return LOOP;}
"{"                            			  	{yylval.ptr=(char *)yytext;return OB;}
"}"                              		         { printf("debugging CB\n");yylval.ptr=(char *)yytext;return CB;}
"T"|"F"                                                  {printf("debugging boolean\n"); yylval.ptr=(char *)yytext;return BOOLEAN;}
"=="|">"|"<"|">="|"<="|"!="                              {yylval.ptr=(char *)yytext;return CMP;}
"%"|"/"|[\-]                                              {yylval.ptr=(char *)yytext;printf("upper pdf executed\n");return PDF;}
"+"|"*"                                                  {yylval.ptr=(char *)yytext;printf("upper pdf executed\n");return PDF;}
print                               			 {yylval.ptr=(char *)yytext;return PRINT;}
=                               			 {yylval.ptr=(char *)yytext;return EQUALS;}
"0"                                                    	 {yylval.ptr=(char *)yytext;return INTEGER;}
[-]?[ ]+?[1-9][0-9]?[0-9]?[0-9]?[0-9]?[0-9]?             {strcpy(yylval.val,yytext);/*strcpy(yylval.name,&yytext[0])*/;return INTEGER;}
[-]?[ ]+?[1-9][0-9][0-9][0-9][0-9][0-9][0-9]+            {yylval.ptr=(char *)yytext;printf("overflow%s",yytext);}
[ ]+?(0)"."(0)+					         {yylval.ptr=(char *)yytext;return FLOAT;} 
(-)?[ ]+?(0)(".")[0]+[1-9]+[0-9]*                        {yylval.ptr=(char *)yytext;return FLOAT;}
(-)?[ ]+?(0)(".")[1-9]+[0-9]*			       	 {yylval.ptr=(char *)yytext;return FLOAT;} 
(-)?[ ]+?([1-9])([0-9]*)"."([0-9]+)                	 {yylval.ptr=(char *)yytext;return FLOAT;}
[a-z][a-z]*	                                	 {yylval.ptr=(char *)yytext;initialisetable(yytext,offset);/*strcpy(yylval.id,yytext);*//*strcpy(book1.name,yytext)*/return IDENTIFIER;}
-[ ]*/-|"-"                                              {yylval.ptr=(char *)yytext;return PDF;}
\([a-z,A-Z,0-9, ,\n]+\)                                  {yylval.ptr=(char *)yytext;return STRING;}
<<EOF>>							 return -1;
.							 printf("unrecognised string: %s\n",yytext);
%%

int yywrap(void){
return 1;
}

int initialisetable(char* identifier,int off){
	if (lookup(identifier)==0){
		strcpy(st[offset].name,identifier);
		offset=offset+1;
	}
}

int lookup(char *value){
        char *temp=*(&value);
	//printf("aaaaaaaaaaaa %s %ld\n",temp,strlen(temp));
	int ret=0;
	for(int i=1;i<=offset;i++){
		if (!strcmp(st[i].name,value)){
		ret=1;
		}
	}
	return ret;
}

int printSymbolTable(){
	int printTill=offset;
	printf("idetifier name repeation \t type \t address \t offset \t \n");
	for(int element=1;element<=offset;element++){
		printf("value from the -----------symbol table %s with \toffset= %d \n",st[element].name,element);
	}

}
int createNode(char *identifier){

struct table st1;
struct node first ;
struct node *new_node,*current;
//new_node=(struct node *)malloc(sizeof(struct node));
//&new_node->var=1;
//new_node->value=identifier;

//first.value->identifier;
}


