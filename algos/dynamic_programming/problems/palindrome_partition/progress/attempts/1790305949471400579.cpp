#include <bits/stdc++.h>
using namespace std;

vector<vector<bool>> generatePalTable(const string &s) {
  int n = s.length();
  vector<vector<bool>> pal(n, vector<bool>(n, false));

  for (int len = 1; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      if (s[l] == s[r] && (len <= 2 || pal[l + 1][r - 1])) {
        pal[l][r] = true;
      }
    }
  }

  return pal;
}

int minPalindromeCuts(const string &input) {
  int ans = 0;
  int n = input.length();
  if (n <= 1)
    return 0;
  vector<vector<bool>> pal = generatePalTable(input);
  vector<int> cuts(n, 0);

  for (int i = 0; i < n; i++) {
    cuts[i] = i;
    for (int j = 0; j <= i; j++) {
      if (pal[j][i]) {
        if (j == 0)
          cuts[i] = 0;
        else
          cuts[i] = min(cuts[i], cuts[j - 1] + 1);
      }
    }
  }

  return cuts[n - 1];
}
