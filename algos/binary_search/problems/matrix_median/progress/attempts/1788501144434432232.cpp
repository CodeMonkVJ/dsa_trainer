#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int matrixMedian(const vector<vector<int>> &matrix) {
  int n = matrix.size();
  int elCount = 0;
  if (n == 0)
    return 0;

  int low = INT_MAX, high = INT_MIN;
  for (int i = 0; i < n; i++) {
    int m = matrix[i].size();
    elCount += m;
    if (m > 0) {
      low = min(low, matrix[i][0]);
      high = max(high, matrix[i][m - 1]);
    }
  }

  int req = elCount / 2 + 1;

  while (low < high) {
    int mid = low + (static_cast<long long>(high) - low) / 2;

    int ubCount = 0;
    for (int i = 0; i < n; i++) {
      int m = matrix[i].size();
      if (m > 0) {
        auto it = upper_bound(matrix[i].begin(), matrix[i].end(), mid);
        ubCount += it - matrix[i].begin();
      }
    }

    if (ubCount < req) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }

  return low;
}
