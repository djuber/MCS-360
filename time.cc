/** @file time.cc
    @author Daniel Uber
    @brief Testing granularity of the clock() function
*/

#include <ctime>
#include <iostream>

using namespace std;

int main(){
  clock_t c1, c2;
  double dt;
  c1 = clock();
  while((c2=clock())==c1) ;
  dt = c2 - c1;
  cout << dt/CLOCKS_PER_SEC << endl;
  return 0;
}
