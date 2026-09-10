#include <bits/stdc++.h>
using namespace std;

bool wordBreak(string s, vector<string> dictionary) {
  int l = s.length();
  if (l == 0)
    return true;

  vector<int> dp(l + 1, false);
  dp[0] = true;
  for (int i = 0; i <= l; i++) {
    if (!dp[i])
      continue;
    for (auto word : dictionary) {
      if (word.empty())
        continue;
      int wordLength = word.length();
      if (i + wordLength <= l && s.substr(i, wordLength) == word) {
        int next = i + wordLength;
        dp[next] = true;
      }
    }
  }

  return dp[l];
}
