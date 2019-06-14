/**************************************************************************
** Program Filename: game.cpp
** Author: Mary Jacobsen
** Date: 4-22-16
** Description: Has all the game functions
** Input: All the functions that game uses
** Output: A game
**************************************************************************/
#include "player.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "dealer.h"
#include "game.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;
/**************************************************************************
** Function: game
** Description: default constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

game::game(){
   	players = NULL;
}
/**************************************************************************
** Function: game
** Description: non-default constructor
** Parameters: const game &other
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

game::game(const game &other){
   	num_players = other.num_players;
	players = new player[num_players];
	for(int i=0; i<num_players; i++){
	   	players[i] = other.players[i];
	}   	
}
/**************************************************************************
** Function: game
** Description: assignment operator
** Parameters: const game &other
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

void game::operator =(const game &other){
   	delete [] players;
	num_players = other.num_players;
	players = new player[num_players];
	for(int i=0; i<num_players; i++){
	   	players[i] = other.players[i];
	}   	
}
/**************************************************************************
** Function: ~game
** Description: destructer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

game::~game(){
   	delete [] players;
       	players = NULL;
}	
/**************************************************************************
** Function: set_players
** Description: sets the number of players and allocates memory for players
** Parameters: int n
** Pre-Conditions: number of players can't be negative
** Post-Conditions: none
**************************************************************************/

void game::set_players(int n){
   	num_players = n;
   	players = new player[num_players];
}
/**************************************************************************
** Function: set_p_hand
** Description: sets a player's hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

void game::set_p_hand(){
   	for(int i=0; i<num_players; i++){
		players[i].get_p_hand().set_hand(0, cards.get_card());
		players[i].get_p_hand().set_hand(1, cards.get_card());
	}
}
/**************************************************************************
** Function: turns
** Description: goes through the turn for each player
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

void game::turns(){
	for(int i=0; i<num_players; i++){
	   	cout<<"Player "<<(i+1)<<"'s turn!"<<endl;
	   	players[i].get_p_hand().print_hand();
		players[i].get_bet() = players[i].bet_amount();
		hit_or_stay(i);
	}
}
/**************************************************************************
** Function: hit_or_stay
** Description: loops through and asks a player to hit or stay until they say stay or go over 21
** Parameters: int i
** Pre-Conditions: i cannot be negative
** Post-Conditions: none
**************************************************************************/

void game::hit_or_stay(int i){
   	int choice, e = 1;
   	while(e == 1){
   		cout<<"Would you like another card(1) or would you like to stay(2)? ";
		cin>>choice;
		if(cin.fail()){
	   		cin.clear();
			cin.ignore();
			cout<<"Invalid input, please try again"<<endl;
		}
		else if(choice > 2 || choice < 1){
		   	cout<<"Please enter 1 or 2."<<endl;
		}
		else if(choice == 1){
		   	players[i].get_p_hand().add_card(cards.get_card());	
			players[i].get_p_hand().print_hand();
			if(players[i].get_p_hand().card_points() > 21){
			   	cout<<"You went over 21."<<endl;
				e = 0;
			}
		}
		else{
		   	e = 0;
		}
	}
}   	
/**************************************************************************
** Function: give_dealer_cards
** Description: gives the dealer a hand
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

void game::give_dealer_cards(){
   	for(int i=0; i<2; i++){
	   	game_dealer.get_d_hand().set_hand(i, cards.get_card());
	}
}
/**************************************************************************
** Function: dealer_add_card
** Description: adds a card to the dealer's hand if the points are under 17
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

void game::dealer_add_card(){
   	int e = 1;
   	while(e == 1){
   		if(game_dealer.get_d_hand().card_points() < 17){
	   		game_dealer.get_d_hand().add_card(cards.get_card());
		}
		else{
		   	e = 0;
		}
	}
}
/**************************************************************************
** Function: get_cards
** Description: returns a reference to the deck
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

deck& game::get_cards(){
   	//cout<<"in get_cards"<<endl;
   	return cards;
}
/**************************************************************************
** Function: get_game_dealer
** Description: returns a reference to the dealer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

dealer& game::get_game_dealer(){
   	return game_dealer;
}
/**************************************************************************
** Function: get_num_players
** Description: returns a reference to the number of players
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

int& game::get_num_players(){
   	return num_players;
}
/**************************************************************************
** Function: calculate_results
** Description: calculates who wins the bets
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/

void game::calculate_results(){
   	int w;
	cout<<"The dealer's hand is:"<<endl;
	game_dealer.get_d_hand().print_hand();
	for(int i=0; i<num_players; i++){
	   	if(players[i].get_p_hand().card_points() == 21){
		   	cout<<"Player "<<(i+1)<<" got blackjack!"<<endl;
			w = (players[i].get_playing_total() + (1.5*(players[i].get_bet())));
			cout<<"You have "<<w<<"!"<<endl;
		}
		else if(game_dealer.get_d_hand().card_points() > 21){
		   	cout<<"Player "<<(i+1)<<" wins the bet!"<<endl;
			w = (players[i].get_playing_total() + players[i].get_bet());
			cout<<"You have "<<w<<"!"<<endl;
		}
		else if(players[i].get_p_hand().card_points() > game_dealer.get_d_hand().card_points() && players[i].get_p_hand().card_points() < 22){
		   	cout<<"Player "<<(i+1)<<" wins the bet!"<<endl;
			w = (players[i].get_playing_total() + players[i].get_bet());
			cout<<"You have "<<w<<"!"<<endl;
		}
		else if(players[i].get_p_hand().card_points() == game_dealer.get_d_hand().card_points()){
		   	cout<<"Player "<<(i+1)<< "tied. They neither win or lose their bet."<<endl;
		}
		else{
		   	cout<<"Player "<<(i+1)<<" loses the bet."<<endl;
			w = (players[i].get_playing_total() - players[i].get_bet());
			cout<<"You have "<<w<<"."<<endl;
		}
	}
}



