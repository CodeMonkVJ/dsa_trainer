#include <bits/stdc++.h>
using namespace std;

pair<int, int> findRepeatingMissing(const vector<int> &values) {
  int n = values.size();

  int expectedSum = (n * (n + 1)) / 2;
  int expectedSquaredSum = (n * (n + 1) * ((2 * n) + 1)) / 6;

  int actualSum = 0;
  int actualSquaredSum = 0;

  for (auto val : values) {
    actualSum += val;
    actualSquaredSum += val * val;
  }

  int diff = actualSum - expectedSum;
  int squaredDiff = actualSquaredSum - expectedSquaredSum;

  int sum = squaredDiff / diff;

  pair<int, int> ans;
  ans.second = (sum - diff) / 2;
  ans.first = sum - ans.second;

  return ans;
}
