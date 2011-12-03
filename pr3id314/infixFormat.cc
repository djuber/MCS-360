/** @file infixFormat.cc
    @author Daniel Uber
    @brief add spaces between arguments and operators
    in an infix expression
*/

#include "project3.h"


/** @fn split_token(std::string t, Stack<std::string> &s)
    given a possibly poorly spaced string t,
    put sensible chunks into s
    revise using a queue? reversing the stack seems silly
*/
void split_token(std::string t, Stack<std::string> &s){
  // push from the front into stmp
  Stack<std::string> stmp;
  std::stringstream tmp;
  bool inNumber = false;
  bool dotted=false;
  char c;
  for(size_t i = 0; i <= t.size();i++){
    if(isdigit(t[i]) || t[i]=='.'){
      if(t[i]=='.'){
	if(dotted) throw InvalidExpression();
	else dotted=true;
      }
      tmp<<t[i];
      inNumber = true;
    } else if(inNumber){
      // clear number characters
      inNumber = false;
      dotted=false;
      stmp.push(tmp.str());
      tmp.str("");
      if(!isWhitespace(t[i]))
	 stmp.push(std::string(&(c=t[i])));
    } else
      if(!isWhitespace(t[i]))
	   stmp.push(std::string(&(c=t[i])));
  }
  while(!stmp.isEmpty())
    // pop from the end
    s.push(stmp.pop());
}

/** @fn infixFormat(std::string &s)
    given an input string as an infix expression
    insert a single space between operands and binary operators
    leave no space between unary negation and its operand
*/
std::string infixFormat(std::string &s){
  Stack<std::string> stack;
  std::stringstream output;
  std::stringstream input(s);
  std::string t;
  bool wasNumber = false;
  bool unary = false;
  do{
    t = "";
    input>>t;
    split_token(t, stack);
    while(!stack.isEmpty()){
      if(!isBracket(stack.top())) {
	if(isOperator(stack.top())){
	  if(!wasNumber && stack.top()!="-"){
	    throw InvalidExpression();
	  } else if (stack.top()=="-"){
	    unary=!wasNumber;
	    wasNumber=false;
	  } else {
	    wasNumber = false;
	  }
	} else {
	  if(wasNumber)
	    throw InvalidExpression();
	  wasNumber = true;
	}
      }
      if(!unary)
	output<<stack.pop()<<" ";
      else{
	output<<stack.pop();
	unary=false;
      }
    }
  } while (t != "");
  return output.str();
}

