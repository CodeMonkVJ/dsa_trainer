#include <bits/stdc++.h>
using namespace std;

struct Item {
  int weight;
  int value;
};

static int maximumValue(const vector<Item> &items, int capacity) {
  int count = items.size();
  vector<vector<int>> dp(count + 1, vector<int>(capacity + 1, 0));

  for (int i = 1; i <= count; i++) {
    for (int w = 1; w <= capacity; w++) {
      if (items[i - 1].weight <= w) {
        dp[i][w] = max(dp[i - 1][w],
                       items[i - 1].value + dp[i - 1][w - items[i - 1].weight]);
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }

  return dp[count][capacity];
}
