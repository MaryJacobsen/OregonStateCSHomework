/*************************************************************************
 ** Program: oliphant.cpp 
 ** Author: Mary Jacobsen
 ** Date: 05/08/2016
 ** Description: Sets up an oliphant, inherits all the animal traits
 ** Input: animal.h, oliphant.h
 ** Output: a zoo game
*************************************************************************/
#include <iostream>
#include "animal.h"
#include "oliphant.h"

using namespace std;

/*************************************************************************
 ** Function: oliphant
 ** Description: constructor
 ** Parameters: uses the animal constructor
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
oliphant::oliphant(): animal(200000, 100, 1){}

/*************************************************************************
 ** Function: payoff
 ** Description: returns payoff
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
int oliphant::payoff(){
   	if(age < 3){
   		return (2 * .25 * cost);
	}
	else{
	   	return (.25 * cost);
	}
}
