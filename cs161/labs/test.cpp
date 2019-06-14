#include <iostream>
using namespace std;

int main() {
   int answer;
   cout<< "Do you like vi as an editor?"<<endl;
   cin>>answer;
   if (answer == 1)
      cout<< "You love vi!"<<endl;
   else if (answer == 0)
      cout<< "You hate vi!"<<endl;	
   return 0;
}
