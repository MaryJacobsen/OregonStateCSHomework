/**************************************************************************
** CS261- Assignment 1 - Q. 0
** Name: Mary Jacobsen
** Date: 6/30/16
** Solution description: In fooA the printf function was used to print the
   value pointed to by iptr, address pointed to by iptr, and the address of
   iptr. printf was also used to print everything in main. The value of x
   was arbitrarily set to 7 to make sure everything was working.
**************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
** Function: fooA
** Description: prints out the value and address pointed to by the pointer
   passed in as well as the address of the pointer itself
** Parameters: a pointer to an int
** Pre-Conditions: must pass in the address of an int
** Post-Conditions: none
**************************************************************************/
void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	printf("Value: %d\n", *iptr);
     
     /*Print the address pointed to by iptr*/
	printf("Address pointed to: %p\n", &(*iptr));
     
     /*Print the address of iptr itself*/
	printf("Adress of iptr: %p\n", &iptr);
}

int main(){
    
    /*declare an integer x*/
	int x = 7;
    
    /*print the address of x*/
	printf("Address of x: %p\n", &x);
    
    /*Call fooA() with the address of x*/
	fooA(&x);
    
    /*print the value of x*/
	printf("Value of x: %d\n", x);
    
    return 0;
}
