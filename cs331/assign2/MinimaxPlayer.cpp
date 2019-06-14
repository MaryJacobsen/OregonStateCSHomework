/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

bool MinimaxPlayer::terminal_test(OthelloBoard* b) {
	if( (!(b->has_legal_moves_remaining(b->get_p1_symbol())) && !(b->has_legal_moves_remaining(b->get_p2_symbol()))) ) {
		//at terminal state
		return 1;
	} else {
		//not at terminal state
		return 0;
	}
}

int MinimaxPlayer::utility(OthelloBoard* b) {
	return b->count_score(b->get_p1_symbol()) - b->count_score(b->get_p2_symbol());	
}

int MinimaxPlayer::max_value(OthelloBoard* b) {

	if(terminal_test(b)) {
		return utility(b);
	}

	int value = -100;
	int num_successors = 0;
	int i = 0;
	MinimaxPlayer::OthelloNode successors[(b->get_num_cols() * b->get_num_rows()) - 4];

	current_symbol = b->get_p1_symbol();
	MinimaxPlayer::OthelloNode* successor_list = get_successors(successors, b, num_successors);

	for(i = 0; i < num_successors; i++) {
		value = std::max(value, min_value(successor_list[i].board));
	}

	return value;
}

int MinimaxPlayer::min_value(OthelloBoard* b) {
	
	if(terminal_test(b)) {
		return utility(b);
	}

	int value = 100;
	int num_successors = 0;
	int i = 0;
	MinimaxPlayer::OthelloNode successors[(b->get_num_cols() * b->get_num_rows()) - 4];

	current_symbol = b->get_p2_symbol();
	MinimaxPlayer::OthelloNode* successor_list = get_successors(successors, b, num_successors);

	for(i = 0; i < num_successors; i++) {
		value = std::min(value, max_value(successor_list[i].board));
	}

	for(i = 0; i < num_successors; i++) {
		delete successor_list[i].board;
	}

	return value;
}		


MinimaxPlayer::OthelloNode* MinimaxPlayer::get_successors(OthelloNode* successors, OthelloBoard* board, int& num_successors) {
	int row, col = 0;
	for(row = 0; row < board->get_num_rows(); row++) {
		for(col = 0; col < board->get_num_cols(); col++) {
			if(board->is_legal_move(col, row, current_symbol)) {
				successors[num_successors].board = new OthelloBoard(*(board));
				successors[num_successors].board->play_move(col, row, current_symbol);
				successors[num_successors].column = col;
				successors[num_successors].row = row;
				successors[num_successors].value = -1;
				num_successors++;
			}
		}
	}
	return successors;
}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // To be filled in by you
  	char player;
	int maxvalue = -100;
	int minvalue = 100;
	int best_board = 0;
	int i = 0;
	int num_successors = 0;
	int depth = 0;

	current_symbol = symbol;

	MinimaxPlayer::OthelloNode successors[(b->get_num_cols() * b->get_num_rows()) - 4];

	MinimaxPlayer::OthelloNode* successor_list = get_successors(successors, b, num_successors);

	if (current_symbol == b->get_p1_symbol()) {
		current_symbol = b->get_p2_symbol();
	} else {
		current_symbol = b->get_p1_symbol();
	}

	for(i = 0; i < num_successors; i++){

		if(b->get_p1_symbol() == symbol) {
			int temp_value = min_value(successor_list[i].board);
			if (temp_value > maxvalue){
				maxvalue = temp_value;
				best_board = i;
			}
		
		} else {
			int temp_value = max_value(successor_list[i].board);
			if (temp_value < minvalue){
				minvalue = temp_value;
				best_board = i;
			}
		}
	}

	col = successor_list[best_board].column;
	row = successor_list[best_board].row; 
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
