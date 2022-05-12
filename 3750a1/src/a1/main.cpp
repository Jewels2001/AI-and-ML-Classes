#include <iostream>
#include <iomanip>
#include "Output.h"
#include "Search.h"
#include "Solve.h"
#include "State.h"
using namespace std;
//
// int main() {
//   cout << "Welcome to the Cannibals and Mercenaries Problem." << endl;
//   Solve g;
//   while (true) {
//     g.display();
//     //get is just initial state
//     //////run search algo here
//     g.counto++;
//   }
//   return 0;
// }


int main(){
  // game g;

  unsigned int numM = 3;
  unsigned int numC = 3;

  State *initialState = new State(numC, numM, true);
  Search &g = Search::getStateGraph(initialState, numC, numM);
  g.showConnections();
  std::get<0>(s) << "," << std::get<1>(s) << "," << std::get<2>(s)
  std:: cout << "Number of boat crossings needed: " << g.BFS(initialState) << std::endl;


  //     g.displaymc();

  //     if (g.side == false)
  //       g.boat_lr();
  //     else
  //       g.boat_rl();
  //     }
  //     g.counto++;
  //   }
  return 0;
}
