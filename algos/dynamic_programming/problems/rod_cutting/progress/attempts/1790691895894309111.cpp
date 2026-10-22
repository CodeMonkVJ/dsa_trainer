#include <bits/stdc++.h>
using namespace std;

int rodCutting(const vector<int> &prices, int n) {
  vector<int> dp(n + 1, 0);

  for (int len = 1; len <= n; len++) {
    for (int cut = 1; cut <= len && cut <= prices.size(); cut++) {
      dp[len] = max(dp[len], prices[cut - 1] + dp[len - cut]);
    }
  }

  return dp[n];
}
