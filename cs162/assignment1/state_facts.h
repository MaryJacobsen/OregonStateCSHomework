/**************************************************************************
** Program: state_facts.h
** Author: Mary Jacobsen
** Date: 04/14/2016
** Description: This has all the includes, structs, and function prototypes
** Input: .h file and the file with all the state facts
** Output: Organizes the state facts
**************************************************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>

struct county{
   	std::string name; //name of county
	std::string *city; //name of cities in county
	int cities; //number of cities
	int population; //total population of county
	float avg_income; //avg household income
	float avg_house; //avg household price
};

struct state{
   	std::string name; //name of state
	struct county *c; //name of counties
	int counties; //number of counties in state
	int population; //total population of state
};

bool is_valid_arguments(char *[], int);
state * create_states(int);
void get_state_data(state *, int, std::ifstream &);
county * create_counties(int);
void get_county_data(county *, int, std::ifstream &);
void delete_info(state *, int);
void alpha_states(int, state *);
void alpha_counties(int, state *);
void order_state_population(int, state *);
void order_county_population(int, state *);
void avg_house_cost(int, state *);
void income_above_amount(int, state *);
void start_over(int *, std::string *);
void set_vars(char *[], int, int *, std::string *);


