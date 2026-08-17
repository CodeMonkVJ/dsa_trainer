#include <bits/stdc++.h>
using namespace std;

int longestConsecutive(const vector<int>& nums) {
  unordered_set<int> values(nums.begin(), nums.end());
  int best = 0;
  for (int value : values) {
    if (values.count(value - 1)) continue;
    int length = 1;
    while (values.count(value + length)) ++length;
    best = max(best, length);
  }
  return best;
}

int main() { cout << longestConsecutive({100, 4, 200, 1, 3, 2}) << '\n'; return 0; }
