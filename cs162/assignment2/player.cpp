/**************************************************************************
** Program Filename: player.cpp
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: Has all the player functions
** Input: All the functions that player objects use
** Output: players
**************************************************************************/
#include "player.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

/**************************************************************************
** Function: player
** Description: default constructer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

player::player(){ //constructer
   	playing_total = 100;
	card_total = 0;
	bet = 0;
}
/**************************************************************************
** Function: player
** Description: default set_playing_total
** Parameters: int p
** Pre-Conditions: p cannot be negative
** Post-Conditions: none
**************************************************************************/

void player::set_playing_total(int p){ //mutator
   	playing_total = p;
}
/**************************************************************************
** Function: set_card_total
** Description: sets card total
** Parameters: int c
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

void player::set_card_total(int c){ //mutator
   	card_total = c;
}
/**************************************************************************
** Function: set_bet
** Description: sets the bet
** Parameters: int b
** Pre-Conditions: b should not a be negative
** Post-Conditions: none
**************************************************************************/

void player::set_bet(int b){ //mutator
   	bet = b;
}
/**************************************************************************
** Function: get_p_hand
** Description: accessor to p_hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

hand& player::get_p_hand(){ //accessor
   	return p_hand;
}
/**************************************************************************
** Function: get_playing_total
** Description: returns playing_total
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

int& player::get_playing_total(){ //accesser
   	return playing_total;
}
/**************************************************************************
** Function: get_card_total
** Description: returns card_total
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

int& player::get_card_total(){ //accesser
   	return card_total;
}
/**************************************************************************
** Function: get_bet
** Description: returns bet
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

int& player::get_bet(){ //accesser
   	return bet;
}
/**************************************************************************
** Function: bet_amount
** Description: gets how much the player wants to bet
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

int player::bet_amount(){
   	int b, e = 1;
	while(e == 1){
   		cout<<"How much would you like to bet? ";
		cin>>b;
		if(cin.fail()){
	   		cin.clear();
			cin.ignore();
			cout<<"Invalid input, please try again"<<endl;
		}
		else if(b > playing_total){
		   	cout<<"You do not have enough to bet that much."<<endl;
		}
		else if(b < 0){
   			cout<<"You may not bet a negative number."<<endl;
     		}
		else{
		   	e = 0;
		}
	}
	return b;
}

	
