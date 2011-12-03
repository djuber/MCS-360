/* file : quiz5.cc
   Daniel Uber
   read numbers from file,
   print to another file
   MCS 360 Quiz 5
*/

#include <vector>
#include <fstream>
#include <iostream>
#include "Ratio.h"

using namespace std;

void writeEmptying(vector<Ratio *> &v, ostream &out){
  vector<Ratio *>::iterator i;
  for(i=v.begin(); i!=v.end(); i=v.begin()){
    out << *(*i) << endl; // iterator is a pointer into the vector
    v.erase(i);
  }
  return;
}

void skipComments(ifstream &in){
  while(in.peek() == '#')
    in.ignore(50000, '\n');
  return;
}

// stop at first line beginning with *
bool asterisk(ifstream &in){return (in.peek() == '*')?true:false;}

void readFromFile(vector<Ratio *> &v, ifstream &in){
  Ratio * t;
  skipComments(in);
  while(!asterisk(in)){
    t = new Ratio;
    in >> (*t);
    (*t).simplify();
    v.push_back(t);
  }
  return;
}

void readFromCin(vector<Ratio *> &v){
  Ratio * t;
  while(cin.peek() != '*'){
    t = new Ratio;
    cin >> *t;
    (*t).simplify();
    v.push_back(t);
  }
  return;
}

void litterWithComments(ostream &out){
  out << "#\n"
      << "# this is the rationalized output from\n"
      << "# the input file. (rdata.csv) \n"
      << " You can do many things with these fractions.\n"
      << "# Data ends at the asterisk *\n"
      << "#\n";
  return;
}

void markWithAsterisk(ostream& out){
  out << "*\n";
  return;
}


int main(){
  vector<Ratio *> v;
  ofstream out;
  ifstream in;
  in.open("rdata.csv");
  if(!in)
    return 1;
  readFromFile(v, in);
  //readFromCin(v);
  in.close();
  cout << "read " << v.size() << " fractions\n";
  out.open("reduced.csv");
  litterWithComments(out);
  writeEmptying(v, out);
  markWithAsterisk(out);
  out.close();
 return 0;
}

