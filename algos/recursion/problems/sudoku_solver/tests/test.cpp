#include <bits/stdc++.h>
using namespace std;
#include "../../../../../test_protocol.hpp"
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char *input, bool expected) {
  ++total;
  if (ok)
    ++passed;
  dsa_test::emit_case(input, expected ? "true" : "false", ok ? "true" : "false",
                      ok == expected);
}
bool valid(const vector<vector<char>> &b) {
  if (b.size() != 9)
    return false;
  for (int i = 0; i < 9; ++i) {
    int row = 0, col = 0;
    for (int j = 0; j < 9; ++j) {
      if (b[i][j] < '1' || b[i][j] > '9')
        return false;
      row |= 1 << (b[i][j] - '1');
      col |= 1 << (b[j][i] - '1');
    }
    if (row != 511 || col != 511)
      return false;
  }
  for (int r = 0; r < 9; r += 3)
    for (int c = 0; c < 9; c += 3) {
      int mask = 0;
      for (int i = r; i < r + 3; ++i)
        for (int j = c; j < c + 3; ++j)
          mask |= 1 << (b[i][j] - '1');
      if (mask != 511)
        return false;
    }
  return true;
}
int main() {
  vector<vector<char>> puzzle = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  auto original = puzzle;
  check(solveSudoku(puzzle) && valid(puzzle), R"({"board":"standard puzzle"})",
        true);
  check(puzzle[0][0] == original[0][0] && puzzle[0][1] == original[0][1],
        R"({"board":"standard puzzle","property":"clues preserved"})", true);
  auto bad = original;
  bad[0][1] = '5';
  check(!solveSudoku(bad), R"({"board":"duplicate clue"})", true);
  vector<vector<char>> empty(9, vector<char>(9, '.'));
  check(solveSudoku(empty) && valid(empty), R"({"board":"empty 9x9"})", true);
  auto invalid = original;
  invalid[0][0] = 'x';
  check(!solveSudoku(invalid), R"({"board":"invalid character x"})", true);
  vector<vector<char>> wrong(8, vector<char>(9, '.'));
  check(!solveSudoku(wrong), R"({"board":"8x9"})", true);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
