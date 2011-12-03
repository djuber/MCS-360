/** @file list.cc
    @author Daniel Uber
    @brief Singly linked list implementation
    MCS 360 Quiz 12
*/

#include "list.h"
#include <iostream>

using namespace std;

List::List() : list(NULL) {}

List::~List() {
  while(!isEmpty())
    deleteFront();
}

inline bool List::isEmpty(){
  return !list;
}

void List::printList(){
  Node * t = list;
  while(t){
    cout<<t->x<<" ";
    t=t->next;
  }
  cout<<endl;
}

void List::insertFront(int x){
  Node * t = new Node();
  t->x = x;
  t->next = list;
  list = t;
}

void List::deleteFront(){
  if(list){
    Node * t = list;
    list = t->next;
    delete t;
  }
  else throw EmptyList();
}

int List::getFront(){
  if(list)
    return list->x;
  else
    throw EmptyList();
}

List& List::operator=(const List &rhs){
  if(this == &rhs) return *this;
  while(list)
    deleteFront();
  Node * t = rhs.list;
  while(t){
    insertFront(t->x);
    t=t->next;
  }
  reverse();
  return *this;
}

List::List(const List &rhs){
  Node * t = rhs.list;
  list = NULL;
  while(t){
    insertFront(t->x);
    t=t->next;
  }
  reverse();
}

List::List(const Node * &rhs){
  const Node * t = rhs;
  list = NULL;
  while(t){
    insertFront(t->x);
    t=t->next;
  }
  reverse();
}


void List::reverse(){
  Node * t = list;
  Node * u;
  list = NULL;
  while(t){
    insertFront(t->x);
    u = t;
    t = t->next;
    delete u;
  }
}
