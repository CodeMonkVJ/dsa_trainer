#include <bits/stdc++.h>
using namespace std;

int largestRectangleArea(const vector<int>& heights) {
  long long best = 0;
  vector<int> starts;
  vector<int> indices;
  for (int i = 0; i <= static_cast<int>(heights.size()); ++i) {
    int current = i == static_cast<int>(heights.size()) ? 0 : heights[i];
    int start = i;
    while (!indices.empty() && heights[indices.back()] > current) {
      int index = indices.back();
      indices.pop_back();
      start = starts.back();
      starts.pop_back();
      best = max(best, static_cast<long long>(heights[index]) * (i - start));
    }
    if (indices.empty() || heights[indices.back()] < current) {
      indices.push_back(i);
      starts.push_back(start);
    }
  }
  return static_cast<int>(best);
}
