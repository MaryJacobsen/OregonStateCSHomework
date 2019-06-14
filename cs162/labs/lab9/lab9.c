#include <stdio.h>
#include <stdlib.h>

struct node{
   	int val; //integer node value
	struct node *next; //pointer to next node
};

struct stack{
   	struct node *head; //pointer to first node in stack
	struct node *tail; //pointer to top of stack
};

void init(struct stack *s){ //initialize stack members
   	s->head = NULL;
	s->tail = NULL;

}

void push(struct stack *s, int v){ //grow contents to store int
   	struct node *n = malloc(sizeof(struct node));
	n->val = v;
	n->next = NULL;
   	if(s->tail == NULL){
	   	s->head = n;
		s->tail = n;
	}
	else{
		s->tail->next = n;
		s->tail = n;
	}
}

int pop(struct stack *s){ //shrink contents and return top int
   	int num;
	struct node *temp = s->head;
	while(temp->next != s->tail){
	   	temp = temp->next;
	}
	temp->next = NULL;
	num = s->tail->val;
	free(s->tail);
	s->tail = temp;
	return num;
}

int peek(struct stack s){
   	return s.tail->val;
}

int main(){
   	struct stack s;
	init(&s);
	printf("after init");
	push(&s, 1);
	printf("We pushed once");
	push(&s, 2);
	push(&s, 3);
	struct node *n = s.head;
	while(n != NULL){
	   	printf("\n%d",n->val);
		n = n->next;
	}

	printf("pop: %d", pop(&s));
	n = s.head;
	while(n != NULL){
	   	printf("%d\n",n->val);
		n = n->next;
	}

	printf("peek: %d", peek(s));


}

