#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

int longestZeroSumSubarray(const vector<int> &nums) {
  unordered_map<int, int> firstSeen;
  firstSeen[0] = -1;

  int n = nums.size();
  vector<int> prefixSum(n);
  int currSum = 0;
  int ans = INT_MIN;

  for (int i = 0; i < nums.size(); i++) {
    currSum += nums[i];
    prefixSum[i] = currSum;
    if (firstSeen.find(currSum) != firstSeen.end()) {
      firstSeen[currSum] = min(firstSeen[currSum], i);
      ans = max(ans, i - firstSeen[currSum]);
    } else {
      firstSeen[currSum] = i;
    }
  }

  return ans != INT_MIN ? ans : 0;
}
