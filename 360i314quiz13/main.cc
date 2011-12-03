//main.cpp
//for testing class Tree
#include <iostream>
#include "tree.h"
using namespace std;
int main(){
    Tree T;
     T.insert(50, 5.0);
     T.insert(25,2.5);
     T.insert(75,7.5);
     T.insert(12,1.2);
     T.insert(37,3.7);
     T.insert(43,4.3);
     T.insert(30,3.0);
     T.insert(33,3.3);
     T.insert(87,8.7);
     T.insert(93,9.3);
     T.insert(97,9.7);
     T.displayTree();

     T.traverse(PREORDER);
     T.traverse(INORDER);
     T.traverse(POSTORDER);
     T.remove(50);
     T.displayTree();
     T.remove(25);
     T.displayTree();
     T.remove(37);
     T.displayTree();
     cout << endl;
     cout << endl;

     return 0;
}
