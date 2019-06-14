/**************************************************************************
** Program Filename: hand.cpp
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: Has all the hand functions
** Input: All the functions that hand objects use
** Output: A hand
**************************************************************************/
#include "card.h"
#include "deck.h"
#include "hand.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/**************************************************************************
** Function: hand
** Description: default constructer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/
hand::hand(){
   	//cout<<"in constructor"<<endl;
   	num_cards = 2;
	cards = new card[num_cards];
}

/**************************************************************************
** Function: set_hand
** Description: mutator
** Parameters: int and a card
** Pre-Conditions: i can't be negative or bigger than 2
** Post-Conditions: none
**************************************************************************/
void hand::set_hand(int i, card c){ //mutator
   	//cout<<"in set_hand"<<endl;
   	cards[i] = c;
	//cout<<cards[i].value<<" ";
	//cout<<cards[i].suit<<endl;;
}

/*************************************************************************
** function: get_hand
** Description: accessor
** Parameters: none
** Pre-Conditions: none
** Post-Condition: returns a cards pointer
**************************************************************************/
card* hand::get_hand(){ //accesser
   	return cards;
}

/*************************************************************************
** Function: get_num_cards
** Description: accesser
** Parameters: none
** Pre-Conditions: none
** Post-Condition: none
**************************************************************************/

int& hand::get_num_cards(){
   	return num_cards;
}

/*************************************************************************
** Function: ~hand
** Description: destructer
** Parameters: none
** Pre-Conditions: none
** Post-Condition: none 
**************************************************************************/

hand::~hand(){ //destructor
  // 	cout<<"in detructor"<<endl;
	delete [] cards;
	cards = NULL;
}
/*************************************************************************
** Function: add_card
** Description: adds a card to a hand
** Parameters: a card
** Pre-Conditions: must pass a card in
** Post-Condition: none 
**************************************************************************/

void hand::add_card(card c){
   //	cout<<"in add_card"<<endl;
   	card *temp;
	num_cards = num_cards +1;
	temp = new card[num_cards];
	for(int i=0; i<num_cards-1; i++){
	  	temp[i] = cards[i];
	}
	delete [] cards;
   	cards = temp;
	cards[num_cards-1] = c;
//	cout<<cards[num_cards-1].value<<" ";
//	cout<<cards[num_cards-1].suit<<endl;;
}
/*************************************************************************
** Function: hand
** Description: copy constructer
** Parameters: reference to a const hand
** Pre-Conditions: none
** Post-Condition: none 
**************************************************************************/

hand::hand(const hand &other){
   //	cout<<"in copy constructer"<<endl;
	num_cards = other.num_cards;
	cards = new card[num_cards];
	for(int i = 0; i<num_cards; i++){
	   	cards[i] = other.cards[i];
	}
}
/*************************************************************************
** Function: hand
** Description: assignment operator
** Parameters: const hand &other
** Pre-Conditions: none
** Post-Condition: none 
**************************************************************************/

void hand::operator =(const hand &other){
   //	cout<<"in operator"<<endl;
	delete [] cards;
	num_cards = other.num_cards;
	cards = new card[num_cards];
	for(int i = 0; i<num_cards; i++){
	   	cards[i] = other.cards[i];
	}
}
/*************************************************************************
** Function: print_hand
** Description: prints a hand
** Parameters: none
** Pre-Conditions: none
** Post-Condition: none 
**************************************************************************/

void hand::print_hand(){
   	for(int i=0; i<num_cards; i++){
	   	if(cards[i].value == 11){
		   	cout<<"Jack ";
		}
		else if(cards[i].value == 12){
		   	cout<<"Queen ";
		}
		else if(cards[i].value == 13){
		   	cout<<"King ";
		}
		else if(cards[i].value == 1){
		   	cout<<"Ace ";
		}
		else{
			cout<<cards[i].value<<" ";
		}
		cout<<cards[i].suit<<endl;
	}
}
/*************************************************************************
** Function: print_one_card
** Description: prints the first card of a hand
** Parameters: none
** Pre-Conditions: none
** Post-Condition: none 
**************************************************************************/

void hand::print_one_card(){
   	cout<<"The dealer's face-up card is ";
   	if(cards[0].value == 11){
	   	cout<<"Jack ";
	}
	else if(cards[0].value == 12){
	   	cout<<"Queen ";
	}
	else if(cards[0].value == 13){
	   	cout<<"King ";
	}
	else if(cards[0].value == 1){
	   	cout<<"Ace ";
	}
	else{
	   	cout<<cards[0].value<<" ";
	}
   	cout<<cards[0].suit<<endl;
}
/*************************************************************************
** Function: card_points
** Description: calculates the card points and returns it
** Parameters: none
** Pre-Conditions: none
** Post-Condition: none 
**************************************************************************/

int hand::card_points(){ //function to total the points in the hand
	int points = 0, ace_count = 0;
	for(int i=0; i<num_cards; i++){
		if(cards[i].value > 1 && cards[i].value < 10){
			points = points + cards[i].value;
		}
		else if(cards[i].value > 9 && cards[i].value < 14){
			points = points + 10;
		}
		else if(cards[i].value == 1){
			ace_count = ace_count + 1;
		}
	}
	for(int i=0; i<ace_count; i++){
		if(points < 11){
			points = points + 11;
		}
		else if(points > 10){
			points = points + 1;
		}
	}
		return points;
}


