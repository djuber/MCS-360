/**
 * @file main.cpp
 * @author Daniel Uber
 * mcs360f11 Quiz 8
 */

#include <iostream>
using namespace std;
#include "list.h"

int main(){
	int x;
	ListItr<int> phead, plist, pnode;
	List<int> L;
	phead = L.zeroth();
	plist = L.first();
	x=1;
	L.insert(x,phead);
	x=2;
	L.insert(x,phead);
	x=3;
	L.insert(x,phead);
	x=4;
	L.insert(x,phead);

	printList(L);

	L.makeEmpty();

	printList(L);

	pnode = phead;
	x=1;
	L.insert(x,pnode);
	pnode.advance();
	x=2;
	L.insert(x,pnode);
	pnode.advance();
	x=3;
	L.insert(x,pnode);
	pnode.advance();
	x=4;
	L.insert(x,pnode);

	printList(L);

	pnode = L.findPrevious(x=3);
	cout << pnode.retrieve() << endl;

	cout << L.zeroth().retrieve() << endl;
	cout << L.first().retrieve() << endl;

	for(ListItr<int> p = L.first() ; !(p.isPastEnd()); p.advance() )
		cout << p.retrieve();
	cout << endl;

	for(ListItr<int> p = L.zeroth() ; !(p.isPastEnd()); p.advance() )
		cout << p.retrieve();
	cout << endl;


	List<int> M = L;
	printList(M);

	M = L;
	printList(M);

	// for(int i = 0; i < 1000; i++)
	//	  M.insert(i, M.zeroth());

	printList(M);
	return 0;
}
