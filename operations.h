/*
 * operations.h
 *
 *  Created on: Mar 28, 2016
 *      Author: ravichawla
 */
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include "y.tab.h"
#include "symbolNode.h"
using namespace std;


void funtionStack(string,string,string);
void readcodegen(char*);
void assignmentCodegen(char*,char*);
void assignmentIdentifier(string);
char* conditionals(char*,char*,char*);
void loopingStatement(char*);
void twoPDFCodegen(char*,char*,char*);
void pdfCodegen(char*);

void makeParent(char*,int);
void printStack();

// another set of methods
struct node*  createNode(char*);
struct node* createSibling(node *,node *);
void gen(struct node*);

void printQueue(char *);
void processPrintQueue(char*);

void callme(char*);

string temporaryVariableGenerator(string);
void setConstant(int,char*);

extern struct node* buildTree(char*);

//helper functions
string IntToString (int );
void updateTable(char *);


//file operations
void fileOpen();
void fileClose();

