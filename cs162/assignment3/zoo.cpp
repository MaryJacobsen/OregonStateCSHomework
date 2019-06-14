/*************************************************************************
 ** Program: zoo.cpp 
 ** Author: Mary Jacobsen
 ** Date: 05/08/2016
 ** Description: Runs a zoo with animals that get fed, bring in  money, multiply, and die
 ** Input: zoo.h, animal.h, oliphant.h, tiger.h, polar_bear.h, and penguin.h
 ** Output: a zoo game
*************************************************************************/
#include "zoo.h"
#include "animal.h"
#include "oliphant.h"
#include "tiger.h"
#include "polar_bear.h"
#include "penguin.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*************************************************************************
** Function: zoo
** Description: constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: arrays set to NULL and bank set to 200000
*************************************************************************/
zoo::zoo(){
   	oliphant_exhibit = NULL;
       	tiger_exhibit = NULL;
	polar_bear_exhibit = NULL;
	penguin_exhibit = NULL;
	bank = 200000;
}
/*************************************************************************
 ** Function: zoo
 ** Description: copy constructor
 ** Parameters: const zoo & other
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
zoo::zoo(const zoo & other){ 
   	num_oliphants = other.num_oliphants;
	oliphant_exhibit = new oliphant[num_oliphants];
	for(int i = 0; i<num_oliphants; i++){
	   	oliphant_exhibit[i] = other.oliphant_exhibit[i];
	}
 	num_tigers = other.num_tigers;
	tiger_exhibit = new tiger[num_tigers];
	for(int i = 0; i<num_tigers; i++){
	   	tiger_exhibit[i] = other.tiger_exhibit[i];
	}
	num_polar_bears = other.num_polar_bears;
	polar_bear_exhibit = new polar_bear[num_polar_bears];
	for(int i = 0; i<num_polar_bears; i++){
		polar_bear_exhibit[i] = other.polar_bear_exhibit[i];
	}
 	num_penguins = other.num_penguins;
	penguin_exhibit = new penguin[num_penguins];
	for(int i = 0; i<num_penguins; i++){
		penguin_exhibit[i] = other.penguin_exhibit[i];
	}
}
/*************************************************************************
 ** Function: zoo
 ** Description: assignment operator
 ** Parameters: const zoo & other
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::operator =(const zoo &other){
   	delete [] oliphant_exhibit;
   	num_oliphants = other.num_oliphants;
	oliphant_exhibit = new oliphant[num_oliphants];
	for(int i = 0; i<num_oliphants; i++){
	   	oliphant_exhibit[i] = other.oliphant_exhibit[i];
	}
   	delete [] tiger_exhibit;
   	num_tigers = other.num_tigers;
	tiger_exhibit = new tiger[num_tigers];
	for(int i = 0; i<num_tigers; i++){
	   	tiger_exhibit[i] = other.tiger_exhibit[i];
	}
   	delete [] polar_bear_exhibit;
	num_polar_bears = other.num_polar_bears;
	polar_bear_exhibit = new polar_bear[num_polar_bears];
	for(int i = 0; i<num_polar_bears; i++){
		polar_bear_exhibit[i] = other.polar_bear_exhibit[i];
	}
   	delete [] penguin_exhibit;
	num_penguins = other.num_penguins;
	penguin_exhibit = new penguin[num_penguins];
	for(int i = 0; i<num_penguins; i++){
		penguin_exhibit[i] = other.penguin_exhibit[i];
	}
}
/*************************************************************************
 ** Function: ~zoo
 ** Description: destructor
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
zoo::~zoo(){
   	delete [] oliphant_exhibit;
	oliphant_exhibit = NULL;
	delete [] tiger_exhibit;
	tiger_exhibit = NULL;
	delete [] polar_bear_exhibit;
	polar_bear_exhibit = NULL;
	delete penguin_exhibit;
	penguin_exhibit = NULL;
}
/*************************************************************************
 ** Function: add_oliphants
 ** Description: adds whatever number of oliphants you pass in
 ** Parameters: int n
 ** Pre-Conditions: cant's negative numbers in
 ** Post-Conditions: none
*************************************************************************/
void zoo::add_oliphants(int n){
   	if(oliphant_exhibit == NULL){
	   	oliphant_exhibit = new oliphant[n];
		for(int i=0; i<n; i++){
		   	oliphant_exhibit[i].set_age(3);
		}
		num_oliphants = n;
	}
	else{
   		oliphant *temp;
		num_oliphants = num_oliphants + n;
		temp = new oliphant[num_oliphants];
		for(int i=0; i<num_oliphants-n; i++){
	   		temp[i] = oliphant_exhibit[i];
		}
		delete [] oliphant_exhibit;
		oliphant_exhibit = temp;
		for(int i=num_oliphants-n-1; i<num_oliphants; i++){
	   		oliphant_exhibit[i].set_age(3);
		}
	}
}
/*************************************************************************
 ** Function: add_tigers
 ** Description: adds whatever number is passed in to the tiger array
 ** Parameters: int n
 ** Pre-Conditions: can't pass in negative numbers
 ** Post-Conditions: none
*************************************************************************/
void zoo::add_tigers(int n){
   	if(tiger_exhibit == NULL){
	   	tiger_exhibit = new tiger[n];
		for(int i=0; i<n; i++){
		   	tiger_exhibit[i].set_age(3);
		}
		num_tigers = n;
	}
	else{
   		tiger *temp; 
		num_tigers = num_tigers + n;
		temp = new tiger[num_tigers];
		for(int i=0; i<num_tigers-n; i++){
	   		temp[i] = tiger_exhibit[i];
		}
		delete [] tiger_exhibit;
		tiger_exhibit = temp;
		for(int i=num_tigers-n-1; i<num_tigers; i++){
			tiger_exhibit[i].set_age(3);
		}
	}
}
/*************************************************************************
 ** Function: add_polar_bears
 ** Description: adds whatever number is passed in to the polar bear array
 ** Parameters: int n
 ** Pre-Conditions: can't be a negative number
 ** Post-Conditions: none
*************************************************************************/
void zoo::add_polar_bears(int n){
   	if(polar_bear_exhibit == NULL){
	   	polar_bear_exhibit = new polar_bear[n];
		for(int i=0; i<n; i++){
		   	polar_bear_exhibit[i].set_age(3);
		}
		num_polar_bears = n;
	}
	else{
   		polar_bear *temp;
		num_polar_bears = num_polar_bears + n;
		temp = new polar_bear[num_polar_bears];
		for(int i=0; i<num_polar_bears-n; i++){
	   		temp[i] = polar_bear_exhibit[i];
		}
		delete [] polar_bear_exhibit;
		polar_bear_exhibit = temp;
		for(int i=num_polar_bears-n-1; i<num_polar_bears; i++){
	   		polar_bear_exhibit[i].set_age(3);
		}
	}
}
/*************************************************************************
 ** Function: add_peguins
 ** Description: adds the number passed in to the penguin array
 ** Parameters: int n
 ** Pre-Conditions: can't be a negative number
 ** Post-Conditions: none
*************************************************************************/
void zoo::add_penguins(int n){
   	if(penguin_exhibit == NULL){
	   	penguin_exhibit = new penguin[n];
		for(int i=0; i<n; i++){
		   	penguin_exhibit[i].set_age(3);
		}
		num_penguins = n;
	}
	else{
   		penguin *temp;
		num_penguins = num_penguins + n;
		temp = new penguin[num_penguins];
		for(int i=0; i<num_penguins-n; i++){
	   		temp[i] = penguin_exhibit[i];
		}
		delete [] penguin_exhibit;
		penguin_exhibit = temp;
		for(int i=num_penguins-n-1; i<num_penguins; i++){
	   		penguin_exhibit[i].set_age(3);
		}
	}
}	
/*************************************************************************
 ** Function: add_baby_oliphant
 ** Description: adds a baby oliphant and sets the age to 0
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::add_baby_oliphant(){
   	add_oliphants(1);
	for(int i=num_oliphants-2; i<num_oliphants; i++){
	   	oliphant_exhibit[i].set_age(0);
	}
}
/*************************************************************************
 ** Function: add_baby_tiger 
 ** Description: adds a baby tiger
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::add_baby_tiger(){
   	add_tigers(1);
	for(int i=num_tigers-2; i<num_tigers; i++){
	   	tiger_exhibit[i].set_age(0);
	}
}
/*************************************************************************
 ** Function: add_baby_polar_bear
 ** Description: adds 2 baby polar bears
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::add_baby_polar_bears(){
   	add_polar_bears(2);
	for(int i=num_polar_bears-3; i<num_polar_bears; i++){
	   	polar_bear_exhibit[i].set_age(0);
	}
}
/*************************************************************************
 ** Function: add_baby_penguiin
 ** Description: adds 3 baby penguins
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::add_baby_penguins(){
   	add_penguins(3);
	for(int i=num_penguins-4; i<num_penguins; i++){
	   	penguin_exhibit[i].set_age(0);
	}
}
/*************************************************************************
 ** Function: take_away_oliphant
 ** Description: takes away one oliphant
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::take_away_oliphant(){
   	if(oliphant_exhibit[num_oliphants-1].get_age() < 3){
	   	bank = bank-400000;
	}
	else{
	   	bank = bank-200000;
	}
	if(bank < 0){
	   	cout<<"You went bankrupt!"<<endl;
		exit(1);
	}
   	num_oliphants = num_oliphants - 1;
   	oliphant *temp = new oliphant[num_oliphants];
	for(int i=0; i<num_oliphants; i++){
	   	temp[i] = oliphant_exhibit[i];
	}
	delete [] oliphant_exhibit;
	oliphant_exhibit = temp;
}
/*************************************************************************
 ** Function: take_away_tiger
 ** Description: takes away one tiger
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::take_away_tiger(){
   	if(tiger_exhibit[num_tigers-1].get_age() < 3){
	   	bank = bank-20000;
	}
	else{
	   	bank = bank-10000;
	}
	if(bank < 0){
	   	cout<<"You went bankrupt!"<<endl;
		exit(1);
	}  	
   	num_tigers = num_tigers - 1;
   	tiger *temp = new tiger[num_tigers];
	for(int i=0; i<num_tigers; i++){
	   	temp[i] = tiger_exhibit[i];
	}
	delete [] tiger_exhibit;
	tiger_exhibit = temp;
}
/*************************************************************************
 ** Function: take_away_polar_bear
 ** Description: takes away one polar bear
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::take_away_polar_bear(){
   	if(polar_bear_exhibit[num_polar_bears-1].get_age() < 3){
	   	bank = bank-10000;
	}
	else{
	   	bank = bank-5000;
	}
	if(bank < 0){
	   	cout<<"You went bankrupt!"<<endl;
		exit(1);
	}
   	num_polar_bears = num_polar_bears - 1;
   	polar_bear *temp = new polar_bear[num_polar_bears];
	for(int i=0; i<num_polar_bears; i++){
	   	temp[i] = polar_bear_exhibit[i];
	}
	delete [] polar_bear_exhibit;
	polar_bear_exhibit = temp;
}
/*************************************************************************
 ** Function: take_away_penguin
 ** Description: takes away one penguin
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::take_away_penguin(){
	if(penguin_exhibit[num_penguins-1].get_age() < 3){
	   	bank = bank-2000;
	}
	else{
	   	bank = bank-1000;
	}
	if(bank < 0){
	   	cout<<"You went bankrupt!"<<endl;
		exit(1);
	}
   	num_penguins = num_penguins - 1;
   	penguin *temp = new penguin[num_penguins];
	for(int i=0; i<num_penguins; i++){
	   	temp[i] = penguin_exhibit[i];
	}
	delete [] penguin_exhibit;
	penguin_exhibit = temp;
}
/*************************************************************************
 ** Function: buy_animals
 ** Description: lets the user buy animals
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::buy_animals(){
	int choice, quantity, e = 1;
	while(e == 1){
	     	cout<<"You have $"<<bank<<" in your bank account."<<endl;
   		cout<<"Would you like to purchase an oliphant for $200,000(1), tiger for $10,000(2), polar bear for $5000(3), or penguin for $1000(4), or nothing(5)?"<<endl;
		cin>>choice;
		if(cin.fail()){
	   		cin.clear();
			cin.ignore();
			cout<<"Please choose 1, 2, 3, 4, or 5."<<endl;
		}
		else if(choice<1 || choice>5){
	   		cout<<"Please choose 1, 2, 3, 4, or 5."<<endl;
		}
		else if(choice == 1){
	   		cout<<"How many(1 or 2)?"<<endl;
			cin>>quantity;
			if(cin.fail()){
	   			cin.clear();
				cin.ignore();
				cout<<"Please enter 1 or 2."<<endl;
			}
			else if(quantity<1 || quantity > 2){
		   		cout<<"Please enter 1 or 2."<<endl;
			}	
			else{
		   		bank = bank - (200000 * quantity);
				if(bank < 0){
				   	cout<<"You went bankrupt!"<<endl;
					exit(1);
				}
		   		add_oliphants(quantity);
			}
		}
		else if(choice == 2){
			cout<<"How many(1 or 2)?"<<endl;
			cin>>quantity;
			if(cin.fail()){
	   			cin.clear();
				cin.ignore();
				cout<<"Please enter 1 or 2."<<endl;
			}
			else if(quantity<1 || quantity > 2){
		   		cout<<"Please enter 1 or 2."<<endl;
			}
			else{
		   		bank = bank - (10000 * quantity);
				if(bank < 0){
				   	cout<<"You went bankrupt!"<<endl;
					exit(1);
				}
		   		add_tigers(quantity);
			}
		}
		else if(choice == 3){
	   		cout<<"How many?(1 or 2)"<<endl;
			cin>>quantity;
			if(cin.fail()){
	   			cin.clear();
				cin.ignore();
				cout<<"Please enter 1 or 2."<<endl;
			}
			else if(quantity<1 || quantity > 2){
		   		cout<<"Please enter 1 or 2."<<endl;
			}
			else{
		   		bank = bank - (5000 * quantity);
				if(bank < 0){
				   	cout<<"You went bankrupt!"<<endl;
					exit(1);
				}
		   		add_polar_bears(quantity);
			}
		}
		else if(choice == 4){
	   		cout<<"How many?(1 or 2)"<<endl;
			cin>>quantity;
			if(cin.fail()){
	   			cin.clear();
				cin.ignore();
				cout<<"Please enter 1 or 2."<<endl;
			}
			else if(quantity<1 || quantity > 2){
		   		cout<<"Please enter 1 or 2."<<endl;
			}
			else{
		   		bank = bank - (1000 * quantity);
				if(bank < 0){
				   	cout<<"You went bankrupt!"<<endl;
					exit(1);
				}
		   		add_penguins(quantity);
			}
		}
		else{
		   	return;
		}
	}
}
/*************************************************************************
 ** Function: random_event
 ** Description: randomly picks an event and calls appropriate function
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::random_event(){
   	int event, choice, e = 1;
   	srand(time(NULL));
	event = rand()%4;
	if(event == 0){
	   	cout<<"Nothing happened."<<endl;
	}
	else if(event == 1){
	   	while(e == 1){
	   		cout<<"There is a sickness in the zoo. Will an oliphant(1), tiger(2), polar_bear(3), or penguin(4) die?"<<endl;
			cin>>choice;
			if(cin.fail()){
	   			cin.clear();
				cin.ignore();
				cout<<"Please choose 1, 2, 3, or 4."<<endl;
				continue;
			}
			else if(choice<1 || choice>4){
	   			cout<<"Please choose 1, 2, 3, or 4."<<endl;
				continue;
			}
			else if(choice == 1){
		   		if(oliphant_exhibit != NULL){
		   			take_away_oliphant();
					return;
				}
				else{
			   		cout<<"You don't have any oliphants."<<endl;
					continue;
				}
			}
			else if(choice == 2){
			   	if(tiger_exhibit != NULL){
		   			take_away_tiger();
					return;
				}
				else{
				   	cout<<"You don't have any tigers."<<endl;
				   	continue;
				}
			}
			else if(choice == 3){
			   	if(polar_bear_exhibit != NULL){
		   			take_away_polar_bear();
					return;
				}
				else{
				   	cout<<"You don't have any polar bears."<<endl;
				   	continue;
				}
			}
			else if(choice == 4){
			   	if(penguin_exhibit != NULL){
		   			take_away_penguin();
					return;
				}
				else{
				   	cout<<"You don't have any penguins."<<endl;
					continue;
				}
			}
		}
	}
	else if(event == 2){
	   	int e = 1;
		while(e == 1){
	   		cout<<"Which animal is having a baby? oliphant(1), tiger(2), polar bear(3), penguin(4)"<<endl;
			cin>>choice;
			if(cin.fail()){
	   			cin.clear();
				cin.ignore();
				cout<<"Please choose 1, 2, 3, or 4."<<endl;
			}
			else if(choice<1 || choice>4){
	   			cout<<"Please choose 1, 2, 3, or 4."<<endl;
			}
			else if(choice == 1){
		   		for(int i=0; i<num_oliphants; i++){
			   		if(oliphant_exhibit[i].get_age() > 2){
		   				add_baby_oliphant();
						return; 
					}
				}
				cout<<"There are no adult oliphants."<<endl;
				continue;
			}
			else if(choice == 2){
				for(int i=0; i<num_tigers; i++){
			   		if(tiger_exhibit[i].get_age() > 2){
		   				add_baby_tiger();
						return;
					}
				}
				cout<<"There are no adult tigers."<<endl;
				continue;
			}
			else if(choice == 3){
		   		for(int i=0; i<num_polar_bears; i++){
			   		if(polar_bear_exhibit[i].get_age() > 2){
		   				add_baby_polar_bears();
						return;
					}
				}
				cout<<"There are no adult polar bears."<<endl;
				continue;
			}
			else if(choice == 4){
				for(int i=0; i<num_penguins; i++){
			   		if(penguin_exhibit[i].get_age() > 2){
		   				add_baby_penguins();
						return;
					}
				}
				cout<<"There are no adult penguins."<<endl;
				continue;
			}

		}
	}
	else if(event == 3){
	   	cout<<"There is a boom in attendence to see the tigers today. Each tiger's payoff will have a bonus of $250 to $500."<<endl;
		for(int i=0; i<num_tigers; i++){
		   	if(tiger_exhibit != NULL){
		   		tiger_exhibit[i].set_bonus(true);
			}
		}
	}
}
/*************************************************************************
 ** Function: feed_animals
 ** Description: loops through and feeds the animals
 ** Parameters: avg food cost
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::feed_animals(int a){
   	cout<<"It is time to feed the animals!"<<endl;
	if(oliphant_exhibit != NULL){
		for(int i=0; i<num_oliphants; i++){
	   		bank = bank-oliphant_exhibit[i].feed(a);
		}
	}
	if(tiger_exhibit != NULL){
	   	for(int i=0; i<num_tigers; i++){
		   	bank = bank-tiger_exhibit[i].feed(a);
		}
	}
	if(polar_bear_exhibit != NULL){
	   	for(int i=0; i<num_polar_bears; i++){
		   	bank = bank-polar_bear_exhibit[i].feed(a);
		}
	}
	if(penguin_exhibit != NULL){
	   	for(int i=0; i<num_penguins; i++){
		   	bank = bank-penguin_exhibit[i].feed(a);
		}
	}
	if(bank < 0){
	   	cout<<"You went bankrupt!"<<endl;
		exit(1);
	}
	cout<<"You have $"<<bank<<" in your bank account."<<endl;
}
/*************************************************************************
 ** Function: payoffs
 ** Description: loops through and adds the payoffs to bank
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::payoffs(){
   	cout<<"Time for payoffs!"<<endl;
   	if(oliphant_exhibit != NULL){
		for(int i=0; i<num_oliphants; i++){
	   		bank = bank + oliphant_exhibit[i].payoff();
		}
	}
	if(tiger_exhibit != NULL){
	   	for(int i=0; i<num_tigers; i++){
		   	bank = bank + tiger_exhibit[i].payoff();
		}
	}
	if(polar_bear_exhibit != NULL){
	   	for(int i=0; i<num_polar_bears; i++){
		   	bank = bank + polar_bear_exhibit[i].payoff();
		}
	}
	if(penguin_exhibit != NULL){
	   	for(int i=0; i<num_penguins; i++){
		   	bank = bank + penguin_exhibit[i].payoff();
		}
	}
	cout<<"You have $"<<bank<<" in your bank account."<<endl;
}
/*************************************************************************
 ** Function: age_animals
 ** Description: loops through and ages the animals
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
*************************************************************************/
void zoo::age_animals(){
   	if(oliphant_exhibit != NULL){
		for(int i=0; i<num_oliphants; i++){
	   		oliphant_exhibit[i].set_age(oliphant_exhibit[i].get_age()+1);
		}
	}
	if(tiger_exhibit != NULL){
	   	for(int i=0; i<num_tigers; i++){
		   	tiger_exhibit[i].set_age(tiger_exhibit[i].get_age()+1);
		}
	}
	if(polar_bear_exhibit != NULL){
	   	for(int i=0; i<num_polar_bears; i++){
		   	polar_bear_exhibit[i].set_age(polar_bear_exhibit[i].get_age()+1);
		}
	}
	if(penguin_exhibit != NULL){
	   	for(int i=0; i<num_penguins; i++){
		   	penguin_exhibit[i].set_age(penguin_exhibit[i].get_age()+1);
		}
	}
}




		   	
		
	   	
	
	




		




