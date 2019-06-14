/***************************************************************************
** Program: assignment4.cpp
** Author: Mary Jacobsen
** Date:02/17/2016
** Description: Wheel of Fortune game for 1 to 3 players
** Input: messages, letter guesses, how many players and rounds
** Output: Wheel of Fortune game
***************************************************************************/

#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale>
#include <cstdlib>
#include <ctype.h>

using namespace std;

/***************************************************************************
** Function: void gameSetUp
** Description: Obtains user input for how many players and rounds and sets them equal to numP and numR
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void gameSetUp(int& numP, int&numR){
   	bool e=true;
   	while(e==true){
   		cout<<"How many players(1-3)? ";
		cin>>numP;
		cin.ignore();

		if(cin.fail()){
		   	cin.clear();
			cin.ignore();
			cout<<"Invalid input"<<endl;
			continue;}
	
		else if(numP<1 || numP>3){
		   	cout<<"Invalid input, not 1-3"<<endl;
			continue;}
	
		cout<<"How many rounds would you like to play? ";
		cin>>numR;
		cin.ignore();
		if(cin.fail()){
			cin.clear();
			cin.ignore();
			cout<<"Invalid input"<<endl;
			continue;}
		e=false;
	}
}
/**************************************************************************
** Funcion: void message
** Description: Obtains the message from the user and stores it in msg
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void message(string& msg){
   	int e=0;
	while(e==0){
   		cout<<"Enter a message."<<endl;
		getline(cin,msg);
		for(int j=0;j<msg.length();j++){
		   	if(!(isalpha(msg[j]))){
	   			cout<<"Only use letters and spaces"<<endl;
				cout<<"Enter a message"<<endl;
				getline(cin,msg);
				continue;}}
		for(int i=0; i<msg.length(); i++){
	   		msg[i]=tolower(msg[i]);}
		system("clear");
		e=1;
	}	
}
/***************************************************************************** Function: void hiddenMessage
** Description: Displays the hidden message
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void hiddenMessage(string& msg, string& hidden){
	hidden=msg;
	for(int i=0; i<msg.size(); i++){
		if(msg[i]==' ')
		   	hidden[i]=' ';
		else
		   	hidden[i]='-';
	}
	cout<<hidden<<endl;
}
/***************************************************************************** Function: void revealCLetters
** Description: Reveals the consonant letters that were guessed
** Parameters: none 
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void revealCLetters(int& money, int& winner, string& msg, string& hidden, int& spin, char& cguess, int& e){

	int correct=0;
	for(int i=0; i<msg.size(); i++){
   		if(msg[i]==cguess)
	      		hidden[i]=cguess;}
		
	for(int j=0; j<msg.size(); j++){
		if(msg[j]==cguess)
   			correct++;}

	money = money+(correct*spin);
	cout<<"You found "<<correct<<" letter(s)"<<endl;
	cout<<hidden<<endl;
	cout<<"You now have $"<<money<<endl;
	if(correct==0)
	   	e=1;
	else if(hidden==msg){
	   	cout<<"You have completed the puzzle!"<<endl;
		e=1;
	   	winner=1;}
}
/***************************************************************************** Function: void revealVLetters
** Description: Reveals the vowels that were guessed
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void revealVLetters(int& winner, string& msg, string&  hidden, char& vguess, int& e){
   	int correct=0;
	for(int i=0; i<msg.size(); i++){
   		if(msg[i]==vguess)
	      		hidden[i]=vguess;
	}

	for(int j=0; j<msg.size(); j++){
		if(msg[j]==vguess)
   			correct++;}

	cout<<"You found "<<correct<<" letter(s)"<<endl;
	cout<<hidden<<endl;
	if(correct==0)
	   	e=1;

	else if(hidden==msg){
	   	cout<<"You completed the puzzle!"<<endl;
		e=1;
		winner=1;}

}
/***************************************************************************** Function: void guessConsonant
** Description: Takes in the consonant they guess
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void guessConsonant(int& money, int& winner, string& msg, string& hidden, int& spin, char& cguess, int& e){
   	
	int g=0;
	while(g==0){
		cout<<"What consonant letter would you like to guess? ";
		cin>>cguess;
		cin.ignore();
		if(cin.fail()){
			cin.clear();
			cin.ignore();
			cout<<"Invalid input"<<endl;
			continue;}
		else if(cguess=='e'||cguess=='u'||cguess=='i'||cguess=='o'||cguess=='a'){
	   		cout<<"Not a consonant"<<endl;
	   		continue;}
		else if(!(isalpha(cguess))){
		   	cout<<"Not a letter"<<endl;
			continue;}
		else{
		   	cguess=tolower(cguess);
			revealCLetters(money, winner, msg, hidden, spin, cguess, e);}
	g=1;
	}
}
/***************************************************************************** Function: void spinWheel
** Description: A random number generater gives them their spin 0-21
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void spinWheel(int& money, int& winner, string& msg, string& hidden, int& spin, char& cguess, int& e){   
	srand(time(NULL));
	spin=rand()%22;
	cout<<"You spun "<<spin<<endl;
	if(spin==0){
	   	money=0;
		cout<<"Bankrupt! You have $"<<money<<endl;
		e=1;}
	else if(spin==21){
	   	cout<<"You lose your turn!"<<endl;
		e=1;}
	else
		guessConsonant(money, winner, msg, hidden, spin, cguess, e);
}
/***************************************************************************** Function: void buyVowel
** Description: Subtracts 10 from their money and takes in their vowel guess
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void buyVowel(int& money, int& winner, string& msg, string& hidden, char& vguess, int& e){
	money=money-10;
	cout<<"You now have $"<<money<<endl;
	int g=0;
	while(g==0){
   		cout<<"What vowel would you like to guess? ";
		cin>>vguess;
		cin.ignore();
		if(cin.fail()){
			cin.clear();
			cin.ignore();
			cout<<"Invalid input"<<endl;
			continue;}
		else if(!(isalpha(vguess))){
		   	cout<<"Not a letter"<<endl;
			continue;}
		vguess=tolower(vguess);
		if(!(vguess=='e'||vguess=='u'||vguess=='i'||vguess=='o'||vguess=='a')){
	   		cout<<"Not a vowel"<<endl;
	   		continue;}
		else{
		   	vguess=tolower(vguess);
	   		revealVLetters(winner, msg, hidden, vguess, e);}
		g=1;
	}
}
/***************************************************************************** Function: void solvePuzzle
** Description: Takes in their puzzle solution and checks if it is correct
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void solvePuzzle(int& money, int& winner, string& msg, string& hidden, int& e){
	string solution;
	int g=0;
	while(g==0){
   		cout<<"Enter your solution"<<endl;
		getline(cin, solution);
		for(int j=0;j<solution.length();j++){
		   	if(!(isalpha(solution[j]))){
	   			cout<<"Only use letters and spaces"<<endl;
				cout<<"Enter your solution"<<endl;
				getline(cin, solution);
				continue;}}
		for(int i=0; i<solution.length(); i++){
	   		solution[i]=tolower(solution[i]);}
		system("clear");
		g=1;
	}	

	if(solution == msg){
	   	cout<<"That is correct!"<<endl;
		hidden=msg;
		winner=1;
		e=1;}
	
	else{
	   	cout<<"Sorry, that is incorrect."<<endl;
		e=1;}
}
/***************************************************************************** Function: void playTurn
** Description: Takes in what they want to do in their turn
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void playTurn(int& money, int& winner, string& msg, string& hidden, int& spin, char& cguess, char& vguess, int& e){
	int choice; 
	e=0;
	while(e==0){
		cout<<"Would you like to  spin the wheel(1), buy a vowel if you have at least $10(2), or solve the puzzle(3)?"<<endl;
		cin>>choice;
		cin.ignore();
		if(cin.fail()){
		   	cin.clear();
			cin.ignore();
			cout<<"Invalid input"<<endl;
			continue;}
		else if(choice<1 || choice>3){
		   	cout<<"Invalid input, not 1-3"<<endl;
			continue;}
		else if(choice==1)
   			spinWheel(money, winner, msg, hidden, spin, cguess, e);
		else if(choice==2){
	   		if(money<10)
		   		cout<<"You do not have at least $10."<<endl;
			else
   				buyVowel(money, winner, msg, hidden, vguess, e);}	
		else if(choice==3)
   			solvePuzzle(money, winner, msg, hidden, e);
		
	}
}

/***************************************************************************** Function: void round
** Description: Keeps track of whose turn it is
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void round(string& msg, string& hidden, int& numP, int& numR, int& p1, int& p2, int& p3, int& w1, int& w2, int& w3, int& activeP, int& spin, char& cguess, char& vguess, int& e){

	activeP=1;

	while(msg!=hidden){

	   	if(activeP==1){
		   	cout<<"Player 1's Turn"<<endl;
			playTurn(p1, w1, msg, hidden, spin, cguess, vguess, e);}
		else if(activeP==2){
		   	cout<<"Player 2's Turn"<<endl;
		   	playTurn(p2, w2, msg, hidden, spin, cguess, vguess, e);}
		else{
		   	cout<<"player 3's Turn"<<endl;
		   	playTurn(p3, w3, msg, hidden, spin, cguess, vguess, e);}
		
		if(activeP<numP)
		   	activeP++;
		else
		   	activeP=1;
	}       	
}
/***************************************************************************** Function: void roundStats
** Description: Prints out everyone's total money at the end of a round
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void roundStats(int& p1, int& p2, int& p3, int& w1, int& w2, int& w3, int& totalP1, int& totalP2, int& totalP3, int& numP){
   	if(w1==1){
	   	totalP1=totalP1+p1;
		totalP2=totalP2+0;
		totalP3=totalP3+0;}
	else if(w2==1){
	   	totalP1=totalP1+0;
		totalP2=totalP2+p2;
		totalP3=totalP3+0;}
	else{
	   	totalP1=totalP1+0;
		totalP2=totalP2+0;
		totalP3=totalP3+p3;}
	if(numP==1)
   		cout<<"Player 1 has $"<<totalP1<<endl;
	else if(numP==2){
   		cout<<"Player 1 has $"<<totalP1<<endl;
     		cout<<"Player 2 has $"<<totalP2<<endl;}
	else{	
		cout<<"Player 1 has $"<<totalP1<<endl;
		cout<<"Player 2 has $"<<totalP2<<endl;
		cout<<"Player 3 has $"<<totalP3<<endl;}

}
/***************************************************************************** Function: void endGame
** Description: Determines and prints out who wins
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void endGame(int& totalP1, int& totalP2, int& totalP3, int& numP){
	if(totalP1>(totalP2&&totalP3))
	   	cout<<"Player 1 wins!"<<endl;
	else if(totalP2>(totalP1&&totalP3))
	   	cout<<"Player 2 wins!"<<endl;
	else if(totalP3>(totalP1&&totalP2))
	   	cout<<"Player 3 wins!"<<endl;
	else
	   	cout<<"It's a tie!"<<endl;
	if(numP==1)
	   	cout<<"Player 1's total is $"<<totalP1<<endl;
	else if(numP==2){
	   	cout<<"Player 1's total is $"<<totalP1<<endl;
		cout<<"Player 2's total is $"<<totalP2<<endl;}
	else{
	cout<<"Player 1's total is $"<<totalP1<<endl;
	cout<<"Player 2's total is $"<<totalP2<<endl;
	cout<<"Player 3's total is $"<<totalP3<<endl;}
}

int main(){
	string msg, hidden;
	int numP, numR, totalP1=0, totalP2=0, totalP3=0, activeP=1, p1, p2, p3, spin, w1=0, w2=0, w3=0, e;
	char cguess, vguess;
	
	gameSetUp(numP, numR);
	
	for(int i=0; i<numR; i++){
	   	p1=0, p2=0, p3=0;
		
		message(msg);
		
		hiddenMessage(msg, hidden);
		
		round(msg, hidden, numP, numR, p1, p2, p3, w1, w2, w3, activeP, spin, cguess, vguess, e);
		
		roundStats(p1, p2, p3, w1, w2, w3, totalP1, totalP2, totalP3, numP);
	}

	endGame(totalP1, totalP2, totalP3, numP);

	return 0;
}
