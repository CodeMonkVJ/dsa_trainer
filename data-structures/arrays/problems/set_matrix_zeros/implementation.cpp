#include <bits/stdc++.h>
using namespace std;

void setZeroes(vector<vector<int>>& matrix) {
  if (matrix.empty() || matrix[0].empty()) return;

  const int rows = static_cast<int>(matrix.size());
  const int cols = static_cast<int>(matrix[0].size());
  bool firstRowZero = false;
  bool firstColZero = false;

  for (int c = 0; c < cols; ++c) firstRowZero |= matrix[0][c] == 0;
  for (int r = 0; r < rows; ++r) firstColZero |= matrix[r][0] == 0;

  for (int r = 1; r < rows; ++r) {
    for (int c = 1; c < cols; ++c) {
      if (matrix[r][c] == 0) {
        matrix[r][0] = 0;
        matrix[0][c] = 0;
      }
    }
  }

  for (int r = 1; r < rows; ++r) {
    for (int c = 1; c < cols; ++c) {
      if (matrix[r][0] == 0 || matrix[0][c] == 0) matrix[r][c] = 0;
    }
  }
  if (firstRowZero) fill(matrix[0].begin(), matrix[0].end(), 0);
  if (firstColZero) {
    for (auto& row : matrix) row[0] = 0;
  }
}
