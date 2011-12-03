/** @file hashchain.cc
    @brief hash table implementation
*/

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include "hashchain.h"

/** this barely deserves a name. */
inline bool evenp(int t){
  return !(t%2);
}

/** this is lousy, but effective
    and not used often enough to warrant optimization
    the cost of integer division to get the modulus
    is probably too high... but more sophisticated methods
    aren't worth the effort
*/
bool primep(int t){
  int a = 1;
  int r = t - 1;
  while(r){
    a = (a * r--) % t;
    if(!a) return false;
  }
  return true;
}

/** find the prime immediately succeeding t
    t need not be prime
    these really should be unsigned
*/
int nextPrime(int t){
  if(primep(t)) return t;
  if(evenp(t))
    t++;
  else
    t+=2;
  while(!primep(t))
    t+=2;
  return t;
}

HashTable newTable(int size){
  HashTable H;
  int i;
  H = (hashtable*)malloc(sizeof(hashtable));
  H->tablesize=nextPrime(size);
  H->ht = (List *)malloc(sizeof(List) * (H->tablesize));
  for(i=0;i<H->tablesize; i++)
    H->ht[i]=NULL;
  return H;
}

void clearTable(HashTable H){
  int i;
  Position t;
  for(i=0;i < H->tablesize; i++){
    while(H->ht[i]){
      t = H->ht[i];
      H->ht[i] = t->next;
      // this was an issue leaking memory by deleting the node
      // without freeing its value
      // free(t->value);
      // but this is not needed (and causes issues elsewhere)
      //      free(t->key);
      free(t);
    }
  }
  return;
}

void destroyTable(HashTable H){
  // delete nodes
  clearTable(H);
  // delete array of lists
  free(H->ht);
  free(H);
  return;
}

Position find(KType key, VType value, HashTable H){
  List L = NULL;
  L = H->ht[h(key,H->tablesize)];
  // strcmp causing invalid read?
  // all reported errors point here.
  while(L && !strcmp(L->value, value))
    L = L->next;
  return L; // Null if not found
}

void put(KType key, VType value, HashTable H){
  int ih;
  Position p, t;
  p = find(key,  value, H);
  if(!p){
    t = (listnode*)malloc(sizeof(listnode));
    if(!t) exit(1);
    t->key = key;
    t->value=value;
    ih=h(key,H->tablesize);
    t->next = H->ht[ih];
    H->ht[ih] = t;
  }
  return;
}

VType get(Position p){
  return p->value;
}

// delete is a reserved word in c++
// remove is never called in code?
VType remove(KType key, VType value, HashTable H){
  int ih = h(key,H->tablesize);
  Position *p, q;
  q = H->ht[ih];
  if(q && q->value == value){
    H->ht[ih] = q->next;
    return value;
  } else
    while(q){
      p = &q;
      q = q->next;
      if(q->value == value){
	(*p)->next = q->next;
	free(q->value);
	free(q);
	return value;
      }
    }
  return (VType)0;
}


