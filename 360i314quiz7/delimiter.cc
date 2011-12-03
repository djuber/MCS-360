// delimiter.cc
// MCS 360 Fall 2011
// Daniel Uber
// logic to handle opening and closing delimiters.
#include "delimiter.h"
#include "stack.h"
#include <fstream>
#include <iostream>
#include <string>

// change these if you need to, and change delimiters if the number changes
char openers[]={'(', '[', '{'};
char closers[] = {')', ']', '}'};
const int delimiters = 3;
// quote marks
char quotes[]={'\'', '\"'};

int openoffset(char c){
  for(int i = 0; i < delimiters; i++)
    if(c == openers[i])
      return i;
  return -1;
}

int closeoffset(char c){
  for(int i = 0; i < delimiters; i++)
    if(c == closers[i])
      return i;
  return -1;
}


int delimiter(std::string s){
  std::ifstream in;
  // start at beginning of the file
  // these choices align with emacs line/column reporting
  // where the first position in a buffer is line 1, column 0
  int line = 1;
  int col = 0;
  char c=0, last=0;
  stack<char> stk;
  in.open(s.c_str());
  if(!in){
    std::cerr<<"Unable to open "<<s<<'\n';
    return -1;
  }
  while(!in.eof()){
    last = c; // store last character, so we can check for \' and \"
    c = in.get();
    // is this a quote?
    if(c=='\'' || c =='\"'){
      if(last != '\\'){
	if (!stk.empty()){
	  if(stk.top()==c)
	    stk.pop();
	} else
	  stk.push(c);
      }
    }
    else{ // if the stack is not empty and there is a quote at the top
      if(!((!stk.empty() && (stk.top()=='\'' || stk.top()=='\"'))))
	for(int i = 0; i < delimiters; ++i){
	  // push opening delimiters
	  if(c == openers[i]){
	    stk.push(c);
	  }
	  //check closing delimiters
	  else if (c == closers[i]){
	    if(stk.empty()){
	      // closing bracket with empty stack
	      std::cerr<<"Unmatched closing "<<c<<" at line "
		       <<line<<" column "<<col<<'\n';
	      in.close();
	      return -1;
	    }
	    if (i != openoffset(stk.top())){
	      //indices should match, otherwise nesting is wrong.
	      std::cerr<<"Mismatched closing " << c << " at line "
		       <<line << " column " << col <<'\n';
	      in.close();
	      return -1;
	    }
	    else (stk.pop());
	  }
	} // for list of delimiters
      if(c=='\n'){
	// reset column and increment line
	col=0;
	line++;
      }
      else // incremement column
	col++;
    } //else (not in a quote)
  }// while not eof
  if(!stk.empty()){
    // there were opening delimiters without a matching closer, report them all
    while(!stk.empty()){
      std::cerr<<"Unclosed "<< stk.top() << " at EOF\n";
      stk.pop();
    }
    in.close();
    return -1;
  }
  in.close();
  return 0;
}
