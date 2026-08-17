#include <bits/stdc++.h>
using namespace std;

int maxProfit(const vector<int>& prices) {
  if (prices.empty()) return 0;
  int lowest = prices[0];
  int best = 0;
  for (size_t i = 1; i < prices.size(); ++i) {
    best = max(best, prices[i] - lowest);
    lowest = min(lowest, prices[i]);
  }
  return best;
}
