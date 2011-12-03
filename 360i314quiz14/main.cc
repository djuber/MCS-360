#include "AVL_Tree.h"
#include "Red_Black_Tree.h"

using namespace std;
int main() {
  AVL_Tree<int> t;
  Red_Black_Tree<int> r;
  int a[] = { 3, 2, 1, 4, 5,
	      6, 7, 16, 15, 14,
	      13, 11, 10, 8, 9};
  const int size = 15;
  ostringstream os;
  for(int i = 0; i < size; i++){
    t.insert(a[i]);
    r.insert(a[i]);
    os<<"AVLTree"<<t.count++<<"-insert-"<<a[i]<<".dot";
    t.writeDotFile(os.str());
    os.str("");
    os<<"RedBlackTree"<<r.count++<<"-inserted-"<<a[i]<<".dot";
    r.writeDotFile(os.str());
    os.str("");
  }
  return 0;
}
