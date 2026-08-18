#include <bits/stdc++.h>
using namespace std;
#include "../../../../../test_protocol.hpp"

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(bool condition, const char *input, bool expected) {
  ++total;
  if (condition)
    ++passed;
  dsa_test::emit_case(input, expected ? "true" : "false",
                      condition ? "true" : "false", condition == expected);
}

bool validBoard(const vector<string> &board) {
  const int n = static_cast<int>(board.size());
  vector<int> columns(n, 0), down(2 * n + 1, 0), up(2 * n + 1, 0);
  for (int row = 0; row < n; ++row) {
    if (static_cast<int>(board[row].size()) != n)
      return false;
    for (int column = 0; column < n; ++column) {
      if (board[row][column] != 'Q' && board[row][column] != '.')
        return false;
      if (board[row][column] == 'Q') {
        ++columns[column];
        ++down[row - column + n];
        ++up[row + column];
      }
    }
  }
  for (int count : columns)
    if (count > 1)
      return false;
  for (int count : down)
    if (count > 1)
      return false;
  for (int count : up)
    if (count > 1)
      return false;
  for (const auto &row : board)
    if (count(row.begin(), row.end(), 'Q') != 1)
      return false;
  return true;
}

int main() {
  auto one = nQueens(1);
  check(one.size() == 1 && validBoard(one[0]) && one[0] == vector<string>{"Q"},
        R"({"n":1})", true);
  check(nQueens(2).empty() && nQueens(3).empty(), R"({"n":[2,3]})", true);
  auto four = nQueens(4);
  check(four.size() == 2, R"({"n":4})", true);
  check(all_of(four.begin(), four.end(), validBoard), R"({"n":4})", true);
  auto five = nQueens(5);
  check(five.size() == 10 && all_of(five.begin(), five.end(), validBoard),
        R"({"n":5})", true);
  check(nQueens(0).empty() && nQueens(-1).empty(), R"({"n":[0,-1]})", true);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
