#include <iostream>
#include <cstdlib>
using namespace std;

bool command_line(int, char**, int*, int*);

int main(int argc, char *argv[]){
   	
	int rows = 0, cols = 0;
//	command_line(argc, argv, &rows, &cols);
	cout<<"rows= "<<rows<<" cols= "<<cols<<endl;	
   	return 0;
}

bool command_line(int argc, char* argv[], int* rows, int* cols)
{

   	if(argc != 3){
	   	return false;
	}

	else if(argv[1]<49 || argv[1]>57 || argv[2]<49 || argv[2]>57){
	   	cout<<"Please enter a valid non-zero integer"<<endl;
		return false;
	}
	else{
	   	*rows=atoi(argv[1]);
		*cols=atoi(argv[2]);
		return true;
	}
	
}
