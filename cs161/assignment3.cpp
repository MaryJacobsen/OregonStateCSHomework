/***************************************************************************
** Program Filename: assignment3
** Author: Mary Jacobsen
** Date: 1-31-16
** Description: Finds a path from start x,y coordinates to end x,y coordinates both inputted by the user
** Input: x,y start and end coordinates
** Output: a four by four grid with a path from the starting coordinates to the ending coordinates
***************************************************************************/
#include <iostream>

using namespace std;

/***************************************************************************
** Function: print_grid
** Description: this prints the grid and and the path using the boolean values passed to it
** Parameters: none
** Pre-Conditions: the booleans must be set to true or false
** Post conditions: none
***************************************************************************/
void print_grid(bool x0y0,bool x0y1,bool x0y2,bool x0y3,bool x1y0,bool x1y1,bool x1y2,bool x1y3,bool x2y0,bool x2y1,bool x2y2,bool x2y3,bool x3y0,bool x3y1,bool x3y2,bool x3y3) {
	
   	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){  
		      if(i==0 && j==0 && x0y0)
			      cout<<"X";
		      else if(i==0 && j==1 && x0y1)
			      cout<<"X";
		      else if(i==0 && j==2 && x0y2)
			      cout<<"X";
		      else if(i==0 && j==3 && x0y3)
			      cout<<"X";
		      else if(i==1 && j==0 && x1y0)
			      cout<<"X";
		      else if(i==1 && j==1 && x1y1)
			      cout<<"X";
		      else if(i==1 && j==2 && x1y2)
			      cout<<"X";
		      else if(i==1 && j==3 && x1y3)
			      cout<<"X";
		      else if(i==2 && j==0 && x2y0)
			      cout<<"X";
		      else if(i==2 && j==1 && x2y1)
			      cout<<"X";
		      else if(i==2 && j==2 && x2y2)
			      cout<<"X";
		      else if(i==2 && j==3 && x2y3)
			      cout<<"X";
		      else if(i==3 && j==0 && x3y0)
			      cout<<"X";
		      else if(i==3 && j==1 && x3y1)
			      cout<<"X";
		      else if(i==3 && j==2 && x3y2)
			      cout<<"X";
		      else if(i==3 && j==3 && x3y3)
			      cout<<"X";
		      else
			      cout<<"0";
		}
		cout<<endl;
	}	
}
/***************************************************************************
** Function: find_path
** Description: it finds a path from the starting point to the ending point
** Parameters: none
** Pre-Conditions: it must have user inputted values for the x,y starting and ending points
** Post-Conditions: none
***************************************************************************/
void find_path(int currentx, int currenty, int endx, int endy) {
	bool x0y0,x0y1,x0y2,x0y3,x1y0,x1y1,x1y2,x1y3,x2y0,x2y1,x2y2,x2y3,x3y0,x3y1,x3y2,x3y3;
	
	
	x0y0=x0y1=x0y2=x0y3=x1y0=x1y1=x1y2=x1y3=x2y0=x2y1=x2y2=x2y3=x3y0=x3y1=x3y2=x3y3=false;
	
	if(currentx==0 && currenty==0)
	   	x0y0=true;
	else if(currentx==0 && currenty==1)
	   	x0y1=true;
	else if(currentx==0 && currenty==2)
	   	x0y2=true;
	else if(currentx==0 && currenty==3)
	   	x0y3=true;
	else if(currentx==1 && currenty==0)
	   	x1y0=true;
	else if(currentx==1 && currenty==1)
	   	x1y1=true;
	else if(currentx==1 && currenty==2)
	   	x1y2=true;
	else if(currentx==1 && currenty==3)
	   	x1y3=true;
	else if(currentx==2 && currenty==0)
	   	x2y0=true;
	else if(currentx==2 && currenty==1)
	   	x2y1=true;
	else if(currentx==2 && currenty==2)
	   	x2y2=true;
	else if(currentx==2 && currenty==3)
	   	x2y3=true;
	else if(currentx==3 && currenty==0)
	   	x3y0=true;
	else if(currentx==3 && currenty==1)
	   	x3y1=true;
	else if(currentx==3 && currenty==2)
	   	x3y2=true;
	else if(currentx==3 && currenty==3)
	   	x3y3=true;
	
	while(currentx!=endx){
	   if(currentx<endx)
		     currentx++;
	   else 
		     currentx--;
     
	   if(currentx==0 && currenty==0)
		   x0y0=true;
	   else if(currentx==0 && currenty==1)
		   x0y1=true;
	   else if(currentx==0 && currenty==2)
		   x0y2=true;
	   else if(currentx==0 && currenty==3)
		   x0y3=true;
	   else if(currentx==1 && currenty==0)
		   x1y0=true;
	   else if(currentx==1 && currenty==1)
		   x1y1=true;
	   else if(currentx==1 && currenty==2)
		   x1y2=true;
	   else if(currentx==1 && currenty==3)
		   x1y3=true;
	   else if(currentx==2 && currenty==0)
		   x2y0=true;
	   else if(currentx==2 && currenty==1)
		   x2y1=true;
	   else if(currentx==2 && currenty==2)
		   x2y2=true;
	   else if(currentx==2 && currenty==3)
		   x2y3=true;
	   else if(currentx==3 && currenty==0)
		   x3y0=true;
	   else if(currentx==3 && currenty==1)
		   x3y1=true;
	   else if(currentx==3 && currenty==2)
		   x3y2=true;
	   else if(currentx==3 && currenty==3)
		   x3y3=true;	   
	}
	while(currenty!=endy){
	   	if(currenty<endy)
		   	currenty++;
		else
		   	currenty--;
	
	   if(currentx==0 && currenty==0)
		   x0y0=true;
	   else if(currentx==0 && currenty==1)
		   x0y1=true;
	   else if(currentx==0 && currenty==2)
		   x0y2=true;
	   else if(currentx==0 && currenty==3)
		   x0y3=true;
	   else if(currentx==1 && currenty==0)
		   x1y0=true;
	   else if(currentx==1 && currenty==1)
		   x1y1=true;
	   else if(currentx==1 && currenty==2)
		   x1y2=true;
	   else if(currentx==1 && currenty==3)
		   x1y3=true;
	   else if(currentx==2 && currenty==0)
		   x2y0=true;
	   else if(currentx==2 && currenty==1)
		   x2y1=true;
	   else if(currentx==2 && currenty==2)
		   x2y2=true;
	   else if(currentx==2 && currenty==3)
		   x2y3=true;
	   else if(currentx==3 && currenty==0)
		   x3y0=true;
	   else if(currentx==3 && currenty==1)
		   x3y1=true;
	   else if(currentx==3 && currenty==2)
		   x3y2=true;
	   else if(currentx==3 && currenty==3)
		   x3y3=true;
	}
	print_grid(x0y0,x0y1,x0y2,x0y3,x1y0,x1y1,x1y2,x1y3,x2y0,x2y1,x2y2,x2y3,x3y0,x3y1,x3y2,x3y3);
}	

int main(){
   	int t=1;
	while(t==1){
   		int currentx, currenty,endx, endy;
		cout<< "Where would you like to start?" <<endl;
		cout<< "x= ";
		cin>>currentx;
		
		if(cin.fail()){
		   	cin.clear();
			cin.ignore();
			cout<<"invalid input, not an integer"<<endl;
			continue;}
		else if(0>currentx || currentx>3){
			cout<<"invalid input, not 0-3"<<endl;
			continue;}
		
		cout<< "y= ";
		cin>>currenty;
		
		if(cin.fail()){
		   	cin.clear();
			cin.ignore();
			cout<<"invalid input, not an integer"<<endl;
			continue;}
		else if(currenty<0 || currenty>3){
		   	cout<<"invalid input, not 0-3"<<endl;
			continue;}
			cout<< "Where would you like to end?" <<endl;
		
		cout<< "x= ";
		cin>>endx;
		
		if(cin.fail()){
		   	cin.clear();
			cin.ignore();
			cout<<"invalid input, not an integer"<<endl;
			continue;}
		else if(endx<0 || endx>3){
		   	cout<<"invalid input, not 0-3"<<endl;
			continue;}
		
		cout<< "y= ";
		cin>>endy;
		
		if(cin.fail()){
		  	cin.clear();
			cin.ignore();
			cout<<"invalid input, not an integer"<<endl;
			continue;}
		else if(endy<0 || endy>3){
		   	cout<<"invalid input, not 0-3"<<endl;
			continue;}
		
	find_path(currentx, currenty,endx, endy);
	
	cout<<"Do you want to find another path? No(0),Yes(1)"<<endl;
	cin>>t;
	if(t<0 || t>1){
		cout<<"invalid input, not 0 or 1"<<endl;
		t=0;}
	else if(cin.fail()){
		cin.clear();
		cin.ignore();
		cout<<"invalid input, not an integer"<<endl;
		t=0;}

	}
 	return 0;	
}
