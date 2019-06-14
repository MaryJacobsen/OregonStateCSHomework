/**************************************************************************
** Program: blackjack
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: game of blackjack
** Input: card.h, deck.h, hand.h, player.h, dealer.h, game.h
** Output: a blackjack game
**************************************************************************/
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "dealer.h"
#include "game.h"
#include <iostream>
#include <cstdlib>

using namespace std;

/**************************************************************************
** Function: main
** Description: controls the game
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

int main(){
   	game bj;
	int np, e = 1;
	bj.get_cards().shuffle();
	while(e == 1){
	   	cout<<"Welcome to Blackjack. Please enter the number of players. ";
		cin>>np;
		if(cin.fail()){
	   		cin.clear();
			cin.ignore();
			cout<<"Invalid input, please try again"<<endl;
		}
		else if(np < 0){
   			cout<<"You may not have a negative number of players."<<endl;
     		}
		else{
   			bj.set_players(np);
			bj.set_p_hand();
			bj.give_dealer_cards();
			bj.get_game_dealer().get_d_hand().print_one_card();
			e = 0;
     		}
	}
	bj.turns();
	bj.dealer_add_card();
	bj.calculate_results();

	return 0;
}
