/*************************************************************************
 ** Program: polar_bear.cpp 
 ** Author: Mary Jacobsen
 ** Date: 05/08/2016
 ** Description: sets up polar_bear which inherits from animal
 ** Input: animal.h polar_bear.h
 ** Output: polar_bear class
*************************************************************************/
#include <iostream>
#include "animal.h"
#include "polar_bear.h"

using namespace std;
/*************************************************************************
 ** Function: polar_bear
 ** Description: constructor
 ** Parameters: uses the animal sontructor
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
polar_bear::polar_bear():animal(5000, 3, 2){}
