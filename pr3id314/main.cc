/** @file main.cc
    @author Daniel Uber
    @brief either run unit tests,
    or scan stdin until eof, processing data and evaluating
    expressions, printing to stdout
    program ends at eof
*/

#ifdef TESTING

#include "test.h"
int main(){
  TestSuite T;
  return T.result()?0:1;
}

#else

#include "project3.h"
using namespace std;

/** main program driver :
    read from stdin until eof
    process expression as infix
    print to stdout formatted infix,
    print to stdout postfix interpretation
    print to stdout value of expression
*/
int main(){
  string t="";
  const string s1 = "Formatted Input: ";
  const string s2 = "Postfix Expression:";
  const string s3 = "Value: ";
  while(!cin.eof() && !cin.fail()){
    getline(cin,t);
    if(!isWhitespace(t)) {
      try{
	t = infixFormat(t);
	cout<<s1<<t<<'\n';
	t = infix2postfix(t);
	cout<<s2<<t<<'\n';
	cout<<s3<<eval_postfix(t)<<'\n';
      } catch (InvalidExpression){
	cerr<<"Invalid Expression!\n";
      }
      catch (StackError){
	// eof could throw this
	// but eof is a signal to quit
	if(!cin.eof())
	  cerr<<"Stack Error (Underflow)\n";
      }
    }
  }
  return 0;
}

#endif

/** @mainpage
    MCS 360 Project 3

    Infix Arithmetic Evaluator

    Daniel Uber, duber3@uic.edu

    This is a simple program that reads arithmetic expressions
    from stdin, then writes an equivalent postfix expression and
    its value to stdout. This is sufficiently clean to be used in
    a pipe or by file indirection. Any error messages are printed
    to stderr.

    The operations +, -, *, /, and ^ are supported, as well as any sequence
    of properly nested parentheses. Thus:

    2 * (1.3 + -1.2) / 3 + 1.5 ^ 2 ^ 3

   Formatted Input: 2 * ( 1.3 + -1.2 ) / 3 + 1.5 ^ 2 ^ 3

   Postfix Expression: 2 1.3 -1.2 + 3 / * 1.5 2 3 ^ ^ +

   Value: 25.6956

    Execution ends at EOF. If used interactively, hit \<CTRL\>-D to exit.
*/
