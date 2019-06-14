/*************************************************************************
** Filename: wumpus.cpp 
** Author: Mary Jacobsen
** Date: 5/22/16
** Description: has the wumpus functions
** Input: event.h wumpus.h
** Output: wumpus
**************************************************************************/

#include "event.h"
#include "wumpus.h"
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

void wumpus::nearby(){
   	cout<<"You smell a terrible stench."<<endl;
}
/*************************************************************************
** Function: enter
** Description: prints the message when player enters
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void wumpus::enter(){
   	cout<<"You entered the room the wumpus is in. It awakened and gobbled you up out of anger."<<endl;
}
/*************************************************************************
** Function: type
** Description: returns the type
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

string wumpus::type(){
   	return "wumpus";
}
/*************************************************************************
** Function: clone
** Description: returns a copy of a new wumpus
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

event* wumpus::clone(){
   	return new wumpus;
}
