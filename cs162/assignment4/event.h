/**************************************************************************
** Filename: event.h
** Author: Mary Jacobsen
** Date: 05/16/2016
** Description: declares event class
** Input: none
** Output: event class
*************************************************************************/ 
#include <iostream>
#include <cstring>
#pragma once
class event {
   	public: 
	   	virtual void nearby()=0;
		virtual void enter()=0;
		virtual std::string type()=0;
		virtual event* clone() = 0;
};

