/** @file list.h
    @author Daniel Uber
    @brief linked list definition
    MCS 360 Week 8 Quiz
*/

#ifndef _LIST_H_
#define _LIST_H_
// added to fix issues with order of inclusion
#include <iostream>

template <class Object>
class List;

template <class Object>
class ListItr;

/* modified to remove header, and pretend it's still there */
template <class Object>
class List{
  /* ListNode is now a private inner struct */
  struct ListNode{
    ListNode(const Object & Element = Object(), ListNode * Next = NULL)
      : element(Element), next(Next) {}
    Object element;
    ListNode * next;
  };
  ListNode *header;
  const Object Default;
 public:
  List();
  List(const List & rhs);
  ~List();
  bool isEmpty() const;
  void makeEmpty();
  ListItr<Object> zeroth() const;
  ListItr<Object> first() const;
  void insert(const Object & x, const ListItr<Object> &p);
  ListItr<Object> find(const Object &x) const;
  ListItr<Object> findPrevious(const Object &x) const;
  void remove(const Object & x);
  const List & operator= (const List  & rhs);
  friend class ListItr<Object>;
};

/** modified to allow dummy node behavior (zeroth)
    actually throw BadIterator()
*/
template <class Object>
class ListItr{
  friend class List<Object>;
public:
  class BadIterator{};
  ListItr() : current( NULL ) {}
  bool isPastEnd() const { return current == NULL;}
  void advance(){
    /* if it was a header,
       then now it isn't,
       and ask the list for first
    */
    if(header) {
      header = false;
      *this = (*listptr).first();
      return;
    }
    if(!isPastEnd())
      current = current->next;
  }
  const Object & retrieve() const throw() {
    // replicate old header node behavior
    if (header)
      return listptr->Default;
    if(isPastEnd())
      throw BadIterator();
    return current->element;
  }
 private:
  /* private portions modified to allow dummy header */
  class List<Object>::ListNode * current;
  bool header; // is the iterator a push_front itr?
  const List<Object> * listptr; // needed to advance from null header iterator
  // original constructor for real iterators
  ListItr( class List<Object>::ListNode * node )
    :current(node), header(false), listptr(NULL) { }
  // new constructor for dummy header iterator
  ListItr( class List<Object>::ListNode * node ,
	   bool head, const List<Object> * list)
    :current(node), header(head), listptr(list) { }
};

// guard against compiling what looks like source code.
#define _LIST_H_INTERNAL_
#include "list.cc"
#undef _LIST_H_INTERNAL_

#endif
