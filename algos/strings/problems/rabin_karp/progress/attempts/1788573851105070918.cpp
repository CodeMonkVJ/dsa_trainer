#include <bits/stdc++.h>
#include <string>
using namespace std;

#define CHR_TO_INT(x) static_cast<unsigned char>(x)

static vector<int> rabinKarpSearch(const string &text, const string &pattern) {
  int n = text.length();
  int m = pattern.length();

  vector<int> ans;

  if (m > n || m == 0)
    return {};

  int patternHash = 0, currentWindowHash = 0, highestPow = 1;
  for (int i = 0; i < m; ++i) {
    patternHash = (patternHash * 4) + CHR_TO_INT(pattern[i]);
    currentWindowHash = (currentWindowHash * 4) + CHR_TO_INT(text[i]);
    if (i > 0)
      highestPow *= 4;
  }

  for (int i = 0; i < n - m + 1; i++) {
    if (i > 0) {
      currentWindowHash =
          ((currentWindowHash - (highestPow * CHR_TO_INT(text[i - 1]))) * 4) +
          CHR_TO_INT(text[i + m - 1]);
    }
    if (currentWindowHash == patternHash &&
        pattern.compare(text.substr(i, m)) == 0) {
      ans.push_back(i);
    }
  }

  return ans;
}
