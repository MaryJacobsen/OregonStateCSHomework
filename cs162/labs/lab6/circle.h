#pragma once
#include "shape.h"
class circle: public shape{
   	private:
	   	double radius;
	public:
		circle();
		void set_radius();
		double get_radius();
		double area();
};
