//-*- c++ -*-
/** @file hashchain.h
    @brief hash table using separate chaining
*/
#ifndef _HASH_CHAIN_H_

typedef char * KType; //key type
typedef char * VType; // value type

struct listnode {
  KType key;
  VType value;
  listnode * next;
};

typedef listnode * Position;
typedef listnode * List;

struct hashtable{
  int tablesize;
  List * ht;
};
typedef hashtable * HashTable;
#define HASH_FUNCTION 1

HashTable newTable(int n);
void clearTable(HashTable h);
void destroyTable(HashTable h);
Position find(KType key, VType value, HashTable h);
void put(KType key, VType value, HashTable h);
VType get(Position p);
VType remove(KType key, VType value, HashTable h);
int h(KType key, int tableSize);

#define _HASH_CHAIN_H_
#endif
