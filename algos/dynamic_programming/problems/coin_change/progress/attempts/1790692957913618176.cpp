#include <bits/stdc++.h>
#include <climits>
using namespace std;

int coinChange(const vector<int> &coins, int amount) {
  if (amount < 0)
    return -1;
  vector<int> dp(amount + 1, amount + 1);
  dp[0] = 0;

  for (int x = 1; x <= amount; x++) {
    for (auto coin : coins) {
      if (coin <= x)
        dp[x] = min(dp[x], 1 + dp[x - coin]);
    }
  }

  return dp[amount] == amount + 1 ? -1 : dp[amount];
}
