/** tree2dot.cc
    create a graphviz input file from a tree data structure.
*/
#include <sstream>
#include <string>
#include <fstream>
#include "tree.h"

std::string tree2dot(Node * r){
  ostringstream out;
  // draw left edges, then left subtree's edges
  if(r->left){
    out<<r->data<<"->"<<r->left->data<<'\n';
    out<<tree2dot(r->left);
  }
  // now draw right edges, ...
  if(r->right){
    out<<r->data<<"->"<<r->right->data<<'\n';
    out<<tree2dot(r->right);
  }
  return out.str();
}

std::string tree2dot(Tree t){
  ostringstream out;
  out<<"digraph Tree {\n";
  out<<tree2dot(t.root);
  out<<"}\n";
}

void writeDotFile(Tree t, std::string filename){
  try{
    ofstream outfile;
    outfile.open(filename);
    outfile<<tree2dot(t);
    outfile.close();
  } except (std:exception){
    std::cerr<<"Writing file "<<filename<<"failed.\n";
  }
}
