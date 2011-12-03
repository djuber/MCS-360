/* funcs.cc : functions called from main
   Daniel Uber
   MCS 360 Week 2 Quiz
*/

#include <fstream>
#include <vector>
#include "funcs.h"
#include <iostream>

using namespace std;

void readFromFileIntoVector(ifstream &in, vector<Score> &v)
{
  int id;  
  float exam1;
  float exam2;
  float final;
  Score s;

  while(in){
    char name[100];
    in >> id >> name >> exam1 >> exam2 >> final;
    s.set_id(id);
    s.set_name(name);
    s.set_exam1(exam1);
    s.set_exam2(exam2);
    s.set_final(final);
 
    v.push_back(s);
  }
  v.pop_back(); // fix quirk in file input
  return;
}

void writeFromVectorToFile(vector<Score> &v, ofstream &out)
{
  for(unsigned int i = 0; i < v.size() ; i++){
    out << v[i].id()
	<< " " 
	<< v[i].name() 
	<< " " 
	<< v[i].score() 
	<< "\n";
  }
  return;
}

// insertion sort on vector of scores by id field
void isort(vector<Score> &v){
  int j, id;
  Score val;
  for(unsigned int i = 1; i < v.size(); i++){
    val = v[i];
    id = val.id();
    j = i - 1;
    while(j >= 0 && v[j].id() > id){
      v[j+1] = v[j];
      j = j - 1;
    }
    v[j+1] = val;
  }

  return;
}



