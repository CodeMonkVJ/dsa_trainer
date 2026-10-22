#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> mergeIntervals(vector<vector<int>> intervals) {
  if (intervals.empty())
    return {};

  sort(intervals.begin(), intervals.end());

  vector<int> curr = intervals[0];
  vector<vector<int>> ans;

  for (int i = 1; i < intervals.size(); i++) {
    int start = intervals[i][0];
    int end = intervals[i][1];

    if (start <= curr[1]) {
      curr[1] = max(end, curr[1]);
    } else {
      ans.push_back(curr);
      curr = intervals[i];
    }
  }

  ans.push_back(curr);

  return ans;
}
