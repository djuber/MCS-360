/** @file postfixEval.cc
    @author Daniel Uber
    @brief definition of postfixEval and required
    function call eval_postfix
*/

#include "project3.h"

/** required function name */
double eval_postfix(std::string postfix){
  return postfixEval(postfix);
}

/** actual function:
    return result of evaluating the expression string
*/
double postfixEval(std::string s){
  std::stringstream input(s);
  std::string t;
  Stack<double> l;
  double dt, a, b;
  // a generally good thing to check
  while(!input.eof() && !input.fail()){
    // get a string from expression
    input>>t;
    // assume t is a number
    if(!isWhitespace(t)){
      try{
	dt = toDouble(t);
	l.push(dt);
      }
      // unless it wasn't
      catch (InvalidExpression) {
	if(isOperator(t)){
	    Operator *Op = &(getOperator(t));
	    a = l.pop();
	    b = l.pop();
	    l.push(Op->operator()(a,b));
	} else {
	  std::cerr<<"Tried to process "<<t<<" as an operator.\n";
	  throw InvalidExpression();
	}
      }
    }
  }
  // return this value, which is on the stack
  try{
    dt = l.pop();
  } catch (StackError){
    // report and rethrow
    std::cerr<<"Stack Error\n";
    throw StackError();
  }
  if(!l.isEmpty()) throw InvalidExpression();
  return dt;
}
