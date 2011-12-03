/** @file postfixFormat.cc
    @author Daniel Uber
    @brief translate infix to postfix
*/

#include "project3.h"


/** required function name */
std::string infix2postfix(std::string infix){
  return postfixFormat(infix);
}

/** take an infix expression (with spaces) and
    produce an equivalent postfix expression

    Rules:

    Push an open bracket.

    Process any other tokens.

    When close bracket : pop until close bracket
*/
std::string postfixFormat(std::string s){
  Stack<std::string> l;
  std::stringstream input(s);
  std::stringstream output;
  std::string t;
  while(!input.eof() && !input.fail()){
    // need to clear this each pass or last term will be present on failed read
    t="";
    input>>t;
    if(!isWhitespace(t)) {
      if(!isBracket(t)){
	try{
	  double d = toDouble(t);
	  output<<" "<<d;
	} catch (InvalidExpression){
	  // if there's an operator on the stack
	  if(!l.isEmpty() && precedence(t, l.top())){
	    while(!l.isEmpty() && precedence(t,l.top()))
	      output<<" "<<l.pop();
	    l.push(t);
	  }
	  else {
	    l.push(t);
	  }
	}
      } else // it is a bracket
	if(t=="(") //push an open bracket
	  l.push(t);
	else if(t==")"){
	  try{ // evaluate everything within parentheses before proceeding
	    if(l.top()=="(") throw InvalidExpression();
	    while(l.top() != "("){
	      output<<" "<<l.pop();
	    }
	    l.pop(); //remove open bracket
	  } catch (StackError){
	    std::cerr<<"Caught StackError (Underflow)\n";
	    std::cerr<<"Partial result: "<<output.str()<<'\n';
	    throw InvalidExpression();
	  }
	}
    }
  }
  while(!l.isEmpty())
    output<<" "<<l.pop();
  return output.str();
}


