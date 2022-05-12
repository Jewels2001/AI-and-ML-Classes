#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include "Game.h"


int main() {
    Game tictactoe;
    cout << "Welcome to Tic-Tac-Toe v1.0 " <<
     "with alpha-beta pruning and min-max algorithm." << endl;
    tictactoe.play();
    std::cin.ignore();
}
