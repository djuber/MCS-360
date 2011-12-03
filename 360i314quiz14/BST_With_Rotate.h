// -*- c++ -*-
/** @file BST_With_Rotate.h
    @author Koffman and Wolfgang
    @brief add the rotate operations to BST class.

    detailed on p627 of KW Data Structures Book
*/

#ifndef BST_WITH_ROTATE_H_
#define BST_WITH_ROTATE_H_
#include "Binary_Search_Tree.h"

/** This class extends the Binary_Search_Tree by adding
    the rotate operations. Rotate will change the balance of
    a search tree wile preserving the search tree property.
    Used as a common base class for self-adjusting trees.
*/
template <typename Item_Type>
class BST_With_Rotate : public Binary_Search_Tree<Item_Type> {
protected:
  /** rotate_right
      @pre local_root is the root of a binary search tree
      @post local_root->left is the root of a binary search tree
      local_root->left->left is raised on level
      local_root->left->right does not change levels
      local_root->right is lowered one level
      local_root is set to the new root.
      @param local_root the root of a tree to be rotated.
  */
  void rotate_right(BTNode<Item_Type>*& local_root) {
    BTNode<Item_Type>* temp = local_root->left;
    local_root->left = temp->right;
    temp->right = local_root;
    local_root = temp;
  }
  /** rotate_left
      @pre local_root is the root of a binary search tree.
      @param local_root is the root of a tree to be rotated.
  */
  void rotate_left(BTNode<Item_Type>*& local_root) {
    BTNode<Item_Type>* temp = local_root->right;
    local_root->right = temp->left;
    temp->left = local_root;
    local_root = temp;
  }
};

#endif
