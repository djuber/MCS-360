// -*- c++ -*-
/** @file AVLNode.h
    @author Koffman & Wolfgang
    @brief extend BTNode for AVL Tree

    detailed on p 636 of KW Data Structures book
*/

#ifndef AVLNODE_H_
#define AVLNODE_H_
#include "BTNode.h"
#include <sstream>

/** a node for an AVL Tree. */
template <typename Item_Type>
struct AVLNode : public BTNode<Item_Type> {
  enum balance_type {LEFT_HEAVY = -1,
		     BALANCED = 0,
		     RIGHT_HEAVY = +1};
  balance_type balance;

  /** constructor : call the BTNode constructor
      and set balance to BALANCED
  */
  AVLNode(const Item_Type& the_data,
	  BTNode<Item_Type>* left_val = NULL,
	  BTNode<Item_Type>* right_val = NULL) :
    BTNode<Item_Type>(the_data, left_val, right_val),
    balance(BALANCED) {}

  /** destructor : do nothing */
  virtual ~AVLNode() {}

  /** to_string */
  virtual std::string to_string() const {
    std::ostringstream os;
    os << balance << ": " << this->data;
    return os.str();
  }
};

#endif
