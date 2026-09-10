#include <bits/stdc++.h>
using namespace std;

int longestUniqueSubstring(const string &text) {
  int lastSeen[256];
  memset(lastSeen, -1, 256 * sizeof(int));
  int n = text.length();
  int best = 0;

  int L = 0;

  for (int R = 0; R < n; R++) {
    unsigned char c = static_cast<unsigned char>(text[R]);
    if (lastSeen[c] != -1) {
      L = max(L, lastSeen[c] + 1);
    }
    lastSeen[c] = R;
    best = max(best, R - L + 1);
  }

  return best;
}
