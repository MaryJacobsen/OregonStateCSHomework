/**************************************************************************
** Filename: wumpus.h
** Author: Mary Jacobsen
** Date: 05/16/2016
** Description: declares wumpus class
** Input: event.h
** Output: wumpus class
*************************************************************************/  
#include "event.h"
#include <iostream>
#include <cstring>
#pragma once
class wumpus: public event {
   	public:
	   	void nearby();
		void enter();
		std::string type();
		event* clone();
};
