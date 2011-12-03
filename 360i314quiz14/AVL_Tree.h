// -*- c++ -*-
/** @file AVL_Tree.h
    @author Koffman and Wolfgang
    @brief AVL_Tree class definition

    detailed on p 635 of KW Data Structures book
*/

#ifndef AVL_TREE_H_
#define AVL_TREE_H_
#include <string>
#include <iostream>
#include <fstream>
#include "BST_With_Rotate.h"
#include "AVLNode.h"

/** definition of AVL Binary Search Tree class.
    @param Item_Type must define less than operator
    and stream operators.
*/
template<typename Item_Type>
class AVL_Tree : public BST_With_Rotate<Item_Type> {
public:
  /** construct an empty AVL Tree */
  AVL_Tree() : BST_With_Rotate<Item_Type>(), count(0), increase(false) {}
  /** Insert an item into this tree.
      @post the item is in the tree
      @param item the item to be inserted.
      @return true only if the item was not in the tree
  */
  virtual bool insert(const Item_Type& item) {
    return insert(this->root, item);
  }
  /** remove an item from the tree
      @post the item is no longer in the tree
      @param item the item to remove
      @return true only if the item was in the tree.
  */
  virtual bool erase(const Item_Type& item) {
    return erase(this->root, item);
  }
  void writeDotFile(std::string filename) const;
  unsigned count;
private:
  // more members needed here.
  /** Insert an item into the tree
      @post the item is in the tree
      @param local_root a reference to the current root.
      @param item the item to insert
      @return true only if the item was not already in the tree.
  */
  virtual bool insert(BTNode<Item_Type>*& local_root,
		      const Item_Type& item);
  /** rebalace_left rebalaces a left heavy tree. This can be left-left
      or left-right. If the left subtree is right heavy, we have a
      left-right case, and we rotate the left subtree left. Finally,
      rotate the tree right.
  */
  void rebalance_left(BTNode<Item_Type>*& local_root);
  /** rebalace_right rebalaces a right heavy tree. This can be right-right
      or right-left. If the right subtree is left heavy, we have a
      right-left case, and we rotate the right subtree right. Finally,
      rotate the tree left.
  */
  void rebalance_right(BTNode<Item_Type>*& local_root);
  // a flag to indicate height of the tree has increased.
  bool increase;
  // if we included removal, we would need a decrease flag as well
  // see page 642 (we only need insert and rotate/rebalance for our purposes
  std::string tree2dot() const;
  virtual bool erase(BTNode<Item_Type>*& local_root,
		     const Item_Type& item) {
    return true;
  }
  std::string  tree2dot(AVLNode<Item_Type>* r) const;
  //  static const std::string name = "AVLTree";
  // a counter for filenames during insertion

};

template <typename Item_Type>
void AVL_Tree<Item_Type>::rebalance_left
(BTNode<Item_Type>*& local_root){
  std::ostringstream hn;
  hn<<"AVLTree"<<count++<<"-before-left-"<<local_root->data<<".dot";
  writeDotFile(hn.str());
  // cast local_root to an AVL_Tree pointer
  AVLNode<Item_Type>* AVL_local_root =
    dynamic_cast<AVLNode<Item_Type>*>(local_root);
  // obtain reference to the left child
  AVLNode<Item_Type>* left_child =
    dynamic_cast<AVLNode<Item_Type>*>(local_root->left);
  // see whether left-right heavy
  if(left_child->balance == AVLNode<Item_Type>::RIGHT_HEAVY){
    // Obtain a reference to the left-right child
    AVLNode<Item_Type>* left_right_child =
      dynamic_cast<AVLNode<Item_Type>*>(left_child->right);
    // adjust the balances to be the new values after rotations
    // are performed
    if(left_right_child->balance == AVLNode<Item_Type>::LEFT_HEAVY){
      left_child->balance = AVLNode<Item_Type>::BALANCED;
      left_right_child->balance = AVLNode<Item_Type>::BALANCED;
      AVL_local_root->balance = AVLNode<Item_Type>::RIGHT_HEAVY;
    } else if (left_right_child->balance ==
	       AVLNode<Item_Type>::BALANCED){
      left_child->balance = AVLNode<Item_Type>::BALANCED;
      AVL_local_root->balance = AVLNode<Item_Type>::BALANCED;
    } else {
      left_child->balance = AVLNode<Item_Type>::LEFT_HEAVY;
      left_right_child->balance = AVLNode<Item_Type>::BALANCED;
      AVL_local_root->balance = AVLNode<Item_Type>::BALANCED;
    }
    std::ostringstream fn;
    fn<<"AVLTree"<<count++<<"-left-"<<local_root->left->data<<".dot";
    rotate_left(local_root->left);
    writeDotFile(fn.str());
  } else { // left-left case
    /* in this case the left child (new root) and the local root
       (new right child) will both be balanced after the rotation.
    */
    left_child->balance = AVLNode<Item_Type>::BALANCED;
    AVL_local_root->balance = AVLNode<Item_Type>::BALANCED;
  }

  //  std::ostringstream gn;
  // gn<<"AVLTree"<<count++<<"-right-"<<local_root->data<<".dot";
  rotate_right(local_root);
  // this will be identical to insert() or before()
  //  writeDotFile(gn.str());
}


template <typename Item_Type>
void AVL_Tree<Item_Type>::rebalance_right
(BTNode<Item_Type>*& local_root){
  std::ostringstream hn;
  hn<<"AVLTree"<<count++<<"-before-right-"<<local_root->data<<".dot";
  writeDotFile(hn.str());
  // cast local_root to an AVL_Tree pointer
  AVLNode<Item_Type>* AVL_local_root =
    dynamic_cast<AVLNode<Item_Type>*>(local_root);
  // obtain reference to the right child
  AVLNode<Item_Type>* right_child =
    dynamic_cast<AVLNode<Item_Type>*>(local_root->right);
  // see whether right-left heavy
  if(right_child->balance == AVLNode<Item_Type>::LEFT_HEAVY){
    // Obtain a reference to the right-left child
    AVLNode<Item_Type>* right_left_child =
      dynamic_cast<AVLNode<Item_Type>*>(right_child->left);
    // adjust the balances to be the new values after rotations
    // are performed
    if(right_left_child->balance == AVLNode<Item_Type>::RIGHT_HEAVY){
      right_child->balance = AVLNode<Item_Type>::BALANCED;
      right_left_child->balance = AVLNode<Item_Type>::BALANCED;
      AVL_local_root->balance = AVLNode<Item_Type>::LEFT_HEAVY;
    } else if (right_left_child->balance ==
	       AVLNode<Item_Type>::BALANCED){
      right_child->balance = AVLNode<Item_Type>::BALANCED;
      AVL_local_root->balance = AVLNode<Item_Type>::BALANCED;
    } else {
      right_child->balance = AVLNode<Item_Type>::RIGHT_HEAVY;
      right_left_child->balance = AVLNode<Item_Type>::BALANCED;
      AVL_local_root->balance = AVLNode<Item_Type>::BALANCED;
    }
    std::ostringstream fn;
    fn<<"AVLTree"<<count++<<"-right-"<<local_root->right->data<<".dot";
    rotate_right(local_root->right);
    writeDotFile(fn.str());
  } else { // right-right case
    /* in this case the right child (new root) and the local root
       (new left child) will both be balanced after the rotation.
    */
    right_child->balance = AVLNode<Item_Type>::BALANCED;
    AVL_local_root->balance = AVLNode<Item_Type>::BALANCED;
  }
  //  std::ostringstream gn;
  // gn<<"AVLTree"<<count++<<"-left-"<<local_root->data<<".dot";
  rotate_left(local_root);

  // this will be identical to insert(data) and can be suppressed.
  //  writeDotFile(gn.str());

}


//implementation of functions
template <typename Item_Type>
bool AVL_Tree<Item_Type>::insert(BTNode<Item_Type>*& local_root,
				 const Item_Type& item) {
  if(!local_root){
    local_root = new AVLNode<Item_Type>(item);
    increase = true;
    return true;
  }
  if(item < local_root->data) {
    bool return_value = insert(local_root->left, item);
    if(increase) {
      AVLNode<Item_Type>* AVL_local_root =
	dynamic_cast<AVLNode<Item_Type>*>(local_root);
      switch(AVL_local_root->balance){
      case AVLNode<Item_Type>::BALANCED :
	AVL_local_root->balance = AVLNode<Item_Type>::LEFT_HEAVY;
	break;
      case AVLNode<Item_Type>::RIGHT_HEAVY :
	AVL_local_root->balance = AVLNode<Item_Type>::BALANCED;
	increase = false;
	break;
      case AVLNode<Item_Type>::LEFT_HEAVY :
	rebalance_left(local_root);
	increase = false;
	break;
      }
    }
    return return_value;
  } else if (local_root->data < item) {
    bool return_value = insert(local_root->right, item);
    if(increase) {
      AVLNode<Item_Type>* AVL_local_root =
	dynamic_cast<AVLNode<Item_Type>*>(local_root);
      switch(AVL_local_root->balance){
      case AVLNode<Item_Type>::BALANCED :
	AVL_local_root->balance = AVLNode<Item_Type>::RIGHT_HEAVY;
	break;
      case AVLNode<Item_Type>::LEFT_HEAVY :
	AVL_local_root->balance = AVLNode<Item_Type>::BALANCED;
	increase = false;
	break;
      case AVLNode<Item_Type>::RIGHT_HEAVY :
	rebalance_right(local_root);
	increase = false;
	break;
      }
    }
    return return_value;
  } else {
    increase = false;
    return false;
  }
}


/** tree2dot generates edge information for this subtree
    if a link is not present, a dummy node (invisible)
    is added to help graphviz find the right balance

    This is partially successful, remove optional else
    clauses if desired.
    Note: all the quoting is to ensure proper processing of negative
    values. This was a problem where items like
    -1->L-1 would do bad things.
*/
template<typename Item_Type>
std::string AVL_Tree<Item_Type>::tree2dot(AVLNode<Item_Type>* r) const {
  std::ostringstream out;
  // draw left edges, then left subtree's edges
  if(r->left){
    out<<"\""<<r->data<<"\"->\""
       <<r->left->data
       <<"\" [color=\"blue\"] \n";
    out<<tree2dot(dynamic_cast<AVLNode<Item_Type>*>(r->left));
  } else { // optional
    out<<"\""<<r->data<<"\"->\"L"
       <<r->data<<"\" [style=\"invis\"]\n";
    out<<"\"L"<<r->data
       <<"\" [style=\"invis\"]\n";
  }
  // now draw right edges, ...
  if(r->right){
    out<<"\""<<r->data<<"\"->\""
       <<r->right->data
       <<"\" [color=\"red\"]\n";
    out<<tree2dot(dynamic_cast<AVLNode<Item_Type>*>(r->right));
  } else { //optional
    out<<"\""<<r->data<<"\"->\"R"
       <<r->data<<"\" [style=\"invis\"]\n";
    out<<"\"R"<<r->data
       <<"\" [style=\"invis\"]\n";
  }
  return out.str();
}

/** tree2dot generates a digraph for a dot file
    describing the tree. Blue links are left, red links are
    right, and all nodes of a given depth will be level.
*/
template <typename Item_Type>
std::string AVL_Tree<Item_Type>::tree2dot() const {
  std::ostringstream out;
  out<<"digraph Tree {\n";
  out<<"//blue is a left link, red is a right link\n";
  if(this->root && (this->root->left || this->root->right))
    out<<tree2dot(dynamic_cast<AVLNode<Item_Type>*>(this->root));
  else if (this->root){ // singleton tree
    out<<this->root->data<<"\n";
  }
  out<<"}\n";
  return out.str();
}

/** writeDotFile generates a file for graphviz/dot family
    of tools with the given filename
*/
template<typename Item_Type>
void AVL_Tree<Item_Type>::writeDotFile(std::string filename) const {
  std::ofstream outfile;
  outfile.open(filename.c_str());
  if(!outfile) throw std::ofstream::failure("Error Opening");
  outfile<<tree2dot();
  outfile.close();
}






#endif
