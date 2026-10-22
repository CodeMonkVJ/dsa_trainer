#include <bits/stdc++.h>
using namespace std;

int editDistance(const string &input, const string &output) {
  int n = input.length();
  int m = output.length();

  if (n == 0)
    return m;
  if (m == 0)
    return n;

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  for (int i = 0; i <= n; i++) {
    dp[i][0] = i;
  }
  for (int j = 0; j <= m; j++) {
    dp[0][j] = j;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (input[i - 1] == output[j - 1])
        dp[i][j] = dp[i - 1][j - 1];
      else {
        dp[i][j] = 1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
      }
    }
  }

  return dp[n][m];
}
