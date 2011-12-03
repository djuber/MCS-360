// -*- c++ -*-
/** @file BTNode.h
    @author Koffman and Wolfgang
    @brief Binary Tree Node structure

    detailed on p458 of KW Data Structures Book
*/

#ifndef BTNODE_H_
#define BTNODE_H_

/** a node for a binary tree
    in order to instantiate this,
    template parameter Item_Type must have
    the stream insertion operator defined.
*/
template <typename Item_Type>
struct BTNode {
  Item_Type data;
  BTNode<Item_Type> * left;
  BTNode<Item_Type> * right;

  BTNode(const Item_Type& the_data,
	 BTNode<Item_Type>* left_val=NULL,
	 BTNode<Item_Type>* right_val=NULL) :
    data(the_data), left(left_val), right(right_val) {}

  // virtual destructor to quiet warnings
  virtual ~BTNode() {}

  virtual std::string to_string() const {
    std::ostringstream os;
    os<<data;
    return os.str();
  }
};

template<typename Item_Type>
std::ostream& operator<<(std::ostream& out,
			 const BTNode<Item_Type>& node){
  return out<<node.to_string();
}

#endif
