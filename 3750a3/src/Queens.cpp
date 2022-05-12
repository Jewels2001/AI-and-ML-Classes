#include <iostream>
#include <vector>
#include <iomanip>

#include "Queens.h"
using namespace std;

Queens::Queens(int num) {
  ans = 0;
  n = num;
  board.resize(n, vector<char>(n, '.'));
  row.resize(n, 0);
  col.resize(n, 0);
  diag1.resize(2*n, 0);
  diag2.resize(2*n, 0);
}
//prints the game board
void Queens::printBoard() {
  cout << "BOARD:" << endl;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

//checks the constraints and runs backtracking algorith
int Queens::compute() {
  queens(0);
  return ans;
}


void Queens::queens(int i) {
  if (i == n) {
    ans++;
    return;
  }
  for(int c=0; c<n; c++) {
    //try (r,c)
    row[i] = c;
    //if same col, diag1, diag2 skip O(1)
    if(col[c] || diag1[i-c+n] || diag2[i+c]) {
      continue;
    }
    //mark col, diag1, diag2 as occupied
    col[c] = 1;
    diag1[i-c+n] = 1;
    diag2[i+c] = 1;

    queens(i+1);

    //unmark everything
    col[c] = 0;
    row[i] = 0;
    diag1[i-c +n] = 0;
    diag2[i+c] = 0;
  }
}
