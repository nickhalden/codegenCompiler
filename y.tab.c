#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140101

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "FP.y"
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

/*new methods*/
extern struct node* createNode(char*);
extern struct node* createSibling(node*,node*);
void gen(struct node*);
void fgen(struct node*);

#line 92 "FP.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {char val[50];int num;float decimal;char *ptr;struct node* new1;struct tree* a_tree;} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 117 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define CMP 257
#define READ 258
#define PRINT 259
#define LOOP 260
#define EQUALS 261
#define IDENTIFIER 262
#define FLOAT 263
#define BOOLEAN 264
#define NUMBER 265
#define INTEGER 266
#define STRING 267
#define MAIN 268
#define FUNCTIONS 269
#define RETURN 270
#define CONSTANTS 271
#define IF 272
#define THEN 273
#define ELSE 274
#define WHILE 275
#define OB 276
#define CB 277
#define ASSGNMT 278
#define COMP 279
#define BOOLOP 280
#define PDF 281
#define TWOPDF 282
#define MOD 283
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    2,    3,    4,    4,    4,    4,    5,
    5,    6,    8,    7,    7,    9,   10,   11,   11,   12,
   12,   12,   12,   12,   12,   12,   13,   15,   19,   19,
   14,   20,   20,   20,   20,   20,   28,   28,   28,   24,
   24,   25,   25,   26,   26,   26,   27,   27,   27,   29,
   29,   21,   21,   22,   22,   23,   23,   23,   16,   16,
   17,   18,   30,   30,
};
static const short yylen[] = {                            2,
    6,    0,    2,    4,    1,    1,    1,    1,    1,    0,
    2,    7,    1,    1,    2,    1,    1,    0,    2,    1,
    1,    1,    1,    1,    1,    1,    5,    4,    1,    2,
    4,    1,    1,    1,    1,    1,    4,    5,    5,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    0,    2,    1,    2,    1,    1,    1,    6,    8,
    5,    5,    5,    3,
};
static const short yydefred[] = {                         0,
    2,    0,    0,   10,    0,    3,    0,    5,    0,   18,
    0,   11,    9,    8,    6,    7,    0,    0,   13,    0,
    4,    0,   19,   20,   21,   22,   23,   24,   25,   26,
   16,    0,   14,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   15,   33,   36,   34,   35,    0,    0,   32,
   29,    0,   56,   57,   58,    0,   54,   18,    0,   64,
    0,    0,   18,   17,   18,   50,   51,    0,    0,   52,
    0,   30,   28,   31,   55,    0,    0,   18,    0,    0,
   46,   45,   44,    0,   41,   40,    0,    0,   63,   61,
   27,    0,   62,   12,   49,   48,   47,    0,   43,   42,
    0,   37,   53,   18,   59,   39,   38,    0,   60,
};
static const short yydgoto[] = {                          2,
    3,    6,    9,   17,    7,   12,   32,   20,   33,   65,
   18,   23,   24,   25,   26,   27,   28,   29,   52,   49,
   88,   56,   57,   87,  101,   84,   98,   50,   70,   30,
};
static const short yysindex[] = {                      -222,
    0,    0, -232,    0, -229,    0, -234,    0, -210,    0,
 -199,    0,    0,    0,    0,    0, -198, -196,    0, -181,
    0, -245,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -253,    0, -231, -180, -215, -179, -178, -192, -190,
 -190, -175,    0,    0,    0,    0,    0, -260, -231,    0,
    0, -236,    0,    0,    0, -259,    0,    0, -231,    0,
 -214, -185,    0,    0,    0,    0,    0, -204, -256,    0,
 -188,    0,    0,    0,    0, -207, -187,    0, -205, -203,
    0,    0,    0, -202,    0,    0, -211, -238,    0,    0,
    0, -209,    0,    0,    0,    0,    0, -186,    0,    0,
 -184,    0,    0,    0,    0,    0,    0, -201,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   66,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,   60,    0,
  -58,    0,    0,    0,    0,    0,    0,    0,    0,  -48,
    0,    0,   38,    0,    0,    0,    0,    0,    0,   37,
};
#define YYTABLESIZE 94
static const short yytable[] = {                         76,
   71,   66,   53,   54,   79,   85,   80,   55,   31,   86,
   77,   34,   35,   36,   37,   38,   42,   74,   39,   92,
   67,   68,   69,   44,   45,   72,   40,   46,   47,   41,
   44,   45,    8,   10,   46,   47,    4,   48,  102,  103,
   73,   11,   34,    5,   48,  108,   53,   54,    1,   39,
   99,   55,   13,   14,  100,   15,   16,   81,   82,   95,
   96,   83,   19,   97,  104,    1,   22,  105,   22,   90,
   22,   93,   22,   94,   22,  109,   62,   63,   21,   22,
   31,   51,   58,   59,   60,   61,   64,   78,   89,   91,
  106,   43,  107,   75,
};
static const short yycheck[] = {                         58,
   49,  262,  262,  263,   63,  262,   65,  267,  262,  266,
   59,  257,  258,  259,  260,  261,  270,  277,  264,   78,
  281,  282,  283,  262,  263,  262,  272,  266,  267,  275,
  262,  263,  262,  268,  266,  267,  269,  276,  277,   88,
  277,  276,  257,  276,  276,  104,  262,  263,  271,  264,
  262,  267,  263,  264,  266,  266,  267,  262,  263,  262,
  263,  266,  262,  266,  274,    0,  276,  277,  276,  277,
  276,  277,  276,  277,  276,  277,   40,   41,  277,  276,
  262,  262,  262,  262,  277,  276,  262,  273,  277,  277,
  277,   32,  277,   56,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 283
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? (YYMAXTOKEN + 1) : (a))
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"CMP","READ","PRINT","LOOP",
"EQUALS","IDENTIFIER","FLOAT","BOOLEAN","NUMBER","INTEGER","STRING","MAIN",
"FUNCTIONS","RETURN","CONSTANTS","IF","THEN","ELSE","WHILE","OB","CB","ASSGNMT",
"COMP","BOOLOP","PDF","TWOPDF","MOD","illegal-symbol",
};
static const char *yyrule[] = {
"$accept : PROGRAM",
"PROGRAM : CONSTANTS CDEFS FUNCTIONS FDEFS MAIN STATEMENTS",
"CDEFS :",
"CDEFS : CDEFS CDEF",
"CDEF : OB CNAME SPARAM CB",
"CNAME : IDENTIFIER",
"SPARAM : INTEGER",
"SPARAM : STRING",
"SPARAM : BOOLEAN",
"SPARAM : FLOAT",
"FDEFS :",
"FDEFS : FDEFS FDEF",
"FDEF : OB FNAME ARGS RETURN RETARG STATEMENTS CB",
"FNAME : IDENTIFIER",
"ARGS : ARG",
"ARGS : ARGS ARG",
"ARG : IDENTIFIER",
"RETARG : IDENTIFIER",
"STATEMENTS :",
"STATEMENTS : STATEMENTS STATEMENT",
"STATEMENT : ASSIGNSTAT",
"STATEMENT : PRINTSTAT",
"STATEMENT : READSTAT",
"STATEMENT : IFSTAT",
"STATEMENT : LOOPSTAT",
"STATEMENT : WHILESTAT",
"STATEMENT : EXP",
"ASSIGNSTAT : OB EQUALS IDENTIFIER PARAM CB",
"READSTAT : OB READ IDENTIFIERS CB",
"IDENTIFIERS : IDENTIFIER",
"IDENTIFIERS : IDENTIFIERS IDENTIFIER",
"PRINTSTAT : OB PRINT PRINT_PARAMS CB",
"PARAM : FUNCALL",
"PARAM : IDENTIFIER",
"PARAM : INTEGER",
"PARAM : STRING",
"PARAM : FLOAT",
"FUNCALL : OB FUNNAME PARAMS CB",
"FUNCALL : OB MOD PARAM1 PARAM2 CB",
"FUNCALL : OB TWOPDF PARAM3 PARAM4 CB",
"PARAM1 : INTEGER",
"PARAM1 : IDENTIFIER",
"PARAM2 : INTEGER",
"PARAM2 : IDENTIFIER",
"PARAM3 : INTEGER",
"PARAM3 : FLOAT",
"PARAM3 : IDENTIFIER",
"PARAM4 : INTEGER",
"PARAM4 : FLOAT",
"PARAM4 : IDENTIFIER",
"FUNNAME : IDENTIFIER",
"FUNNAME : PDF",
"PARAMS :",
"PARAMS : PARAMS PARAM",
"PRINT_PARAMS : PRINT_PARAM",
"PRINT_PARAMS : PRINT_PARAMS PRINT_PARAM",
"PRINT_PARAM : IDENTIFIER",
"PRINT_PARAM : FLOAT",
"PRINT_PARAM : STRING",
"IFSTAT : OB IF EXP THEN STATEMENTS CB",
"IFSTAT : OB IF EXP THEN STATEMENTS ELSE STATEMENTS CB",
"LOOPSTAT : OB LOOP IDENTIFIER STATEMENTS CB",
"WHILESTAT : OB WHILE EXP STATEMENTS CB",
"EXP : OB CMP PARAM PARAM CB",
"EXP : OB BOOLEAN CB",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 408 "FP.y"
                   
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
#line 410 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 134 "FP.y"
	{printf("PARSED SUCCESSFULLY: \n ");
				   /*$$=createNode("PROGRAM");*/
				    /*$$->child=createNode($3); */
				    /*$$->child->sib=createNode($5);*/



				    /*$$->child->child=$4;*/
				    /*$3->sib=createNode($5);*/
				    /*$3->child=$4;*/
			            /*$5->child=$6; */

				   yyval.new1=createNode(yystack.l_mark[-1].val);
				   yyval.new1->child=yystack.l_mark[0].new1;
       				   gen(yyval.new1);

				   yyval.new1->sib=createNode("FUNCTIONS");
				   yyval.new1->sib->child=yystack.l_mark[-2].new1;
				   if (yystack.l_mark[-2].new1==NULL){
					printf("no function call found\n");
				   }	
				   else{
				   fgen(yyval.new1->sib);
				   }
				   }
break;
case 2:
#line 160 "FP.y"
	{;}
break;
case 3:
#line 161 "FP.y"
	{ ;}
break;
case 4:
#line 162 "FP.y"
	{int pos=lookup(yystack.l_mark[-2].val);setConstant(pos,yystack.l_mark[-1].val);}
break;
case 5:
#line 163 "FP.y"
	{;}
break;
case 6:
#line 164 "FP.y"
	{;}
break;
case 7:
#line 165 "FP.y"
	{;}
break;
case 8:
#line 166 "FP.y"
	{;}
break;
case 9:
#line 167 "FP.y"
	{;}
break;
case 10:
#line 170 "FP.y"
	{;}
break;
case 11:
#line 171 "FP.y"
	{
				  if (yyval.new1 == NULL){
                                                yyval.new1=yystack.l_mark[0].new1;
                                                }else{
                                                        if (yystack.l_mark[-1].new1->sib == NULL){
                                                                yystack.l_mark[-1].new1->sib=yystack.l_mark[0].new1;
                                                        }else{
                                                                 struct node *head;
                                                                head=(struct node *)malloc(sizeof(node));
                                                                for(head=yystack.l_mark[-1].new1;head->sib!=NULL;head=head->sib){
                                                                 }
                                                                head->sib = yystack.l_mark[0].new1;
                                                                }
                                                        yyval.new1=yystack.l_mark[-1].new1;
                                                        }
				}
break;
case 12:
#line 188 "FP.y"
	{strcpy(st[funoffset].type,"f");
						  st[funoffset].elementNumber=vcounter;
						  yyval.new1=createNode(yystack.l_mark[-5].val);
						  yyval.new1->child=yystack.l_mark[-4].new1;
						  yyval.new1->child->child=createNode(yystack.l_mark[-2].val);
						  yyval.new1->child->child->child = yystack.l_mark[-1].new1;
						  }
break;
case 13:
#line 196 "FP.y"
	{funoffset=lookup(yystack.l_mark[0].val);}
break;
case 14:
#line 199 "FP.y"
	{ 		
			 char *p1 = yystack.l_mark[0].val;
			 char *p2;
			 p2=strdup(p1);
			st[funoffset].fargs[vcounter]=p2;
			vcounter=vcounter+1;
			yyval.new1=createNode(yystack.l_mark[0].val);
			}
break;
case 15:
#line 207 "FP.y"
	{      
			
			  if (yystack.l_mark[-1].new1->sib == NULL){
                                        yystack.l_mark[-1].new1->sib = createNode(yystack.l_mark[0].val);
                                        yyval.new1=yystack.l_mark[-1].new1;
                                       }else{
                                              struct node *head;
                                               head=(struct node *)malloc(sizeof(node));
                                               for(head=yystack.l_mark[-1].new1;head->sib!=NULL;head=head->sib){
                                                }
                                             head->sib = createNode(yystack.l_mark[0].val);
                                             yyval.new1=yystack.l_mark[-1].new1;
                                             }

			 char *p4 = yystack.l_mark[0].val;
			 char *p5;
			 p5=strdup(p4);
			st[funoffset].fargs[1]=p5;
			/*printf("from the arg: %s \n",st[3].fargs[1]);*/
			vcounter=vcounter+1;
			}
break;
case 16:
#line 229 "FP.y"
	{;}
break;
case 17:
#line 231 "FP.y"
	{;}
break;
case 18:
#line 232 "FP.y"
	{;}
break;
case 19:
#line 233 "FP.y"
	{
					if (yyval.new1 == NULL){
                                        	yyval.new1=yystack.l_mark[0].new1;
                                       		}else{
							if (yystack.l_mark[-1].new1->sib == NULL){
								yystack.l_mark[-1].new1->sib=yystack.l_mark[0].new1;
							}else{
								 struct node *head;
                                                        	head=(struct node *)malloc(sizeof(node));
                                                        	for(head=yystack.l_mark[-1].new1;head->sib!=NULL;head=head->sib){
                                                       		 }
                                                        	head->sib = yystack.l_mark[0].new1;
								}
                                             		yyval.new1=yystack.l_mark[-1].new1;
                                             		}
						
					}
break;
case 20:
#line 251 "FP.y"
	{newcount=newcount+1;}
break;
case 21:
#line 252 "FP.y"
	{newcount=newcount+1;}
break;
case 22:
#line 253 "FP.y"
	{yyval.new1=yystack.l_mark[0].new1;newcount=newcount+1;}
break;
case 23:
#line 254 "FP.y"
	{newcount=newcount+1;}
break;
case 24:
#line 255 "FP.y"
	{newcount=newcount+1;}
break;
case 25:
#line 256 "FP.y"
	{newcount=newcount+1;}
break;
case 26:
#line 257 "FP.y"
	{ newcount=newcount+1;}
break;
case 27:
#line 259 "FP.y"
	{
						yyval.new1=createNode(yystack.l_mark[-3].val);
						yyval.new1->child=createNode(yystack.l_mark[-2].val);/* pass up*/
					        yyval.new1->child->sib=yystack.l_mark[-1].new1; /* sibling*/
					       }
break;
case 28:
#line 268 "FP.y"
	{
			yyval.new1=createNode(yystack.l_mark[-2].val);
			yyval.new1->child=yystack.l_mark[-1].new1;
		   }
break;
case 29:
#line 273 "FP.y"
	{
			yyval.new1=createNode(yystack.l_mark[0].val);
			}
break;
case 30:
#line 276 "FP.y"
	{
				
				if (yystack.l_mark[-1].new1->sib == NULL){
                                	yystack.l_mark[-1].new1->sib = createNode(yystack.l_mark[0].val);
                                        yyval.new1=yystack.l_mark[-1].new1;
                                       }else{
                                              struct node *head;
                                               head=(struct node *)malloc(sizeof(node));
                                               for(head=yystack.l_mark[-1].new1;head->sib!=NULL;head=head->sib){
                                             	}
                                             head->sib = createNode(yystack.l_mark[0].val);
                                             yyval.new1=yystack.l_mark[-1].new1;
                                             }
			 }
break;
case 31:
#line 291 "FP.y"
	{
					yyval.new1=createNode(yystack.l_mark[-2].val);/*printnode*/
					yyval.new1->child=yystack.l_mark[-1].new1;
					/*printf("child would be %s \n\n",$$->name);*/
/*					printf("child would be %s \n\n",$$->child->sib->sib->sib->sib->name);*/
					}
break;
case 32:
#line 298 "FP.y"
	{/*rule1*/;}
break;
case 33:
#line 299 "FP.y"
	{/*rule2*/;yyval.new1=createNode(yystack.l_mark[0].val);strcpy(yyval.new1->mytype,"id");}
break;
case 34:
#line 300 "FP.y"
	{/*rule3*/;yyval.new1=createNode(yystack.l_mark[0].val);}
break;
case 35:
#line 301 "FP.y"
	{/*rule3*/;yyval.new1=createNode(yystack.l_mark[0].val);}
break;
case 36:
#line 302 "FP.y"
	{/*rule3*/;yyval.new1=createNode(yystack.l_mark[0].val);}
break;
case 37:
#line 304 "FP.y"
	{int post=lookup(yystack.l_mark[-2].val);
					 if (post>0) 
						{ st[post].nextline=linecount;
					        };
					 yyval.new1=createNode(yystack.l_mark[-2].val);
                                         yyval.new1->child=yystack.l_mark[-1].new1;
					 }
break;
case 38:
#line 311 "FP.y"
	{
					  	yyval.new1=createNode(yystack.l_mark[-3].val);
                                          	yyval.new1->child=createNode(yystack.l_mark[-2].val);
                                         	yyval.new1->child->sib=createNode(yystack.l_mark[-1].val);
					  }
break;
case 39:
#line 316 "FP.y"
	{
					  yyval.new1=createNode(yystack.l_mark[-3].val);
					  yyval.new1->child=createNode(yystack.l_mark[-2].val);
					  yyval.new1->child->sib=createNode(yystack.l_mark[-1].val);
					 }
break;
case 40:
#line 322 "FP.y"
	{;}
break;
case 41:
#line 322 "FP.y"
	{;}
break;
case 42:
#line 323 "FP.y"
	{;}
break;
case 43:
#line 323 "FP.y"
	{;}
break;
case 44:
#line 324 "FP.y"
	{;}
break;
case 45:
#line 324 "FP.y"
	{;}
break;
case 46:
#line 324 "FP.y"
	{;}
break;
case 47:
#line 325 "FP.y"
	{;}
break;
case 48:
#line 325 "FP.y"
	{;}
break;
case 49:
#line 325 "FP.y"
	{;}
break;
case 50:
#line 327 "FP.y"
	{;}
break;
case 51:
#line 328 "FP.y"
	{;}
break;
case 52:
#line 330 "FP.y"
	{;}
break;
case 53:
#line 331 "FP.y"
	{ 
					        if (yystack.l_mark[-1].new1 == NULL){
							yyval.new1=yystack.l_mark[0].new1;
						}else{
							if (yystack.l_mark[-1].new1->sib == NULL){
                                                		yystack.l_mark[-1].new1->sib = yystack.l_mark[0].new1;
                                                		yyval.new1=yystack.l_mark[-1].new1;
                                           		 }else{
		                                              struct node *head;
        	                                              head=(struct node *)malloc(sizeof(node));
                       		                              for(head=yystack.l_mark[-1].new1;head->sib!=NULL;head=head->sib){
                                      			          }
                                            		       head->sib = yystack.l_mark[0].new1;
	                                             		yyval.new1=yystack.l_mark[-1].new1;
							 }
						}
					     }
break;
case 54:
#line 348 "FP.y"
	{yyval.new1=yystack.l_mark[0].new1;}
break;
case 55:
#line 349 "FP.y"
	{
					     /*printf("\n %s ",$$->name);*/
					     if (yystack.l_mark[-1].new1->sib == NULL){
						yystack.l_mark[-1].new1->sib = yystack.l_mark[0].new1;
						yyval.new1=yystack.l_mark[-1].new1;
					  	}else{
							struct node *head;
 							head=(struct node *)malloc(sizeof(node));
							for(head=yystack.l_mark[-1].new1;head->sib!=NULL;head=head->sib){
							}
							head->sib = yystack.l_mark[0].new1;
							yyval.new1=yystack.l_mark[-1].new1;
							}	
							
					    }
break;
case 56:
#line 365 "FP.y"
	{initialisetable(yystack.l_mark[0].val,offset);
			 yyval.new1=createNode(yystack.l_mark[0].val);}
break;
case 57:
#line 367 "FP.y"
	{
		    yyval.new1=createNode(yystack.l_mark[0].val);}
break;
case 58:
#line 369 "FP.y"
	{
			yyval.new1=createNode(yystack.l_mark[0].val);}
break;
case 59:
#line 377 "FP.y"
	{;}
break;
case 60:
#line 385 "FP.y"
	{
	     yyval.new1=createNode(yystack.l_mark[-6].val);
	     yyval.new1->child=yystack.l_mark[-5].new1;
	     
	     yyval.new1->sib=yystack.l_mark[-1].new1;

	     yyval.new1->child->child=yystack.l_mark[-3].new1;
	     }
break;
case 61:
#line 394 "FP.y"
	{;}
break;
case 62:
#line 395 "FP.y"
	{
					yyval.new1=createNode(yystack.l_mark[-3].val);
					yyval.new1->child=yystack.l_mark[-2].new1;
					yyval.new1->child->child=yystack.l_mark[-1].new1;
					}
break;
case 63:
#line 400 "FP.y"
	{
				 yyval.new1=createNode(yystack.l_mark[-3].val);
			         yyval.new1->sib=yystack.l_mark[-2].new1;
			         yyval.new1->sib->sib=yystack.l_mark[-1].new1;
				}
break;
case 64:
#line 405 "FP.y"
	{;}
break;
#line 1045 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
