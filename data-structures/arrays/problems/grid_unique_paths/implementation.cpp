#include <bits/stdc++.h>
using namespace std;

long long uniquePaths(int rows, int columns) {
  if (rows <= 0 || columns <= 0) return 0;
  vector<long long> ways(columns, 1);
  for (int row = 1; row < rows; ++row) {
    for (int column = 1; column < columns; ++column) {
      ways[column] += ways[column - 1];
    }
  }
  return ways.back();
}

int main() { return 0; }
