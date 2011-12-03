// stack.cc
// included from stack.h, not a real source file, don't compile me!
// this file is empty if not inside stack.h
#ifdef _STACK_H_INTERNAL_

template<class T>
stack<T>::stack(){
  head=NULL;
}

template<class T> T stack<T>::top(){
  if(head)
    return head->value;
  else
    throw new underflow;
}

template<class T>
void stack<T>::pop(){
  node<T> *tmp;
  tmp = head;
  if(tmp){
    head = head->next;
    delete tmp;
    return;
  }
  else{
    throw new underflow();
  }
}

template<class T>
void stack<T>::push(T val){
  node<T> *tmp = new node<T>;
  tmp->next = head;
  tmp->value = val;
  head = tmp;
  return;
}

template<class T>
bool stack<T>::empty(){
  return !head;
}

// nead a destructor or it will leak at exit.
template<class T>
stack<T>::~stack(){
  while(head){
    pop();
  }
}
#endif
