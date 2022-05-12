#ifndef QUEENS
#define QUEENS

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

class Queens {

  private:
    int ans;
    int n;
    vector<int> row;
    vector<bool> col;
    vector<bool> diag1;
    vector<bool> diag2;
    vector<vector<char>> board;
    //checks the constraints and runs backtracking algorithm
    bool queens(int i);

 public:
    //constructor
    Queens(int num);
    //destructor
    ~Queens() {}
    //returns answer
    int compute();
    //prints the game board
    void printBoard();
};
#endif
