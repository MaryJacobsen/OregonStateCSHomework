/*************************************************************************
** File: list.h
** Description: declaration of a linked list and function prototypes for it
** Input: none
** Output: none
*************************************************************************/

struct node{
   	int val;
	struct node *next;
	struct node *prev;
};

struct list{
   	struct node *head;
	struct node *tail;
};

int length(struct list); //return number of nodes in list
void print(struct list); //print the value of nodes in list
void push_front(struct list *, int); //push to front of list
void push_back(struct list *, int); //push to end of list

void clear(struct list *); //remove all nodes from list
void remove_val(struct list *, int); //remove all nodes w/ int as val
void sort_ascending(struct list *); 
void sort_descending(struct list *);

//insert into a location in the list, start at 0 for front
void insert(struct list*, int, int);
