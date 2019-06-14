/*******************************************************************************
** Program Filename: Assignment2
** Author: Mary Jacobsen
** Date: 1-17-16
** Description: Financial Calculator
** Input: The user inputs financial data 
** Output: Calculates loan balance, continuous compounded interest, or future value
*******************************************************************************/


#include <iostream>

#include <cmath>

using namespace std;


/********************************************************************************* Function: Loan Balance
** Description: Calculates loan balance
** Parameters: 
** Pre-Conditions:
** Post-Conditions:
*******************************************************************************/

float loan_balance() {
	float A, i, n, P, glb;
	cout << "Enter in the initial investment";
	cin >> A;

	cout << "Enter your interest rate per period as a decimal";
	cin >> i;

	cout << "Enter the number of time periods";
	cin >> n;

	cout << "Enter the amount of each equal payment";
	cin >> P;
	
	cout<< "Enter a goal loan balance in dollars by the provided time";
	cin>> glb;

	float balance;
	balance = i+1;
	balance = pow(balance, n);
	balance = balance * A;
	float b;
	b = 1+i;
	b = pow(b, n);
	b = b-1;
	float l;
	l = P/i;
	b = b*l;
	balance = balance-b;

	cout<< "Your goal amount was "<< glb<<endl;
	cout<< "The actual amount after "<<n<<" time periods is "<<balance<<endl;
	if (glb >= balance)
		cout<< "You will meet your goal"<<endl;
	else
		cout<< "You will not meet your goal"<<endl;
}


/*******************************************************************************
** Function: Continuously Compounded Interest
** Description: Calculates continuously compounded interest
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*******************************************************************************/

float continuously_compounded_interest() {
	float P, r, t, cci, gcci;
	cout << "Enter in the initial investment";
	cin >> P;
	cout << "Enter in your annual interest rate as a decimal";
	cin >> r;
	cout << "Enter in the amount of years";
	cin >> t;
	cout << "Enter your goal amount in dollers by the provided time"<<endl;
	cin >> gcci;
	
	cci = r*t;
	cci = pow((M_E), cci);
	cci = P*cci;
	
	cout<< "Your goal amount after "<<t<<" years was "<<gcci<<endl;
	cout<< "Your actual amount after "<<t<<" years was "<<cci<<endl;
	
	if (gcci >= cci)
		cout<< "You will not meet your goal"<<endl;

	else
		cout<< "You will meet your goal"<<endl;
}


/********************************************************************************* Function: Future Value
** Description: Calculates future value
** Parameters:
** Pre-Conditions:
** Post Conditions:
*******************************************************************************/

float future_value() {
	float C0, r, n, gfv, fv;
	cout << "Enter in your starting cash flow";
	cin >> C0;
	cout << "Enter in your rate of return as a decimal";
	cin >> r;
	cout << "Enter in the number of time periods";
	cin >> n;
	cout << "Enter in your goal amount by the provided time";
	cin >> gfv;

	fv = 1+r;
	fv = pow(fv, n);
	fv = C0*fv;
	
	cout<< "Your goal amount after "<<n<<" time periods was "<<gfv<<endl;
	cout<< "Your actual amount after "<<n<<" time periods was "<<fv<<endl;
	
	if (gfv >= fv)
		cout<< "You will not meet your goal"<<endl;
	else
		cout<< "You will meet your goal"<<endl;
}


int main() {
	int choice;
	cout << "Welcome to the financial calculater."<<endl;
	cout<< "What would you like to calculate?"<<endl;
	cout<< "Loan Balance(1)"<<endl;
	cout<< "Continuously Compounded Interest(2)"<<endl;
	cout<< "Future Value(3)"<<endl;
	cin>> choice;

	if (choice == 1){
		cout<< "You have chosen to calculate loan balance"<<endl;  
		loan_balance();
		}	
	else if (choice == 2){
		cout<< "You have chosen to calculate continuously compounded interest"<<endl;
		continuously_compounded_interest();
		}	
	else if (choice == 3){
		cout<< "You have chosen to calculate future value"<<endl;
		future_value();
		}
	else
		cout<< "Not a valid input"<<endl;

		return 0;
}
