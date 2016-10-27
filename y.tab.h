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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {char val[50];int num;float decimal;char *ptr;struct node* new1;struct tree* a_tree;} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
