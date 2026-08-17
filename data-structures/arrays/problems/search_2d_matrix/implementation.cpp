#include <bits/stdc++.h>
using namespace std;

bool searchMatrix(const vector<vector<int>>& matrix, int target) {
  if (matrix.empty() || matrix[0].empty()) return false;
  const int rows = static_cast<int>(matrix.size());
  const int cols = static_cast<int>(matrix[0].size());
  int left = 0;
  int right = rows * cols - 1;
  while (left <= right) {
    const int mid = left + (right - left) / 2;
    const int value = matrix[mid / cols][mid % cols];
    if (value == target) return true;
    if (value < target) left = mid + 1;
    else right = mid - 1;
  }
  return false;
}

int main() { return 0; }
