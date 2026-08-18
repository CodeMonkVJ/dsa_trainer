#include <bits/stdc++.h>
using namespace std;

int minCharsForPalindrome(const string &s) {
  return static_cast<int>(s.size());
}

int main() {
  cout << minCharsForPalindrome("AACECAAAA") << '\n';
  return 0;
}
