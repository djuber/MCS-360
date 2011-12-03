// file: q3p1.cc
// Quiz 3 Problem 1
// Daniel Uber MCS 360 Fall 2011

#include <iostream>
using namespace std;

int main(){
  const int n = 10;

  float a[n];

  for(int i = 0; i < n; i++) {
    a[i] = float(i) + 1;
  }
  for(int i = 0; i < n; i++){
    cout << *(a + i) << '\n';
  }
  return 0;
}

