#include "list.h"


int main(){
  List l1;
  for(int i = 0; i < 10; i++)
    l1.insertFront(i);
  l1.printList();
  List l2=l1; // copy constructor
  for(int i = 0; i < 5; i++)
    l2.deleteFront();
  l1.printList(); // should be 2 1
  l2.printList(); // should be 1
  l1=l2; // assignment operator
  l1.printList();
  return 0;
}
