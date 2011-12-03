/* main.cc : main program driver 
   Daniel Uber
   MCS 360 Week 2 Quiz
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "score.h"
#include "funcs.h"

const char infile_name[]="examscore.dat";
const char outfile_name[] = "score.dat";

using namespace std;


int main(){

  ifstream in;
  ofstream out;
  in.open(infile_name);

  
  vector<Score> v;
  
  if(!in){ // this works
    cout<<"Could not open " << infile_name <<"\n";

    exit(1);
  }



  readFromFileIntoVector(in, v);
  in.close();

  isort(v);

  out.open(outfile_name);
  writeFromVectorToFile(v, out); 
  out.close();

  return 0;
}
