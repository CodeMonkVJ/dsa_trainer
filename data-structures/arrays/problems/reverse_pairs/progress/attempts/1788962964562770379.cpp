#include <bits/stdc++.h>
using namespace std;

static vector<int> merge(vector<int> &left, vector<int> &right) {
  vector<int> ans;
  int n = left.size();
  int m = right.size();
  int i = 0, j = 0;
  while (i < n && j < m) {
    if (left[i] < right[j]) {
      ans.push_back(left[i++]);
    } else if (left[i] > right[j]) {
      ans.push_back(right[j++]);
    } else {
      ans.push_back(left[i++]);
      ans.push_back(right[j++]);
    }
  }
  while (i < n) {
    ans.push_back(left[i++]);
  }
  while (j < m) {
    ans.push_back(right[j++]);
  }
  return ans;
}

static vector<int> sort(vector<int> &values, long long &ans) {
  int l = values.size();
  if (l <= 1)
    return values;

  int split = l / 2;
  vector<int> left(values.begin(), values.begin() + split);
  vector<int> right(values.begin() + split, values.end());
  vector<int> sortedLeft = sort(left, ans);
  vector<int> sortedRight = sort(right, ans);

  int n = sortedLeft.size();
  int m = sortedRight.size();

  int j = 0;
  long long count = 0;
  for (int i = 0; i < n; i++) {
    while (j < m && sortedLeft[i] > 2LL * sortedRight[j])
      j++;
    count += j;
  }
  ans += count;
  return merge(sortedLeft, sortedRight);
}

long long reversePairs(vector<int> &nums) {
  long long ans = 0;
  vector<int> sorted = sort(nums, ans);
  for (int i = 0; i < nums.size(); i++) {
    nums[i] = sorted[i];
  }
  return ans;
}
