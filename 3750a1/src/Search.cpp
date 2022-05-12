#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <tuple>
#include <cassert>

//#include "State.h"
#include "Search.h"

using namespace std;
unsigned int Search::numCannibals, Search::numMissionaries;

Search& Search::getStateGraph(State *s, unsigned int c, unsigned int m) {
  numCannibals = c;
  numMissionaries = m;
  static Search sg;
  sg.connectStates(s);
  return sg;
}

unsigned int Search::getTotalNumCannibals() {
  return numCannibals;
}

unsigned int Search::getTotalNumMissionaries() {
  return numMissionaries;
}

bool Search::s(State *s, std::set<State*> sset) {
  for(std::set<State*>::iterator i = sset.begin(); i != sset.end(); i++) {
    if((*i)->getState() == s->getState()) {
      return true;
    }
  }
  return false;
}

bool Search::connectStates(State *initialState) {
  if(s(initialState, allStates)) {
    return true;
  }
  allStates.insert(initialState);
  std::vector<State*> nextStates;
  generateLegalNextStates(initialState, nextStates);
  if(nextStates.size() > 0) {
    for(size_t i = 0; i < nextStates.size(); i++) {
      State *s = nextStates[i];
      if(s) {
        addState(initialState, s);
      }
    }
    for(size_t i = 0; i < nextStates.size(); i++) {
      State *s = nextStates[i];
      connectStates(s);
    }
  }
  return true;
}

bool Search::generateLegalNextStates(State *initialState, std::vector<State*>& nextStates) {
  unsigned int num_c = std::get<0>((*initialState).getState());
  unsigned int num_m = std::get<1>((*initialState).getState());
  bool boatSide = std::get<2>((*initialState).getState());

  if (boatSide) {
    int i = 2;
    while (i > 0 && num_c > 0) {
      --num_c;
      --i;
      State *s1 = new State(num_c, num_m, !boatSide);
      if(!s1->isLegalState()) {
        delete[] s1;
        continue;
      }
      if(s(s1, allStates)) {
        continue;
      }
      nextStates.push_back(s1);
    }

    num_c = std::get<0>((*initialState).getState());
    i = 2;
    while(i > 0 && num_m > 0) {
      --num_m;
      --i;
      State *s2 = new State(num_c, num_m, !boatSide);
      if(!s2->isLegalState()) {
        delete[] s2;
        continue;
      }
      if(s(s2, allStates)) {
        continue;
      }
      nextStates.push_back(s2);
    }

    num_m = std::get<1>((*initialState).getState());
    if(num_c > 0 && num_m > 0) {
      State *s3 = new State(num_c - 1, num_m - 1, !boatSide);
      if(s3->isLegalState() && !s(s3, allStates)) {
        nextStates.push_back(s3);
      }
      else {
        delete[] s3;
      }
    }
  }
  else {
    num_c = std::get<0>((*initialState).getState());
    num_m = std::get<1>((*initialState).getState());
    while (num_c < getTotalNumCannibals()) {
      ++num_c;
      State *s4 = new State(num_c, num_m, !boatSide);
      if(!s4->isLegalState()) {
        delete[] s4;
        continue;
      }
      if(s(s4, allStates)) {
        continue;
      }
      nextStates.push_back(s4);
    }

    num_c = std::get<0>((*initialState).getState());
    while (num_m < getTotalNumMissionaries()) {
      ++num_m;
      State *s5 = new State(num_c, num_m, !boatSide);
      if(!s5->isLegalState()) {
        delete[] s5;
        continue;
      }
      if(s(s5, allStates)) {
        continue;
      }
      nextStates.push_back(s5);
    }

    num_m = std::get<1>((*initialState).getState());
    if(num_c < getTotalNumCannibals() && num_m < getTotalNumMissionaries()) {
      State *s6 = new State(num_c + 1, num_m + 1, !boatSide);
      if(s6->isLegalState() && !s(s6, allStates)) {
        nextStates.push_back(s6);
      }
      else {
        delete[] s6;
      }
    }
  }

  if (nextStates.size() == 0) {
    return false;
  }
  return true;
}

bool Search::isSolvable() {
  for(std::set<State*>::iterator i = allStates.begin(); i != allStates.end(); i++) {
   if((*i)->isGoalState()) {
     return true;
   }
 }
 return false;
}

void Search::addState(State *s1, State *s2) {
  adjStates[s1].push_back(s2);
}

void Search::showConnections() {
  for(std::map<State*, std::vector<State*> >::iterator i = adjStates.begin(); i != adjStates.end(); i++) {
   ((*i).first)->printState();
   std::cout << "  ";
   std::vector<State*> v = (*i).second;
   for(std::vector<State*>::iterator j = v.begin(); j != v.end(); j++) {
     (*j)->printState();
     std::cout << "  ";
   }
   std::cout << "\n";
 }
}

void Search::printAllStates() {
  for(std::set<State*>::iterator i = allStates.begin(); i != allStates.end(); i++) {
    (*i)->printState();
  }
}

int Search::BFS(State* s1) {
  int numBoatCrossing = 0;
  std::set<State*> visited;
  std::list<State*> q;

  std::vector<State*> path;

  visited.insert(s1);
  q.push_back(s1);
  path.push_back(s1);

  bool goalReached = false;
  while(!q.empty()) {
    path = {q.front()};
    bool boatCrossed = false;
    State *s2 = q.front();
    q.pop_front();

    for(std::vector<State*>::iterator sIter = adjStates[s2].begin(); sIter != adjStates[s2].end(); sIter++) {
      if(s(*sIter, visited)) {
        continue;
      }
      if(!boatCrossed) {
        boatCrossed = true;
        ++numBoatCrossing;
      }
      if((*sIter)->isGoalState()) {
        goalReached = true;
        break;
      }
      visited.insert(*sIter);
      q.push_back(*sIter);
    }
    if(goalReached) {
      return numBoatCrossing;
    }
  }
  assert(0); // control should never reach here
  return numBoatCrossing;
}
