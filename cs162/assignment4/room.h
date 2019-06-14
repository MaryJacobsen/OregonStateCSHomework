/**************************************************************************
** Filename: room.h
** Author: Mary Jacobsen
** Date: 05/16/2016
** Description: declares room class
** Input: event.h
** Output: room class
*************************************************************************/ 
#include "event.h"
#include <iostream>
#include <cstring>
#pragma once
class room {
   	private:
   		event *e;
	public:
	       	room();	
		room(const room &);
		~room();
		void set_e(event*);
		event* get_e();
};
