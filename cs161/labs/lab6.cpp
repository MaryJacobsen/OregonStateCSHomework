#include <iostream>
#include <string>
using namespace std;

string getSentence(){
   	string str;
	getline(cin,str);
	return str;

bool determinePalindrome(){
   	for(int i=0; i<str.length(); i++){
	   	if(str.at(i) != str.length-(i-1)
			return false;
		}
		return true;
	}

string getSearchString(){
	cout<<"What would you like to search? ";
	string s=getSentence();
	return s;
}

string getReplaceString(){
	cout<<"What would you like to replace it with? ";
	string r=getSentence();
	return r;

int searchReplace(string& str){
	int place;
	place=str.find(getSearchString(););
	str.replace(place, str.length(), getReplaceString(););
	cout<<str<<endl;

int main(){
	int choice, h;
	while(h=1){
		string str=getSentence();
		cout<<"Would you like to determine if palindrome(1), replace string(2), enter a new string(3), or quit(4)? ";    
		cin>>choice;
			if(choice==1){
				bool p=determinePalindrome();
			if(p==true){
		   		cout<<"That is a palindrome."<<endl;
			else
		   		cout<<"That is not a palindrome"<<endl;
			}
			}
			else if(choice==2)
	   			searchReplace(str);
			else if(choice==3)
	   			continue;
			else
	   			break;
	}	
return 0;
}		
