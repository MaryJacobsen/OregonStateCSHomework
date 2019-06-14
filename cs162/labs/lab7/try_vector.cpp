#include "./vector.hpp"
//#include <vector>
#include <iostream>
using std::cout;
using std::endl;

int main(){
   	vector<int> v; 
//	std::vector<int> stdv;

	v.push_back(23);
//	stdv.push_back(23);
	try{
		for(int i=0; i<12; i++){
	   		cout<<v.at(i)<<" ";
		}
	}
	catch(std::out_of_range &e){
	   	cout<<"n catch"<<endl;
		cout<<e.what()<<endl;
	}
	cout<<endl;
//	for(int i=0; i<stdv.size(); i++){
//	   	cout<<stdv[i]<<" ";
//	}
//	cout<<endl;

	return 0;
}
