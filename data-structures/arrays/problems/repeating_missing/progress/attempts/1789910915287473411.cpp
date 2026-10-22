#include <bits/stdc++.h>
#include <utility>
using namespace std;

pair<int, int> findRepeatingMissing(const vector<int> &values) {
  int n = values.size();
  long long actualSum = 0, expectedSum = n * (n + 1) / 2, actualSquaredSum = 0,
            expectedSquaredSum = n * (n + 1) * (2 * n + 1) / 6;

  for (auto v : values) {
    actualSum += v;
    actualSquaredSum += (long long)(v * v);
  }

  long long diff = actualSum - expectedSum,
            squaredDiff = actualSquaredSum - expectedSquaredSum;

  pair<int, int> ans = make_pair(0, 0);
  long long sum = squaredDiff / diff;

  ans.second = (sum - diff) / 2;
  ans.first = sum - ans.second;

  return ans;
}
