/*************************************************************************
** Filename: driver.cpp 
** Author: Mary Jacobsen
** Date: 5/22/16
** Description: runs the game
** Input: all the event files room.h game.h
** Output: a game
**************************************************************************/

#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "escape_rope.h"
#include "bats.h"
#include "empty.h"
#include "gold.h"
#include "pit.h"
#include "event.h"
#include "game.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/*************************************************************************
** Function: is_greater_than_three
** Description: checks if a char is greater than 3
** Parameters: pointer to a char
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

bool is_greater_than_three(char* num){
   	for(int i=0; num[i]=='\0'; i++){
	   	if(num[i]<48 || num[i]>57){
		   	return false;
		}
	}
	if(atoi(num) < 4){
	   	return false;
	}
	return true;
}
/*************************************************************************
** Function: start_over_same_caves
** Description: sets everything to false to start over
** Parameters: reference to a game
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/

void start_over_same_caves(game &g){
   	if(g.get_kill_wumpus()){
	   	g.add_wumpus();
	}
	g.set_player_row(g.get_escape_rope_row());	
	g.set_player_column(g.get_escape_rope_column());
   	g.set_kill_wumpus(false);
	g.set_grab_gold(false);
	g.set_arrows(3);
	g.set_lose(false);
	g.set_win(false);
}

int main(int argc, char *argv[]){
   	// command line 
   	int size;
	char choice;
	char input;
   	if(argc != 2){
	   	cout<<"Not the correct number of arguments"<<endl;
		exit(1);
	}

	if(is_greater_than_three(argv[1])){
	   	size = atoi(argv[1]);
	}
	else{
	   	cout<<"Please enter a positive integer no smaller than 4."<<endl;
		exit(1);
	}
	while(true){
   		game g(size);
		while(true){
		   	cout<<endl;
		   	g.enter();
			while(g.get_win() == false && g.get_lose() == false){
			   	cout<<endl;
			//	g.print_grid();
				cout<<endl;
				g.print_hidden_grid();
				cout<<endl;
				cout<<"Would you like to move(1) or shoot(2)? ";
				cin>>input;
				if(input == '1'){
				   	cout<<endl;
				   	g.move();
					cout<<endl;
					g.enter();
					if(g.get_bat() == true){
					   	cout<<endl;
					   	g.enter();
						cout<<endl;
						g.print_hidden_grid();
						cout<<endl;
						g.set_bat(false);
					}
				}
				else if(input == '2'){
				   	g.shoot();
						if(g.get_arrows() == 0){
						   	if(g.get_kill_wumpus() == false){
							   	g.set_lose(true);
								cout<<"You lost because you ran out of arrows before killing the wumpus."<<endl;
							}
						}
				}
				else{
				   	cout<<"Invalid input"<<endl;
				}
			}
			cout<<"Would you like to start over with the same caves(1), different caves(2), or give up(3)?: ";
			cin>>choice;
			if(choice == '1'){
		   		start_over_same_caves(g);
		     		continue;
			}
			else if(choice == '2'){
	     			break;
			}
			else{
   				exit(0);
    			}

		}
	}
					
  	return 0;
}
