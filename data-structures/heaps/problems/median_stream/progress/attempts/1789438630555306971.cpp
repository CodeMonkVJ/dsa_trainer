#include <bits/stdc++.h>
#include <functional>
#include <queue>
using namespace std;

class MedianStream {
  priority_queue<int, vector<int>, greater<int>> upper;
  priority_queue<int, vector<int>> lower;

public:
  void rebalance() {
    if (lower.size() > upper.size() + 1) {
      upper.push(lower.top());
      lower.pop();
    } else if (upper.size() > lower.size()) {
      lower.push(upper.top());
      upper.pop();
    }
  }
  void addNumber(int value) {
    if (lower.empty() || value <= lower.top()) {
      lower.push(value);
    } else {
      upper.push(value);
    }
    rebalance();
  }
  double getMedian() const {
    if (lower.size() == 0 && upper.size() == 0)
      return 0.0;
    if (lower.size() == upper.size())
      return ((double)lower.top() + upper.top()) / 2.0;
    else
      return (double)lower.top();
  }
};
