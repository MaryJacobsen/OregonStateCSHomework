/**************************************************************************
** Program Filename: Assignment5
** Author: Mary Jacobsen
** Date: 02-28-16
** Description: Translates English to Morse Code or Morse Code to English depending on the user's choice
** Input: A c-string in English or a c-string in Morse Code
** Output: Translation to Morse or English
***************************************************************************/

#include <iostream>
#include <ctype.h>
#include <cstdlib>

using namespace std;

/***************************************************************************
** Function: Morse_Eng
** Description: Translates the user input from Morse to English
** Parameters: User input Morse c-string, 2D array of Morse, alpha c-string, number of dots and dashes, number of spaces, and int i
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void Morse_Eng(char * input, char Engmorse[28][7], char alpha[], int numd, int nums, int i, int length){
   	int j;
		if(nums==7){
		   	cout<<" ";}

		else{
	   		for(int k=0;k<28; k++){
	   			for(j=0; j<numd; j++){
			   		if(input[j+i]!=Engmorse[k][j]){
				   		break;}   	
				}
					if(j==numd && Engmorse[k][j]=='\0'){
				     		cout<<alpha[k];
						break;}
			}
		}
}		

/***************************************************************************
** Function: get_Morse
** Description: Gets the c-string of Morse from the user and calls the translation function
** Parameters: User inputted c-string of Morse, 2D array with the Morse, alpha c-string, number of dots and dashes, number of spaces, and int i
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void get_Morse(char * input, char Engmorse[28][7], char alpha[], int numd, int nums, int i, int length){
	int e=0;
   	while(e==0){
		for(i=0; i<length;i++){
	   		if(input[i]=='-'||input[i]=='.'){
		   		numd++;
				nums=0;}
			else if(input[i]==' '){
		   		nums++;
				if(nums==3){
			   		Morse_Eng(input, Engmorse, alpha, numd, nums, i-(2+numd), length);
					numd=0;}
				else if(nums==7){
		   			Morse_Eng(input, Engmorse, alpha, numd, nums, i, length);}
			}	
			else if(input[i]!='-' && input[i]!='.' && input[i]!=' '){
		   		cout<<"invalid input"<<endl;
		   		continue;}
		}
		e=1;
	}	
		if(numd>0){
			Morse_Eng(input, Engmorse, alpha, numd, nums, i-numd, length);}
	cout<<endl;
}

/***************************************************************************
** Function: Eng_morse
** Description: Translates the user inputted English c-string to Morse Code
** Parameters: The c-string Eng and the 2D array that has the morse in it
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void Eng_morse(char *input, char Engmorse[28][7], int length){
   	char L;
   	for(int i=0; i<length; i++){
	   	if(input[i] == ' ')
		   	cout <<"    ";

		else if(input[i]=='.')
		   	cout<<".-.-.-   ";

		else if(input[i]==',')
		   	cout<<"--..--   ";

		else{
	   		L = input[i]  - 65;
			cout<<Engmorse[L];
			cout<<"   ";}
	}
}	

/***************************************************************************
** Function: get_Eng
** Description: Gets a c-string from the user in English
** Parameters: The c-string Eng
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

void get_Eng(char * input, int length){
   	int e=0;
	while(e==0){
	   	int error=0;
		for(int i=0; i<length; i++){
	   		if((!(input[i]>96 && input[i]<123)) && (!(input[i]>64 && input[i]<91)) && (input[i]!=32) && (input[i]!=44) && (input[i]!=46)){
		   		cout<<"Invalid input"<<endl;
				exit(0);}
		}	
		if(error==1){
	   		e=0;}
		else{
		   	e=1;}
	}
}

/***************************************************************************
** Function: resize 
** Description: takes one character at a time from the get_user_input function and grows length which grows temp
** Parameters: input c-string and length
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

char *resize(char input[], int &length){
   	char *temp = new char[++length];

	for(int i=0; i<length-1; i++){
	   	temp[i] = input[i];
	}
	if(input != NULL){
	   	delete [] input;
	}
	return temp;
}

/***************************************************************************
** Function: get_user_string 
** Description: this function takes in the user string character by character and then passes each character into a resize function 
** Parameters: input c-string and int length
** Pre-Conditions: none
** Post-Conditions: none
***************************************************************************/

char *get_user_string(char input[], int & length){
   	char c;
	cout << "Enter the phrase you would like to translate: ";
	while(true){
		cin.get(c);
		if(c == '\n'){
	   		break;
		}
		input = resize(input, length);
		input[length-1] = toupper(c);
	}
	input[length] = '\0';
	return input;
}

int main(){
   	int nums=0, numd=0, i=0, choice, length=0;
	char * input = NULL;
	char alpha[29]="ABCDEFGHIJKLMNOPQRSTUVWXYZ,.";
	char Engmorse[28][7] = {{'.','-','\0'},{'-','.','.','.','\0'},{'-','.','-','.','\0'},{'-','.','.','\0'},{'.','\0'},{'.','.','-','.','\0'},{'-','-','.','\0'},{'.','.','.','.','\0'},{'.','.','\0'},{'.','-','-','-','\0'},{'-','.','-','\0'},{'.','-','.','.','\0'},{'-','-','\0'},{'-','.','\0'},{'-','-','-','\0'},{'.','-','-','.','\0'},{'-','-','.','-','\0'},{'.','-','.','\0'},{'.','.','.','\0'},{'-','\0'},{'.','.','-','\0'},{'.','.','.','-','\0'},{'.','-','-','\0'},{'-','.','.','-','\0'},{'-','.','-','-','\0'},{'-','-','.','.','\0'},{'-','-','.','.','-','-','\0'},{'.','-','.','-','.','-','\0'}};
	int y=0;
	while(y==0){
		cout<<"Would you like to translate from English to Morse(1) or Morse to English(2)?"<<endl;
		cin>>choice;
		cin.ignore();
		if(cin.fail()){
   			cin.clear();
     			cin.ignore();
			cout<<"invalid input"<<endl;
			continue;}
		else if(choice!=1 && choice!=2){
   			cout<<"invalid input"<<endl;
			continue;}	
		else if (choice==1){
			input = get_user_string(input, length);
			get_Eng(input, length);
			Eng_morse(input, Engmorse, length);}


		else if(choice==2){
		   	input=get_user_string(input, length);
			get_Morse(input, Engmorse, alpha, numd, nums, i, length);}
		y=1;
	}	
		return 0;
}
