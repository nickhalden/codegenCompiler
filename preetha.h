struct elementNode{
	char id[50];
	char type[20]; 
	int offset;
}element;
struct hashtable{
	int size;
	element* member;
	
} ht[100];
