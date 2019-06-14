#include <stdio.h>
#include <stdlib.h>

struct stack {
   	int *contents; //dynamic array of ints
	int top; //stores the top of the stack
};

void init(struct stack * s){
   	s->contents = malloc(sizeof(int)*0);
	s->top = 0;
}

void push(struct stack * s, int input){
   	int i=0;
   	int *temp = malloc(sizeof(int)*s->top+1);
	for(i; i<s->top; i++){
	   	temp[i] = s->contents[i];
	}
	free(s->contents);
	s->contents = temp;
	s->contents[s->top] = input;
	s->top++;

}

int pop(struct stack *s){
   	int i=0, temp_int = s->contents[s->top-1];
   	int *temp = malloc(sizeof(int)*s->top-1);
	for(i; i<s->top-1; i++){
	   	temp[i] = s->contents[i];
	}
	free(s->contents);
	s->contents = temp;
	s->top--;
	return temp_int;
}

int peek(struct stack s){
   	return s.contents[s.top-1];
}

void destroy(struct stack *s){
   	free(s->contents);
}

int empty(struct stack s){
   	if(s.top == 0){
	   	return 1;
	}
	else{
	   	return 0;
	}
}

int size(struct stack s){
   	return s.top;
}

int main(){
   	struct stack *s;
	int i=0;
	init(s);
	push(s, 5);
	push(s, 6);
	push(s, 7);
	printf("%d\n", pop(s));
	for(i; i<s->top; i++){
	   	printf("%d\n", s->contents[i]);
	}
	printf("peek: %d\n", peek(*s));
	printf("empty: %d\n", empty(*s));
	printf("size: %d\n", size(*s));
	destroy(s);
	return 0;
}

	   	


