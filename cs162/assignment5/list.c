/*************************************************************************
** File: list.c
** Author: Mary Jacobsen
** Date: 06/04/16
** Description: implementation for the functions in list.c
** Input: list.h
** Output: functions to fill and sort a linked list of ints
*************************************************************************/
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*************************************************************************
** Function: length
** Description: returns the length of the linked list
** Parameters: a struct list
** Pre-Conditions: none
** Post-Conditions: returns an int
*************************************************************************/
int length(struct list l){
   	int count = 0;
   	struct node *temp = l.head;
   	while(temp != NULL){
	   	count++;
		temp = temp->next;
	}
//	printf("length = %d\n", count);
	return count;
}

/*************************************************************************
** Function: print
** Description: prints the linked list
** Parameters: a struct list
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
void print(struct list l){
   	int count = 0;
   	struct node *temp = l.head;
	while(temp != NULL){
		printf("%d ", temp->val);
		temp = temp->next;
	}
	printf("\n");
}

/*************************************************************************
** Function: push_front
** Description: adds a node to the front of the list
** Parameters: pointer to a struct list and a value
** Pre-Conditions: positive value for the node
** Post-Conditions: none
*************************************************************************/
void push_front(struct list *l, int n){
   	struct node *new_node = malloc(sizeof(struct node));
	new_node->val = n;
	new_node->prev = NULL;
	if(l->head == NULL){
	   	new_node->next = NULL;
	   	l->head = new_node;
		l->tail = new_node;
	}
	else{
	   	new_node->next = l->head;
		l->head->prev = new_node;
		l->head = new_node;
	}
}

/*************************************************************************
** Function: push_back
** Description: adds a node to the back of the list
** Parameters: pointer to a struct list and a value
** Pre-Conditions: positive value
** Post-Conditions: none
*************************************************************************/
void push_back(struct list *l, int n){
   	struct node *new_node = malloc(sizeof(struct node));
	new_node->val = n;
	new_node->next = NULL;
	if(l->tail == NULL){
	   	l->head = new_node;
		l->tail = new_node;
		new_node->prev = NULL;
	}
	else{
   		l->tail->next = new_node;
		new_node->prev = l->tail;
     		l->tail = new_node;
	}		
}

/*************************************************************************
** Function: clear
** Description: removes/frees all the nodes from the list
** Parameters: pointer to a struct list
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
void clear(struct list *l){
   	struct node *temp;
   	temp = l->head;
	while(temp != NULL){

	   	l->head = temp->next;
		free(temp);
		temp = l->head;
	}
}

/*************************************************************************
** Function: remove_val
** Description: removes all the nodes with the value passed in from the list
** Parameters: pointer to a struct list and a value
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
void remove_val(struct list *l, int n){
   	if(length(*l) < 2 && l->head->val == n){
	   	clear(l);
		return;
	}
	if(length(*l) < 2 && l->head->val != n){
	   	return;
	}
   	struct node *temp, *temp_temp;
   	temp = l->head;
	while(temp != NULL){
	   	if(l->head->val == n){
		   	l->head = temp->next;
			free(temp);
			temp = l->head;
			l->head->prev = NULL;
			continue;
		}
		if(l->tail->val == n){
		   	temp_temp = l->tail;
		   	l->tail = l->tail->prev;
			free(temp_temp);
			l->tail->next = NULL;
			continue;
		}
		else if(temp->val == n){
		   	temp_temp = temp;
		 	temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			temp = temp->next; 
			free(temp_temp);	
		}
		else{
		   	temp = temp->next;
		}
	}
}

/*************************************************************************
** Function: sort_ascending
** Description: sorts the values from smallest to largest
** Parameters: pointer to a struct list
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
void sort_ascending(struct list *l){
   	if(length(*l) < 2){
	   	return;
	}
	struct node *temp, *a, *b;
	int i, j, tempval;
	for(i=0; i<length(*l); i++){
	   	temp = l->head;
	      	for(j=0; j<length(*l)-1; j++){
		   	a = temp;
			b = temp->next;
			if(a->val > b->val){
			 	tempval = a->val;
				a->val = b->val;
				b->val = tempval;	
		//		a->next = b->next;
		//		a->prev = b;
		//		b->next = a;
		//		b->prev = temp->prev;
			//	if(j != length(*l)-2){
		//		   	a->next->prev = a;
			//	}
			//	if(temp != l->head){
		//			b->prev->next = b;
			//	}
			}
			temp = temp->next;
		}
	}
}

/*************************************************************************
** Function: sort_descending
** Description: sorts the values from biggest to smallest
** Parameters: pointer to a struct list
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
void sort_descending(struct list *l){
 	if(length(*l) < 2){
	   	return;
	}
	struct node *temp, *a, *b, *c, *d;
	int i, j, tempval;
	for(i=0; i<length(*l); i++){
	   	temp = l->tail;
		for(j=0; j<length(*l)-1; j++){
		   	a = temp;
			b = temp->prev;
		//	if(j != length(*l)-3){
		//		c = temp->prev->prev;
		//	}
		//	if(j != 0){
		//	   	d = temp->next;
		//	}
			if(a->val > b->val){
			   	tempval = a->val;
				a->val = b->val;
				b->val = tempval;
		//	   	b->next = a->next;
		//		b->prev = a;
		//		a->next = b;
		//		a->prev = c;
		//		if(j != length(*l)-3){	
		//			c->next  = a;
		//		}
		//		if(j != 0){
		//			d->prev = b;
		//		}
			}
			temp = temp->prev;
		}
	}		   	
}

/*************************************************************************
** Function: insert
** Description: inserts a node into the linked list
** Parameters: pointer to a struct list, a value, and a index number
** Pre-Conditions: needs a pointer to a linked list and two positive ints
** Post-Conditions: none
*************************************************************************/
void insert(struct list *l, int v, int loc){
   	if(loc<0 || loc>length(*l)){
	   	printf("That is not on the list.\n");
		return;
	}
	int i;
	struct node *new_node = malloc(sizeof(struct node));
	new_node->val = v;
	struct node *temp = l->head;
	if(loc == length(*l)){
	   	new_node->prev = l->tail;
		new_node->next = NULL;
		l->tail->next = new_node;
		l->tail = new_node;
	}
	else if(loc == 0){
		new_node->next = l->head;
		l->head->prev = new_node;
		l->head = new_node;
		new_node->prev = NULL;
	}
	else{
		for(i=0; i<loc; i++){
	   		if(i == loc-1){
				new_node->next = temp->next;
				new_node->prev = temp;
				temp->next = new_node;
			}
		temp = temp->next;
		}	
	}		   	
}
