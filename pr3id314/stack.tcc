/** @file stack.tcc : implementation details of the Stack class
 */
#ifdef _STACK_H_INTERNAL_DETAILS_

template <typename t>
void Stack<t>::push(t value){
  node * n = new node();
  n->value = value;
  n->next = head;
  head = n;
}

template <typename t>
bool Stack<t>::isEmpty()
{ return head == NULL; }

template <typename t>
t Stack<t>::pop(){
  if(isEmpty())
    throw StackError();
  t r = head->value;
  node * tmp = head;
  head = head->next;
  delete tmp;
  return r;
}

template <typename t>
t Stack<t>::top(){
  if(isEmpty())
    throw StackError();
  return head->value;
}

template <typename t>
Stack<t>::~Stack(){
  while(!isEmpty())
    pop();
}



#endif
