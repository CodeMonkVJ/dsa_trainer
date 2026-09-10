#include <bits/stdc++.h>
using namespace std;

void updateBestPalindrome(const string &palindromeString, int left, int right,
                          int &bestLength, int &bestStart,
                          string &bestPalindrome) {
  int currLength = right - left + 1;
  if (currLength > bestLength) {
    bestLength = currLength;
    bestStart = left;
    bestPalindrome = palindromeString.substr(left, currLength);
  } else if (currLength == bestLength) {
    if (left < bestStart) {
      bestStart = left;
      bestPalindrome = palindromeString.substr(left, currLength);
    }
  }
}

static string longestPalindromicSubstring(const string &palindromeString) {
  int bestStart = 0, bestLength = 0;
  string bestPalindrome = "";
  int n = palindromeString.length();
  if (n == 0)
    return "";
  for (int i = 0; i < n; i++) {
    // odd length palindrome
    int left = i, right = i;
    while (left >= 0 && right < n &&
           palindromeString[left] == palindromeString[right]) {
      updateBestPalindrome(palindromeString, left, right, bestLength, bestStart,
                           bestPalindrome);
      left--;
      right++;
    }

    // even length palindrome
    left = i, right = i + 1;
    while (left >= 0 && right < n &&
           palindromeString[left] == palindromeString[right]) {
      updateBestPalindrome(palindromeString, left, right, bestLength, bestStart,
                           bestPalindrome);
      left--;
      right++;
    }
  }

  return bestPalindrome;
}
