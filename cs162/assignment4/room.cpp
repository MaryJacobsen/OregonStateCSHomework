#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "escape_rope.h"
#include "bats.h"
#include "empty.h"
/*************************************************************************
** Filename: room.cpp
** Author: Mary Jacobsen
** Date: 5/22/16
** Description: has all the room functions
** Input: all the event functions room.h 
** Output: room
**************************************************************************/
#include "bats.h"
#include "wumpus.h"
#include "empty.h"
#include "gold.h"
#include "pit.h"
#include "event.h"
#include "room.h"
#include <iostream>
#include <cstring>

using namespace std;
/*************************************************************************
** Function: room
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

room::room(){
   	e = new empty;
}
/*************************************************************************
** Function: room
** Description: copy constructor
** Parameters: const room & other
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

room::room(const room & other){
   	e = other.e->clone();
}
/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void room::set_e(event *x){
   	delete e;
   	e = x;
}
/*************************************************************************
** Function: ~room
** Description: destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

room::~room(){
   	delete e;
	e = NULL;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

event* room::get_e(){
   	return e;
}
