/**************************************************************************
** Program Filename: game.h
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: game class
** Input: card.h, deck.h, hand.h, dealer. player.h
** Output: blackjack game
**************************************************************************/
#include "player.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "dealer.h"

class game{
   	private:
	   	deck cards;
		player *players;
		dealer game_dealer;
		int num_players;
	public:
		game();
		game(const game&); //copy constructer
		void operator =(const game&);
		~game();
		void set_players();
		void set_game_dealer();
		void set_players(int);
		void set_p_hand();
		deck& get_cards();
		//player& get_players();
		dealer& get_game_dealer();
		int& get_num_players();
		void give_dealer_cards();
		void dealer_add_card();
		void turns();
		void hit_or_stay(int);
		void calculate_results();
};



