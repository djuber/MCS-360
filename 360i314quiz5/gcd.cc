/* gcd.cc
   Daniel Uber
   MCS 360 Quiz 5
*/

// gcd produces a positive integer which divides its arguments
// the compiler uses the remainder portion of an idiv when you invoke the
// modulus operator, which has unpredictable effects on the sign
// idiv remainder will have same sign as the dividend, and be less
// in absolute value than the divisor. For mixed sign inputs, the
// sign of the output is dependent on the number of iterations in the while
// loop
int gcd(int m, int n){
  int r;
  while (n != 0){
    r = m % n;
    m = n;
    n = r;
}
  return (m>0)?m:-m;
}
