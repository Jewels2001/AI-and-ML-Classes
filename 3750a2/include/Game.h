#ifndef GAME
#define GAME

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

#include "Move.h"
using namespace std;

class Game {
  static const int BOARDSIZE = 3;

  private:
    enum class Player {
        none = '-',
        human = 'X',
        computer = 'O'
    };


    Player board[BOARDSIZE][BOARDSIZE];

 public:
    //constructor
    Game();
    //destructor
    ~Game() {}
    //prints the game board
    void printBoard();
    //checks if there is a tie
    bool isTie();
    //checks if a player has won
    bool checkWin(Player player);

    //implements minimax algo
    Move minimax();
    //searchs for max (alpha)
    int maxSearch(int level);
    //searchs for min (beta)
    int minSearch(int level);
    //gets player's input
    void getHumanMove();
    //plays the game
    void play();
};
#endif
