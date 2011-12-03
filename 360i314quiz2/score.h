/* score.h: score class definition
   Daniel Uber
   MCS 360 Week 2 Quiz
*/

#ifndef SCORE_H
#define SCORE_H

// cstring for strcpy
#include <cstring>

class Score 
{
  int _id;
  char _name[100];
  float _exam1;
  float _exam2;
  float _final;
  float _score;
 public:
  Score() {}
  inline void set_id(int id_) {_id = id_;}
  // assignment of a pointer variable to another is the wrong thing to do
  inline void set_name(char *name_) {strcpy(_name, name_);}
  //  inline void set_name(const char *name_) {_name = name_;}
  inline void set_exam1(float exam1_) {_exam1 = exam1_;}
  inline void set_exam2(float exam2_) {_exam2 = exam2_;}
  inline void set_final(float final_) {_final = final_;}

  inline float score() {return _score = .4*_final + .3*_exam1 + .3*_exam2;}
  inline float exam1() {return _exam1;}
  inline float exam2() {return _exam2;}
  inline float final() {return _final;}
  inline char *name() {return _name;}
  inline int id() {return _id;}
};

#endif
