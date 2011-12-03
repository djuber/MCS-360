// stack.h
// declare a stack type
#ifndef _STACK_H_
#define _STACK_H_

template <class T> struct node{
  T value;
  node<T> * next;
};

template <class T> class stack{
 public:
  T top();
  void pop();
  void push(T val);
  bool empty();
  stack();
  ~stack();
  class underflow{};
 private:
  node<T> * head;
};

// Now I need a source file in my include directory.
// really not that useful. Guard against inadvisable use
#define _STACK_H_INTERNAL_
#include "stack.cc"
// clear the guard
#undef _STACK_H_INTERNAL_

#endif

