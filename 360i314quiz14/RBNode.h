// -*- c++ -*-
/** @file RBNode.h
    @author Koffman and Wolfgang
    @brief Red Black Tree Node

    detailed on p650 of KW Data Structures book
*/

#ifndef RBNODE_H_
#define RBNODE_H_

#include "BTNode.h"
#include <sstream>

/** a node for red black trees */
template <typename Item_Type>
struct RBNode : public BTNode<Item_Type> {
  bool is_red;
  RBNode(const Item_Type& the_data,
	 BTNode<Item_Type>* left_val = NULL,
	 BTNode<Item_Type>* right_val = NULL) :
    BTNode<Item_Type>(the_data, left_val, right_val), is_red(true) {}

  /** destructor does nothing, here to suppress warnings */
  virtual ~RBNode() {}

  // to_string
  virtual std::string to_string() const {
    std::ostringstream os;
    if(is_red)
      os<<"   red: "<<this->data;
    else
      os<<" black: "<<this->data;
    return os.str();
  }
};

#endif
