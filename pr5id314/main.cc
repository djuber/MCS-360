/** @file main.cc
    @author Roy Lowman
    @brief modified project 5 main function
    changed numfuns to add hash functions defined in hashfunctions.cc
    changed a few things to plug memory leaks.
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include "hashchain.h"

#define NUMFUNS 10
// global
int hashFunction=0;

struct htstats {
  int numElements;
  int tableSize;
  int hashFunction;
  float loadFactor;
  int* collisions;
  int maxCollisions;
  float PutGetTime;
};

void rand_words(int numwords);
char * newString(int size);
int * newArrayi (int n);
KType* newArrays(int n);
void freeArrays(KType *a, int n);
void freeArrayi(int* a);
void printResults(htstats hs, htstats hfsummary[]);
int findArrayMaxi(int *a, int n);
void allSummary(htstats hfSummary[], int n);

// 53 lines is too long! This is complicated, and leaks memory
int main(int argc, char **argv){
  int i, n, ifun;
  clock_t t1, t2;
  float dt;
  KType* data;
  HashTable H;
  Position p;
  KType key;
  VType value, v1;
  FILE * fid;
  htstats hs; // doesn't actually call newTable?
  htstats hfsummary[NUMFUNS];
  if(argc!=3){
    printf("Usage: run number load\n");
    exit(1);
  }
  hs.numElements = atoi(argv[1]);
  hs.loadFactor = atoi(argv[2]);
  rand_words(hs.numElements);
  fid = fopen("randwords.txt", "r");
  if(!fid) exit(1);
  data = newArrays(hs.numElements);
  for(i=0; i<hs.numElements; i++)
    fscanf(fid, " %s", data[i]);
  fclose(fid);
  n = hs.tableSize = (int)(hs.numElements/hs.loadFactor);
  for(ifun=0; ifun < NUMFUNS; ifun++){
    hashFunction = hs.hashFunction = ifun;
    H = newTable(n); // created 112 bytes in 7 blocks
    n = hs.tableSize = H->tablesize;
    hs.collisions = newArrayi(n);
    t1=clock();
    for(i=0;i<hs.numElements;i++){
      key=data[i];
      value=newString(8);
      strcpy(value,key);
      put(key,value,H);
      hs.collisions[h(key,n)]++;
      free(value);
    }
    for(i=0;i<hs.numElements;i++){
      p = find(data[i],data[i],H);
      if(p) // this caused a segfault since find can return null
	v1 = get(p);
    }
    t2=clock();
    dt = (float)(t2-t1)/CLOCKS_PER_SEC;
    hs.PutGetTime = dt;
    printResults(hs,hfsummary);
    destroyTable(H);
    freeArrayi(hs.collisions);
  }
  allSummary(hfsummary,NUMFUNS);
  freeArrays(data, hs.numElements);
  return 0;
}

char* newString(int size){
  char *s;
  s = (char*)malloc(size * sizeof(char) + 1);
  if(!s) exit(1);
  s[0] = '\0';
  return s;
}

int* newArrayi(int n){
  int * a, i;
  a = (int*)malloc(n*sizeof(int));
  if(!a) exit(1);
  for(i=0;i<n;i++)
    a[i]=0;
  return a;
}

KType* newArrays(int n){
  KType * a;
  int i;
  a = (KType * )malloc(n*sizeof(KType)); // why char* here?
  if(!a) exit(1);
  for(i=0;i<n;i++)
    a[i]=newString(8);
  return a;
}

void freeArrayi(int* a){
  free(a);
}

void freeArrays(KType *a, int n){
  for(int i = 0; i < n; i++)
    free(a[i]);
  free(a);
}

void printResults(htstats hs, htstats hfsummary[]){
  int i, n, answer;
  n = hs.tableSize;
  hs.maxCollisions = findArrayMaxi(hs.collisions,n);
  printf("numElements:\t\t%d\n"
	 "tableSize:\t%d\n"
	 "hashFunction:\t%d\n"
	 "loadFactor:\t%.2f\n"
	 "maxCollisions:%d\n"
	 "PutGetTime:\t%.3f seconds\n",
	 hs.numElements,
	 hs.tableSize,
	 hs.hashFunction,
	 hs.loadFactor,
	 hs.maxCollisions,
	 hs.PutGetTime);
  puts("print collision array? 1=yes, 0=no");
  scanf(" %d", &answer);
  if(answer){
    puts("Number of collisions at each hash index:");
    for(i=0;i<n;i++)
      printf("-%d",hs.collisions[i]);
  }
  puts("");
  // arguably, this could be somewhere else...
  puts("===========================new hash function=====================");
  hfsummary[hs.hashFunction]=hs;
  return;
}

int findArrayMaxi(int *a, int n){
  int i, max;
  max = a[0];
  for(i=1;i<n;i++)
    if(max < a[i])
      max = a[i];
  return max;
}

void allSummary(htstats hfsummary[], int n){
  int i;
  printf("numElements:\t%d\n", hfsummary[0].numElements);
  printf("tableSize:\t%d\n", hfsummary[0].tableSize);
  printf("loadFactor:\t%.2f\n", hfsummary[0].loadFactor);
  puts("hashFunction \t Max Collisions \t Put&GetTime(sec)");
  for(i=0;i<n;i++)
    printf("%d\t\t%d\t\t%.3f\n",
	   hfsummary[i].hashFunction,
	   hfsummary[i].maxCollisions,
	   hfsummary[i].PutGetTime);
  return;
}


