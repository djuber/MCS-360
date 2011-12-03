// main.cc
// Daniel Uber
// MCS 360 Quiz 4

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

struct Complex{
  double re;
  double im;
};

extern void isort(vector<Complex *> &v);
extern void readFromFile(vector<Complex *> &v, ifstream &in);
extern void writeToFileEmptying(vector<Complex *> &v, ofstream &out);

// // quick testing
// void fill(vector<Complex *> &v, int n){
//   Complex * z;
//   for(int i = 0; i < n; i++){
//     z = new Complex;
//     z->re = (i+10)%3 * 0.5 * i;
//     z->im = i * 0.25;
//     v.push_back(z);
//   }
//   return;
// }

// // quick testing
// void printEmptying(vector<Complex *> &v) {
//   vector<Complex *>::iterator i;

//   for(i = v.begin(); i != v.end(); i = v.begin()){
//     cout << (*i)->re << "\t" << (*i)->im << "\n";
//     v.erase(i);
//   }
//   return;
// }



int main(){
  vector<Complex *> v;
  ifstream infile;
  ofstream outfile;

  infile.open("zdata.dat");
  if(!infile){
    cerr<<"Failed to open zdata.dat\n";
    return 1;
  }
  readFromFile(v,infile);
  infile.close();
  isort(v);
  outfile.open("zsorted.dat");
  writeToFileEmptying(v,outfile);
  return 0;
}
