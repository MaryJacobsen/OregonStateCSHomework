/*************************************************************************
 ** Program: penguin.cpp 
 ** Author: Mary Jacobsen
 ** Date: 05/08/2016
 ** Description: sets up penguin which inherits from animal
 ** Input: animal.h, penguin.h
 ** Output: penguin class
*************************************************************************/
#include <iostream>
#include "animal.h"
#include "penguin.h"

using namespace std;

/*************************************************************************
 ** Function: penguin
 ** Description: constructor
 ** Parameters: uses the animal constructor
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
penguin::penguin(): animal(1000, 1, 3){}
