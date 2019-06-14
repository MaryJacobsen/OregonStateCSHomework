#include "event.h"
#include "gold.h"
#include <iostream>
#include <cstring>

using namespace std;

void gold::nearby(){
   	cout<<"You see a glimmer nearby."<<endl;
}

void gold::enter(){
   	cout<<"You entered the room with the gold and picked it up."<<endl;
}

string gold::type(){
   	return "gold";
}

event* gold::clone(){
   	return new gold;
}
