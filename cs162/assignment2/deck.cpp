/**************************************************************************
** Program Filename: deck.cpp
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: Has all the deck functions
** Input: All the functions that deck objects use
** Output: A deck
**************************************************************************/

#include "card.h"
#include "deck.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
/**************************************************************************
** Function: deck
** Description: default constructer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

deck::deck(){ //constructor
	char club = 'c', spade = 's', heart = 'h', diamond = 'd';
	place = 0; 
	num_cards = 52; 
	int card_count = 0;
	for(int c=1; c<14; c++){
		cards[card_count].suit = "club";
		cards[card_count].value = c;
	//	cout<<cards[card_count].value<<" ";
	//	cout<<cards[card_count].suit<<endl;
		card_count++;
	}
	for(int s=1; s<14; s++){
		cards[card_count].suit = "spade";
		cards[card_count].value = s;
	//	cout<<cards[card_count].value<<" ";
	//	cout<<cards[card_count].suit<<endl;
		card_count++;
	}
	for(int h=1; h<14; h++){
		cards[card_count].suit = "heart";
		cards[card_count].value = h;
	//	cout<<cards[card_count].value<<" ";
	//	cout<<cards[card_count].suit<<endl;
		card_count++;
	}
	for(int d=1; d<14; d++){
		cards[card_count].suit = "diamond";
		cards[card_count].value = d;
	//	cout<<cards[card_count].value<<" ";
	//	cout<<cards[card_count].suit<<endl;
		card_count++;
	}
}
/**************************************************************************
** Function: get_card
** Description: gets the top card from the deck and increments the place also calls the shuffle once place gets to 52
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

card deck::get_card(){ //accessor
   	if(place > 51)
	   	shuffle();
	place++;
	return cards[place-1];
}
/**************************************************************************
** Function: shuffle
** Description: shuffles the deck
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

void deck::shuffle(){ //shuffles the deck
//   	cout<<"in shuffle"<<endl;
	card temp;
	int card_one, card_two;
	srand(time(NULL));
	for(int i=0; i<75; i++){
		card_one = rand()%52;
		card_two = rand()%52;
		temp = cards[card_one];
		cards[card_one] = cards[card_two];
		cards[card_two] = temp;
	}
	place = 0;
}


