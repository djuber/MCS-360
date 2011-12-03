/** @file randwords.cc
    @author Daniel Uber
    @brief generate randwords.txt
    extended to use all letters and numbers.
    random is not seeded, so the same words are made every time.
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

string rand_word(){
  char buf[9];
  long r;
  buf[8] = '\0';
  for(int i = 0; i<8; i++){
    r = 0;
    while(! ( isalpha(r) || isdigit(r))){
      r = random();
      r = 1 + (r % 255); // in range 1-255
      if(isalpha(r) || isdigit(r))
	buf[i]= r;
    }
  }
  return string(buf);
}

void rand_words(int number){
  ofstream out("randwords.txt");
  if(out){
    for(int i = 0; i < number; i++)
      out<<" "<<rand_word();
    out<<"\n";
    out.close();
  }
  else
    exit(1);
}
