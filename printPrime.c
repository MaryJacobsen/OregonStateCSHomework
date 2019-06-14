/**********************************************************************************
 ** Program Filename: printPrime.c
 ** Author: Mary Jacobsen
 ** Date: Jun 24, 2016
 ** Author: Mary Jacobsen
 ** Description: Prints prime numbers in an infinite loop until the user stops it
 **********************************************************************************/

#include <stdio.h>

/**********************************************************************************
** Function: prime
** Description: checks if a number is prime
** Parameters: an integer
** Pre-Conditions: must be a positive number
** Post-Conditions: none
***********************************************************************************/
int prime(int num) {
	int i;
	for (i = 2; i < num; i++) {
		if (num % i == 0) {
			return 0;
		}
	}
	return 1;
}
int main() {
	int num = 2;
	while (1) {
		if (prime(num) == 1) {
			printf("%d\n", num);
		}
		num++;
	}
	return 0;
}
