#include <bits/stdc++.h>
#include <deque>
using namespace std;

static vector<int> slidingWindowMaximum(const vector<int> &values,
                                        int windowSize) {
  int n = values.size();
  if (n == 0)
    return {};
  if (windowSize <= 0 || windowSize > n)
    return {};

  deque<int> q;
  vector<int> ans;

  for (int i = 0; i < n; i++) {
    while (!q.empty() && q.front() <= i - windowSize)
      q.pop_front();

    while (!q.empty() && values[q.back()] <= values[i])
      q.pop_back();

    q.push_back(i);

    if (i >= windowSize - 1)
      ans.push_back(values[q.front()]);
  }

  return ans;
}
