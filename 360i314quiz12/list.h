/** @file list.h
    @author Daniel Uber
    @brief Linked List Interface
*/
#ifndef _LIST_H_
#define _LIST_H_

struct Node {
  int x;
  Node * next;
};

struct EmptyList {};

class List{
public:
  List();
  ~List();
  List& operator=(const List &rhs);
  List(const Node * &rhs);
  List(const List &rhs);
  bool isEmpty();
  // this should really just produce a string,
  // not decide where to send it
  void printList();
  void insertFront(int x);
  void deleteFront();
  int getFront();
  void reverse();
private:
  Node * list;
};


#endif
