// -*- c++ -*-
/** @file Binary_Tree.h
    @author Koffman and Wolfgang
    @brief class for a binary tree

    detailed on pp 460-461 of Data Structures book
*/

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include "BTNode.h"

template<typename Item_Type>
class Binary_Tree {
public:
  /** construct an empty tree */
  Binary_Tree() : root(NULL) {}
  /** construct a tree with two subtrees.
      @param the_data The data at the root node.
      @param left_child The left subtree
      @param right_child The right subtree
  */
  Binary_Tree(const Item_Type& the_data,
	      const Binary_Tree<Item_Type>& left_child = Binary_Tree(),
	      const Binary_Tree<Item_Type>& right_child = Binary_Tree()) :
    root(new BTNode<Item_Type>(the_data,
			       left_child.root,
			       right_child.root)) {}
  /** virtual destructor to avoid warnings */
  virtual ~Binary_Tree() {} //Do Nothing
  /** return the left subtree */
  Binary_Tree<Item_Type> get_left_subtree() const;
  /** return the right subtree */
  Binary_Tree<Item_Type> get_right_subtree() const;
  /** return the data field of the root */
  const Item_Type& get_data() const;
  /** Indicate that this is the empty tree */
  bool is_null() const;
  /** Indicate that this is a leaf */
  bool is_leaf() const;
  /** return a string representation of the tree */
  virtual std::string to_string() const;
  /** read a binary tree from stream */
  static Binary_Tree<Item_Type> read_binary_tree(std::istream& in);
protected:
  /** construct a binary tree with given node as root */
  Binary_Tree(BTNode<Item_Type>* new_root) : root(new_root) {}
  // data field
  BTNode<Item_Type>* root;
};

template<typename Item_Type>
std::ostream& operator<<(std::ostream& out,
			 const Binary_Tree<Item_Type>& tree) {
  return out<< tree.to_string();
}

template<typename Item_Type>
std::istream& operator>>(std::istream& in,
			 const Binary_Tree<Item_Type>& tree){
  tree = Binary_Tree<Item_Type>::read_binary_tree(in);
  return in;
}

template <typename Item_Type>
const Item_Type&
Binary_Tree<Item_Type>::get_data() const {
  if(!root)
    throw std::invalid_argument("get_data on empty tree");
  else
    return root->data;
}

template <typename Item_Type>
Binary_Tree<Item_Type>
Binary_Tree<Item_Type>::get_left_subtree() const {
  if(!root)
    throw std::invalid_argument("get_left_subtree on empty tree");
  return Binary_Tree<Item_Type>(root->left);
}

template <typename Item_Type>
Binary_Tree<Item_Type>
Binary_Tree<Item_Type>::get_right_subtree() const {
  if(!root)
    throw std::invalid_argument("get_right_subtree on empty tree");
  return Binary_Tree<Item_Type>(root->right);
}

template<typename Item_Type>
bool Binary_Tree<Item_Type>::is_leaf() const {
  if (root)
    return !(root->left || root->right);
  else
    return true;
}

template<typename Item_Type>
bool Binary_Tree<Item_Type>::is_null() const {
  return !root;
}

template<typename Item_Type>
std::string Binary_Tree<Item_Type>::to_string() const {
  // preorder traversal one node per line
  // all non-null nodes have two children each.
  std::ostringstream os;
  if(is_null())
    os<<"NULL\n";
  else {
    os << *root << '\n';
    os << get_left_subtree().to_string();
    os << get_right_subtree().to_string();
  }
  return os.str();
}

template <typename Item_Type>
Binary_Tree<Item_Type>
Binary_Tree<Item_Type>::read_binary_tree(std::istream& in){
  std::string line;
  getline(in, line);
  if(line=="NULL"){
    return Binary_Tree<Item_Type>();
  } else {
    Item_Type the_data;
    std::istringstream ins(line);
    ins >> the_data;
    Binary_Tree<Item_Type> left = read_binary_tree(in);
    Binary_Tree<Item_Type> right = read_binary_tree(in);
    return Binary_Tree(the_data, left, right);
  }
}

#endif
