/*************************************************************************
** Program: test_list.c
** Author: Mary Jacobsen
** Date: 06/04/2016
** Description: fills and sorts a linked list of integers taken in from a file
** Input: list.h and a file
** Output: sorted linked list of integers
*************************************************************************/
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
   	char filename[20];
	struct list l;
	l.head = NULL;
	l.tail = NULL;
	FILE *fileptr;
	char num[3], loc[5]; //We will read positive integers 0-99

	printf("Enter filename: ");
	scanf("%s", filename);
	fileptr = fopen(filename, "r");

	//continue reading until we are at the end of the file
	while(fscanf(fileptr, "%s", num)!=EOF){
	   	printf("number is: %d\n", atoi(num));
		//push to front of list
		push_front(&l, atoi(num));
		//push to back of list
		push_back(&l, atoi(num));
	}

	//print length of list
	printf("\n");
	printf("length: %d\n", length(l));

	//print the contents of the list
	print(l);

	//sort in ascending order
	sort_ascending(&l);
	//print the contents of the list
	printf("\n");
	print(l);

	//sort in descending order
	sort_descending(&l);
	//print the contents of the list
	printf("\n");
	print(l);
	
	//prompt user for item/integer to remove from list
	printf("\n");
	printf("What value would you like to remove? ");
	scanf("%s", num);
	printf("\n");
	//remove specific item/integer from the list
	remove_val(&l, atoi(num));
	//print the contents of the list
	printf("\n");
	print(l);
	
	//prompt user for the item/int to add and location in list
	printf("\n");
	printf("What value would you like to add? ");
	scanf("%s", num);
	printf("\n");
	printf("Where would you like to add it?(index starts at 0) ");
	scanf("%s", loc);
	printf("\n");
	//insert int into specific location
	insert(&l, atoi(num), atoi(loc));
	//print the contents of the list
	printf("\n");
	print(l);

	//clear list - no memory leaks
	clear(&l);
	
	fclose(fileptr);

	return 0;
}
	

