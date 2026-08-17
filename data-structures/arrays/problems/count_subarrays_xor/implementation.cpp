#include <bits/stdc++.h>
using namespace std;

long long countSubarraysWithXor(const vector<int>& nums, int target) {
  unordered_map<int, long long> frequency{{0, 1}};
  int prefix = 0;
  long long answer = 0;
  for (int value : nums) {
    prefix ^= value;
    answer += frequency[prefix ^ target];
    ++frequency[prefix];
  }
  return answer;
}

int main() { cout << countSubarraysWithXor({4, 2, 2, 6, 4}, 6) << '\n'; return 0; }
