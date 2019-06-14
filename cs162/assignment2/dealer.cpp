/**************************************************************************
** Program Filename: dealer.cpp
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: Has all the functions that the dealer objects use
** Input: card.h, deck.h, hand.h, dealer.h
** Output: dealer
**************************************************************************/

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "dealer.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
/**************************************************************************
** Function: dealer
** Description: default constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

dealer::dealer(){ //constructor
   	int card_total = 0;
}
/**************************************************************************
** Function: set_card_total
** Description: sets the card total
** Parameters: int t
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

void dealer::set_card_total(int t){ //mutator
   	card_total = t;
}
/**************************************************************************
** Function: get_d_hand
** Description: accessor to the dealer's hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

hand& dealer::get_d_hand(){
   	return d_hand;
}
/**************************************************************************
** Function: get_card_total
** Description: accessor to the card total
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

int& dealer::get_card_total(){
   	return card_total;
}



