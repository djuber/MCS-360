/* funcs.h : declarations for functions
   Daniel Uber, MCS 360 week 2 lab
*/
#ifndef _FUNCS_H__
#define _FUNCS_H__

#include <vector>
#include <fstream>
#include "score.h"

void readFromFileIntoVector(std::ifstream &in, std::vector<Score> &v);
void writeFromVectorToFile(std::vector<Score> &v, std::ofstream &out);
void isort(std::vector<Score> &v);

#endif
