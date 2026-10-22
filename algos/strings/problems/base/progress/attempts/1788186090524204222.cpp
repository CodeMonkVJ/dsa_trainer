#include <bits/stdc++.h>
using namespace std;

static vector<int> buildPrefixTable(const string &arr) {
  int n = arr.length();
  vector<int> lps(n);
  int i = 1, len = 0;

  while (i < n) {
    if (arr[i] != arr[len]) {
      if (len > 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    } else {
      len++;
      lps[i] = len;
      i++;
    }
  }

  return lps;
}

static vector<int> findOccurrences(const string &text, const string &pattern) {
  int i = 0, j = 0;
  int n = text.length(), m = pattern.length();
  vector<int> ans;

  if (m == 0)
    return ans;

  vector<int> lps = buildPrefixTable(pattern);

  while (i < n) {
    if (text[i] == pattern[j]) {
      i++;
      j++;

      if (j == m) {
        ans.push_back(i - m);
        j = lps[j - 1];
      }
    } else {
      if (j > 0) {
        j = lps[j - 1];
      } else if (j == 0) {
        i++;
      } else {
        ans.push_back(i - m);
        j = lps[j - 1];
      }
    }
  }

  return ans;
}
