#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

#include "Game.h"
using namespace std;

Game::Game() {
  for (unsigned int i = 0; i < BOARDSIZE; i++) {
    for (unsigned int j = 0; j < BOARDSIZE; j++) {
      board[i][j] = Player::none;
    }
  }
}

void Game::printBoard() {
  std::cout << "+-----------------+";
  for (unsigned int i = 0; i < BOARDSIZE; i++) {
    std::cout << "\n|";
    for (unsigned int j = 0; j < BOARDSIZE; j++) {
      std::cout << std::setw(3) << static_cast<char>(board[i][j]) << std::setw(3) << " |";
    }
  }
  std::cout << "\n+-----------------+\n";
}

bool Game::isTie() {
  for (unsigned int i = 0; i < BOARDSIZE; i++) {
    if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
    return false;
  }
  return true;
}

bool Game::checkWin(Player player) {
  for (unsigned int i = 0; i < BOARDSIZE; i++) {
    // Check horizontals
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
    return true;

    // Check verticals
    if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
    return true;
  }

  // Check diagonals
  if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
  return true;

  if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
  return true;

  return false;
}

Move Game::minimax() {
  int score = std::numeric_limits<int>::max();
  Move move;

  for (unsigned int i = 0; i < BOARDSIZE; i++) {
    for (unsigned int j = 0; j < BOARDSIZE; j++) {
      if (board[i][j] == Player::none) {
        board[i][j] = Player::computer;

        int temp = maxSearch(1);

        if (temp < score) {
          score = temp;
          move.x = i;
          move.y = j;
        }
        board[i][j] = Player::none;
      }
    }
  }
  return move;
}

int Game::maxSearch(int level) {
  if (checkWin(Player::human)) { return 10; }
  else if (checkWin(Player::computer)) { return -10; }
  else if (isTie()) { return 0; }

  int score = std::numeric_limits<int>::min();

  for (unsigned int i = 0; i < BOARDSIZE; i++) {
    for (unsigned int j = 0; j < BOARDSIZE; j++) {
      if (board[i][j] == Player::none) {
        board[i][j] = Player::human;
        score = std::max(score, minSearch(level+1)-level);
        board[i][j] = Player::none;
      }
    }
  }
  return score;
}

int Game::minSearch(int level) {
  if (checkWin(Player::human)) { return 10; }
  else if (checkWin(Player::computer)) { return -10; }
  else if (isTie()) { return 0; }

  int score = std::numeric_limits<int>::max();

  for (unsigned int i = 0; i < BOARDSIZE; i++) {
    for (unsigned int j = 0; j < BOARDSIZE; j++) {
      if (board[i][j] == Player::none) {
        board[i][j] = Player::computer;
        score = std::min(score, maxSearch(level+1)+level);
        board[i][j] = Player::none;
      }
    }
  }
  return score;
}

void Game::getHumanMove() {
  bool fail = true;
  unsigned int x = -1, y = -1;

  do {
    std::cout << "Your Move: \n";
    std::cout << "Please enter coordinate values:\n";

    char a, b;

    bool bad = true;
    std::cin >> a >> b;
    while(bad) {
      x = a - '0';
      y = b - '0';
      if(!isdigit(a) || !isdigit(b)) {
        bad = true;
        cout << "You did not enter a number.\n";
      }
      else if(x < 0 || y < 0) {
        bad = true;
        cout << "Coordinate must be greater than 0!\n";
      }
      else if(x > 2 || y > 2) {
        bad = true;
        cout << "Coordinate must be less than 2!\n";
      }
      else {
        bad = false;
        break;
      }
      cin >> a >> b;
    }

    fail = board[x][y] != Player::none;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  } while (fail);

  board[x][y] = Player::human;
}

void Game::play() {
  unsigned int turn = 0;
  bool exit = false;


  std::cout << "Enter your move in coordinate form [row, col]. Ex: \n" <<
  "00  01  02 \n10  11  12 \n20  21  22\n" ;
  printBoard();

  do
  {
    // human move
    if (turn == 0)
    {
      getHumanMove();

      if (checkWin(Player::human))
      {
        std::cout << "Human Wins\n";
        exit = true;
      }
    }
    else
    {
      std::cout << "\nComputer Move: ";

      Move aimove = minimax();
      std::cout << aimove.x << aimove.y << "\n";
      board[aimove.x][aimove.y] = Player::computer;

      if (checkWin(Player::computer))
      {
        std::cout << "Computer Wins\n";
        exit = true;
      }
    }

    if (isTie())
    {
      std::cout << "\n*** Tie ***\n";
      exit = true;
    }

    turn ^= 1;
    printBoard();


  } while (!exit);
  std::cout << "Press any key to exit...\n";
}
