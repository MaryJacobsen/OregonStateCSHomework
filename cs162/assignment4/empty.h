/**************************************************************************
** Filename: empty.h
** Author: Mary Jacobsen
** Date: 05/16/2016
** Description: declares empty class
** Input: event.h
** Output: empty class
*************************************************************************/ 
#include "event.h"
#include <iostream>
#include <cstring>
#pragma once
class empty: public event {
   	public:
	   	void nearby();
		void enter();
		std::string type();
		event* clone();
};
