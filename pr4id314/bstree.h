/** @file bstree.h
    @author Daniel Uber
    @brief Binary Search Tree
*/
#ifndef BSTREE_H
#define BSTREE_H
#include <string>
#include <iostream>
/** @class BinarySearchTree
    @brief Hold integers, support insert, remove, find,
    and display.
*/
class BinarySearchTree{
  /** @class Node
      @brief Hold an int and two pointers
      leaf is simple a predicate.
  */
protected:
  struct Node{
    /** the data payload, an integer */
    int data;
    /** left points to a subtree with all elements
	less than data */
    Node * left;
    /** right points to a subtree with all elements
	greater than data */
    Node * right;
    Node() : data(0), left(0), right(0) {}
    /** leaf: true if node has no children */
    bool leaf(){return right==0 && left == 0;}
  };
  /** root holds the tree nodes */
  Node * root;
  Node * findNode(int data);
  void insert(int data, Node * &r);
  void insert(Node * &to, Node * &from);
  void remove(int data, Node * &r);
  void display(std::ostream &os, Node *r);
  std::string tree2dot();
  std::string tree2dot(Node * r);
  int count() const;
  int count(Node * r) const;
  int deepest() const;
  int deepest(Node * r) const;
  int shallowest() const;
  int shallowest(Node * r) const;
  int minimum() const;
  int minimum(Node * r) const;
  int maximum() const;
  int maximum(Node *r) const;
public:
  BinarySearchTree() : root(0) {};
  ~BinarySearchTree();
  void insert(int data);
  void remove(int data);
  bool find(int data);
  void display(std::ostream &os);
  void summary(std::ostream &os);
  void writeDotFile(std::string filename);
};

#endif
