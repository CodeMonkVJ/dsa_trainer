#include <bits/stdc++.h>
using namespace std;

class MedianStream {
  priority_queue<int> lower;
  priority_queue<int, vector<int>, greater<int>> upper;

  void rebalance() {
    if (lower.size() > upper.size() + 1) {
      upper.push(lower.top());
      lower.pop();
    } else if (upper.size() > lower.size()) {
      lower.push(upper.top());
      upper.pop();
    }
  }

public:
  void addNumber(int value) {
    if (lower.empty() || value <= lower.top()) lower.push(value);
    else upper.push(value);
    rebalance();
  }

  double getMedian() const {
    if (lower.empty()) return 0.0;
    if (lower.size() == upper.size())
      return (static_cast<double>(lower.top()) + upper.top()) / 2.0;
    return lower.top();
  }
};
