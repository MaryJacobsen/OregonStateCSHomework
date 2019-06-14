/**************************************************************************
** Filename: pit.h
** Author: Mary Jacobsen
** Date: 05/16/2016
** Description: declares pit class
** Input: event.h
** Output: pit class
*************************************************************************/ 
#include "event.h"
#include <iostream>
#include <cstring>
#pragma once
class pit: public event {
   	public:
	   	void nearby();
		void enter();
		std::string type();
		event* clone();
};
