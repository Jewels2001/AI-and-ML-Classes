#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <tuple>
#include <cassert>

#include "State.h"
#include "Search.h"
#include "Output.h"

using namespace std;

typedef tuple<unsigned int, unsigned int, bool> Tuple;

State::State (unsigned int numC, unsigned int numM, bool boatL) {
  assert(numC >= 0 && numM >= 0);
  s = std::make_tuple(numC, numM, boatL);
}

//num cannibals always less than or equal to missionaries
bool State::isLegalState() {
  bool legalLeftSide = std::get<1>(s) > 0 ? std::get<0>(s) <= std::get<1>(s) : true;
  bool legalRightSide = (Search::getTotalNumMissionaries() - std::get<1>(s)) > 0 ?
                        (Search::getTotalNumCannibals() - std::get<0>(s))
                        <= (Search::getTotalNumMissionaries() - std::get<1>(s)) : true;
  return (legalLeftSide && legalRightSide);
}
//<0,0,0>
bool State::isGoalState() const {
  if (std::get<0>(s) == 0 &&
      std::get<1>(s) == 0 &&
      std::get<2>(s) == false) {
        return true;
  }
  return false;
}

void State::printState() {
  // int counto, i;
  // char left[6], right[6];
  // int m_num = 3;
  // int c_num = 3;
  // bool side;
  // int ml_count, cl_count;
  // int mr_count, cr_count;
  // displaymc()
      if (std::get<2>(s))
        g.boat_lr();
      else
        g.boat_rl();
      }
   std::cout << std::get<0>(s) << "," << std::get<1>(s) << "," << std::get<2>(s) << std::endl;
}

Tuple State::getState() {
  return s;
}

 //Tuple s; <num cannibals, num missionaries, boat side>  (1=left, 0=right)


// state-sorting rule
// template<class T> struct ptr_less {
//   bool operator()(T* lhs, T* rhs) {
//     return lhs->getState() < rhs->getState();
//   }
// };
