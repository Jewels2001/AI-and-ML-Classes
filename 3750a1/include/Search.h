#ifndef SEARCH
#define SEARCH

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <tuple>

#include "State.h"

using namespace std;

typedef long long ll;

class Search {
 public:
  static Search& getStateGraph(State *s, unsigned int c, unsigned int m);
  static unsigned int getTotalNumCannibals();
  static unsigned int getTotalNumMissionaries();

  bool s(State *s, std::set<State*> sset);
  bool connectStates(State *initialState);
  bool generateLegalNextStates(State *initialstate, std::vector<State*>& nextStates);
  bool isSolvable();

  void addState(State *s1, State *s2);
  void showConnections();
  void printAllStates();

  int BFS(State*s);
 private:
  static unsigned int numMissionaries;
  static unsigned int numCannibals;

  std::map<State*, std::vector<State*>, ptr_less<State>> adjStates;
  std::set<State*> allStates;

  Search() {}
  void operator=(Search&);
  Search (const Search&);
};
#endif
