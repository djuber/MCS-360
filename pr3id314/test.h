/* -*-c++-*- Convince emacs this is what I want */
/** @file test.h
    @author Daniel Uber
    @brief a poorly implemented test framework
*/

#include "project3.h"


/** @class test
    @brief a virtual base for all tests

    tests must return status and take no arguments,
    and should catch and label
    any unexpected exceptions
    setup/teardown can be done in ctor/dtor
    a test which throws/fails to catch an exception is broken
*/
class test {
public:
  /** a description of the test */
  std::string msg;
  /** all tests are callable */
  virtual bool operator() ()=0;
  /** return a description of this test */
  std::string message() {return msg;}
};

/** @class TestCase
    @brief a specific test to run

    a Test Case will print msg, run test, print status
    can only be templated on test types,
    i.e. those that implement message() and
    bool operator()
    results are stored for later inspection
*/
template <typename TEST>
class TestCase {
 private:
  bool result;
 public:
  TestCase(){
    TEST t;
    std::string msg = t.message();
    std::cerr<<'\n'<<msg<<": ";
    flush(std::cout);
    if(t()){
      result = true;
      std::cerr<<"\n\t\t\tPASS.\n";
    }
    else{
      // align this one tabstop over for visibility
      std::cerr<<"\n\t\t\t\tFAIL.\n";
      result = false;
    }
  }
  /** status yields the pass/fail result of this test case */
  bool status() { return result; }
};

/** class TestSuite
    @brief a test suite constructor runs each of its tests
    result method reports whether any tests failed
*/
class TestSuite {
  // only true when all tests pass
  bool allresults;

  // test postfixEval simple
  class test1 :public test{
  public:
    test1() {
      msg = "Test 1: postfixEval(\"2 3 +\") ";
    }
    bool operator() (){
      std::string s ="2 3 +";
      try{
	return postfixEval(s) == 5.0;
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error ";
	return false;
      }
    }
  };

  // test postfixFormat simple
  class test2 : public test {
  public:
    test2(){
      msg="Test 2: postfixFormat() ";
    }
    bool operator() () {
      std::string s = "2 + 3";
      try{
	return postfixEval(postfixFormat(s)) == 5.0;
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression error ";
	return false;
      } catch (StackError){
	std::cerr<<"Caught StackError (Underflow) ";
	return false;
      }
    }
  };

  // test toDouble
  class test3 : public test {
  public:
    test3() {
      msg = "Test 3: toDouble(2.3) ";
    }
    bool operator() (){
      std::string s = "2.3";
      return toDouble(s)==2.3;
    }
  };

  // test toDouble
  class test4 : public test {
  public:
    test4(){
      msg = "Test 4: toDouble(-2.3) ";
    }
    bool operator() () {
      std::string s = "-2.3";
      return toDouble(s)==-2.3;
    }
  };

  // test toDouble throw
  class test5 : public test {
  public:
    test5(){
      msg="Test 5: toDouble(\"Hello World!\") throws ";
    }
    bool operator() () {
      std::string s = "Hello World!\n";
      try{
	toDouble(s);
	return false;
      } catch (InvalidExpression){
	std::cerr<<"Caught InvalidExpression Error ";
	return true;
      }
    }
  };

  class test6 :public test{
  public:
    test6(){
      msg="Test 6: postfixEval(\"2 3 *\") ";
    }
    bool operator() (){
      std::string s ="2 3 *";
      try{
	return postfixEval(s) == 6.0;
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error ";
	return false;
      }
    }
  };

  class test6a :public test{
  public:
    test6a(){
      msg="Test 6a: postfixEval(\"2 3 ^\") ";
    }
    bool operator() (){
      std::string s ="2 3 ^";
      try{
	if(postfixEval(s) == 8.0)
	  return true;
	else {
	  std::cerr<<postfixEval(s)<<'\n';
	  return false;
	}
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error ";
	return false;
      }
    }
  };

  class test7 :public test{
  public:
    test7(){
      msg="Test 7: postfixEval(\"2 3 4 *\") ";
    }
    bool operator() (){
      std::string s ="2 3 4 *";
      try{
	bool result = (postfixEval(s) == 12.0);
	return !result;
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error ";
	return true;
      }
    }
  };

  // test postfixFormat simple
  class test8 : public test {
  public:
    test8(){
      msg="Test 8: postfixFormat() ";
    }
    bool operator() () {
      std::string s = "2 + 3 + 4";
      try{
	return postfixEval(postfixFormat(s)) == 9.0;
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression error ";
	return false;
      } catch (StackError){
	std::cerr<<"Caught StackError (Underflow) ";
	return false;
      }
    }
  };

  // test postfixFormat simple + extra space
  class test8a : public test {
  public:
    test8a(){
      msg="Test 8a: postfixFormat() with extra space ";
    }
    bool operator() () {
      std::string s = "        2 + 3 + 4      ";
      try{
	s= postfixFormat(s);
	std::cerr<<s<<'\n';
	return postfixEval(s)==9.0;
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression error ";
	return false;
      } catch (StackError){
	std::cerr<<"Caught StackError (Underflow) ";
	return false;
      }
    }
  };

  // check precedence
  class test8b : public test {
  public:
    test8b(){
      msg="Test 8b: postfixFormat with precedence ";
    }
    bool operator() () {
      std::string s = "2 * 2  + 3 * 2"; //10
      try{
	std::cerr<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	return postfixEval(s)==10.0;
      } catch (InvalidExpression){
	std::cerr<<"Caught InvalidExpression error ";
	return false;
      } catch (StackError) {
	std::cerr<<"Caught StackError error ";
	return false;
      }
    }
  };

  // check precedence
  class test8c : public test {
  public:
    test8c(){
      msg="Test 8c: postfixFormat with precedence ";
	}
    bool operator() () {
      std::string s = "2 + 2 * 3 + 2"; //10
      try{
	std::cerr<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	return postfixEval(s)==10.0;
      } catch (InvalidExpression){
	std::cerr<<"Caught InvalidExpression error ";
	  return false;
      } catch (StackError) {
	std::cerr<<"Caught StackError error ";
	return false;
      }
    }
  };

  // check precedence
  class test8d : public test {
  public:
    test8d(){
      msg="Test 8d: postfixFormat with precedence ";
    }
    bool operator() () {
      std::string s = "3 + 2 * 3 ^ 2 + 2 * 3"; // 27
      try{
	std::cerr<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	if(postfixEval(s)==27.0) return true;
	else{
	  std::cerr<<postfixEval(s)<<'\n';
	  return false;
	}
      } catch (InvalidExpression){
	std::cerr<<"Caught InvalidExpression error ";
	return false;
      } catch (StackError) {
	std::cerr<<"Caught StackError error ";
	return false;
      }
    }
  };

  // check parens
  class test8e : public test {
  public:
    test8e(){
      msg="Test 8e: postfixFormat with parens ";
    }
    bool operator() () {
      std::string s = "(3 + 2) * 3 ^ 2"; //45
      try{
	std::cerr<<s<<'\n';
	s = infixFormat(s);
	std::cerr<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	if(postfixEval(s)==45.0) return true;
	else{
	  std::cerr<<postfixEval(s)<<'\n';
	  return false;
	}
      } catch (InvalidExpression){
	std::cerr<<"Caught InvalidExpression error ";
	return false;
      } catch (StackError) {
	std::cerr<<"Caught StackError error ";
	return false;
      }
    }
  };

  // check parens nesting
  class test8f : public test {
  public:
    test8f(){
      msg="Test 8f: postfixFormat with nested parens ";
    }
    bool operator() () {
      std::string s = "((3 + 2) * 3) ^ 2"; //225
      try{
	std::cerr<<s<<'\n';
	s = infixFormat(s);
	std::cerr<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	if(postfixEval(s)==225.0) return true;
	else{
	  std::cerr<<postfixEval(s)<<'\n';
	  return false;
	}
      } catch (InvalidExpression){
	std::cerr<<"Caught InvalidExpression error ";
	return false;
      } catch (StackError) {
	std::cerr<<"Caught StackError error ";
	return false;
      }
    }
  };

  // check parens nesting
  class test8g : public test {
  public:
    test8g(){
      msg="Test 8g: postfixFormat with improperly nested parens ";
    }
    bool operator() () {
      std::string s = "((3 + 2) * 3 ^ 2"; //225
      try{
	std::cerr<<s<<'\n';
	s = infixFormat(s);
	std::cerr<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	if(postfixEval(s)==225.0) return false;
	else{
	  std::cerr<<postfixEval(s)<<'\n';
	  return false;
	}
      } catch (InvalidExpression){
	std::cerr<<"Caught InvalidExpression error ";
	return true;
      } catch (StackError) {
	std::cerr<<"Caught StackError error ";
	return false;
      }
    }
  };


  // check parens nesting, reject empty parens
  class test8h : public test {
  public:
    test8h(){
      msg="Test 8h: postfixFormat rejects empty parens ";
    }
    bool operator() () {
      std::string s = "(3 + 2) * ()3 ^ 2";
      try{
	std::cerr<<s<<'\n';
	s = infixFormat(s);
	std::cerr<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	if(postfixEval(s)==45.0) return false;
	else{
	  std::cerr<<postfixEval(s)<<'\n';
	  return false;
	}
      } catch (InvalidExpression){
	std::cerr<<"Caught InvalidExpression error ";
	return true;
      } catch (StackError) {
	std::cerr<<"Caught StackError error ";
	return false;
      }
    }
  };



  class test9 : public test {
  public:
    test9(){
      msg="Test 9: infixFormat() ";
    }
    bool operator() () {
      std::string s = "2+3";
      std::string sf = infixFormat(s);
     std::cerr<<s<<'\t'<<sf<<'\n';
      return (sf == "2 + 3" || sf == "2 + 3 ");
    }
  };

  class test9a : public test {
  public:
    test9a(){
      msg="Test 9a: infixFormat() ";
    }
    bool operator() () {
      std::string s = "2 + 3";
      std::string sf = infixFormat(s);
      std::cerr<<s<<'\t'<<sf<<'\n';
      return (sf == "2 + 3" || sf == "2 + 3 ");
    }
  };

  class test9b : public test {
  public:
    test9b(){
      msg="Test 9b: infixFormat() ";
    }
    bool operator() () {
      std::string s = "2.2 + 3.3";
      std::string sf = infixFormat(s);
      std::cerr<<s<<'\t'<<sf<<'\n';
      return (sf == "2.3 + 3.3" || sf == "2.2 + 3.3 ");
    }
  };

  class test9c : public test {
  public:
    test9c(){
      msg="Test 9c: infixFormat() ";
    }
    bool operator() () {
      std::string s = "((2.2+3.3))";
      std::string sf = infixFormat(s);
      std::cerr<<s<<'\t'<<sf<<'\n';
      return (sf == "( ( 2.3 + 3.3 ) )"
	      || sf == "( ( 2.2 + 3.3 ) ) ");
    }
  };

  class test9d : public test {
  public:
    test9d(){
      msg="Test 9d: infixFormat() extra spaces";
    }
    bool operator() () {
      std::string s = "2.2      +              3.3";
      std::string sf = infixFormat(s);
      std::cerr<<s<<'\t'<<sf<<'\n';
      return (sf == "2.3 + 3.3"
	      || sf == "2.2 + 3.3 ");
    }
  };

  // postfix is invalid infix
  class test9e : public test {
  public:
    test9e(){
      msg="Test 9e: infixFormat() balks at postfix";
    }
    bool operator() () {
      std::string s = "2 3 +";
      try {
      std::string sf = infixFormat(s);
      return false;
      } catch (InvalidExpression) {
	return true;
      }
    }
  };

  class test9f : public test {
  public:
    test9f(){
      msg="Test 9f: infixFormat(\"-2\") ";
    }
    bool operator() () {
      std::string s = "-2";
      try {
	std::string sf = infixFormat(s);
	return (sf=="-2" || sf=="-2 ");
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error\n";
	return false;
      }
    }
  };

  class test9g : public test {
  public:
    test9g(){
      msg="Test 9g: infixFormat(\"-2 + -2\") ";
    }
    bool operator() () {
      std::string s = "-2 + -2";
      try {
	std::string sf = infixFormat(s);
	return (sf=="-2 + -2" || sf=="-2 + -2 ");
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error\n";
	return false;
      }
    }
  };

  class test9h : public test {
  public:
    test9h(){
      msg="Test 9h: infixFormat(\"2.2.2\") ";
    }
    bool operator() () {
      std::string s = "2.2.2";
      try {
	std::string sf = infixFormat(s);
	return (sf=="-2 + -2" || sf=="-2 + -2 ");
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error\n";
	return true;
      }
    }
  };

  class test10 : public test {
  public:
    test10(){
      msg="Test 10: 2/1/2==1 ";
    }
    bool operator() () {
      std::string s = "2/1/2";
      try {
	s = infixFormat(s);
	std::cerr<<'\n'<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	std::cerr<<postfixEval(s)<<'\n';
	return postfixEval(s)==1.0;
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error\n";
	return false;
      }
    }
  };

  class test10a : public test {
  public:
    test10a(){
      msg="Test 10a: 2-2-1==-1 ";
    }
    bool operator() () {
      std::string s = "2-2-1";
      try {
	s = infixFormat(s);
	std::cerr<<'\n'<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	std::cerr<<postfixEval(s)<<'\n';
	return postfixEval(s)==-1.0;
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error\n";
	return false;
      }
    }
  };

  class test10b : public test {
  public:
    test10b(){
      msg="Test 10b: 2-2+1==1 ";
    }
    bool operator() () {
      std::string s = "2-2+1";
      try {
	s = infixFormat(s);
	std::cerr<<'\n'<<s<<'\n';
	s = postfixFormat(s);
	std::cerr<<s<<'\n';
	std::cerr<<postfixEval(s)<<'\n';
	return postfixEval(s)==1.0;
      } catch (InvalidExpression) {
	std::cerr<<"Caught InvalidExpression Error\n";
	return false;
      }
    }
  };

  class operatorTest1 : public test {
  public:
    operatorTest1(){
      msg = "Operator Test 1: 2 * 2 = 4 ";
    }
    bool operator() (){
      Operator *t = &(getOperator("*"));
      return t->operator()(2,2) == 4;
    }
  };

  class operatorTest2 : public test {
  public:
    operatorTest2(){
      msg = "Operator Test 2: 2 / 2 = 1 ";
    }
    bool operator() (){
      Operator *t = &(getOperator("/"));
      return t->operator()(2,2) == 1;
    }
  };

  class operatorTest3 : public test {
  public:
    operatorTest3(){
      msg = "Operator Test 3: 2 - 2 = 0 ";
    }
    bool operator() (){
      Operator *t = &(getOperator("-"));
      return t->operator()(2,2) == 0;
    }
  };

  class operatorTest3a : public test {
  public:
    operatorTest3a(){
      msg = "Operator Test 3a: 2 - 1 = 1 ";
    }
    bool operator() (){
      Operator *t = &(getOperator("-"));
      return t->operator()(1,2) == 1;
    }
  };

  class operatorTest4 : public test {
  public:
    operatorTest4(){
      msg = "Operator Test 4: 2^3 = 16 ";
    }
    bool operator() (){
      Operator *t = &(getOperator("^"));
      return t->operator()(3,2) == 8;
    }
  };

  class operatorTest5 : public test {
  public:
    operatorTest5(){
      msg = "Operator Test 5: 2%4 = 2 ";
    }
    bool operator() (){
      Operator *t = &(getOperator("%"));
      return t->operator()(4,2) == 2;
    }
  };

  class precedenceTest1 : public test {
  public:
    precedenceTest1(){
      msg =  "Precedence Test 1: + and - are equal ";
    }
    bool operator() () {
      std::string plus="+";
      std::string minus="-";
      // neither should be less than the other
      return precedence(minus,plus)&& precedence(plus,minus);
    }
  };

  class precedenceTest2 : public test {
  public:
    precedenceTest2(){
      msg="Precedence Test 2: * > + ";
    }
    bool operator() () {
      std::string plus="+";
      std::string times="*";
      // times < plus false, plus < times true
      return !(precedence(times,plus)) && precedence(plus,times);
    }
  };

  class precedenceTest3 : public test {
  public:
    precedenceTest3(){
      msg = "Precedence Test 3: * > - ";
    }
    bool operator() () {
      std::string minus="-";
      std::string times="*";
      return !(precedence(times,minus)) && precedence(minus, times);
    }
  };

  class precedenceTest4 : public test {
  public:
    precedenceTest4(){
      msg = "Precedence Test 4: *, /, and % are equal ";
    }
    bool operator() () {
      std::string times="*";
      std::string divide="/";
      std::string modulus="%";
      return precedence(times,divide)
	&& precedence(divide,times)
	&& precedence(times,modulus)
	&& precedence(modulus,times)
	&& precedence(modulus,divide)
	&& precedence(divide,modulus);
    }
  };

  class precedenceTest5 : public test {
  public:
    precedenceTest5(){
      msg = "Precedence Test 5: ^ > * ";
    }
    bool operator() () {
      std::string power="^";
      std::string times="*";
      // power < times false, times < power true
      return !(precedence(power,times)) && precedence(times, power);
    }
  };

  class precedenceTest6: public test {
  public:
    precedenceTest6(){
      msg = "Precedence Test 6: ^ = ^ ";
    }
    bool operator() () {
      std::string power="^";
      // power < power false
      return !precedence(power,power);
    }
  };

  class precedenceTest7 : public test {
  public:
    precedenceTest7(){
      msg = "Precedence Test 7: ^ > + ";
    }
    bool operator() () {
      std::string power="^";
      std::string plus="+";
      // power < times false, times < power true
      return !(precedence(power,plus)) && precedence(plus, power);
    }
  };

  class stackTest1 : public test {
  public:
    stackTest1(){
      msg="Stack Test 1: push/top ";
    }
    bool operator() () {
      Stack<double> s;
      s.push(2.0);
      return s.top()==2.0;
    }
  };

  class stackTest2 : public test {
  public:
    stackTest2(){
      msg="Stack Test 2: push/pop/empty ";
    }
    bool operator() () {
      Stack<std::string> s;
      s.push("+");
      s.push("-");
      return s.pop()=="-" && s.pop()=="+" && s.isEmpty();
    }
  };

  class whitespaceTest1 : public test {
  public:
    whitespaceTest1(){
      msg="Whitespace Test 1: a bunch of spaces ";
    }
    bool operator() () {
      std::string s = "          ";
      return isWhitespace(s);
    }
  };

  class whitespaceTest2 : public test {
  public:
    whitespaceTest2(){
      msg="Whitespace Test 2: empty string ";
    }
    bool operator() () {
      std::string s = "";
      return isWhitespace(s);
    }
  };

  class whitespaceTest3 : public test {
  public:
    whitespaceTest3(){
      msg="Whitespace Test 3: not empty ";
    }
    bool operator() () {
      std::string s = "       A       ";
      return !isWhitespace(s);
    }
  };

 public:
  // constructor
  TestSuite() {
    // run tests
    TestCase<precedenceTest1> PT1;
    TestCase<precedenceTest2> PT2;
    TestCase<precedenceTest3> PT3;
    TestCase<precedenceTest4> PT4;
    TestCase<precedenceTest5> PT5;
    TestCase<precedenceTest6> PT6;
    TestCase<precedenceTest7> PT7;
    TestCase<test1> T1;
    TestCase<test2> T2;
    TestCase<test3> T3;
    TestCase<test4> T4;
    TestCase<test5> T5;
    TestCase<test6> T6;
    TestCase<test6a> T6a;
    TestCase<test7> T7;
    TestCase<test8> T8;
    TestCase<test8a> T8a;
    TestCase<test8b> T8b;
    TestCase<test8c> T8c;
    TestCase<test8d> T8d;
    TestCase<test8e> T8e;
    TestCase<test8f> T8f;
    TestCase<test8g> T8g;
    TestCase<test8h> T8h;
    TestCase<test9> T9;
    TestCase<test9a> T9a;
    TestCase<test9b> T9b;
    TestCase<test9c> T9c;
    TestCase<test9d> T9d;
    TestCase<test9e> T9e;
    TestCase<test9f> T9f;
    TestCase<test9g> T9g;
    TestCase<test9h> T9h;
    TestCase<test10> T10;
    TestCase<test10a> T10a;
    TestCase<test10b> T10b;
    TestCase<stackTest1> ST1;
    TestCase<stackTest2> ST2;
    TestCase<whitespaceTest1> WST1;
    TestCase<whitespaceTest2> WST2;
    TestCase<whitespaceTest3> WST3;
    TestCase<operatorTest1> OT1;
    TestCase<operatorTest2> OT2;
    TestCase<operatorTest3> OT3;
    TestCase<operatorTest3a> OT3a;
    TestCase<operatorTest4> OT4;
    TestCase<operatorTest5> OT5;

    // consolidate results : this should be automated
    allresults = true;
    allresults &= PT1.status();
    allresults &= PT2.status();
    allresults &= PT3.status();
    allresults &= PT4.status();
    allresults &= PT5.status();
    allresults &= PT6.status();
    allresults &= PT7.status();
    allresults &= T1.status();
    allresults &= T2.status();
    allresults &= T3.status();
    allresults &= T4.status();
    allresults &= T5.status();
    allresults &= T6.status();
    allresults &= T6a.status();
    allresults &= T7.status();
    allresults &= T8.status();
    allresults &= T8a.status();
    allresults &= T8b.status();
    allresults &= T8c.status();
    allresults &= T8d.status();
    allresults &= T8e.status();
    allresults &= T8f.status();
    allresults &= T8g.status();
    allresults &= T8h.status();
    allresults &= T9.status();
    allresults &= T9a.status();
    allresults &= T9b.status();
    allresults &= T9c.status();
    allresults &= T9d.status();
    allresults &= T9e.status();
    allresults &= T9f.status();
    allresults &= T9g.status();
    allresults &= T9h.status();
    allresults &= T10.status();
    allresults &= T10a.status();
    allresults &= T10b.status();
    allresults &= ST1.status();
    allresults &= ST2.status();
    allresults &= WST1.status();
    allresults &= WST2.status();
    allresults &= WST3.status();
    allresults &= OT1.status();
    allresults &= OT2.status();
    allresults &= OT3.status();
    allresults &= OT3a.status();
    allresults &= OT4.status();
    allresults &= OT5.status();
    return;
  }
  /** result is the overall success/failure of this suite */
  bool result() {return allresults;}
};

