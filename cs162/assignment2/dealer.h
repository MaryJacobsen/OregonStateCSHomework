/**************************************************************************
** Program Filename: dealer.h
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: dealer class
** Input: card.h, deck.h, hand.h
** Output: dealer class
**************************************************************************/

#include "card.h"
#include "deck.h"
#include "hand.h"
#pragma once

class dealer{
   	private: 
	   	hand d_hand;
		int card_total;
	public:
		dealer();
		void set_card_total(int);
		hand& get_d_hand();
		int& get_card_total();
};

