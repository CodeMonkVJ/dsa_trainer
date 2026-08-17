#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> mergeIntervals(vector<vector<int>> intervals) {
  if (intervals.empty()) return {};

  sort(intervals.begin(), intervals.end(), [](const vector<int>& left, const vector<int>& right) {
    if (left[0] != right[0]) return left[0] < right[0];
    return left[1] < right[1];
  });

  vector<vector<int>> merged;
  merged.push_back(intervals[0]);
  for (size_t i = 1; i < intervals.size(); ++i) {
    vector<int>& current = merged.back();
    if (intervals[i][0] <= current[1]) {
      current[1] = max(current[1], intervals[i][1]);
    } else {
      merged.push_back(intervals[i]);
    }
  }
  return merged;
}
