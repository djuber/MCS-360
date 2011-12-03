/** @file bstree.cc
    @author Daniel Uber
    @brief Implementation for Binary Search Tree
*/

#include "bstree.h"
#include <fstream>
#include <sstream>

/** findNode returns NULL if not found */
BinarySearchTree::Node * BinarySearchTree::findNode(int data){
  Node * p = root;
  while(p && p->data != data){
    if(data < p->data)
      p = p->left;
    else
      p = p->right;
  }
  return p;
}

/** check if findNode returned NULL */
bool BinarySearchTree::find(int data){
  return findNode(data)!=NULL;
}

/** add an item (uniquely) to the tree */
void BinarySearchTree::insert(int data){
  insert(data, root);
}

/** add an item to the subtree rooted at r */
void BinarySearchTree::insert(int data, Node * &r){
  if(r){
    if(r->data > data)
      insert(data, r->left);
    else if (r->data < data)
      insert(data, r->right);
  }
  else {
    r= new Node();
    r->data = data;
  }
}

/** send items in the tree to os
    @param os should be an open stream
*/
void BinarySearchTree::display(std::ostream &os){
  display(os,root);
  os<<"\n";
}

/** send items in the subtree rooted at r to os */
void BinarySearchTree::display(std::ostream &os,
			       BinarySearchTree::Node * r){
  if(r){
    display(os,r->left);
    os<<r->data<<" ";
    os.flush();
    display(os, r->right);
  }
}

/** yield number of nodes in the tree */
int BinarySearchTree::count() const {
  return count(root);
}

/** number of nodes in the subtree rooted at r */
int BinarySearchTree::count(BinarySearchTree::Node * r) const{
  if(r)
    return count(r->left) + count(r->right) + 1;
  else
    return 0;
}

/** find the longest path to a leaf */
int BinarySearchTree::deepest() const {
  return deepest(root);
}

/** find the longest path to a leaf in the subtree rooted at r */
int BinarySearchTree::deepest(BinarySearchTree::Node *r) const {
  if(r){
    int L = deepest(r->left);
    int R = deepest(r->right);
    L = (L>R)?L:R;
    return L+1;
  }
  else return 0;
}

/** find the shortest path to a leaf */
int BinarySearchTree::shallowest() const {
  return shallowest(root);
}

/** find the shortest path to a leaf in the subtree rooted at r */
int BinarySearchTree::shallowest(BinarySearchTree::Node * r) const {
  if(r){
    int L = shallowest(r->left);
    int R = shallowest(r->right);
    if(R && L)
      L = (L>R)?R:L;
    else
      L = L?L:R;
    return L+1;
  }
  else return 0;
}

/** find the smallest value in the tree */
int BinarySearchTree::minimum() const {
  return minimum(root);
}

/** find the smallest value in the tree rooted at r */
int BinarySearchTree::minimum(BinarySearchTree::Node *r) const{
  if(r){
    if(r->left)
      return minimum(r->left);
    else
      return r->data;
  }
  // this only happens in an empty tree
  return 0;
}

/** find the largest value in the tree */
int BinarySearchTree::maximum() const {
  return maximum(root);
}

/** find the largest value in the subtree rooted at r */
int BinarySearchTree::maximum(BinarySearchTree::Node *r) const{
  if(r){
    if(r->right)
      return maximum(r->right);
    else
      return r->data;
  }
  // again, only in the empty tree
  else return 0;
}

/** send summary information to os
    @param os should be an open stream
*/
void BinarySearchTree::summary(std::ostream &os){
  if(root){
    os<<"Depth: "<<deepest() - 1<<'\n';
    os<<"Shallowest Depth: "<<shallowest() - 1<<'\n';
    os<<"Number of Nodes: "<<count()<<'\n';
    os<<"Smallest value: "<<minimum()<<'\n';
    os<<"Largest value: "<<maximum()<<'\n';
    os<<"Root Node: "<<root->data<<'\n';
  }
  else {
    os<<"Empty Tree, not much to say.\n";
  }
}

/** remove the node with value data from the tree */
void BinarySearchTree::remove(int data){
  remove(data, root);
}

/** remove the node with value data from the subtree rooted at r
    attach left subtree to the node's place
    attach right subtree at the first available right link in the
    left subtree.
*/
void BinarySearchTree::remove(int data,
			      BinarySearchTree::Node * &r){
  if(r){
    if( data < r->data)
      remove(data, r->left);
    else if(data > r->data)
      remove(data, r->right);
    else {
      Node * t = r;
      r = r->left;
      insert(r, t->right);
      delete t;
    }
  }
}

/** graft from onto to in a proper place.
    Major assumption is that both subtrees are sorted, and
    the intersection of the intervals
    [min(from), max(from)] \\cap [min(to),max(to)]
    is the empty set. This is always the case when remove
    calls it
*/
void BinarySearchTree::insert(BinarySearchTree::Node * &to,
			      BinarySearchTree::Node * &from){
  if(to){
    if(from){
      if(from->data > to->data)
	insert(to->right, from);
      else if (from->data < to->data)
	insert(to->left, from);
      else{ // this is probably unnecessary
	insert(to->right, from->right);
	insert(to->left, from->left);
	delete from;
      }
    }
  }
  else to = from;
}

/** destructor, remove root until it's not there */
BinarySearchTree::~BinarySearchTree(){
  while(root)
    remove(root->data, root);
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
std::string BinarySearchTree::tree2dot(BinarySearchTree::Node * r){
  std::ostringstream out;
  // draw left edges, then left subtree's edges
  if(r->left){
    out<<"\""<<r->data<<"\"->\""
       <<r->left->data
       <<"\" [color=\"blue\"] \n";
    out<<tree2dot(r->left);
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
    out<<tree2dot(r->right);
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
std::string BinarySearchTree::tree2dot(){
  std::ostringstream out;
  out<<"digraph Tree {\n";
  out<<"//blue is a left link, red is a right link\n";
  if(root && (root->left || root->right))
    out<<tree2dot(root);
  else if (root){ // singleton tree
    out<<"root->"<<root->data<<"\n";
  }
  out<<"}\n";
  return out.str();
}

/** writeDotFile generates a file for graphviz/dot family
    of tools with the given filename
*/
void BinarySearchTree::writeDotFile(std::string filename){
  std::ofstream outfile;
  outfile.open(filename.c_str());
  if(!outfile) throw std::ofstream::failure("Error Opening");
  outfile<<tree2dot();
  outfile.close();
}

