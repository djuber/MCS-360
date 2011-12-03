// -*- c++ -*-
/** @file Binary_Search_Tree.h
    @author Koffman and Wolfgang
    @brief Definition of the binary search tree class.

    detailed on pp 469-470 of KW Data Structures Book
*/

#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include "Binary_Tree.h"

/** @class Binary_Search_Tree class
    @tparam Item_Type must define the less than operator
    and the stream operators.
*/
template <typename Item_Type>
class Binary_Search_Tree : public Binary_Tree<Item_Type> {
public:
  Binary_Search_Tree() : Binary_Tree<Item_Type>() {}
  /** Insert an item into the tree.
      @post The item is in the tree.
      @param item The item to be inserted.
      @return true if the item was not already in the tree.
  */
  virtual bool insert(const Item_Type& item);
  /** remove an item from the tree.
      @post The item is no longer in the tree.
      @param item The item to be removed.
      @return true if the item was in the tree.
  */
  virtual bool erase(const Item_Type& item);
  /** Determine whether an item is in the tree.
      @param item The item sought.
      @return A const pointer to the item if in the tree, NULL if not.
  */
  const Item_Type* find(const Item_Type& target) const;
private:
  /** Insert an item into the tree.
      @post: The item is in the tree.
      @param local_root A reference to the current root.
      @param item The item to be inserted.
      @return true if the item was not already in the tree.
  */
  virtual bool insert(BTNode<Item_Type>*& local_root,
		      const Item_Type& item);
  /** remove an item from the tree.
      @post the item is no longer in the tree.
      @param local_root A reference to the current root.
      @param item The item to be removed.
      @return true if the item was in the tree.
  */
  virtual bool erase(BTNode<Item_Type>*& local_root,
		     const Item_Type& item);
  /** Determine whether an item is in the tree
      @param local_root A reference to the current root
      @param item The item sought.
      @return a constant pointer to the item in the tree,
      or NULL.
  */
  const Item_Type* find(BTNode<Item_Type>*& local_root,
			const Item_Type& item) const;
  /** Find a replacement for a node which is being deleted.
      This function finds the rightmost child of the left
      subtree. (will have no right child). The data in this
      local_root replaces the data in the old_root. The pointer
      to local_root is then saved in old_root and local_root is
      replaced by its left child.
      @param old_root Reference to the pointer to the old parent.
      @param local_root Reference to the pointer to the local_root.
  */
  virtual void replace_parent(BTNode<Item_Type>*& old_root,
			      BTNode<Item_Type>*& local_root);
};

// find detailed on p471
template <typename Item_Type>
const Item_Type* Binary_Search_Tree<Item_Type>::find
(const Item_Type& target) const {
  return find(this->root, target);
}

template <typename Item_Type>
const Item_Type* Binary_Search_Tree<Item_Type>::find
(BTNode<Item_Type>*& local_root,
 const Item_Type& target) const {
  if(!local_root)
    return NULL;
  if(target < local_root->data)
    return find(local_root->left, target);
  else if (local_root->data < target)
    return find(local_root->right, target);
  else
    return &(local_root->data);
}

// insert on p474
template <typename Item_Type>
bool Binary_Search_Tree<Item_Type>::insert
(const Item_Type& item) {
  return insert(this->root, item);
}

template <typename Item_Type>
bool Binary_Search_Tree<Item_Type>::insert
(BTNode<Item_Type>*& local_root,
 const Item_Type& item){
  if(!local_root){
    local_root = new BTNode<Item_Type>(item);
    return true;
  } else {
    if(item < local_root->data) {
      return insert(local_root->left, item);
    } else if (local_root->data < item) {
      return insert(local_root->right, item);
    } else {
      return false;
    }
  }
}

// erase on pp476-477
template <typename Item_Type>
bool Binary_Search_Tree<Item_Type>::erase
(const Item_Type& item) {
  return erase(this->root, item);
}

template <typename Item_Type>
bool Binary_Search_Tree<Item_Type>::erase
(BTNode<Item_Type>*& local_root,
 const Item_Type& item) {
  if(!local_root) //nothing to do in the empty tree
    return false;
  else {
    if (item < local_root->data)
      return erase(local_root->left, item);
    else if  (local_root->data < item)
      return erase(local_root->right, item);
    else { // we did find the item to remove
      if(!local_root->left) {
	local_root = local_root->right;
      } else if (!local_root->right) {
	local_root = local_root->left;
      } else {
	BTNode<Item_Type>* old_root = local_root;
	replace_parent(old_root, old_root->left);
	delete old_root;
      }
      return true;
    }
  }
}

// replace parent on p478 (is this correct?)
template <typename Item_Type>
void Binary_Search_Tree<Item_Type>::replace_parent
(BTNode<Item_Type>*& old_root,
 BTNode<Item_Type>*& local_root) {
  if(local_root->right) {
    replace_parent(old_root, local_root->right);
  } else {
    old_root->data = local_root->data;
    old_root = local_root;
    local_root = local_root->left;
  }
}

#endif
