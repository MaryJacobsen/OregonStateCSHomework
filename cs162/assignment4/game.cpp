/*************************************************************************
** Filename: game.cpp 
** Author: Mary Jacobsen
** Date: 5/22/16
** Description: has all the game functions
** Input: all the event files room.h game.h
** Output: a game
**************************************************************************/

#include "game.h"
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "escape_rope.h"
#include "bats.h"
#include "empty.h"
#include "gold.h"
#include "pit.h"
#include <iostream>
#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

/*************************************************************************
** Function: game(int)
** Description: constructor
** Parameters: int size of grid
** Pre-Conditions: needs to be positive no smaller than 4
** Post-Conditions: none
*************************************************************************/

game::game(int s){
	int r=0, c=0;
	arrows = 3;
	size = s;
	grab_gold = false;
	kill_wumpus = false;
	win = false;
	lose = false;
	bat = false;
   	for(int i=0; i<size; i++){
	   	vector<room> v;
	   	for(int j=0; j<size; j++){
		   	room r;
			v.push_back(r);
		}
		grid.push_back(v);
	}
	
	srand(time(NULL));
	while(true){
		r = rand() % size;
		c = rand() % size;
		if(grid.at(r).at(c).get_e()->type() == "empty"){
		   	event *x = new wumpus;
	   		grid.at(r).at(c).set_e(x);
			wumpus_row = r;
			wumpus_column = c;
			break;
		}
	}
	while(true){
		r = rand() % size;
		c = rand() % size;
		if(grid.at(r).at(c).get_e()->type() == "empty"){
		   	event *x = new gold;
	   		grid.at(r).at(c).set_e(x);
			break;
		}
	}
	while(true){
		r = rand() % size;
		c = rand() % size;
		if(grid.at(r).at(c).get_e()->type() == "empty"){
		   	event *x = new bats;
	   		grid.at(r).at(c).set_e(x);
			break;
		}
	}
	while(true){
		r = rand() % size;
		c = rand() % size;
		if(grid.at(r).at(c).get_e()->type() == "empty"){
		   	event *x = new bats;
	   		grid.at(r).at(c).set_e(x);
			break;
		}
	}
	while(true){
		r = rand() % size;
		c = rand() % size;
		if(grid.at(r).at(c).get_e()->type() == "empty"){
		   	event *x = new pit;
	   		grid.at(r).at(c).set_e(x);
			break;
		}
	}
	while(true){
		r = rand() % size;
		c = rand() % size;
		if(grid.at(r).at(c).get_e()->type() == "empty"){
		   	event *x = new pit;
	   		grid.at(r).at(c).set_e(x);
			break;
		}
	}
	while(true){
		r = rand() % size;
		c = rand() % size;
		if(grid.at(r).at(c).get_e()->type() == "empty"){
		   	event *x = new escape_rope;
	   		grid.at(r).at(c).set_e(x);
			player_row = r;
			player_column = c;
			escape_rope_row = r;
			escape_rope_column = c;
			break;
		}
	}
}
/*************************************************************************
** Function: print_grid
** Description: prints a grid
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void game::print_grid(){
   	for(int r=0; r<size; r++){
	   	for(int c=0; c<size; c++){
		   	cout<<grid.at(r).at(c).get_e()->type()<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
/*************************************************************************
** Function: print_hidden_grid
** Description: prints a hidden grid
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void game::print_hidden_grid(){
   	for(int r=0; r<size; r++){
	   	for(int c=0; c<size; c++){
		   	if(r == player_row && c == player_column){
			   	cout<<"|"<<grid.at(r).at(c).get_e()->type()<<"|";
			}
			else{
		   		cout<<"|xxxxx|";
			}
		}
		cout<<endl;
	}
	cout<<endl;
}
/*************************************************************************
** Function: on_grid
** Description: checks if coordinates are on the grid
** Parameters: two ints
** Pre-Conditions: positive
** Post-Conditions: none
*************************************************************************/

bool game::on_grid(int r, int c){
   	if(r < 0 || r >= size || c < 0 || c >= size){
	   	return false;
	}
	else{
	   	return true;
	}
}
/*************************************************************************
** Function: move
** Description: moves the player on the grid
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void game::move(){
   	char choice;
	while(true){
	   	cout<<"You are at ("<<player_row<<", "<<player_column<<")."<<endl;
   		cout<<"Would you like to move North(n), East(e), South(s), or West(w)? ";
		cin>>choice;
		cout<<endl;
		if(choice == 'n'){
		   	if(on_grid(player_row-1, player_column)){
			      	player_row = player_row - 1;
				break;
			}
			else{
				cout<<"That is not in the caves."<<endl;
				continue;
			}
		}
		else if(choice == 'e'){
		   	if(on_grid(player_row, player_column+1)){
			      	player_column = player_column + 1;
				break;
			}
			else{
				cout<<"That is not in the caves."<<endl;
				continue;
			}
		}
		else if(choice == 's'){
		   	if(on_grid(player_row+1, player_column)){
			      	player_row = player_row + 1;
				break;
			}
			else{
				cout<<"That is not in the caves."<<endl;
				continue;
			}
		}
		else if(choice == 'w'){
		   	if(on_grid(player_row, player_column-1)){
			      	player_column = player_column - 1;
				break;
			}
			else{
				cout<<"That is not in the caves."<<endl;
				continue;
			}
		}
		else{
			cout<<"Please enter n, e, s, or w."<<endl;
			continue;
		}
	}
}
/*************************************************************************
** Function: enter
** Description: enters a room
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void game::enter(){
	//message
   	grid.at(player_row).at(player_column).get_e()->enter();
	
	//effects of entering the room
	if(grid.at(player_row).at(player_column).get_e()->type() == "pit" || grid.at(player_row).at(player_column).get_e()->type() == "wumpus"){
	   	lose = true;
		return;
	}

	else if(grid.at(player_row).at(player_column).get_e()->type() == "gold"){
	   	grab_gold = true;
	}

	else if(grid.at(player_row).at(player_column).get_e()->type() == "bats"){
	   	int r, c;
		bat = true;
		srand(time(NULL));
	   	while(true){
		   	r = rand() % size;
			c = rand() % size;
			if(on_grid(r, c)){
			   	player_row = r;
				player_column = c;
				break;
			}
		}
	}

	else if(grid.at(player_row).at(player_column).get_e()->type() == "escape_rope"){
	   	if(kill_wumpus == true && grab_gold == true){
		   	cout<<"You won!"<<endl;
		   	win = true;
			return;
		}
	}	

	//percepts for rooms directly adajacent to the player
   	if(on_grid(player_row-1, player_column)){
   		grid.at(player_row-1).at(player_column).get_e()->nearby();
    	}

	if(on_grid(player_row, player_column+1)){
   		grid.at(player_row).at(player_column+1).get_e()->nearby();
    	}

	if(on_grid(player_row+1, player_column)){
   		grid.at(player_row+1).at(player_column).get_e()->nearby();
    	}	

	if(on_grid(player_row, player_column-1)){
   		grid.at(player_row).at(player_column-1).get_e()->nearby();
    	}
}
/*************************************************************************
** Function: shoot
** Description: shoots an arrow
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void game::shoot(){
   	if(kill_wumpus == true){
	   	cout<<"You already killed the wumpus."<<endl;
		return;
	}
	arrows = arrows-1;
    	char choice;
	int r, c;
	while(true){
	   	cout<<"You are at ("<<player_row<<", "<<player_column<<")."<<endl;
   		cout<<"Would you like to shoot North(n), East(e), South(s), or West(w)? ";
		cin>>choice;
		cout<<endl;
		if(choice == 'n'){
		   	if( (on_grid(player_row-1, player_column) && grid.at(player_row-1).at(player_column).get_e()->type() == "wumpus") ||  (on_grid(player_row-2, player_column) && grid.at(player_row-2).at(player_column).get_e()->type() == "wumpus") ||  (on_grid(player_row-3, player_column) && grid.at(player_row-3).at(player_column).get_e()->type() == "wumpus") ){
			   	cout<<"You killed the wumpus!"<<endl;
				kill_wumpus = true;
				event *x = new empty;
				grid.at(wumpus_row).at(wumpus_column).set_e(x);
				break;
			}
			else{
			   	cout<<"Your arrow hit a wall."<<endl;
				srand(time(NULL));
				int t = rand()%4;
				if(t == 0){
				   	cout<<"You woke up the wumpus but it fell back asleep."<<endl;
				}
				else{
				   	cout<<"You woke up the wumpus and it moved to a different room!"<<endl;
					while(true){
						r = rand()%size;
						c = rand()%size;		
						if(on_grid(r, c) && grid.at(r).at(c).get_e()->type() == "empty"){
							event *x = new empty;
							grid.at(wumpus_row).at(wumpus_column).set_e(x);
							wumpus_row = r;
							wumpus_column = c;
							event *w = new wumpus;
							grid.at(wumpus_row).at(wumpus_column).set_e(w);
							break;
						}
						else{
							continue;
						}
					}
				}
				break;
			}
		}
		else if(choice == 'e'){
		   	if( (on_grid(player_row, player_column+1) && grid.at(player_row).at(player_column+1).get_e()->type() == "wumpus") ||  (on_grid(player_row, player_column+2) && grid.at(player_row).at(player_column+2).get_e()->type() == "wumpus") ||  (on_grid(player_row, player_column+3) && grid.at(player_row).at(player_column+3).get_e()->type() == "wumpus") ){
			   	cout<<"You killed the wumpus!"<<endl;
				kill_wumpus = true;
				event *x = new empty;
				grid.at(wumpus_row).at(wumpus_column).set_e(x);
				break;
			}
			else{
			   	cout<<"Your arrow hit a wall."<<endl;
				srand(time(NULL));
				int t = rand()%4;
				if(t == 0){
				   	cout<<"You woke up the wumpus but it fell back asleep."<<endl;
				}
				else{
				   	cout<<"You woke up the wumpus and it moved to a different room!"<<endl;
					while(true){
						int count = 0;
						count++;		
						r = rand()%size;
						c = rand()%size;		
						if(on_grid(r, c) && grid.at(r).at(c).get_e()->type() == "empty"){
							event *x = new empty;
							grid.at(wumpus_row).at(wumpus_column).set_e(x);
							wumpus_row = r;
							wumpus_column = c;
							event *w = new wumpus;
							grid.at(wumpus_row).at(wumpus_column).set_e(w);
							break;
						}
						else{
							continue;
						}
					}
				}
				break;
			}
		}
		else if(choice == 's'){
		   	if( (on_grid(player_row+1, player_column) && grid.at(player_row+1).at(player_column).get_e()->type() == "wumpus") ||  (on_grid(player_row+2, player_column) && grid.at(player_row+2).at(player_column).get_e()->type() == "wumpus") ||  (on_grid(player_row+3, player_column) && grid.at(player_row+3).at(player_column).get_e()->type() == "wumpus") ){
			   	cout<<"You killed the wumpus!"<<endl;
				kill_wumpus = true;
				event *x = new empty;
				grid.at(wumpus_row).at(wumpus_column).set_e(x);
				break;
			}
			else{
			   	cout<<"Your arrow hit a wall."<<endl;
				srand(time(NULL));
				int t = rand()%4;
				if(t == 0){
				   	cout<<"You woke up the wumpus but it fell back asleep."<<endl;
				}
				else{
				   	cout<<"You woke up the wumpus and it moved to a different room!"<<endl;
					while(true){
						r = rand()%size;
						c = rand()%size;		
						if(on_grid(r, c) && grid.at(r).at(c).get_e()->type() == "empty"){
							event *x = new empty;
							grid.at(wumpus_row).at(wumpus_column).set_e(x);
							wumpus_row = r;
							wumpus_column = c;
							event *w = new wumpus;
							grid.at(wumpus_row).at(wumpus_column).set_e(w);
							break;
						}
						else{
							continue;
						}
					}
				}
				break;
			}
		}
		else if(choice == 'w'){
		   	if( (on_grid(player_row, player_column-1) && grid.at(player_row).at(player_column-1).get_e()->type() == "wumpus") ||  (on_grid(player_row, player_column-2) && grid.at(player_row).at(player_column-2).get_e()->type() == "wumpus") ||  (on_grid(player_row, player_column-3) && grid.at(player_row).at(player_column-3).get_e()->type() == "wumpus") ){
			   	cout<<"You killed the wumpus!"<<endl;
				kill_wumpus = true;
				event *x = new empty;
				grid.at(wumpus_row).at(wumpus_column).set_e(x);
				break;
			}
			else{
			   	cout<<"Your arrow hit a wall."<<endl;
				srand(time(NULL));
				int t = rand()%4;
				if(t == 0){
				   	cout<<"You woke up the wumpus but it fell back asleep."<<endl;
				}
				else{
				   	cout<<"You woke up the wumpus and it moved to a different room!"<<endl;
					while(true){
						r = rand()%size;
						c = rand()%size;		
						if(on_grid(r, c) && grid.at(r).at(c).get_e()->type() == "empty"){
							event *x = new empty;
							grid.at(wumpus_row).at(wumpus_column).set_e(x);
							wumpus_row = r;
							wumpus_column = c;
							event *w = new wumpus;
							grid.at(wumpus_row).at(wumpus_column).set_e(w);
							break;
						}
						else{
							continue;
						}
					}
				}
				break;
			}
		}
		else{
		   	cout<<"Please enter n, e, s, or w."<<endl;
			continue;
		}
	}
}
/*************************************************************************
** Function: add_wumpus
** Description: adds a wumpus to a random empty room
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void game::add_wumpus(){
   	 int r, c;
	srand(time(NULL));
	while(true){
		r = rand() % size;
		c = rand() % size;
		if(grid.at(r).at(c).get_e()->type() == "empty"){
		   	event *x = new wumpus;
	   		grid.at(r).at(c).set_e(x);
			wumpus_row = r;
			wumpus_column = c;
			break;
		}
	}
}

/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: positive int no smaller than 4
** Post-Conditions: none
*************************************************************************/
void game::set_size(int s){
   	size = s;
}

/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: on grid
** Post-Conditions: none
*************************************************************************/	
void game::set_player_row(int p){
   	player_row = p;
}
/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: on grid
** Post-Conditions: none
*************************************************************************/
void game::set_player_column(int c){
   	player_column = c;
}
/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: positive int 
** Post-Conditions: none
*************************************************************************/
void game::set_arrows(int a){
   	arrows = a;
}
/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: bool 
** Post-Conditions: none
*************************************************************************/
void game::set_kill_wumpus(bool k){
   	kill_wumpus = k;
}
/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: bool
** Post-Conditions: none
*************************************************************************/
void game::set_grab_gold(bool g){
   	grab_gold = g;
}
/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: bool  
** Post-Conditions:none
*************************************************************************/
void game::set_win(bool w){
   	win = w;
}
/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: bool
** Post-Conditions: none
*************************************************************************/
void game::set_lose(bool l){
   	lose = l;
}
/*************************************************************************
** Function: mutator
** Description: sets a private member
** Parameters: what you want to set it to
** Pre-Conditions: bool
** Post-Conditions:none
*************************************************************************/
void game::set_bat(bool b){
   	bat = b;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
int game::get_size(){
   	return size;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

int game::get_player_row(){
   	return player_row;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

int game::get_player_column(){
   	return player_column;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

int game::get_escape_rope_row(){
   	return escape_rope_row;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

int game::get_escape_rope_column(){
   	return escape_rope_column;
}
 /*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
  	
int game::get_arrows(){
   	return arrows;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

bool game::get_grab_gold(){
   	return grab_gold;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

bool game::get_kill_wumpus(){
   	return kill_wumpus;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

bool game::get_win(){
   	return win;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

bool game::get_lose(){
   	return lose;
}
/*************************************************************************
** Function: accessor
** Description: gets a private member
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

bool game::get_bat(){
   	return bat;
}







   	
   	
   	
