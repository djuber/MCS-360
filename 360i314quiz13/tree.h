/** @file tree.h
    @brief Binary Search Tree
*/

#include <iostream>
#include <stack>
#ifndef TREE_H
#define TREE_H

// not sure this belongs in a header file
using namespace std;

enum traverseType{PREORDER,INORDER,POSTORDER};

struct Node {
  int i;
  double d;
  Node * pL;
  Node * pR;
  Node() :i(0), d(0.0), pL(NULL), pR(NULL) {}
  ~Node(){ cout << "X- "<<i<<" ";}
  void displayNode(){
    cout<<"{"<<i<<","<<d<<"} ";
  }
};

class Tree{
public:
  Tree() : pRoot(NULL){}
  ~Tree() {destroy();}
  Node *find(int key);
  void insert(int id, double dd);
  // use of magic int's was bothersome
  void traverse(traverseType t);
  void displayTree();
  void remove(int key);
private:
  Node* pRoot;
  void preOrder(Node* pLocalRoot);
  void inOrder(Node* pLocalRoot);
  void postOrder(Node* pLocalRoot);
  void destroy();
  void destroyRec(Node *pLocalRoot);
  void insert(Node * &to, Node * &from);
  Node *findParent(Node *t);
};
#endif
