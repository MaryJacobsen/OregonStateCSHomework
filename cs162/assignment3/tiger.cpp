/*************************************************************************
 ** Program: tiger.cpp 
 ** Author: Mary Jacobsen
 ** Date: 05/08/2016
 ** Description: sets up the tiger, inherits from animal class, overrides payout function
 ** Input: animal.h, tiger.h
 ** Output: tiger class
*************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "animal.h"
#include "tiger.h"

using namespace std;

/*************************************************************************
 ** Function: tiger
 ** Description: constructor
 ** Parameters: uses animal constructor
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
tiger::tiger():animal(10000, 5, 1){
	bonus = false;
}
/*************************************************************************
 ** Function: set_bonus
 ** Description: sets the bonus to true or false
 ** Parameters: bool b
 ** Pre-Conditions: needs to be true or false
 ** Post-Conditions: none
*************************************************************************/
void tiger::set_bonus(bool b){
   	bonus = b;
}
/*************************************************************************
 ** Function: payoff
 ** Description: returns the payoff
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
int tiger::payoff(){
 	srand(time(NULL));
	int b = ((rand() % 251) + 250);
	
   	if(bonus && age < 3){
	   	return ((2 * .1 * cost) + b);
	}
	else if(age < 3){
	   	return (2 * .1 * cost);
	}
	else if(bonus){
	   	return ((.1 * cost) + b);
	}
	else{
	   	return (.1 * cost);
	}
}
