/*************************************************************************
 ** Program: driver.cpp 
 ** Author: Mary Jacobsen
 ** Date: 05/08/2016
 ** Description: Runs a zoo with animals that get fed, bring in  money, multiply, and die
 ** Input: zoo.h, animal.h, oliphant.h, tiger.h, polar_bear.h, and penguin.h
 ** Output: a zoo game
*************************************************************************/
#include "animal.h"
#include "penguin.h"
#include "polar_bear.h"
#include "tiger.h"
#include "oliphant.h"
#include "zoo.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
   	int choice, food, e = 1;
	while(true){
		cout<<"What is the average food cost for animals?"<<endl;
		cin>>food;
		if(cin.fail()){
	   		cin.clear();
			cin.ignore();
			cout<<"Please enter a postitive integer."<<endl;
			continue;
		}
		else if(food < 0){
	  		cout<<"Please enter a positive integer."<<endl;
	       		continue;
		}
		else{
   			break;
    		}
	}		
   	zoo z;
	z.buy_animals();
	while(true){
		z.feed_animals(food);
		z.random_event();
		z.payoffs();
		z.age_animals();
		while(true){
			cout<<"Do you want to buy an animal(1), continue to the next day(2), or end the game(3)?"<<endl;
			cin>>choice;
			if(cin.fail()){
	   			cin.clear();
				cin.ignore();
				cout<<"Please choose 1, 2, or 3."<<endl;
				continue;
			}
			else if(choice < 1 || choice > 3){
	   			cout<<"Please choose 1, 2, or 3."<<endl;
				continue;
			}
			else if(choice == 1){
		   		z.buy_animals();
				break;
			}
			else if(choice == 2){
		   		break;
			}
			else if(choice == 3){
		   		exit(1);
			}
		}
	}
   	return 0;
}
