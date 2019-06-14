#include "shape.h"
#include "circle.h"
#include <iostream>

using namespace std;

int main(){
	circle c;
	c.set_radius();
	cout<<"area: "<<c.area()<<endl;
   	return 0;
}
