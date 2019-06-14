#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
   freopen("act.txt", "r", stdin);
   int r=1, act, start, end, setnum = 1;
   while (cin >> r) {
       vector<pair <int, pair <int, int> > > v;
       for (int i = 0; i < r; ++i) {
           cin >> act >> start >> end;
           v.push_back(make_pair(start, make_pair(end, act)));     
       }
       sort(v.rbegin(), v.rend());
       int last = 0;
       vector<int> selected;
       selected.push_back(v[0].second.second);
       for (int i = 1; i < r; ++i) {
           if (v[i].second.first <= v[last].first) { 
               selected.push_back(v[i].second.second);
               last = i;
           }
       }
       reverse(selected.begin(), selected.end());
       cout << "Set " << setnum << "\nNumber of activities selected = " << selected.size() << "\n";
       cout << "Activities: ";
       for (int i : selected) {
           cout << i << " ";
       }
       cout << "\n\n";
       setnum++;  
   }
}
