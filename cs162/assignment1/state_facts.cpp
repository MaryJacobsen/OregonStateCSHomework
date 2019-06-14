/**************************************************************************
** Program: state_facts.cpp
** Author: Mary Jacobsen
** Date: 04/14/2016
** Description: This has all the function definitions
** Input: .h file and the file with all the state facts
** Output: Organizes the state facts
**************************************************************************/
#include "state_facts.h"

using namespace std;

/*************************************************************************
** Function: delete_info
** Description: deletes the memory alocated on the heap for the arrays
** Parameters: pointer to state array, number of states
** Pre-Conditions: This function gets called after the facts have been organized
** Post-Conditions: none
*************************************************************************/
void delete_info(state *s, int numstates){
   	for(int i=0; i<numstates; i++){
		for(int h=0; h<s[i].counties; h++){
   			delete [] s[i].c[h].city;
			
		}
	}
	for(int j=0; j<numstates; j++){
	   	delete [] s[j].c;
	}
	delete [] s;	
}

county * create_counties(int num){
   	return new county[num];
}
/*************************************************************************
** Function: get_county_data
** Description: fills the county structs using the file inputted by the user
** Parameters: pointer to the county array, number of counties, and ifstream& input
** Pre-Conditions: must have valid file
** Post-Conditions: filled county structs
*************************************************************************/
void get_county_data(county *c, int numcounties, ifstream& input){
	for(int k=0; k<numcounties; k++){
	   	input>>c[k].name;
		input>>c[k].population;
		input>>c[k].avg_income;
		input>>c[k].avg_house;
		input>>c[k].cities;
		c[k].city = new string [c[k].cities];
		for(int m=0; m<c[k].cities; m++){
			input>>c[k].city[m];
			
		}
	}
}
/*************************************************************************
** Function: get_state_data
** Description: fills the state structs using the file inputted by the user
** Parameters: pointer to the state array
** Pre-Conditions: must have valid file and non-zero, postitive numstates
** Post-Conditions: filled state structs
*************************************************************************/
void get_state_data(state *s, int numstates, ifstream& input){
	for(int i=0; i<numstates; i++){
		input>>s[i].name;
		input>>s[i].population;
		input>>s[i].counties;
		s[i].c = create_counties(s[i].counties);
	        get_county_data(s[i].c, s[i].counties, input);
	}
}
/*************************************************************************
** Function: create_states
** Description: creates the state array
** Parameters: number of states
** Pre-Conditions: non-zero, positive int for numstates
** Post-Conditions: none
*************************************************************************/
state *create_states(int numstates){
	return new state[numstates];
}
/*************************************************************************
** Function: is_positive_int
** Description: checks to see if what is passed in is a positive, non-zero int
** Parameters: pointer to a char
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
bool is_positive_int(char *num){
   	if(strcmp(num,"0") == 0){
	   	cout<<"The number of states should not be 0"<<endl;
		return false;
	}
   	for(int i=0; num[i] != '\0'; i++){
	   	if(num[i] == '-' || num[i]<48 || num[i]>57){
		   	cout<<"The number of states must be a positive, non-zero integer"<<endl;
		   	return false;
		}
	}
	return true;
}
/*************************************************************************
** Function: is_valid_arguments
** Description: checks if the command line arguments are valid
** Parameters: the command line arguments
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
bool is_valid_arguments(char *argv[], int argc){
   	if(argc != 5){
	   	cout<<"Please supply exactly four arguments."<<endl;
	   	exit(1);
	}
	int ns = -1;
	string file = "nofile";
	for(int i=1; i<argc; i+=2){
	   	if(strcmp(argv[i],"-s")==0 && ns == -1){
		   	if(is_positive_int(argv[i+1]) == false){
			   	return false;
			}
			else{
			   	ns = 1;
			}
		}
		else if(strcmp(argv[i],"-f")==0 && file == "nofile"){ 
		   	file = "good";
		}
	}
	if(ns == -1 || file == "nofile"){
 		cout<<"Please supply the number of states(-s) and the file name(-f)."<<endl;
		exit(1);
	}
	return true;
}
/*************************************************************************
** Function: set_vars
** Description: sets numstates and the filename
** Parameters: command line arguments, pointer to numstates, and pointer to filename
** Pre-Conditions: command line arguments are valid
** Post-Conditions: none
*************************************************************************/
void set_vars(char *argv[], int argc, int * ns, string * f){
   	for(int i=1; i<argc; i+=2){
	   	if(strcmp(argv[i],"-s")==0){
			*ns = atoi(argv[i+1]);
		}
		else if(strcmp(argv[i],"-f")==0){
		   	*f = argv[i+1];
		}
	}
}
/*************************************************************************
** Function: alpha_counties
** Description: puts the counties in order by name according to state
** Parameters: numstates and pointer to array of states
** Pre-Conditions: none 
** Post-Conditions: none
*************************************************************************/
void alpha_counties(int numstates, state *s){
   	county temp;
	for(int j=0; j<numstates; j++){
	   	for(int k=0; k<s[j].counties; k++){
		   	for(int m=0; m<s[j].counties-1; m++){
		   		if(s[j].c[m].name > s[j].c[m+1].name){
					temp = s[j].c[m];
					s[j].c[m] = s[j].c[m+1];
					s[j].c[m+1] = temp;
				}
			}
		}
	}
	cout<<"The counties in order by name according to state:"<<endl;
	for(int j=0; j<numstates; j++){
	   	cout << s[j].name << endl;
	   	for(int k=0; k<s[j].counties; k++){
		   	cout<< s[j].c[k].name <<" "<< endl;
		}
		cout << endl;
	}
}
/*************************************************************************
** Function: alpha_states
** Description: puts the states in order by name
** Parameters: numstates and pointer to array of states
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
void alpha_states(int numstates, state *s){
   	state temp;
   	for(int i=0; i<numstates; i++){
	   	for(int m=0; m<numstates-1; m++){
	   		if(s[m].name > s[m+1].name){
		   		temp = s[m];
				s[m] = s[m+1];
				s[m+1] = temp;
			}
		}
	}
	cout<<"The states in order by name:"<<endl;
	for(int i=0; i<numstates; i++){
	   	cout<< s[i].name <<" ";
	}
	cout<<endl;
}
/*************************************************************************
** Function: avg_house_cost
** Description: finds the average house cost of the counties
** Parameters: numstates and array of states
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/	   	
void avg_house_cost(int numstates, state *s){
   	float sum=0;
   	for(int j=0; j<numstates; j++){
	   	for(int k=0; k<s[j].counties; k++){
			sum = sum + s[j].c[k].avg_house;
		}
		cout<<"The average household cost for all the counties in "<< s[j].name <<" is "<< (sum/s[j].counties) << endl;
		sum = 0;
	}
}
/*************************************************************************
** Function: order_county_population
** Description: puts the counties in order by population according to state
** Parameters: numstates and array of states
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
void order_county_population(int numstates, state *s){
   	county temp;
	for(int j=0; j<numstates; j++){
	   	for(int k=0; k<s[j].counties; k++){
		   	for(int m=0; m<s[j].counties-1; m++){
		   		if(s[j].c[m].population > s[j].c[m+1].population){
			   		temp = s[j].c[m];
					s[j].c[m] = s[j].c[m+1];
					s[j].c[m+1] = temp;
				}
			}
		}
	}
	cout<<"The counties in order by population according to state:"<<endl;
	for(int j=0; j<numstates; j++){
	   	cout << s[j].name << endl;
	   	for(int k=0; k<s[j].counties; k++){
			cout << s[j].c[k].name <<" : "<< s[j].c[k].population << endl;
		}
		cout <<"The county with the largest population is "<< s[j].c[s[j].counties-1].name <<" with "<< s[j].c[s[j].counties-1].population << endl;
	}
}
/*************************************************************************
** Function: order_state_population
** Description: puts the states in order by population
** Parameters: numstates and array of states
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
void order_state_population(int numstates, state *s){
   	state temp;
   	for(int i=0; i<numstates; i++){
		for(int m=0; m<numstates-1; m++){
	   		if(s[m].population > s[m+1].population){
		   		temp = s[m];
				s[m] = s[m+1];
				s[m+1] = temp;
			}
		}
	}
	cout<<"The states in order by population:"<<endl;
	for(int j=0; j<numstates; j++){
	   	cout<< s[j].name <<" : "<< s[j].population << endl;
	}
	cout<<"The state with the largest population is "<< s[numstates-1].name <<" with "<< s[numstates-1].population << endl;
}
/*************************************************************************
** Function: income_above_amount
** Description: checks which counties have average incomes above a user inputted amount
** Parameters: numstates and array of states
** Pre-Conditions: none 
** Post-Conditions: none
*************************************************************************/
void income_above_amount(int numstates, state *s){
   	int amount, e = 0;
	while(e == 0){
   		cout<<"Enter the income you would like to check which counties are above."<<endl;
		cin>>amount;
		if(cin.fail()){
		   	cin.clear();
			cin.ignore();
			cout<<"Invalid Input Please try again."<<endl;
			continue;
		}
		cout<<"The counties that have average incomes above the amount specified are: ";
		for(int j=0; j<numstates; j++){
	   		for(int k=0; k<s[j].counties; k++){
		   		if(s[j].c[k].avg_income > amount){
			   		cout<<s[j].c[k].name<<" ";
				}
			}
		}
		cout<<endl;
		e = 1;
	}
}
/*************************************************************************
** Function: start_over
** Description: gets the number pf states and the filename from the user
** Parameters: pointers to numstates and filename
** Pre-Conditions: none
** Post-Conditions: none
*************************************************************************/
void start_over(int *ns, string *f){
   	int e = 0;
	while(e == 0){
   		cout<<"Please enter how many states you would like."<<endl;
		cin>>*ns;
		if(cin.fail()){
		   	cin.clear();
			cin.ignore();
	   		cout<<"Please enter a positive, non-zero integer."<<endl;
			continue;
		}
		if(*ns<1){
		   	cout<<"Please enter a positive, non-zero integer."<<endl;
			continue;
		}
		else{
	   		cout<<"Please enter the file."<<endl;
			cin>>*f;
			e = 1;
		}
	}
}


