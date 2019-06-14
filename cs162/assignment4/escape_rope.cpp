/*************************************************************************
** Filename: escape_rope.cpp
** Author: Mary Jacobsen
** Date: 5/22/16
** Description: escape_rope functions
** Input: event.h escape_rope.h
** Output: escape_rope
**************************************************************************/

#include "event.h"
#include "escape_rope.h"
#include <iostream>
#include <cstring>

using namespace std;
/*************************************************************************
** Function: nearby
** Description: just returns
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void escape_rope::nearby(){
   	return;
}
/*************************************************************************
** Function: enter
** Description: prints the message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void escape_rope::enter(){
   	cout<<"You entered the room with the escape rope in it."<<endl;
}
/*************************************************************************
** Function: type
** Description: returns the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

string escape_rope::type(){
  	return "escape_rope";
}
/*************************************************************************
** Function: clone
** Description: returns a copy of a new escape_rope
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

event* escape_rope::clone(){
   	return new escape_rope;
}
