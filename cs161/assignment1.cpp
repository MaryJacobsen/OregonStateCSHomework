#include <iostream>
#include <cmath>
#include <climits>
#define PI 3.14159265
using namespace std;
int main(){
	float sol = cos((2*PI)/3);
	cout<< "cos((2*PI)/3) "<<sol<<endl;
	 sol = 2*sin((2*PI)/3);
	cout<< "2*sin((2*PI)/3)"<<sol<<endl;
	 sol = tan((-3*PI)/4);
	cout<< "tan((-3*PI)/4)"<<sol<<endl;
	 sol = log10(55);
	cout<< "log10(55)"<<sol<<endl;
	 sol = log(60);
	cout<< "log(60)"<<sol<<endl;
	sol = log(15);
	cout<< "log(15)"<<sol<<endl;
	sol = log(2);
	cout<< "log(2)"<<sol<<endl;
	sol = (log(15))/(log(2));
	cout<< "(log(15))/(log(2))"<<sol<<endl;
	sol = log(40);
	cout<< "log(40)"<<sol<<endl;
	sol = log(4);
	cout<< "log(4)"<<sol<<endl;
	sol = (log(40))/(log(4));
	cout<< "(log(40))/(log(4))"<<sol<<endl;
	sol = 3*sin(1);
	cout<< "3*sin(1)"<<sol<<endl;
	sol = 3*sin(10);
	cout<< "3*sin(10)"<<sol<<endl;
	sol = 3*sin(100);
	cout<< "3*sin(100)"<<sol<<endl;
	sol = log(1+1);
	cout<< "log(1+1)"<<sol<<endl;
	sol = log(2);
	cout<< "log(2)"<<sol<<endl;
	sol = (log(1+1))/(log(2));
	cout<< "(log(1+))/(log(2))"<<sol<<endl;
	sol = log(pow(10,2)+1);
	cout<< "log(pow(10,2)+1)"<<sol<<endl;
	sol = log(2);
	cout<< "log(2)"<<sol<<endl;
	sol = (log(pow(10,2)+1))/(log(2));
	cout<< "(log(pow(10,2)+1))/(log(2))"<<sol<<endl;
	sol = log(pow(100,2)+1);
	cout<< "log(pow(100,2)+1)"<<sol<<endl;
	sol = log(2);
	cout<< "log(2)"<<sol<<endl;
	sol = (log(pow(100,2)+1))/(log(2));
	cout<< "(log(pow(100,2)+1))/(log(2))"<<sol<<endl;
	cout<< SHRT_MIN<< endl;
	cout<< SHRT_MAX<< endl;
	cout<< USHRT_MAX<< endl;
	cout<< INT_MIN<< endl;
	cout<< INT_MAX<< endl;
	cout<< UINT_MAX<< endl;
	cout<< LONG_MIN<<endl;
	cout<< LONG_MAX<<endl;
	cout<< ULONG_MAX<<endl;
	int int_max = pow(2, sizeof(int)*8-1)-1;
	cout << "int max:"<< int_max <<endl;
	unsigned int uint_max = pow(2, sizeof(unsigned int)*8)-1;
	int int_min = pow(2, sizeof(int)*8-1);
	cout << "uint_max:"<< uint_max <<endl;
	cout << "int min:"<< int_min <<endl;
	long long_max =(long) pow(2, sizeof(long)*8-1)-1;
	cout << "long max:"<< long_max << endl;
	unsigned long ulong_max =(unsigned long) pow(2, sizeof(unsigned long)*8)-1;
	cout << "ulong max:"<< ulong_max << endl;
	long long_min =(long) pow(2, sizeof(long)*8-1);
	cout << "long min:"<< long_min << endl;
	short short_max = pow(2, sizeof(short)*8-1)-1;
	cout << "short max:"<< short_max << endl;
	short short_min = pow(2, sizeof(short)*8-1);
	cout << "short min:"<< short_min <<endl;
	unsigned short ushort_max = pow(2, sizeof(unsigned short)*8)-1;
	cout << "ushort max: " << ushort_max << endl;
		
	
	return 0;
}
