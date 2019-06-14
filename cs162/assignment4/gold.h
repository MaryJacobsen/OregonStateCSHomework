/**************************************************************************
** Filename: gold.h
** Author: Mary Jacobsen
** Date: 05/16/2016
** Description: declares gold class
** Input: event.h
** Output: gold class
*************************************************************************/ 
#include "event.h"
#include <iostream>
#include <cstring>
#pragma once
class gold: public event {
   	public:
	   	void nearby();
		void enter();
		std::string type();
		event* clone();
};
