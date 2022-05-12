#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <tuple>

using namespace std;

typedef tuple<unsigned int, unsigned int, bool> Tuple;

class State {
 public:

   State (unsigned int numC, unsigned int numM, bool boatL);
   ~State() {}

   bool isLegalState();
   bool isGoalState() const;
   void printState();

   Tuple getState();

 private:
   Tuple s; // <num cannibals, num missionaries, boat side>  (1=left, 0=right)
};

// state-sorting rule
template<class T> struct ptr_less {
  bool operator()(T* lhs, T* rhs) {
    return lhs->getState() < rhs->getState();
  }
};
#endif
