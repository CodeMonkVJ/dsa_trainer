#include <bits/stdc++.h>
using namespace std;

int largestRectangleArea(const vector<int> &heights) {
  int n = heights.size();
  if (n == 0)
    return 0;
  if (n == 1)
    return heights[0];

  int maxArea = 0;
  stack<int> s;
  s.push(0);

  for (int i = 1; i < n; i++) {
    while (!s.empty() && heights[i] < heights[s.top()]) {
      int top = s.top();
      s.pop();
      int right = i;
      int width = s.empty() ? i : right - s.top() - 1;
      maxArea = max(maxArea, heights[top] * width);
    }
    s.push(i);
  }

  while (!s.empty()) {
    int top = s.top();
    s.pop();
    int right = n;
    int width = s.empty() ? n : right - s.top() - 1;
    maxArea = max(maxArea, heights[top] * width);
  }

  return maxArea;
}
