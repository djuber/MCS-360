/** @file list.cc
    @author Daniel Uber
    @brief Linked List Implementation
*/

/**
    Construct the list.
    modified to put default value in place for zeroth().retrieve()
*/
template <class Object>
List<Object>::List() : Default(Object()) {
  header = NULL;
}

/**
   Test if the list is empty
*/
template <class Object>
bool List<Object>::isEmpty() const {
  return header == NULL;
}

/**
   return an iterator representing the header node
   custom constructor call to set up behavior
   flag true marks zeroth as a push_front iterator
   and a list pointer is passed to allow advance to work
*/
template <class Object>
ListItr<Object> List<Object>::zeroth() const {
  return ListItr<Object> (header, true, this);
}

/**
   Return an iterator representing the first node in the list
   This is now header rather than header->next
*/
template <class Object>
ListItr<Object> List<Object>::first() const {
  return ListItr<Object> (header);
}

/**
   Simple print function
   Doesn't need to be in here...
*/
template <class Object>
void printList(const List<Object> & list){
  if(list.isEmpty())
    std::cerr<< "Empty List\n";
  else {
    ListItr<Object> itr = list.first();
    for(; !itr.isPastEnd(); itr.advance())
      std::cout<<itr.retrieve()<<" ";
  }
  std::cout<<'\n';
}

/**
   Return iterator corresponding to the first node containing item x
   iterator isPastEnd if item is not found
*/
template <class Object>
ListItr<Object> List<Object>::find(const Object & x) const {
  ListNode *itr = first();
  while( itr != NULL && itr->element != x)
    itr = itr->next;
  return ListItr<Object>(itr);
}

/**
   Remove the first occurence of an item x
*/
template <class Object>
void List<Object>::remove(const Object & x) {
  ListItr<Object> p = findPrevious(x);
  if(p.current->next != NULL){
    ListNode *oldNode = p.current->next;
    p.current->next = p.current->next->next;
    delete oldNode;
  }
}

/**
   return iterator to node before x
   iterator is last item if not found.
*/
template <class Object>
ListItr<Object> List<Object>::findPrevious(const Object & x) const {
  ListNode *itr = header;
  while(itr != NULL && itr->next != NULL && itr->next->element != x)
    itr = itr->next;
  return ListItr<Object> (itr);
}

/**
   insert x after p
   need extra case handling here for push_front behavior
*/
template <class Object>
void List<Object>::insert(const Object & x, const ListItr<Object> & p) {
  if(p.header){
    header = new ListNode(x, header);
  }
  else if(p.current != NULL) {
    p.current->next = new ListNode(x, p.current->next);
  }
}

/**
   make the list empty
   modified for style reasons
   remove(first().retrieve()) was a little inefficient
*/
template <class Object>
void List<Object>::makeEmpty(){
  while (!isEmpty()){
    ListNode * tmp = header;
    header = header->next;
    delete tmp;
  }
}
/**
   destructor
   modified since we no longer have a header node,
   so no need to delete it. (Bad things happen if you do.
*/
template <class Object>
List<Object>::~List(){
  makeEmpty();
}

/**
   Deep copy of linked lists
*/
template <class Object>
const List<Object> & List<Object>::operator= (const List<Object> & rhs) {
  if( this != &rhs){
    makeEmpty();
    ListItr<Object> ritr = rhs.first();
    ListItr<Object> itr = zeroth();
    for(; !ritr.isPastEnd(); ritr.advance(), itr.advance())
      insert(ritr.retrieve(), itr);
  }
  return *this;
}

/**
   copy constructor
   modified to allow zeroth to print default value
*/
template <class Object>
List<Object>::List( const List<Object> & rhs)
  :Default(Object())
{
  header = NULL;
  *this = rhs;
}
