#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(const string &s) {
  int left = 0;
  int right = s.length() - 1;

  while (left <= right) {
    if (s[left] != s[right]) {
      return false;
    }
    left++;
    right--;
  }

  return true;
}

void backtrack(int start, const string &s, vector<vector<string>> &result,
               vector<string> &current) {
  int n = s.length();
  if (start == n) {
    result.push_back(current);
    return;
  }

  for (int end = start; end < n; end++) {
    string t = s.substr(start, end - start + 1);
    if (isPalindrome(t)) {
      current.push_back(t);
      backtrack(end + 1, s, result, current);
      current.pop_back();
    }
  }
}

vector<vector<string>> partition(const string &s) {
  vector<vector<string>> result;
  vector<string> current;

  backtrack(0, s, result, current);

  return result;
}
