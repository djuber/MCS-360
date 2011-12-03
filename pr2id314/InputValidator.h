/** @file InputValidator.h
    @author Daniel Uber
    @brief A templated type validator from cin/cout
*/
#ifndef _INPUT_VALIDATOR_H_
#define _INPUT_VALIDATOR_H_
// recycled from project 1

#include <iostream>
#include <string>

// T must implement <, see <T,C>InputValidator
// also do not use for strings. Use charbuf instead.

/** @class InputValidator

    @tparam T is the type of input to look for

    T must provide the equality operator
    This is error prone with doubles so some
    external checks are in order

*/

template <typename T> class InputValidator{
  T response;
public:
  /** input() presents a prompt and returns response.
      @brief checks that response was received from cin.
      @param prompt is a string to present before reading
      @return response
  */
  T input(std::string prompt) {
    std::cin.clear();
    std::cout<<prompt;
    std::cin>>response;
    if(std::cin.fail())
      return input(prompt);
    else
      return response;
  }

  /** guardedInput presents a prompt and ensures some new
      information was given. Allows a custom reprompt.

      @param prompt is the string to present prior to input
      @param reprompt is a corrective hint
      @param guard is a known bad value that should not be set
      @post response is not guard.
      @return response
  */
  T guardedInput(std::string prompt, std::string reprompt, T guard){
    response = guard;
    while(response==guard){
      std::cout<<prompt;
      std::cin>>response;
      if(std::cin.fail()){
	std::cout<<reprompt;
	response=guard;
	std::cin.clear();
	std::cin.ignore(100,'\n');
      }
    }
    return response;
  }
};

#endif
