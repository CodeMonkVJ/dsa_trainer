#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

int longestUniqueSubstring(const string &text) {
  int left = 0;
  int maxLen = 0;
  int n = text.length();
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;

  set<char> unique;
  for (int right = 0; right < n; right++) {
    while (unique.count(text[right])) {
      unique.erase(text[left]);
      left++;
    }

    unique.insert(text[right]);
    maxLen = max(maxLen, right - left + 1);
  }

  return maxLen;
}
