/**************************************************************************
** Filename: escape_rope.h
** Author: Mary Jacobsen
** Date: 05/16/2016
** Description: declares escape_rope class
** Input: event.h
** Output: escape_rope class
*************************************************************************/ 
#include "event.h"
#include <iostream>
#include <cstring>
#pragma once
class escape_rope: public event {
   	public:
	   	void nearby();
		void enter();
		std::string type();
		event* clone();
};
