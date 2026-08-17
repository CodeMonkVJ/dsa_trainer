#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> generatePascal(int numRows) {
  if (numRows <= 0) return {};
  vector<vector<int>> triangle;
  triangle.reserve(numRows);
  for (int r = 0; r < numRows; ++r) {
    triangle.push_back(vector<int>(r + 1, 1));
    for (int c = 1; c < r; ++c) {
      triangle[r][c] = triangle[r - 1][c - 1] + triangle[r - 1][c];
    }
  }
  return triangle;
}
