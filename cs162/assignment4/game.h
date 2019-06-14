#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "escape_rope.h"
#include "bats.h"
#include "empty.h"
#include "gold.h"
#include "pit.h"
#include <iostream>
#include <cstring>
#include <vector>
#pragma once
class game{
   	private:
	   	int size;
   		int player_row;
		int player_column;
		int wumpus_row;
		int wumpus_column;
		int escape_rope_row;
		int escape_rope_column;
		int arrows;
		bool bat;
		bool grab_gold;
		bool kill_wumpus;
		bool win;
		bool lose;
		std::vector< std::vector< room > > grid;
	public:
		game(int);
		void print_grid();
		void print_hidden_grid();
		bool on_grid(int, int);
		void move();
		void shoot();
		void enter();
		void add_wumpus();
		void set_size(int);
		void set_player_row(int);
		void set_player_column(int);
		void set_escape_rope_row(int);
		void set_escape_rope_column(int);
		void set_arrows(int);
		void set_kill_wumpus(bool);
		void set_grab_gold(bool);
		void set_win(bool);
		void set_lose(bool);
		void set_bat(bool);
		int get_size();
		int get_player_row();
		int get_player_column();
		int get_escape_rope_row();
		int get_escape_rope_column();
		int get_arrows();
		bool get_grab_gold();
		bool get_kill_wumpus();
		bool get_win();
		bool get_lose();
		bool get_bat();
};





