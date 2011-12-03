// -*- c++ -*-
/** @file Red_Black_Tree.h
    @author Koffman and Wolfgang
    @brief Red Black Tree definition

    detailed on p 653 to 655 of KW Data Structures book
*/
#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_
#include <string>
#include <iostream>
#include <fstream>
#include "BST_With_Rotate.h"
#include "RBNode.h"

template <typename Item_Type>
class Red_Black_Tree : public BST_With_Rotate<Item_Type> {
public:
  Red_Black_Tree() : BST_With_Rotate<Item_Type>(), count(0) {}
  virtual ~Red_Black_Tree() {}
  bool insert(const Item_Type& item);
  bool erase(const Item_Type& item) {
    return erase(this->root, item);
  }
  void writeDotFile(std::string filename) const;
  int count;
private:
  static bool is_red(BTNode<Item_Type>* node);
  static void set_red(BTNode<Item_Type>*& local_root,
	       bool redness);
  void move_black_down(BTNode<Item_Type>*& local_root);
  bool insert(BTNode<Item_Type>*& local_root,
	      const Item_Type& item);
  // we don't need to erase this time
  bool erase(BTNode<Item_Type>*& local_root,
	     const Item_Type& item) {
    return true;
  }
  std::string tree2dot() const;
  std::string  tree2dot(BTNode<Item_Type>* r) const;
};

/******************************************************/
template <typename Item_Type>
bool Red_Black_Tree<Item_Type>::is_red(BTNode<Item_Type>* node) {
  RBNode<Item_Type>* RB_node =
    dynamic_cast<RBNode<Item_Type>*>(node);
  if(RB_node)
    return RB_node->is_red;
  else
    return false;
}

template <typename Item_Type>
void Red_Black_Tree<Item_Type>::set_red
(BTNode<Item_Type>*& node, bool red) {
  RBNode<Item_Type>* RB_node =
    dynamic_cast<RBNode<Item_Type>*>(node);
  if(RB_node)
    RB_node->is_red= red;
}

template <typename Item_Type>
void Red_Black_Tree<Item_Type>::move_black_down
(BTNode<Item_Type>*& local_root) {
  if(local_root && local_root->left && local_root->right){
    RBNode<Item_Type> *RB_left=
      dynamic_cast<RBNode<Item_Type>*>(local_root->left);
    RBNode<Item_Type> *RB_right=
      dynamic_cast<RBNode<Item_Type>*>(local_root->right);
    if(RB_left->is_red && RB_right->is_red){
      set_red(local_root->left, false);
      set_red(local_root->right, false);
      set_red(local_root, true);
    }
  }
}

// p 653
template <typename Item_Type>
bool Red_Black_Tree<Item_Type>::insert
(const Item_Type& item) {
  if(this->root == NULL) {
    RBNode<Item_Type>* new_root = new RBNode<Item_Type>(item);
    new_root->is_red = false;
    this->root = new_root;
    return true;
  } else {
    bool return_value = insert(this->root, item);
    set_red(this->root, false);
    return return_value;
  }
}

// p 653-654, note, header avoids passing any NULL
// pointers into this function
// the balancing is fairly heavy lifting.
template <typename Item_Type>
bool Red_Black_Tree<Item_Type>::insert
(BTNode<Item_Type>*& local_root,
 const Item_Type& item) {
  std::ostringstream hn;
  if(item < local_root->data){
    if(local_root->left == NULL) {
      local_root->left = new RBNode<Item_Type>(item);
      // write dot file here? No
      // hn<<"RedBlackTree"<<count++<<"-insert-"<<local_root->data<<".dot";
      // writeDotFile(hn.str());
      // hn.str("");
      return true;
    } else {
      // check for two red children, swap colors if found
      move_black_down(local_root);
      //recursively insert into the left subtree
      bool return_value = insert(local_root->left, item);
      if(is_red(local_root->left)) {
	if(is_red(local_root->left->left)){
	  // child and left-left grandchild are both red
	  // Need to change colors and rotate
	  set_red(local_root->left, false);
	  set_red(local_root, true);
	  // write dot file here
	  hn<<"RedBlackTree"<<count++<<"-right-"<<local_root->data<<".dot";
	  writeDotFile(hn.str());
	  hn.str("");
	  rotate_right(local_root);
	  return return_value;
	} else if(is_red(local_root->left->right)) {
	  // This will require a double rotation
	  set_red(local_root->left->right,false);
	  set_red(local_root, true);
	  // write dot file here?
	  hn<<"RedBlackTree"<<count++<<"-left-"<<local_root->data<<".dot";
	  writeDotFile(hn.str());
	  hn.str("");
	  rotate_left(local_root->left);
	  // and here?
	  hn<<"RedBlackTree"<<count++<<"-right-"<<local_root->data<<".dot";
	  writeDotFile(hn.str());
	  hn.str("");
	  rotate_right(local_root);
	  return return_value;
	}
      }
    }
  } // if insert left side
  else if (local_root->data < item) {
   if(local_root->right == NULL) {
      local_root->right = new RBNode<Item_Type>(item);
      // write dot file here? No...
      // hn<<"RedBlackTree"<<count++<<"-insert-"<<local_root->data<<".dot";
      // writeDotFile(hn.str());
      // hn.str("");
      return true;
    } else {
      // check for two red children, swap colors if found
      move_black_down(local_root);
      //recursively insert into the left subtree
      bool return_value = insert(local_root->right, item);
      if(is_red(local_root->right)) {
	if(is_red(local_root->right->right)){
	  // child and right-right grandchild are both red
	  // Need to change colors and rotate
	  set_red(local_root->right, false);
	  set_red(local_root, true);
	  // write dot file here?
	  hn<<"RedBlackTree"<<count++<<"-left-"<<local_root->data<<".dot";
	  writeDotFile(hn.str());
	  hn.str("");
	  rotate_left(local_root);
	  return return_value;
	} else if(is_red(local_root->right->left)) {
	  // This will require a double rotation
	  set_red(local_root->right->left,false);
	  set_red(local_root, true);
	  // write dot file here?
	  hn<<"RedBlackTree"<<count++<<"-right-"<<local_root->data<<".dot";
	  writeDotFile(hn.str());
	  hn.str("");
	  rotate_right(local_root->right);
	  // write dot file here?
	  hn<<"RedBlackTree"<<count++<<"-left-"<<local_root->data<<".dot";
	  writeDotFile(hn.str());
	  hn.str("");
	  rotate_left(local_root);
	  return return_value;
	}
      }
   }
  } else { //already present
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
std::string Red_Black_Tree<Item_Type>::tree2dot(BTNode<Item_Type>* r)
const {
  std::ostringstream out;
  // draw left edges, then left subtree's edges
  if(r->left){
    out<<"\""<<r->data<<"\"->\""
       <<r->left->data
       <<"\" [color=\"blue\"] \n";
    out<<tree2dot(dynamic_cast<RBNode<Item_Type>*>(r->left));
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
    out<<tree2dot(dynamic_cast<RBNode<Item_Type>*>(r->right));
  } else { //optional
    out<<"\""<<r->data<<"\"->\"R"
       <<r->data<<"\" [style=\"invis\"]\n";
    out<<"\"R"<<r->data
       <<"\" [style=\"invis\"]\n";
  }
  if((dynamic_cast<RBNode<Item_Type>*>(r))->is_red) // make red nodes red
    out<<"\""<<r->data<<"\" [color=\"red\"]\n";
  else
    out<<"\""<<r->data<<"\" [color=\"black\"]\n";
  return out.str();
}

/** tree2dot generates a digraph for a dot file
    describing the tree. Blue links are left, red links are
    right, and all nodes of a given depth will be level.
*/
template <typename Item_Type>
std::string Red_Black_Tree<Item_Type>::tree2dot() const {
  std::ostringstream out;
  out<<"digraph Tree {\n";
  out<<"//blue is a left link, red is a right link\n";
  if(this->root && (this->root->left || this->root->right))
    out<<tree2dot(dynamic_cast<RBNode<Item_Type>*>(this->root));
  else if (this->root){ // singleton tree : will be black
    out<<this->root->data<<"\n";
  }
  out<<"}\n";
  return out.str();
}

/** writeDotFile generates a file for graphviz/dot family
    of tools with the given filename
*/
template<typename Item_Type>
void Red_Black_Tree<Item_Type>::writeDotFile(std::string filename) const {
  std::ofstream outfile;
  outfile.open(filename.c_str());
  if(!outfile) throw std::ofstream::failure("Error Opening");
  outfile<<tree2dot();
  outfile.close();
}



#endif
