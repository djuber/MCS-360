/** @file tree.cc
    @brief Binary Search Tree Implementation
*/
#include "tree.h"

using namespace std;

Node *Tree::find(int key){
  Node *pCur = pRoot;
  // bug here: find in an empty tree segfaults
  // fixed, and eliminated interior check (which was wrong)
  while(pCur && pCur->i != key) {
    if(key < pCur->i)
      pCur=pCur->pL;
    else
      pCur = pCur->pR;
  }
  return pCur;
}

void Tree::insert(int id, double dd){
  // initialize new data node
  Node *pNew = new Node();
  pNew->i = id;
  pNew->d = dd;
  // add to the tree
  if(!pRoot)
    pRoot = pNew;
  else{
    Node *pCur = pRoot;
    Node *pParent;
    while(true){
      pParent = pCur;
      if(id < pCur->i){
	pCur = pCur->pL;
	if(pCur==NULL){
	  pParent->pL = pNew;
	  return;
	}
      }
      else {
	pCur = pCur->pR;
	if(pCur==NULL){
	  pParent->pR = pNew;
	  return;
	}
      }
    }
  }
}

void Tree::traverse(traverseType t){
  switch(t){
  case PREORDER:
    cout<<"\nPreorder Traversal: ";
    preOrder(pRoot);
    break;
  case INORDER:
    cout<<"\nInOrder Traversal: ";
    inOrder(pRoot);
    break;
  case POSTORDER:
    cout<<"\nPostOrder Traversal: ";
    postOrder(pRoot);
    break;
  }
  cout<<'\n';
}

void Tree::preOrder(Node* pLocalRoot){
  if(pLocalRoot){
    cout<<pLocalRoot->i<<" ";
    preOrder(pLocalRoot->pL);
    preOrder(pLocalRoot->pR);
  }
}

void Tree::inOrder(Node *pLocalRoot){
  if(pLocalRoot){
    inOrder(pLocalRoot->pL);
    cout<<pLocalRoot->i<<" ";
    inOrder(pLocalRoot->pR);
  }
}

void Tree::postOrder(Node *pLocalRoot){
  if(pLocalRoot){
    postOrder(pLocalRoot->pL);
    postOrder(pLocalRoot->pR);
    cout<<pLocalRoot->i<<" ";
  }
}

void Tree::displayTree(){
  cout<<"displayTree()\n";
  stack<Node *> globalStack;
  globalStack.push(pRoot);
  int nBlanks=32;
  bool isRowEmpty=false;
  for(int i = 0; i < 30; i++)
    cout<<".";
  cout<<endl;
  while(!isRowEmpty){
    stack<Node *> localStack;
    isRowEmpty = true;
    for(int j = 0; j < nBlanks; j++)
      cout<<" ";
    while(!globalStack.empty()){
      Node * temp = globalStack.top();
      globalStack.pop();
      if(temp){
	cout<<temp->i;
	localStack.push(temp->pL);
	localStack.push(temp->pR);
	if(temp->pL || temp->pR)
	  isRowEmpty=false;
      } else {
	cout<<"--";
	localStack.push(NULL);
	localStack.push(NULL);
      }
      for(int j=0; j<nBlanks*2 - 2; j++)
	cout<<" ";
    }
    cout<<'\n';
    nBlanks /=2;
    while(!localStack.empty()){
      globalStack.push(localStack.top());
      localStack.pop();
    }
  }
  for(int i = 0; i < 30; i++)
    cout<<".";
  cout<<'\n';
}

void Tree::destroy(){
  destroyRec(pRoot);
}

void Tree::destroyRec(Node * pLocalRoot){
  if(pLocalRoot){
    destroyRec(pLocalRoot->pL);
    destroyRec(pLocalRoot->pR);
    delete pLocalRoot;
  }
}

void Tree::remove(int key){
  Node * t = find(key); // get the right node
  if(t) {
    // no need to work if there's no key in tree
    // one easy case
    if(t==pRoot){
      pRoot = t->pL;
      insert(pRoot, t->pR);
      delete t;
    }
    else{
      // unfortunately, now we need to find the parent!
      Node *p = findParent(t);
      // this is horribly naive, but not wrong...
      // graft left subtree onto parent, and insert right
      // subtree into left (which will fall to rightmost)
      if (t==p->pL) {
	p->pL = t->pL;
	insert(p->pL, t->pR);
      } else {
	p->pR = t->pL;
	insert(p->pR, t->pR);
      }
    }
  }
}

Node *Tree::findParent(Node *t){
  Node * p = pRoot;
  while(t!=p->pR  && t!=p->pL){
    if(t->i < p->i)
      p = p->pL;
    else
      p = p->pR;
  }
  return p;
}

void Tree::insert(Node * &to, Node * &from){
  if(to){
    if(from->i > to->i)
      insert(to->pR, from);
    else
      insert(to->pL, from);
  }
  else
    to = from;
}

