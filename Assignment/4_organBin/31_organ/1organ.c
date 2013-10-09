#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOODTYPESIZE 5


typedef struct {
	int month;
	int day;
	int year;
} dateT;

// Time
typedef struct {
	int hour;
	int minute;
} timeT;
// Patient on waiting list
typedef struct {
	char * name;
	char * organname;
	char bloodtype[BLOODTYPESIZE];
	dateT dateAdded ;
	timeT timeAdded;
	int received;
} organT;

struct node {
	organT patient ;
	struct node * left ;
	struct node * right ;
};

struct node * allocNode(){

	char ch ;
	char * name = (char *)malloc(sizeof(char)*20);
	char * organname = (char *)malloc(sizeof(char)*20);

	char bloodtype[BLOODTYPESIZE];
	int month ;
	int day;
	int year ;

	int hour ;
	int minute;

	scanf("%s %s %s %d%c%d%c%d %d%c%d",name,organname,bloodtype,&month,&ch,&day,&ch,&year,&hour,&ch,&minute);

	struct node * nodes = (struct node * ) malloc(sizeof(struct node));
	nodes->patient.name = (char *) malloc(sizeof(char)*strlen(name));
	nodes->patient.organname = (char *) malloc(sizeof(char)*strlen(bloodtype));
	nodes->patient.received = 0 ;

	strcpy(nodes->patient.name,name);
	strcpy(nodes->patient.organname,organname);
	strcpy(nodes->patient.bloodtype,bloodtype);

	nodes->patient.dateAdded.month = month;
	nodes->patient.dateAdded.day= day ;
	nodes->patient.dateAdded.year = year;

	nodes->patient.timeAdded.minute= minute;
	nodes->patient.timeAdded.hour = hour ;
	nodes->left = NULL ;
	nodes->right = NULL ;

	free(name);
	free(organname);

	return nodes ;
}
struct node * insert(struct node * root, struct node * element){
	if ( root == NULL ){
		return element ;
	}
	else{
		if ( strcmp(root->patient.organname,element->patient.organname)==0){
			if ( strcmp(root->patient.bloodtype,element->patient.bloodtype)==0){
				if ( root->patient.dateAdded.year > element->patient.dateAdded.year ){
					if ( root->right != NULL ){
						root->right= insert(root->right,element);
					}
					else{
						root->right = element ;
					}
				}
				else if (root->patient.dateAdded.year < element->patient.dateAdded.year ){
					if ( root->left != NULL ){
						root->left = insert(root->left ,element);
					}
					else{
						root->left = element ;
					}
				}
				else{
					if ( root->patient.dateAdded.month < element->patient.dateAdded.month ){
						if ( root->right != NULL ){
							root->right= insert(root->right,element);
						}
						else{
							root->right = element ;
						}
					}
					else if ( root->patient.dateAdded.month > element->patient.dateAdded.month ){
						if ( root->left != NULL ){
							root->left = insert(root->left,element);
						}
						else{
							root->left = element ;
						}
					}
					else{
						if ( root->patient.dateAdded.day < element->patient.dateAdded.day ){
							if ( root->right != NULL ){
								root->right= insert(root->right,element);
							}
							else{
								root->right = element ;
							}
						}
						else if ( root->patient.dateAdded.day > element->patient.dateAdded.day ){
							if ( root->left != NULL ){
								root->left = insert(root->left,element);
							}
							else{
								root->left = element ;
							}
						}
						else{
							printf("");
						}
					}
				}
			}
			else{
				if (root->right != NULL){
					root->right = insert(root->right,element);
				}
				else{
					root->right = element ;
				}
			}
		}
		else{
			if ( root->right != NULL ){
				root->right= insert(root->right,element);
			}
			else{
				root->right = element ;
			}
		}
	}
	return root ;
}

struct node * test(struct node * root,struct node * element){
	if ( root == NULL ){
		return element ;
	}
	else{
		if ( strcmp(root->patient.organname,element->patient.organname) == 0 ){
			if ( root->right!=NULL){
				root->right = test(root->right,element);
			}
			else{
				root->right = element ;
			}
		}
		else{
			if (root->left != NULL ){
				root->left = test(root->left,element);
			}
			else{
				root->left = element ;
			}
		}
	}
	return root ;
}
void printNodes(struct node * list){
	if ( list != NULL ){
		printNodes(list->left);
		printf("%s %s %s %d/%d/%d %d:%d\n",list->patient.name,list->patient.organname,list->patient.bloodtype,
							   			   list->patient.dateAdded.month,
										   list->patient.dateAdded.day,
										   list->patient.dateAdded.year,
										   list->patient.timeAdded.hour,
										   list->patient.timeAdded.minute);
		printNodes(list->right);
	}
}
struct node * read(){
	int numLines ;
	scanf("%d",&numLines);
	int i = 0 ;
	struct node * nodes = allocNode();
	struct node * hlpr = nodes ;
	for ( i = 1 ; i < numLines ; i++){
		nodes->left=allocNode();
		nodes=nodes->left ;
	}
	return hlpr;
}

void print(struct node * nodes){
	struct node * list = nodes ;
	while ( list!= NULL ){
		printf("%s %s %s %d/%d/%d %d:%d\n",list->patient.name,list->patient.organname,list->patient.bloodtype,
							   			   list->patient.dateAdded.month,
										   list->patient.dateAdded.day,
										   list->patient.dateAdded.year,
										   list->patient.timeAdded.hour,
										   list->patient.timeAdded.minute);
		list=list->left;
	}
}

struct node * snip (struct node ** root,struct node * target ){
	struct node * hlpr = *root;
	struct node * found ;
	if ( *root != NULL ){
		if ( *root == target ){
			hlpr = *root ;
			*root = (*root)->left ;
			found = hlpr ;
			found->left = NULL ;
		}
		else{
			while ( hlpr->left != target ){
				hlpr=hlpr->left ;
			}
			found = hlpr->left ;
			hlpr->left=hlpr->left->left;
			found->left = NULL ;
		}
	}
	return found;
}
struct node * group(struct node * nodes, struct node * accum){
	struct node * hlp = nodes ;
	struct node * accumulate = accum ;
	while ( nodes != NULL ){
		if ( strcmp(nodes->patient.organname,accumulate->patient.organname) == 0 ){
			accumulate->left = snip(&hlp,nodes);
			accumulate=accumulate->left ;
			nodes = hlp ;
		}
		else{
			hlp = nodes ;
			nodes=nodes->left ;
		}
	}
	return accum;
}
int main(){
	struct node * nodes = read();
	struct node * accum = snip(&nodes,nodes);
	accum = group(nodes,accum);
	print(accum);
	printf("\n");
	print(nodes);
	printf("\n");
	accum = snip(&nodes,nodes);
	accum = group(nodes,accum);
	print(accum);
	printf("\n");
	print(nodes);
	printf("\n");
	accum = snip(&nodes,nodes);
	accum = group(nodes,accum);
	print(accum);
	printf("\n");
	print(nodes);
	printf("\n");
	accum = snip(&nodes,nodes);
	accum = group(nodes,accum);
	print(accum);
	printf("\n");
	print(nodes);
	printf("\n");
	accum = snip(&nodes,nodes);
	accum = group(nodes,accum);
	print(accum);
	printf("\n");
	print(nodes);
	printf("\n");
	accum = snip(&nodes,nodes);
	accum = group(nodes,accum);
	print(accum);
	printf("\n");
	print(nodes);
	printf("\n");
	accum = snip(&nodes,nodes);
	accum = group(nodes,accum);
	print(accum);
	printf("\n");
	print(nodes);
	printf("\n");
	return 0 ;
}