/** @file AVLTree.cc
    @author Daniel Uber
    @brief an AVL tree implementation adapted from Binary
    Search Tree used in project 4.
*/
#include <iostream>
#include "bstree.h"

/** AVLTree is a self balancing search tree
    we use the AVL algorithm for balancing. To wit,
    insert will inspect the count of the node on the return
    and balance as necessary. The count field has been added to
    AVLNode, which could have inherited from BSTNode.
*/
class AVLTree : public BinarySearchTree {
  using std::ostream;
  AVLNode *root;
protected:
  /** an AVLNode is a simple Binary Tree Node.
      We will implement the tree as a binary search tree.
      Additionally, insert() will balance along the way up.
  */
  struct AVLNode : public BinarySearchTree::Node{
    int count; // the balance of this node, may be -2 to +2
    AVLNode() : count(0) {}
  }

public:
  AVLTree() : root(NULL) {}
  ~AVLTree();
  // BinarySearchTree definition in bstree.h:
  //   Node * findNode(int data);
  //   void insert(int data, Node * &r);
  //   void insert(Node * &to, Node * &from);
  //   void remove(int data, Node * &r);
  //   void display(std::ostream &os, Node *r);
  //   void writeTree(std::ostream &os, Node * r, int depth);
  //   std::string tree2dot();
  //   std::string tree2dot(Node * r);
  //   int count() const;
  //   int count(Node * r) const;
  //   int deepest() const;
  //   int deepest(Node * r) const;
  //   int shallowest() const;
  //   int shallowest(Node * r) const;
  //   int minimum() const;
  //   int minimum(Node * r) const;
  //   int maximum() const;
  //   int maximum(Node *r) const;
  // public:
  //   void insert(int data);
  //   void remove(int data);
  //   bool find(int data);
  //   void display(std::ostream &os);
  //   void writeTree(std::ostream &os);
  //   void summary(std::ostream &os);
  //   void writeDotFile(std::string filename);

};


