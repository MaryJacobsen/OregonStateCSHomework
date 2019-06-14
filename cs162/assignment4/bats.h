/**************************************************************************
** Filename: bats.h
** Author: Mary Jacobsen
** Date: 05/16/2016
** Description: declares bats class
** Input: event.h
** Output: bats class
*************************************************************************/ 
#include "event.h"
#include <iostream>
#include <cstring>
#pragma once
class bats: public event {
   	public:
	   	void nearby();
		void enter();
		std::string type();
		event* clone();
};
