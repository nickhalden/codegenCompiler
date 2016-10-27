#include <iostream>
#include <stdio.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <sstream>
#include <queue>
#include <list>
#include "operations.h"
#include <fstream>

extern int newcount;
int mycount=0;
int linecount = 1;
int printLine = 0;
int temporaryIncrementer = 1;
extern int offset;
int registerCount = 0;
extern void printSymbolTable();
struct node* buildTree(char*);
void traverseTree(struct node*);
void processStack();
int count = 0;

ofstream myfile;
ofstream addfile;
int label = 0;

using namespace std;

stack<node*> nodeStack;
queue<char*> printData;
extern int lookup(char*);
extern struct table {
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
} st[100];

//helpers
string IntToString(int a) {
	ostringstream temp;
	temp << a;
	return temp.str();
}

string temporaryVariableGenerator(string temp) {
	string str = "t" + IntToString(temporaryIncrementer);
	return str;
}

void updateTable(const char* updateIdentifier) {
	offset = offset + 1;
	strcpy(st[offset].name, updateIdentifier);
	cout << " updating the table with : " << updateIdentifier << "and at: "
			<< offset << endl;

}
//
void readcodegen(char* param) {
	int pos = lookup(param);
	myfile << "\n" << linecount << " read M[" << st[pos].offsetinfo << "]"
			<< endl;

	cout << "\n" << linecount << " read M[" << st[pos].offsetinfo << "]"
			<< endl;
	linecount = linecount + 1;
}

void assignmentCodegen(char* identifier, char* variable) {

	if (strcmp(variable, "{") == 0) {
		//cout << "function call found<< \n"; deal with this
	} else {
		int pos1 = lookup(variable);
		int pos2 = lookup(identifier);
		if (pos1 != -100000) {
			myfile << linecount << " load R[" << registerCount << "]" << " M["
					<< pos1 << "];" << endl;

			cout << linecount << " load R[" << registerCount << "]" << " M["
					<< pos1 << "];" << endl;
			linecount = linecount + 1;

			cout << linecount << "store M[" << pos2 << "] R[" << registerCount
					<< "];" << endl;
			strcpy(st[pos2].value, st[pos1].value); //set the value up need to change this
			registerCount++;
			linecount = linecount + 1;

		} else {
			cout << linecount;
			cout << " load R[" << registerCount << "]" << " " << variable << ";"
					<< endl;
			registerCount++;
			linecount = linecount + 1;
		}

	}

}

char* conditionals(char *conditinal, char *operand1, char *operand2) {

	cout << "" << linecount << " " << conditinal << " R[" << registerCount
			<< "] ";

	myfile << "" << linecount << " " << conditinal << " R[" << registerCount
			<< "] ";

	int one = lookup(operand1);
	int two = lookup(operand2);

	if (one > 0) {
		cout << "M[" << one << "]";
		myfile << "M[" << one << "]";

	} else {
		cout << " " << operand1 << "";
		myfile << " " << operand1 << "";
	}
	if (two > 0) {
		cout << "M[" << two << "]";
		myfile << "M[" << two << "]";

	} else {
		cout << " " << operand2 << "";
		myfile << " " << operand2 << "";
	}

	cout << ";" << endl;
	myfile << ";" << endl;
	linecount = linecount + 1;
	return conditinal;
}
void loopingStatement(char *what) {
	cout << linecount << " " << what << " R[" << registerCount << "]";

	myfile << linecount << " " << what << " R[" << registerCount << "]";
	linecount = linecount + 1; //add a goto statement
}
//deals with the functions that have only two parameters % and /
void twoPDFCodegen(char* op, char* operand1, char* operand2) {
	char cnd[10];
	if (strcmp(op, "%") == 0) {
		strcpy(cnd, "MOD");
	} else if (strcmp(op, "-") == 0) {
		strcpy(cnd, "SUB");
	} else {
		strcpy(cnd, "DIV");
	}
	cout << linecount << " " << cnd << " R[" << registerCount << "] " << "R["
			<< registerCount << "] ";

	myfile << linecount << " " << cnd << " R[" << registerCount << "] " << "R["
			<< registerCount << "] ";

	int one = lookup(operand1);
	int two = lookup(operand2);


	if (one > 0) {
		cout << "M[" << one << "]";
		myfile << "M[" << one << "]";

	} else {
		cout << " " << operand1 << "";
		myfile << " " << operand1 << "";
	}
	if (two > 0) {
		cout << "M[" << two << "]";
		myfile << "M[" << two << "]";

	} else {
		cout << " " << operand2;
		myfile << " " << operand2;
	}
	//}
	cout << ";" << endl;
	myfile << ";" << endl;
	linecount = linecount + 1;
}

void callme(char* param) {
	printData.push(param);
	processPrintQueue(param);
}

void processPrintQueue(char *a) {
	if (strcmp(a, "}")) {
		if (printLine == 0) {
			cout << linecount << " print  ";

			myfile << linecount << " print  ";
			printLine = 1;
		}
		while (!printData.empty()) {
			char *check = printData.front();
			if (lookup(check) > 0) {
				cout << "M[" << lookup(check) << "]";
				myfile << "M[" << lookup(check) << "]";

			} else {
				cout << check;
				myfile << check;

			}
			printData.pop();
			cout << " ";
			myfile << " ";
		}

	} else {
		linecount = linecount + 1;
		cout << endl;
		myfile << endl;
	}
}

void pdfCodegen(char *fname) {
	char cnd[10];
	if (strcmp(fname, "+") == 0) {
		strcpy(cnd, "ADD");
		cout << cnd << " from the function" << endl;
		myfile << cnd << " from the function" << endl;
	} else {
		strcpy(cnd, "MUL");
	}

	//cout << FuData.front(); Function Data

}

void functionStack(string nonterminal, string second, string third) {
	stack<string> fstack;
	fstack.push(nonterminal);
	fstack.push(second);
	fstack.push(third);
	cout << "----" << fstack.top() << endl;
}

struct node* buildTree(char* element) {
	struct node *first;
	first = (struct node *) malloc(sizeof(node));
	strcpy(first->name, element);
	first->child = NULL;
	first->sib = NULL;
	first->parent = NULL;
	if (!nodeStack.empty()) {
		if (nodeStack.top()->parentFlag == 1) {

		} else {
			node *check = nodeStack.top();
			//first->sib=nodeStack.top();
			first->sib = check;
		}

	}
	nodeStack.push(first);
	return first;
}

void makeParent(char *parent, int count) {
	struct node *parentNode;
	parentNode = (struct node *) malloc(sizeof(node));
	strcpy(parentNode->name, parent);
	parentNode->child = nodeStack.top();
	parentNode->parentFlag = 1;
	//parentNode->parent=NULL;
	while (count > 0) {
		count = count - 1;
		nodeStack.pop();
	}
	if (!nodeStack.empty()) {
		parentNode->sib = nodeStack.top();
	} else {
	}
	nodeStack.push(parentNode);
	//cout << " size after adding " << parent << " "<< nodeStack.size() << " ";

}

void printStack() {
	//cout << " \ntaverse method called \n";
	//traverseTree(nodeStack.top());
}

void traverseTree(struct node* root) {
	if (root->sib) {
		traverseTree(root->sib);
	}
	cout << root->name << " ";
	if (root->child) {
		traverseTree(root->child);
		cout << " \n";
	}
	return;
}

void conditionalsTree(struct node* root, struct node* A, struct node* B) {
	root->child = A;
	A->sib = B;
	//readTree(root);
}

void readTree(node *root) {
	cout << "printingTree from read function\n";
	printf("%s ", root->child->name);
	printf("%s\n", root->child->sib->name);

}

void fileOpen() {
	myfile.open("sample2.mc");
	addfile.open("addFile");
	myfile << "goto L0;\n";

}
void fileClose() {
	myfile.close();
	addfile.close();
}

struct node* createNode(char *element) {
	struct node *first;
	first = (struct node *) malloc(sizeof(node));
	strcpy(first->name, element);
	first->child = NULL;
	first->sib = NULL;
	first->parent = NULL;
	return first;
}
struct node* createSibling(node *element1, node *element2) {
	//cout << "from function :" << element1->sib->name;
	//      << endl;
	struct node *head;
	head = (struct node *) malloc(sizeof(node));

	struct node *ret;
	ret = (struct node *) malloc(sizeof(node));

	for (head = element1; head->sib != NULL; head = head->sib) {
		cout << " iter the loop " << head->name;
	}

	if (head->sib == NULL) {
		cout << "if cond :" << element1->name;
		element1->sib = element2;
	}

	return element1;
}

void gen(struct node* root) {

	if (strcmp(root->name, "MAIN") == 0) {
		cout << "main" << endl;
		struct node *mhead;
		mhead = (struct node *) malloc(sizeof(node));
		mhead = root->child;
		for (mhead = root->child; mhead != NULL; mhead = mhead->sib) {
			gen(mhead);
		}
	}
	if (strcmp(root->name, "print") == 0) {
		addfile << root->name << " ";
		struct node *phead;
		phead = (struct node *) malloc(sizeof(node));
		for (phead = root->child; phead != NULL; phead = phead->sib) {
			if (lookup(phead->name) > 0) {
				addfile << " M[" << lookup(phead->name) << "] "
						<< st[lookup(phead->name)].value;
			} else {
				addfile << phead->name << " ";
			}
		}
		addfile << ";" << endl;
		mycount=mycount+1;
	}
	if (strcmp(root->name, "read") == 0) {
		//cout << root->name << " ";
		struct node *rhead;
		rhead = (struct node *) malloc(sizeof(node));
		for (rhead = root->child; rhead != NULL; rhead = rhead->sib) {
			addfile << "read M[" << lookup(rhead->name) << "];" << endl;
			mycount=mycount+1;
			//cout << rhead->name <<" ";
		}

	}
	if (strcmp(root->name, "=") == 0) {
		//cout << root->name << " ";
		struct node *ahead;
		ahead = (struct node *) malloc(sizeof(node));
		for (ahead = root->child; ahead != NULL; ahead = ahead->sib) {

			if (strcmp(ahead->name, "+") == 0) {
				gen(ahead);
			} else if (strcmp(ahead->name, "*") == 0) {
				gen(ahead);
			} else if (strcmp(ahead->name, "%") == 0) {
				gen(ahead);
			} else if (strcmp(ahead->name, "-") == 0) {
				gen(ahead);
			} else {

			}

		}
		addfile << "store " << "M[" << lookup(root->child->name) << "] " << "R"
				<< registerCount << ";" << endl;
		mycount=mycount+1;

	}
	if (strcmp(root->name, "while") == 0) {
		struct node *ahead;
		ahead = (struct node *) malloc(sizeof(node));
		for (ahead = root->child->sib; ahead != NULL; ahead = ahead->sib) {
			//exp node
			if (lookup(ahead->name) > 0) {
				cout << "load R[" << registerCount << "] M["
						<< lookup(ahead->name) << "]; " << endl;
				mycount=mycount+1;
			} else {
				cout << root->child->name << " R[" << registerCount << "] "
						<< ahead->name << ";";
			}
		}
		cout << endl;
		mycount=mycount+1;
		cout << "if R" << registerCount << " goto " << mycount + 2  << ";"
				<< endl;
		linecount = linecount + 1;
		cout << "goto " << " $ ;" << endl;
		mycount=mycount+1;
		struct node *ahead1;

		ahead1 = (struct node *) malloc(sizeof(node));
		for (ahead1 = root->child->child; ahead1 != NULL; ahead1 =
				ahead1->sib) {
			gen(ahead1);
		}
	}
	if (strcmp(root->name, "+") == 0) {
		int start = 0;
		struct node *ahead;
		ahead = (struct node *) malloc(sizeof(node));
		int flag = 0;
		if (strcmp(st[lookup(root->child->sib->name)].type, "constant") == 0) {
			addfile << "load R0 " << st[lookup(root->child->sib->name)].value
					<< ";" << endl;
			mycount=mycount+1;
			start = 1;
			flag = 1;

		}
		for (ahead = root->child->sib; ahead != NULL; ahead = ahead->sib) {

			if (strcmp(st[lookup(ahead->name)].type, "constant") == 0) {
				if (flag == 1)
					continue;
				else {
					start = 1;
					addfile << "load R" << start << " " << "M["
							<< lookup(ahead->name) << "];" << endl;
					mycount=mycount+1;
					addfile << "add " << "R" << start - 1 << " " << "R"
							<< start - 1 << " " << st[lookup(ahead->name)].value
							<< ";" << endl;
					mycount=mycount+1;
				}

			} else {
				addfile << "load R" << start << " " << "M["
						<< lookup(ahead->name) << "];" << endl;
				start = start + 1;
				if (start == 2) {
					addfile << "add " << "R" << start - 2 << " " << "R"
							<< start - 2 << " " << "R" << start - 1 << ";"
							<< endl;
					mycount=mycount+1;
					start = start - 1;
				}
			}

		}

		addfile << "load R" << start << " " << "M[" << lookup(root->child->name)
				<< "];" << endl;
		mycount=mycount+1;
		addfile << "add " << "R" << start - 1 << " " << "R" << start - 1 << " "
				<< "R" << start << ";" << endl;
		mycount=mycount+1;

		cout << endl;
	}
	if (strcmp(root->name, "%") == 0) {

		count = registerCount;
				int start = registerCount;
				struct node *ahead;
				ahead = (struct node *) malloc(sizeof(node));
				ahead = root->child;
				//cout << ahead->name << endl;
				for (ahead = root->child; ahead != NULL; ahead = ahead->sib) {
					if (lookup(ahead->name)>0) {
						cout << "load R" << registerCount << " M["
								<< lookup(ahead->name)
								<< "];";
						cout << endl;
						mycount=mycount+1;

					}else{
						cout << "mod" << " R"
								<< registerCount
								<< " R" << registerCount
								<< " "
								<< ahead->name
						        << ";";
						cout << endl;
						mycount=mycount+1;

					}

				}

	}
	if (strcmp(root->name, "-") == 0) {
		count = registerCount;
		int start = registerCount;
		struct node *ahead;
		ahead = (struct node *) malloc(sizeof(node));
		for (ahead = root->child; ahead != NULL; ahead = ahead->sib) {
			//addfile << endl;
			if (strcmp(st[lookup(ahead->name)].type, "constant") == 0) {
				addfile << "load R" << registerCount << " "
						<< st[lookup(ahead->name)].value;
				addfile << ";" << endl;
				mycount=mycount+1;
			} else {
				addfile << "load R" << registerCount << " " << "M["
						<< lookup(ahead->name) << "];" << endl;
				mycount=mycount+1;
				registerCount = registerCount + 1;
				//cout << "R " << st[lookup(ahead->name)];
			}
		}
		addfile << "sub R" << start;

		//cout << start+1;
		for (start; start <= registerCount; start++) {
			addfile << " " << "R" << start;
		}
		registerCount = count;
		addfile << ";";
		addfile << endl;
		mycount=mycount+1;
	}

	if (strcmp(root->name, "*") == 0) {
		int start = 0;
		struct node *ahead;
		ahead = (struct node *) malloc(sizeof(node));
		int flag = 0;
		if (strcmp(st[lookup(root->child->sib->name)].type, "constant") == 0) {
			cout << "load R0 " << st[lookup(root->child->sib->name)].value
					<< ";" << endl;
			mycount=mycount+1;
			start = 1;
			flag = 1;

		}
		for (ahead = root->child->sib; ahead != NULL; ahead = ahead->sib) {
			if (strcmp(st[lookup(ahead->name)].type, "constant") == 0) {
				if (flag == 1)
					continue;
				else {
					start = 1;
					cout << "load R" << start << " " << "M["
							<< lookup(ahead->name) << "];" << endl;
					mycount=mycount+1;
					cout << "mul " << "R" << start - 1 << " " << "R"
							<< start - 1 << " " << st[lookup(ahead->name)].value
							<< ";" << endl;
					mycount=mycount+1;
				}

			} else {
				cout << "load R" << start << " " << "M[" << lookup(ahead->name)
						<< "];" << endl;
				mycount=mycount+1;
				start = start + 1;
				if (start == 2) {
					cout << "add " << "R" << start - 2 << " " << "R"
							<< start - 2 << " " << "R" << start - 1 << ";"
							<< endl;
					mycount=mycount+1;
					start = start - 1;
				}
			}

		}

		cout << "load R" << start << " " << "M[" << lookup(root->child->name)
				<< "];" << endl;
		mycount=mycount+1;
		cout << "mul " << "R" << start - 1 << " " << "R" << start - 1 << " "
				<< "R" << start << ";" << endl;
		mycount=mycount+1;

	}
	if (strcmp(root->name, "if") == 0) {


		struct node *ahead;
		ahead = (struct node *) malloc(sizeof(node));
		for (ahead = root->child->sib; ahead != NULL; ahead = ahead->sib) {
			//exp node
			if (lookup(ahead->name) > 0) {
				cout << "load R[" << registerCount << "] M["
						<< lookup(ahead->name) << "]; " << endl;
				mycount=mycount+1;
			} else {
				cout << root->child->name << " R[" << registerCount << "] "
						<< ahead->name << ";";
				cout << endl;
				mycount=mycount+1;
			}
		}

		cout << "if R" << registerCount << " goto " << mycount + 2 << ";"
				<< endl;

		mycount=mycount+1;
		linecount = linecount + 1;
		cout << "goto " << " $ ;" << endl;
		mycount=mycount+1;
		struct node *ahead1;
		ahead1 = (struct node *) malloc(sizeof(node));
		for (ahead1 = root->child->child; ahead1 != NULL; ahead1 =
				ahead1->sib) {
			gen(ahead1);
		}
		mycount=mycount+1;
		cout << endl;

	}

}

void fgen(struct node* root) {

	if (strcmp(root->name, "FUNCTIONS") == 0) {
		cout << "label" << label << endl;
		struct node *mhead;
		mhead = (struct node *) malloc(sizeof(node));
		for (mhead = root->child->child->child->child; mhead != NULL; mhead =
				mhead->sib) {
			registerCount=registerCount+2;
			gen(mhead);
		}
		label = label + 1;
	}



}

