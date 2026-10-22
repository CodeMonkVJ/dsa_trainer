#include <bits/stdc++.h>
#include <climits>
using namespace std;

int coinChange(const vector<int> &coins, int k) {
  if (k < 0)
    return -1;
  vector<int> dp(k + 1, -1);
  dp[0] = 0;

  for (int i = 0; i <= k; i++) {
    int best = INT_MAX;

    for (auto c : coins) {
      if (c <= 0)
        continue;

      if (c <= i && dp[i - c] != -1) {
        best = min(best, 1 + dp[i - c]);
      }
    }

    if (best != INT_MAX)
      dp[i] = best;
  }

  return dp[k];
}
