#include <bits/stdc++.h>
using namespace std;

int longestUniqueSubstring(const string& text) {
  array<int, 256> last;
  last.fill(-1);
  int left = 0, best = 0;
  for (int right = 0; right < static_cast<int>(text.size()); ++right) {
    unsigned char current = static_cast<unsigned char>(text[right]);
    left = max(left, last[current] + 1);
    best = max(best, right - left + 1);
    last[current] = right;
  }
  return best;
}

int main() { cout << longestUniqueSubstring("abcabcbb") << '\n'; return 0; }
