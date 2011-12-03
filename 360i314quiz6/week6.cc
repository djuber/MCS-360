// file : week6.cc
// read stock prices from file, output a table of closing prices
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>

const char infilename[]="data.txt";
const char outfilename[]="output.txt";

using namespace std;

int main(){
  string line;
  char tab = '\t';
  ifstream fin(infilename);
  if(!fin){
    cerr<<"Problem opening "<<infilename<<endl;
    return EXIT_FAILURE;
  }
  ofstream fout;
  istringstream iss;
  ostringstream oss;
  int stock;
  double price, change, hi, low;
  //make field header line
  oss<<"stock_number"<<tab<<setw(12)<<"curr_price"
     <<tab<<setw(12)<<"change"<<endl;
  // setup persistent stream options
  oss<<fixed<<showpoint<<right;
  while(getline(fin,line)){
    iss.str(line);
    while(isspace(iss.peek()))
      iss.ignore();
    if( iss.str()==""){
      iss.clear();
      break;
    }

    iss>>stock>>price>>change>>hi>>low;
    iss.clear();
    oss<<setw(12)<<stock<<tab
	<<setw(12)<<setprecision(2)<<price<<tab
	<<setw(12)<<setprecision(2)<<change<<endl;
  }

 fin.close();
 fout.open("output.txt");
 fout<<oss.str();
 fout.close();
 return 0;
}
