/*************************************************************************
 ** Program: animal.cpp 
 ** Author: Mary Jacobsen
 ** Date: 05/08/2016
 ** Description: Has all the animal functions
 ** Input: animal.h
 ** Output: an animal class to make it easier to make types of animals
*************************************************************************/
#include "animal.h"
#include <iostream>

using namespace std;
/*************************************************************************
 ** Function: animal
 ** Description: non-default constructor
 ** Parameters: cost, food cost, number of babies
 ** Pre-Conditions: they need to be positive
 ** Post-Conditions: none
*************************************************************************/
animal::animal(int c, int f, int b){
   	age = 0;
	cost = c;
	food_cost = f;
	num_babies = b;
}
/*************************************************************************
 ** Function: set_age
 ** Description: sets the age
 ** Parameters: int a
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void animal::set_age(int a){
   	age = a;
}
/*************************************************************************
 ** Function: get_age
 ** Description: accessor
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
int& animal::get_age(){
  	return age;
}	
/*************************************************************************
 ** Function: get_cost
 ** Description: accessor
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
int& animal::get_cost(){
   	return cost;
}
/*************************************************************************
 ** Function: get_num_babies
 ** Description: accessor
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
int& animal::get_num_babies(){
  	return num_babies;
}
/*************************************************************************
 ** Function: feed
 ** Description: returns the cost to feed that animal
 ** Parameters: average food cost
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
int animal::feed(int avg_food_cost){
   	return (avg_food_cost * food_cost);
}
/*************************************************************************
 ** Function: payoff
 ** Description: returns the payoff for the animal
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
int animal::payoff(){
   	if(age < 3){
   		return (2 * (.05) * cost);
	}
	else{
	   	return ((.05) * cost);
	}
}
/*************************************************************************
 ** Function: sick
 ** Description: returns how much the sick animal costed
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
int animal::sick(){
   	if(age < 3){
	   	return (cost * 2);
	}
	else{
	   	return cost;
	}
}
   	
