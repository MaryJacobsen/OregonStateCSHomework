/**************************************************************************
** Program: assignment6
** Author: Mary Jacobsen
** Date: 3-10-16
** Description: Minesweeper Game
** Input: The user inputs the rows, columns, and mines using command line
** Output: A minesweeper game
**************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <cstdlib>

using namespace std;
/**************************************************************************
** Function: makeBoard
** Description: Makes a dynamic 2D array the size of rows and cols
** Parameters: rows, cols, and mines 
** Pre-Conditions: Need to have rows and cols set to positive ints
** Post-Conditions: none
*************************************************************************/  
char** makeBoard(int rows, int cols, int mines){
	char** board = new char *[rows];
      	for(int i=0; i<rows; i++){
		board[i] = new char[cols];
     	}
	for(int j=0; j<rows; j++){
	   	for(int k=0; k<cols; k++){
		   	board[j][k] = '0';
		}
	}
	return board;	
}
/**************************************************************************
** Function: makeUserBoard
** Description: Makes a dynamic 2D array (specifically the board the user sees 
** Parameters: rows, cols, and mines
** Pre-Conditions: rows and cols must be set to positive ints
** Post-Conditions: none
**************************************************************************/ 
char** makeUserBoard(int rows, int cols, int mines){
   	char** userBoard = new char *[rows];
	for(int i=0; i<rows; i++){
	   	userBoard[i] = new char[cols];
	}
	for(int j=0; j<rows; j++){
	   	for(int k=0; k<cols; k++){
		   	userBoard[j][k] = '#';
		}
	}
	return userBoard;
}
/**************************************************************************
** Function: printBoard
** Description: Prints a board
** Parameters: rows, cols, and a 2D array
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/  
void printBoard(int rows, int cols, char** board){
   	for(int r=0; r<rows; r++){
	   	cout<<"|";
	   	for(int c=0; c<cols; c++){
		   	cout<<board[r][c]<<"|";
		}
		cout<<endl;
	}
}			   	
/**************************************************************************
** Function: mineBoard
** Description: puts mines on the key board
** Parameters: rows, cols, mines, key board
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/  
void mineBoard(int rows, int cols, int mines, char** board){
	int nummines=0, a, b;
	srand(time(NULL));
	while(nummines<mines){
	   	a=rand()%rows;
		b=rand()%cols;
		if(board[a][b]=='*'){
		   	continue;
		}
		else{
		   	board[a][b]='*';
			nummines++;
		}
	}
}
/**************************************************************************
** Function: numberBoard
** Description: puts the numbers on the key board
** Parameters: rows, cols, mines, key board
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/ 	
void numberBoard(int rows, int cols, int mines, char** board){
   	char minecount;
	for(int r=0; r<rows; r++){
	   	for(int c=0; c<cols; c++){
		   	minecount='0';
			if(board[r][c]=='*'){
			   	continue;
			}	
			else{
				if(c != 0 && board[r][c-1]=='*')
					minecount++;
				if(c != cols-1 && board[r][c+1]=='*')
					minecount++;
				if(r != 0 && c != 0 && board[r-1][c-1]=='*')
					minecount++;
				if(r != 0 && board[r-1][c]=='*')
					minecount++;
				if(r != 0 && c != cols-1 && board[r-1][c+1]=='*')
					minecount++;
				if(r != rows-1 && c != 0 && board[r+1][c-1]=='*')
					minecount++;
				if(r != rows-1 && board[r+1][c]=='*')
					minecount++;
				if(r != rows-1 && c != cols-1 && board[r+1][c+1]=='*')
					minecount++;
			}
			board[r][c] = minecount;
		}
	}
}

/**************************************************************************
** Function: isPositiveInt
** Description: checks if the user put positive ints for the command line
** Parameters: a pointer to a char
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/
bool isPositiveInt(char* num){
   	for(int i=0; num[i]=='\0'; i++){
	   	if((int)num[i]<48 || (int)num[i]>57){
		   	return false;
		}
	}
	return true;
}
/**************************************************************************
** Function: flagCell
** Description: Asks the cell the user wants to flag and flags it
** Parameters: rows, cols, board the user sees
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/
void flagCell(int rows, int cols, char** userBoard){
   	int r, c, e = 1;
	while(e == 1){
   		cout<<"row, column: ";
		cin>>r>>c;
		if(cin.fail()){
		   	cin.clear();
			cin.ignore();
	   		cout<<"Invalid Input"<<endl;
			continue;
		}
		else if(r<0 || r>rows-1 || c<0 || c>cols-1){
	   		cout<<"That is not on the board. Try again."<<endl;
			continue;
		}	
		else{
		   	if(userBoard[r][c] != '#' && userBoard[r][c] != '!'){
			   	cout<<"You have already opened that cell."<<endl;
				continue;
			}
			if(userBoard[r][c] == '!'){
			   	cout<<"You have already flagged that cell."<<endl;
				continue;
			}
			else{
	   			userBoard[r][c] = '!';
				e = 0;
				printBoard(rows, cols, userBoard);
			}
		}
	}
}
/**************************************************************************
** Function: win
** Description: checks if the user has won
** Parameters: rows, cols, mines, gameOver, userBoard, and board
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/ 
void win(int rows, int cols, int mines, int & gameOver, char** userBoard, char** board){
   	for(int r = 0; r<rows; r++){
	   	for(int c = 0; c<cols; c++){
		   	if(userBoard[r][c] == '#'){
			   	if(board[r][c] != '*'){
				   	return;
				}
			}
		}
	}
	cout<<"YOU WIN!"<<endl;
	gameOver = 0;
}
/**************************************************************************
** Function: openCell 
** Description: opens the cell the user wants to open
** Parameters: rows, cols, mines, gameOver, userBoard, and board
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/ 
void openCell(int rows, int cols, int mines, int & gameOver, char** userBoard, char** board){
	int r, c, e = 1;
	while(e == 1){
   		cout<<"row, column: ";
		cin>>r>>c;
		if(cin.fail()){
		   	cin.clear();
			cin.ignore();
	   		cout<<"Invalid Input"<<endl;
			continue;
		}
		else if(r<0 || r>rows-1 || c<0 || c>cols-1){
	   		cout<<"That is not on the board. Try again."<<endl;
			continue;
		}	
		else{
		   	if(userBoard[r][c] != '#' && userBoard[r][c] != '!'){
			   	cout<<"You already opened that cell."<<endl;
   		   		continue;
			}
			else if(board[r][c]=='*'){
			   	cout<<"YOU LOSE!"<<endl;
				printBoard(rows, cols, board);
				gameOver = 0;
				e = 0;
			}
			else{
				userBoard[r][c] = board[r][c];
				printBoard(rows, cols, userBoard);
			   	win(rows, cols, mines, gameOver, userBoard, board);
				e = 0;
			}
		}
	}
}
/**************************************************************************
** Function: play
** Description: Asks if the user would like to open or flag a cell
** Parameters: rows, cols, mines, gameOver, userBoard, board
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/  
void play(int rows, int cols, int mines, int & gameOver, char** userBoard, char** board){
   	int e=1, choice;
	while(e == 1 && gameOver == 1){
   		cout<<"Would you like to flag(1) or open(2) a cell?"<<endl;
		cin>>choice;
		if(cin.fail()){
   			cin.clear();
     			cin.ignore();
			cout<<"Invalid Input"<<endl;
			continue;
		}
		else if(choice != 1 && choice != 2){
   			cout<<"Invalid Input, not 1 or 2"<<endl;
     			continue;
		}
		else if(choice==1){
		   	flagCell(rows, cols, userBoard);
		}
		else if(choice==2){
		   	openCell(rows, cols, mines, gameOver, userBoard, board);
		}
	}
}
/**************************************************************************
** Function: deleteArrays
** Description: frees the memory on the heap of the two arrays so the user can play again
** Parameters: rows, cols, mines, userBoard, board
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/ 
void deleteArrays(int rows, int cols, int mines, char** userBoard, char** board){
	for(int r=0; r<rows; r++){
	   	delete [] board[r];
		delete [] userBoard[r];
	}
	delete [] board;
	delete [] userBoard;
}
/**************************************************************************
** Function: restartGame
** Description: gets user input for rows, cols, and mines
** Parameters: rows, cols, and mines
** Pre-Conditions: none
** Post-Conditions: none
**************************************************************************/ 
void restartGame(int & rows, int & cols, int & mines){
   	int e = 1;
   	while(e == 1){
   		cout<<"How many rows would you like?"<<endl;
		cin>>rows;
		if(cin.fail()){
   			cin.clear();
     			cin.ignore();
			cout<<"Invalid Input"<<endl;
			continue;
		}
		else if(rows<0){
	   		cout<<"Cannot be negative"<<endl;
			continue;
		}
		cout<<"How many columns would you like?"<<endl;
		cin>>cols;
		if(cin.fail()){
   			cin.clear();
     			cin.ignore();
			cout<<"Invalid Input"<<endl;
			continue;
		}
		else if(cols<0){
	   		cout<<"Cannot be negative"<<endl;
			continue;
		}
		cout<<"How many mines would you like?"<<endl;
		cin>>mines;
		if(cin.fail()){
   			cin.clear();
     			cin.ignore();
			cout<<"Invalid Input"<<endl;
			continue;
		}
		else if(mines<0 || mines>(rows*cols)){
	   		cout<<"Mines cannot be smaller than zero or bigger than rows x columns"<<endl;
			continue;
		}
		e = 0;
	}
}
int main(int argc, char *argv[]){
   	int e = 1, gameOver = 1, cols = -1, rows = -1, mines = -1, userChoice;
  	if(argc != 7){
	   	cout<<"invalid input"<<endl;
		exit(1);
	}
	for(int i=1; i<argc; i+=2){
	   	if(strcmp(argv[i],"-r")==0 && rows==-1){
		   	if(isPositiveInt(argv[i+1])){
		   		rows=atoi(argv[i+1]);
			}
			else{
				cout<<"invalid input"<<endl;
				exit(1);
			}
		}
		else if(strcmp(argv[i],"-c")==0 && cols==-1){
   			if(isPositiveInt(argv[i+1])){
		   		cols=atoi(argv[i+1]);
			}
			else{
				cout<<"invalid input"<<endl;
				exit(1);
			}
		}
		else if(strcmp(argv[i],"-m")==0 && mines==-1){
			if(isPositiveInt(argv[i+1])){
		   		mines=atoi(argv[i+1]);
			}
			else{
				cout<<"invalid input"<<endl;
				exit(1);
			}
		}
	}
	if(rows==-1 || cols==-1 || mines== -1 || mines > (rows*cols)){
		cout<<"invalid input"<<endl;
		exit(1);
	}
	while(e == 1){
		char** board = makeBoard(rows, cols, mines);
		mineBoard(rows, cols, mines, board);
		numberBoard(rows, cols, mines, board);
		char** userBoard = makeUserBoard(rows, cols, mines);
		printBoard(rows, cols, userBoard);
		play(rows, cols, mines, gameOver, userBoard, board);
		deleteArrays(rows, cols, mines, userBoard, board);
		cout<<"Would you like to play again? Yes(1), No(2)"<<endl;
		cin>>userChoice;
		if(cin.fail()){
   			cin.clear();
     			cin.ignore();
			cout<<"Invalid Input"<<endl;
			exit(1);
		}
		else if(userChoice != 1 && userChoice != 2){
   			cout<<"Invalid Input, not 1 or 2"<<endl;
     			exit(1);
		}
		else if(userChoice == 1){
		   	restartGame(rows, cols, mines);
			gameOver = 1;
		}
		else if(userChoice == 2){
		   	exit(0);
		}
	}
	
	return 0;
}
