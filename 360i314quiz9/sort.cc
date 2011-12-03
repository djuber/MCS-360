/** @file : isort2.cc
    @author Daniel Uber
*/

#include <iostream> // for std::cout
#include <cstdlib> // for rand()
#include <ctime> // for clock
#include <sys/resource.h> // for rlimit

/** singly linked list node structure
*/
struct node {
  int value;
  node * next;
  node(int v) : value(v), next(NULL) {}
};
typedef node * list;

/** insert a single node in order
    walk forward until either it's time
    to put the item in the list
    or you've reached the end
 */
list insert(list &List, node * t){
  list head = List;
  list prev = NULL;
  while(head && t->value > head->value){
    prev = head;
    head = head->next;
  }
  if(prev){
    prev->next = t;
    t->next = head;
  }
  else {
    t->next = head;
    List = t;
  }
  return List;
}

/** insert a number into a list
 */
list insert(list &List, int v){
  return List = insert(List, new node(v));
}

/** print items in the list one at a time
    then a newline.
*/
void print(list List){
  while(List){
    std::cout<<List->value<<" ";
    List = List->next;
  }
  std::cout<<"\n";
}

/** insertion sort
    a list of one item is sorted
    in this case we recursively sort the tail first
    and insert in order the node at the head
*/
list isortList(list &List){
  if(!(List && List->next))
    return List;
  //sort tail
  List->next = isortList(List->next);
  // find a place for head
  list tmp = new node(List->value);
  list tmp2 = List->next;
  delete List;
  List = insert(tmp2, tmp);
  return List;
}

/** free all memory in nodes */
void empty(list &l){
  while(l){
    node * tmp = l;
    l = l->next;
    delete tmp;
  }
  return;
}

/** add a number to the head of the list */
list push_front(list &List, int v){
  list tmp = new node(v);
  tmp->next = List;
  return List = tmp;
}

/** destructively reverse list
    this recycles cells
    used in merge
*/
list nreverse(list &L){
  list result = NULL;
  list t;
  while(L){
    t = L;
    L=L->next;
    push_front(result, t->value);
    delete t;
  }
  return L=result;
}

/** merge: given two sorted lists
    return a sorted list of the elements of both lists
    ! this is a terrible idea if these share structure !
*/
list merge(list L1, list L2){
  list t1 = L1;
  list t2 = L2;
  list t3 = NULL;
  // we'll add these reversed first, then flip at the end
  list result = NULL;
  if(!L1)
    return L2;
  if(!L2)
    return L1;
  while(t1 && t2)
    if(t2->value > t1->value){
      t3 = t1;
      t1 = t1->next;
      push_front(result, t3->value);
      delete t3;
    } else {
      t3 = t2;
      t2 = t2->next;
      push_front(result, t3->value);
      delete t3;
    }
  while(t1){
    t3 = t1;
    t1 = t1->next;
    push_front(result, t3->value);
    delete t3;
  }
  while(t2){
    t3 = t2;
    t2 = t2->next;
    push_front(result, t3->value);
    delete t3;
  }
  // reverse result and return
  return nreverse(result);
}

/* return second part, modify first part */
list split(list List){
  list t= List;
  list u = List;
  while(u && u->next && u->next->next){
    t = t -> next;
    u = u->next->next;
  }
  u = t->next;
  t->next = NULL;
  return u;
}

/** mergesort:
    a singleton is sorted,
    otherwise split and merge the sorted sublists
*/
list mergesort(list &List){
  if(List && List->next){
    list t = List;
    list u = split(t);
    t = mergesort(t);
    u = mergesort(u);
    List = merge(t,u);
  }
  return List;
}

/** test the functions above */
int main(){
  clock_t time;
  list List = NULL;
  int lim = 1;
  // rlimit limit;
  // getrlimit(RLIMIT_STACK, &limit);
  // limit.rlim_cur=limit.rlim_max;
  // setrlimit(RLIMIT_STACK, &limit);
  for(int p = 0; p < 20; p++){
    for(int i = 0; i < lim; i++)
      push_front(List, rand() % (2*i + 1));
    time = clock();
    isortList(List);
    time = clock() - time;
    // see time(3): POSIX requires 1000000 CLOCKS_PER_SEC
    std::cout<<"for "<<lim<<" elements isort took "<<time
	     <<" microseconds.\n";
    empty(List);
    List=NULL;
    // mergesort now
   for(int i = 0; i < lim; i++)
      push_front(List, rand() % (2*i + 1));
    time = clock();
    mergesort(List);
    time = clock() - time;
    // see time(3): POSIX requires 1000000 CLOCKS_PER_SEC
    std::cout<<"for "<<lim<<" elements msort took "<<time
	     <<" microseconds.\n";
    empty(List);
    List=NULL;
    lim *= 2;
  }
  return 0;
}
