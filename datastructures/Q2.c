/* CS261- Assignment 1 - Q.2*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a = (*a)*2;
    
    /*Set b to half its original value*/
	*b = (*b)/2;
    
    /*Assign a+b to c*/
	c = (*a) + (*b);
    
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x=5, y=6, z=7, val;

    /*Print the values of x, y and z*/
    printf("value of x: %d\n", x);
    printf("value of y: %d\n", y);
    printf("value of z: %d\n", z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    val = foo(&x, &y, z);
    
    /*Print the value returned by foo*/
    printf("value returned by foo: %d\n", val);
    
    /*Print the values of x, y and z again*/
    printf("value of x: %d\n", x);
    printf("value of y: %d\n", y);
    printf("value of z: %d\n", z);
 
    /*Is the return value different than the value of z?  Why?*/
    /*Yes because z was passed by value into foo so the value of z could not be changed outside of the function. Since the address of x and y were passed in, they were changed outside the function*/
    return 0;
}
    
    
