/** @file list2.cc
    @author Daniel Uber
    @brief Singly linked list implementation with header node
    MCS 360 Quiz 12
*/

#include "list.h"
#include <iostream>

using namespace std;

List::List() {
  list = new Node();
  list->next=NULL;
}

List::~List() {
  while(!isEmpty())
    deleteFront();
  delete list;
}

inline bool List::isEmpty(){
  return !(list->next);
}

void List::printList(){
  Node * t = list->next;
  while(t){
    cout<<t->x<<" ";
    t=t->next;
  }
  cout<<endl;
}

void List::insertFront(int x){
  Node * t = new Node();
  t->x = x;
  t->next = list->next;
  list->next = t;
}

void List::deleteFront(){
  if(list->next){
    Node * t = list->next;
    list->next = t->next;
    delete t;
  }
  else throw EmptyList();
}

int List::getFront(){
  if(list->next)
    return list->next->x;
  else
    throw EmptyList();
}

List& List::operator=(const List &rhs){
  if(this == &rhs) return *this;
  while(list->next)
    deleteFront();
  Node * t = rhs.list->next;
  while(t){
    insertFront(t->x);
    t=t->next;
  }
  reverse();
  return *this;
}

List::List(const List &rhs){
  Node * t = rhs.list->next;
  list = new Node();
  list->next=NULL;
  while(t){
    insertFront(t->x);
    t = t->next;
  }
  reverse();
}

List::List(const Node * &rhs){
  const Node * t = rhs;
  list = new Node();
  list->next = NULL;
  while(t){
    insertFront(t->x);
    t=t->next;
  }
  reverse();
}


void List::reverse(){
  Node * t = list->next;
  Node * u;
  list->next = NULL;
  while(t){
    insertFront(t->x);
    u = t;
    t = t->next;
    delete u;
  }
}
