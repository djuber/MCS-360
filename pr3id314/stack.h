/** @file stack.h
    @brief definition of stack class
    @author Daniel Uber
*/
#ifndef _STACK_H_
#define _STACK_H_

/** class StackError
    @brief an exception thrown on underflow
*/
class StackError {};

// bare minumum stack type
/** class Stack<t>
    @tparam t : content type
    @brief use a singly linked list to support stack
    operations
*/
template <typename t> class Stack {

  struct node {
    t value;
    node * next;
  };

  node * head;

public:

  Stack() : head(NULL) {}

  ~Stack();
  /** isEmpty returns true if there are no items in the stack */
  bool isEmpty();
  /** push puts an item at the top of the stack */
  void push(t value);
  /** pop removes the top item */
  t pop();
  /** top returns the top item */
  t top();
};

#define _STACK_H_INTERNAL_DETAILS_
#include "stack.tcc"
#undef _STACK_H_INTERNAL_DETAILS_


#endif
