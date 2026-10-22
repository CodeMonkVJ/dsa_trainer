#include <bits/stdc++.h>
using namespace std;

int minEggDrops(int eggs, int floors) {
  vector<vector<int>> dp(eggs + 1, vector<int>(floors + 1, 0));

  for (int i = 0; i <= eggs; i++) {
    dp[i][1] = 1;
  }
  for (int i = 0; i <= floors; i++) {
    dp[1][i] = i;
  }

  for (int e = 2; e <= eggs; e++) {
    for (int f = 2; f <= floors; f++) {
      int worstFloor = INT_MAX;
      for (int x = 1; x <= f; x++) {
        int worst = 1 + max(dp[e - 1][x - 1], dp[e][f - x]);
        worstFloor = min(worst, worstFloor);
      }
      dp[e][f] = worstFloor;
    }
  }

  return dp[eggs][floors];
}
