%{
#include <stdio.h>     
#include<iostream>
#include <stdlib.h>
#include <map>
#include <unistd.h>
#include <string.h>
#include <string>
#include "operations.h"

extern void fileOpen();
extern void fileClose();
extern void initialisetable(char*,int);
extern int offset;
int funoffset=0;
int vcounter=0;
int newcount=1;
extern int linecount;

enum Atag {AD,SU,CM,EX,ID,PR,FC};


void setConstant(int,char*);


using namespace std;

void yyerror (char *s);


extern int lookup(char*);
extern int yylex();
extern int yylineno;
extern char *yytext;
extern int yywrap();
extern int printSymbolTable();


struct table
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

typedef struct expression *expressionTree;
typedef enum {PlusOp, MinusOp, TimesOp, DivideOp} optype;
struct expression {
enum {operatorExp, constantExp, variableExp} kind;
union {
struct {
optype op;
expressionTree left;
expressionTree right;
} oper;
int constantval;
char *variable;
} u;
};

enum treetype {operator_node, number_node, variable_node};
typedef struct tree {
enum treetype nodetype;
union{
int a_number;
char a_variable;
struct {struct tree 
	*left,
	*right;
	char opp;
	} an_operator;
}body;
}tree;

//new methods
extern struct node* createNode(char*);
extern struct node* createSibling(node*,node*);
void gen(struct node*);
void fgen(struct node*);

%}

%union {char val[50];int num;float decimal;char *ptr;struct node* new1;struct tree* a_tree;}       
%token <val> CMP
%token <val>READ
%token <val>PRINT
%token <val> LOOP
%token <val>EQUALS
%token <val> IDENTIFIER
%token <val> FLOAT 
%token <val> BOOLEAN 
%token <val> NUMBER 
%token <val> INTEGER
%token <val> STRING  
%token <val> MAIN FUNCTIONS RETURN CONSTANTS
%token <val> IF THEN ELSE WHILE
%token <val>  OB CB ASSGNMT COMP BOOLOP PDF TWOPDF MOD 


%type <new1> PROGRAM  
%type <val> CDEFS CDEF CNAME  SPARAM  
%type <new1> FDEFS FDEF ARGS 
%type <val>  FNAME  ARG RETARG

%type <new1> STATEMENTS STATEMENT ASSIGNSTAT PRINTSTAT READSTAT IFSTAT LOOPSTAT WHILESTAT
%type <new1> IDENTIFIERS
%type <new1> PARAM PARAMS 
%type <new1> PRINT_PARAMS 
%type <new1> PRINT_PARAM 
%type <val> PARAM1 PARAM2 PARAM3 PARAM4
%type <new1> FUNCALL 
%type <val> FUNNAME
%type <new1> EXP


%start PROGRAM

%right THEN ELSE

%%

/* YACC definations */
PROGRAM : CONSTANTS CDEFS
	  FUNCTIONS FDEFS 	   	
	  MAIN STATEMENTS          {printf("PARSED SUCCESSFULLY: \n ");
				   //$$=createNode("PROGRAM");
				    //$$->child=createNode($3); 
				    //$$->child->sib=createNode($5);



				    //$$->child->child=$4;
				    //$3->sib=createNode($5);
				    //$3->child=$4;
			            //$5->child=$6; 

				   $$=createNode($5);
				   $$->child=$6;
       				   gen($$);

				   $$->sib=createNode("FUNCTIONS");
				   $$->sib->child=$4;
				   if ($4==NULL){
					printf("no function call found\n");
				   }	
				   else{
				   fgen($$->sib);
				   }
				   };
	  
CDEFS :    /*empty*/{;}
	| CDEFS CDEF        { ;};
CDEF :  OB CNAME SPARAM CB {int pos=lookup($2);setConstant(pos,$3);};
CNAME : IDENTIFIER         {;};
SPARAM : INTEGER{;}
 	|STRING {;} 
	|BOOLEAN {;}
	| FLOAT {;} 
        ; 

FDEFS : {;}
        |       FDEFS FDEF      {
				  if ($$ == NULL){
                                                $$=$2;
                                                }else{
                                                        if ($1->sib == NULL){
                                                                $1->sib=$2;
                                                        }else{
                                                                 struct node *head;
                                                                head=(struct node *)malloc(sizeof(node));
                                                                for(head=$1;head->sib!=NULL;head=head->sib){
                                                                 }
                                                                head->sib = $2;
                                                                }
                                                        $$=$1;
                                                        }
				};

FDEF : OB FNAME ARGS RETURN RETARG STATEMENTS CB {strcpy(st[funoffset].type,"f");
						  st[funoffset].elementNumber=vcounter;
						  $$=createNode($2);
						  $$->child=$3;
						  $$->child->child=createNode($5);
						  $$->child->child->child = $6;
						  };

FNAME : IDENTIFIER         {funoffset=lookup($1);};


ARGS : ARG	{ 		
			 char *p1 = $1;
			 char *p2;
			 p2=strdup(p1);
			st[funoffset].fargs[vcounter]=p2;
			vcounter=vcounter+1;
			$$=createNode($1);
			}
|      ARGS ARG   {      
			
			  if ($1->sib == NULL){
                                        $1->sib = createNode($2);
                                        $$=$1;
                                       }else{
                                              struct node *head;
                                               head=(struct node *)malloc(sizeof(node));
                                               for(head=$1;head->sib!=NULL;head=head->sib){
                                                }
                                             head->sib = createNode($2);
                                             $$=$1;
                                             }

			 char *p4 = $2;
			 char *p5;
			 p5=strdup(p4);
			st[funoffset].fargs[1]=p5;
			//printf("from the arg: %s \n",st[3].fargs[1]);
			vcounter=vcounter+1;
			};

ARG: IDENTIFIER {;};

RETARG : IDENTIFIER     {;};
STATEMENTS :   {;}
                |STATEMENTS STATEMENT   {
					if ($$ == NULL){
                                        	$$=$2;
                                       		}else{
							if ($1->sib == NULL){
								$1->sib=$2;
							}else{
								 struct node *head;
                                                        	head=(struct node *)malloc(sizeof(node));
                                                        	for(head=$1;head->sib!=NULL;head=head->sib){
                                                       		 }
                                                        	head->sib = $2;
								}
                                             		$$=$1;
                                             		}
						
					};

STATEMENT : ASSIGNSTAT {newcount=newcount+1;} 
          | PRINTSTAT    {newcount=newcount+1;}   
          | READSTAT  {$$=$1;newcount=newcount+1;}
          | IFSTAT {newcount=newcount+1;}
          | LOOPSTAT{newcount=newcount+1;}
          | WHILESTAT {newcount=newcount+1;}
          | EXP { newcount=newcount+1;};

ASSIGNSTAT : OB EQUALS IDENTIFIER PARAM CB   {
						$$=createNode($2);
						$$->child=createNode($3);// pass up
					        $$->child->sib=$4; // sibling
					       };

READSTAT : 	OB 
		READ 
		IDENTIFIERS
		CB {
			$$=createNode($2);
			$$->child=$3;
		   };
		
IDENTIFIERS : IDENTIFIER {
			$$=createNode($1);
			}
	    | IDENTIFIERS IDENTIFIER {
				
				if ($1->sib == NULL){
                                	$1->sib = createNode($2);
                                        $$=$1;
                                       }else{
                                              struct node *head;
                                               head=(struct node *)malloc(sizeof(node));
                                               for(head=$1;head->sib!=NULL;head=head->sib){
                                             	}
                                             head->sib = createNode($2);
                                             $$=$1;
                                             }
			 };

PRINTSTAT : OB PRINT PRINT_PARAMS CB    {
					$$=createNode($2);//printnode
					$$->child=$3;
					//printf("child would be %s \n\n",$$->name);
//					printf("child would be %s \n\n",$$->child->sib->sib->sib->sib->name);
					};
					
PARAM : FUNCALL{/*rule1*/;} | 
		IDENTIFIER{/*rule2*/;$$=createNode($1);strcpy($$->mytype,"id");} | 
	    INTEGER {/*rule3*/;$$=createNode($1);}| 
	    STRING {/*rule3*/;$$=createNode($1);} | 
	    FLOAT   {/*rule3*/;$$=createNode($1);};
					
FUNCALL : OB FUNNAME PARAMS CB           {int post=lookup($2);
					 if (post>0) 
						{ st[post].nextline=linecount;
					        };
					 $$=createNode($2);
                                         $$->child=$3;
					 }
	| OB MOD PARAM1 PARAM2 CB	 {
					  	$$=createNode($2);
                                          	$$->child=createNode($3);
                                         	$$->child->sib=createNode($4);
					  }
	| OB TWOPDF PARAM3 PARAM4 CB	 {
					  $$=createNode($2);
					  $$->child=createNode($3);
					  $$->child->sib=createNode($4);
					 }
	;
PARAM1  :  INTEGER {;}| IDENTIFIER {;};
PARAM2  :  INTEGER {;} | IDENTIFIER{;};
PARAM3	:  INTEGER {;}| FLOAT {;}| IDENTIFIER {;};	
PARAM4 	:  INTEGER {;}| FLOAT {;} | IDENTIFIER {;}; 

FUNNAME :  IDENTIFIER {;} 
        |PDF  {;}
	;
PARAMS:  {;}
		| PARAMS PARAM              { 
					        if ($1 == NULL){
							$$=$2;
						}else{
							if ($1->sib == NULL){
                                                		$1->sib = $2;
                                                		$$=$1;
                                           		 }else{
		                                              struct node *head;
        	                                              head=(struct node *)malloc(sizeof(node));
                       		                              for(head=$1;head->sib!=NULL;head=head->sib){
                                      			          }
                                            		       head->sib = $2;
	                                             		$$=$1;
							 }
						}
					     };
PRINT_PARAMS : PRINT_PARAM {$$=$1;}
	     | PRINT_PARAMS PRINT_PARAM   {
					     //printf("\n %s ",$$->name);
					     if ($1->sib == NULL){
						$1->sib = $2;
						$$=$1;
					  	}else{
							struct node *head;
 							head=(struct node *)malloc(sizeof(node));
							for(head=$1;head->sib!=NULL;head=head->sib){
							}
							head->sib = $2;
							$$=$1;
							}	
							
					    };

PRINT_PARAM : IDENTIFIER {initialisetable($1,offset);
			 $$=createNode($1);}
	    |FLOAT {
		    $$=createNode($1);}
	    | STRING {
			$$=createNode($1);} ;

IFSTAT:  OB 		
	 IF 
	 EXP 
	 THEN 
	 STATEMENTS 
	 CB {;}
	| OB 
	  IF
	  EXP
	  THEN 
	  STATEMENTS 
	  ELSE 
	  STATEMENTS 
	  CB {
	     $$=createNode($2);
	     $$->child=$3;
	     
	     $$->sib=$7;

	     $$->child->child=$5;
	     };

LOOPSTAT: OB LOOP IDENTIFIER  STATEMENTS CB {;};
WHILESTAT : OB WHILE EXP STATEMENTS CB {
					$$=createNode($2);
					$$->child=$3;
					$$->child->child=$4;
					};
EXP : OB CMP PARAM PARAM CB {
				 $$=createNode($2);
			         $$->sib=$3;
			         $$->sib->sib=$4;
				}
    | OB BOOLEAN CB {;};


%%                   
int main (int argc, char* argv[]) {
fileOpen();
yyparse ( );
printSymbolTable();
fileClose();
return 0;
}

void setConstant(int pos,char constantValue[20]){
//printf("at offset %d set value: %s\n",pos,constantValue);
strcpy(st[pos].value,constantValue);
strcpy(st[pos].type,"constant");
}


void yyerror (char *s) {fprintf (stderr, "%s\n", s);} 
