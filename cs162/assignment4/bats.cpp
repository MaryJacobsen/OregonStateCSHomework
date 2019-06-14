/*************************************************************************
** Filename: bats.cpp 
** Author: Mary Jacobsen
** Date: 5/22/16
** Description: bats functions
** Input: event.h bats.h
** Output: bats
**************************************************************************/

#include "event.h"
#include "bats.h"
#include <iostream>
#include <cstring>

using namespace std;
/*************************************************************************
** Function: nearby
** Description: prints percepts
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void bats::nearby(){
   	cout<<"You hear wings flapping"<<endl;
}
/*************************************************************************
** Function: enter
** Description: prints enter message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void bats::enter(){
   	cout<<"You entered a room with super bats. An angry bat picked you up and took you to another room."<<endl;
}
/*************************************************************************
** Function: type
** Description: returns type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

string bats::type(){
   	return "bats";
}
/*************************************************************************
** Function: clone
** Description: returns copy
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

event* bats::clone(){
   	return new bats;
}
