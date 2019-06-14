/**************************************************************************
** Program Filename: player.h
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: player class
** Input: card.h, deck.h, hand.h
** Output: player
**************************************************************************/

#include "card.h"
#include "deck.h"
#include "hand.h"

#pragma once
class player{
   	private:
	   	hand p_hand;
		int playing_total;
		int card_total;
		int bet;
	public:
		player(); //constructer
		void set_playing_total(int); //mutator
		void set_card_total(int); //mutator
		void set_bet(int); //mutator
		hand& get_p_hand(); //accesser
		int& get_playing_total(); //accesser
		int& get_card_total(); //accesser
		int& get_bet(); //accesser
		int bet_amount();

};
