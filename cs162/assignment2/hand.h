#include "card.h"
#include "deck.h"

#pragma once
class hand{
   	private:
	   	card *cards;
		int num_cards;
	public:
		hand(); // default constructer
		hand(const hand &); //copy constructer
		void operator =(const hand &);
		~hand(); //destructor
		void set_hand(int, card); //mutator
		card* get_hand(); //accesser
		int& get_num_cards(); //accesser
		void print_hand();
		void print_one_card();
		void add_card(card);
		int card_points(); //function to total the points in a hand
		
};
