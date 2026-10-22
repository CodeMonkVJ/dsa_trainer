#include <bits/stdc++.h>
using namespace std;

int rodCutting(const vector<int> &prices, int rodLength) {
  int n = prices.size();
  vector<int> dp(rodLength + 1);
  for (int l = 1; l <= rodLength; l++) {
    int bestPrice = 0;
    for (int piece = 1; piece <= min(l, n); piece++) {
      bestPrice = max(bestPrice, prices[piece - 1] + dp[l - piece]);
    }
    dp[l] = bestPrice;
  }

  return dp[rodLength];
}
