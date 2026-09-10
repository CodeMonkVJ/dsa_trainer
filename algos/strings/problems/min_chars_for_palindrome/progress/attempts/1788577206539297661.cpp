#include <bits/stdc++.h>
using namespace std;

vector<int> buildLpsArray(string lpsString) {
  int n = lpsString.length();
  vector<int> ans(n, 0);
  int len = 0;
  int i = 1;
  while (i < n) {
    if (lpsString[i] == lpsString[len]) {
      len++;
      ans[i] = len;
      i++;
    } else {
      if (len > 0) {
        len = ans[len - 1];
      } else {
        ans[i] = 0;
        i++;
      }
    }
  }

  return ans;
}

int minCharsForPalindrome(const string &s) {
  int n = s.length();

  if (n == 0)
    return 0;

  string reversed(s.rbegin(), s.rend());
  string lpsString = s + '|' + reversed;

  vector<int> lpsArray = buildLpsArray(lpsString);

  return n - lpsArray.back();
}
