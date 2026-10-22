#include <bits/stdc++.h>
using namespace std;

int largestRectangleArea(const vector<int> &heights) {
  stack<int> s;
  int maxArea = 0;
  int n = heights.size();

  for (int i = 0; i < n; i++) {
    while (!s.empty() && heights[s.top()] > heights[i]) {
      int top = s.top();
      s.pop();

      int width = s.empty() ? i : i - s.top() - 1;

      maxArea = max(maxArea, heights[top] * width);
    }
    s.push(i);
  }

  while (!s.empty()) {
    int top = s.top();
    s.pop();

    int width = s.empty() ? n : n - s.top() - 1;

    maxArea = max(maxArea, heights[top] * width);
  }
  return maxArea;
}
