#ifndef SOLVE_H
#define SOLVE_H

#include <iostream>
#include <iomanip>
using namespace std;

#include "Search.h"
#include "State.h"


class Solve {
 public:
   Solve();
   ~Solve() {};

   vector<Tuple> getPath();
 private:
   vector<Tuple> path;
};
#endif
