struct node{
	//   enum treetype nodetype;
	char name[50];
	struct node* child;
	struct node* sib;
	struct node* addr;
	struct node* parent;
	int parentFlag;
	char mytype[1];
};

