/**************************************************************************
** Program Filename: deck.h
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: deck class
** Input: card.h, 
** Output: deck
**************************************************************************/


#include "card.h"
#pragma once
class deck{
   	private:
	   	card cards[52];
		int num_cards;
		int place;
	public:
		deck(); //constructor 
		card get_card(); //accessor		
		void shuffle();

};
		


		   	

