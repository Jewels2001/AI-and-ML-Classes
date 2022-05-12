#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Queens.h"

void prompt() {
  cout << "Please enter your desired n (up to 15): " << endl;
  cout << "Any larger will take awhile as the backtracking algorithm is O(n^n)" << endl;
  cout << "A '0' will exit the program." << endl;
}


int main() {
  int n;
  cout << "Welcome to the N-Queens Problem v1.0 " <<
    "with backtracking search algorithm." << endl;
  prompt();
  while(cin >> n, n != 0) {
    if(n == 0) {
      return 0;
    }
    std::cin.ignore();
    Queens x(n);
    int ans = x.compute();
    cout << "ANSWER: " << ans << endl << endl;
    prompt();
  }
}
