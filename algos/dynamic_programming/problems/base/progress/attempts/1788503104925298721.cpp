#include <bits/stdc++.h>
using namespace std;

struct Item {
  int weight;
  int value;
};

static int maximumValue(const vector<Item> &items, int capacity) {
  int maxValue = 0;
  int n = items.size();
  if (n == 0)
    return 0;

  vector<int> dp(capacity + 1, 0);

  for (int i = 0; i < n; i++) {
    int w = items[i].weight;
    int v = items[i].value;
    if (capacity >= w) {
      for (int c = capacity; c >= w; c--) {
        dp[c] = max(dp[c], v + dp[c - w]);
      }
    }
  }

  return dp[capacity];
}
