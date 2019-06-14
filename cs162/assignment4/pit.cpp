/*************************************************************************
** Filename: pit.h 
** Author: Mary Jacobsen
** Date: 5/22/16
** Description: pit functions
** Input: event.h pit.h
** Output: pit
**************************************************************************/

#include "event.h"
#include "pit.h"
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

void pit::nearby(){
   	cout<<"You feel a breeze."<<endl;
}
/*************************************************************************
** Function: enter
** Description: prints enter message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void pit::enter(){
   	cout<<"You entered a room with a bottomless pit and fell in."<<endl;
}
/*************************************************************************
** Function: type
** Description: returns type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

string pit::type(){
   	return "pit";
}
/*************************************************************************
** Function: clone
** Description: returns a copy
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

event* pit::clone(){
   	return new pit;
}
