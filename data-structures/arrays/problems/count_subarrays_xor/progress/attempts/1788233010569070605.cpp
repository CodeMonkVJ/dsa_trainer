#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

long long countSubarraysWithXor(const vector<int> &nums, int target) {
  long long ans = 0;
  unordered_map<int, int> freq;
  freq[0] = 1;
  int current = 0;
  for (int i = 0; i < nums.size(); i++) {
    current ^= nums[i];
    ans += freq[current ^ target];
    freq[current]++;
  }

  return ans;
}
