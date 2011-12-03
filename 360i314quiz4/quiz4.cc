/* quiz4.cc : functions to fill, sort, and empty vectors used in week 4 quiz */

#include <vector>
#include <fstream>

using namespace std;

struct Complex{
  double re;
  double im;
};

void isort(vector<Complex *> &v){
  Complex * t;
  vector<Complex *>::iterator i, j;
  for(i=v.begin();i != v.end(); ++i){
    t = *i;
    for(j=i; j!=v.begin() && (*(j-1))->re > t->re; --j)
      *j = *(j-1);
    *j=t;
  }
  return;
}

void writeToFileEmptying(vector<Complex *> &v, ofstream &out){
  vector<Complex *>::iterator i;
  for(i=v.begin(); i!=v.end(); i=v.begin()){
    out << (*i)->re << " , " << (*i)->im << "\n";
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
int asterisk(ifstream &in){return (in.peek() == '*')?1:0;}

void readFromFile(vector<Complex *> &v, ifstream &in){
  Complex * t;
  skipComments(in);
  while(!asterisk(in)){
    t = new Complex;
    in >> t->re;
    in.ignore(5000, ',');
    in >> t->im;
    in.ignore(5000, '\n');
  v.push_back(t);
  }
  return;
}
