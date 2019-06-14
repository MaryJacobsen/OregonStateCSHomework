/*************************************************************************
** Filename: empty.cpp
** Author: Mary Jacobsen
** Date: 5/22/16
** Description: empty functions
** Input: event.h empty.h
** Output: empty
**************************************************************************/

#include "event.h"
#include "empty.h"
#include <iostream>
#include <cstring>

using namespace std;
/*************************************************************************
** Function: nearby
** Description: prints the percepts
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void empty::nearby(){
   	return;
}
/*************************************************************************
** Function: enter
** Description: prints the enter message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void empty::enter(){
   	cout<<"You entered an empty room."<<endl;
}
/*************************************************************************
** Function: type
** Description: returns the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

string empty::type(){
   	return "empty";
}
/*************************************************************************
** Function: clone
** Description: returns a copy of new empty
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

event* empty::clone(){
   	return new empty;
}
