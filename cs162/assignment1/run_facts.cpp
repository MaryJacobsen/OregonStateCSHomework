/**************************************************************************
** Program: run_facts.cpp
** Author: Mary Jacobsen
** Date: 04/14/2016
** Description: This is the driver
** Input: .h file and the file with all the state facts
** Output: Organizes the state facts
**************************************************************************/

#include "state_facts.h"

using namespace std;

int main(int argc, char *argv[]){
   	int numstates, e = 1, choice;
   	int * ns; 
	ns = &numstates;
	string filename;
	string * f; 
	f = &filename;
   	if(is_valid_arguments(argv, argc) == false){
	   	start_over(ns, f);
	}
	else{
		set_vars(argv, argc, ns, f);
	}
       	while(e == 1){	   
		ifstream input;
		input.open(filename.c_str());
		if(input.fail()){
	   		cout<<"Not a valid file"<<endl;
			start_over(ns, f);
			continue;
		}
		state *s;
		s = create_states(numstates);
		get_state_data(s, numstates, input);
		order_state_population(numstates, s);
		order_county_population(numstates, s);
		avg_house_cost(numstates, s);
		alpha_states(numstates, s);
		alpha_counties(numstates, s);
		income_above_amount(numstates, s);
		delete_info(s, numstates);
		cout<<"Would you like to know about anymore states? Yes(1), No(0)"<<endl;
		cin>>choice;
		if(cin.fail()){
			e = 0;
		}
		else if(choice < 1 || choice > 1){
		   	e = 0;
		}
		else{
		   	start_over(ns, f);
		}
	}
	return 0;
}
