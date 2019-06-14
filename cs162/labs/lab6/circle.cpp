#include "shape.h"
#include "circle.h"
#include <cstring>
#include <iostream>

using namespace std;

circle::circle():shape("circle", "purple") {}

void circle::set_radius(){
   	cout<<"Please enter the radius."<<endl;
	cin>>radius;
}

float circle::get_radius(){
   	return radius;
}

float circle::area(){
  	return (3.14 * radius * radius);
}
