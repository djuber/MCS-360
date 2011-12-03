/** @file hashfunction.cc
    @brief various string hashing routines
*/

#include <cstdio>
#include <cstdlib>
#include "hashchain.h"
// for encrypt
#include <unistd.h>
#include <cerrno>

extern int hashFunction;

static int h0(KType key, int tablesize);
static int h1(KType key, int tablesize);
static int h2(KType key, int tablesize);
static int h3(KType key, int tablesize);
static int h4(KType key, int tablesize);
static int h5(KType key, int tablesize);
static int h6(KType key, int tablesize);
static int h7(KType key, int tablesize);
static int h8(KType key, int tablesize);
static int h9(KType key, int tablesize);

int h(KType key, int tablesize){
  int (*hf)(KType, int);
  switch(hashFunction){
  case 0: hf=h0; break;
  case 1: hf=h1; break;
  case 2: hf=h2; break;
  case 3: hf=h3; break;
  case 4: hf=h4; break;
  case 5: hf=h5; break;
  case 6: hf=h6; break;
  case 7: hf=h7; break;
  case 8: hf=h8; break;
  case 9: hf=h9; break;
  default:
    puts("Bad hash function choice!");
    exit(1);
  }
  // calculate hash
  return hf(key,tablesize);
}

static int h0(KType key, int tablesize){
  return key[0] % tablesize; //first letter hash
}

static int h1(KType k, int tablesize){
  int base = 31;
  unsigned int h = 0;
  for(;*k !='\0';k++)
    h = h*base + *k;
  return h % tablesize;
}

static int h2(KType k, int tablesize){
  int base = 31;
  int h = 0;
  while(*k != '\0')
    h = (h*base + *k++)%tablesize;
  return h;
}

static int h3(KType k, int tablesize){
  unsigned int h = 0;
  while(*k != '\0')
    h = ((h<<5) + *k++);
  return h % tablesize;
}

static int h4(KType k, int tablesize){
  unsigned int h = 0;
  while(*k != '\0')
    h = ((h<<5) + *k++) % tablesize;
  return h;
}

static int h5(KType k, int tablesize){
  unsigned int h = 0;
  while(*k != '\0')
    h += *k++;
  return h % tablesize;
}

static int h6(KType k, int tablesize){
  return (k[0] + 27*k[1] + 729*k[2])%tablesize;
}

union hh {
  unsigned number;
  // assume 32 bit for portability.
  char s[4];
};

// h7 : use hh type above and try to use more bits
// this is too complicated... 2.5 times longer time than h1
// with no improvement in distribution
static int h7(KType k, int tablesize){
  hh u;
  u.number = 0;
  int c = 0;
  for(int i = 0; k[i] != '\0'; i++){
    c = i % 4;
    // load up to four characters of string into u
    while(c){
      int index = i - c;
      u.s[c] *= k[i];
      u.s[c] += k[index] << 2;
      u.s[c--] += k[i] & 0xAA;
    }
    u.number *= 31;
  }
  return u.number % tablesize;
}

// this is faster and almost equivalent to the above
static int h8(KType k, int tablesize){
  hh u;
  u.number = 0;
  int i = 0;
  while(k[i] != '\0'){
    // and instead of multiply
    u.s[i%4] ^= k[i];
    i++;
  }
  u.number += u.number << 2;
  u.number += u.number >> 2;
  return u.number % tablesize;
}

// use encrypt(3) to make a new number
// this is DES with key = plaintext
// this doesn't do too much better than the naive
// approaches above.
static int h9(KType k, int tablesize){
  char buf[64];
  unsigned int out=0;
  // grab the digits in k
  for(int i=0; i< 8; i++){
    if(k[i]!='\0')
      for(int j=0; j < 8; j++){
	buf[i*8 + j] = (k[i]&(1<<j))>0;
      }
  }
  // use the input as the key?
  setkey(buf);
  errno=0;
  encrypt(buf, 0);
  if(errno == ENOSYS)
    exit(1);
  for(int i = 0; i<64; i++){
    out += (buf[i]<<i);
  }

  return out % tablesize;
}
