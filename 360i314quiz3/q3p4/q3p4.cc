// file: q3p4.cc
// Quiz 3 Problem 4
// Daniel Uber MCS 360 Fall 2011

#include <iostream>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

float *f(float x, float y, float z);

inline float frand();

int main(){
  float x, y, z;

  float *ret;
  // seed the rng so we can see different results
  srand(time(NULL));
   // check it a few times if you uncomment these lines
  //  for(int i = 0; i < 100000; i++)
  //{
      x = frand();
      y = frand();
      z = frand();

      ret = f(x,y,z);

      cout << x << ' ' << y
	   << ' ' << z << ' '
	   << ret[0] << ' ' << ret[1]
	   << ' ' << ret[2] << '\n';
      //}
  return 0;
}

inline float frand() {
  // calling rand without seeding first is kind of foolish
  return static_cast<float>(rand()) / static_cast<float>( RAND_MAX);
}

float *f(float x, float y, float z){
  char c = 0;
  static float ret[3];
  float max, min;
  ret[0] = (x + y + z)/3.0;
  // lucky for me, booleans eval to 1 or 0
  c = (x > y) + 2*(x > z) + 4*(y > z);
  // and the compiler can write spaghetti code for us
  switch(c){
  case 0: // x<y, x<z, y<z, so x is min, z is max
    min = x;
    max = z;
    break;
  case 1: // x > y, x < z, y < z, y < x < z
    min = y;
    max = z;
    break;
  case 2: // x < y, x > z, y < z, so there is equality somewhere?
    cerr << "big problems\n";
    exit(1);
    break; // for forms sake
  case 3: // x > y, x > z, y < z, x is max, y is min
    min= y;
    max= x;
    break;
  case 4: // x<y, x<z, y > z, so y is max, x is min
    min = x;
    max = y;
     break;
  case 5: // x > y, x < z, y > z, y<x<z<y, problems again
    cerr << "problems encountered\n";
    exit(1);
    break;
  case 6: // x < y, x > z, y > z, so y max, z min
    min=z;
    max=y;
    break;
  case 7: // x > y > z
    min = z;
    max = x;
    break;
  default:
    cerr << "Why am I here?\n";
    exit(1);
    break;
  }
  ret[1] = min;
  ret[2] = max;
  return ret;
}
