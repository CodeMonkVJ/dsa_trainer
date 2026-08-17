#include <bits/stdc++.h>
using namespace std;

void mergeSortedArrays(vector<int>& first, vector<int>& second) {
  const int total = static_cast<int>(first.size() + second.size());
  auto valueAt = [&](int index) -> int& {
    if (index < static_cast<int>(first.size())) return first[index];
    return second[index - static_cast<int>(first.size())];
  };

  for (int gap = (total + 1) / 2; gap > 0; gap = gap == 1 ? 0 : (gap + 1) / 2) {
    for (int left = 0, right = gap; right < total; ++left, ++right) {
      if (valueAt(left) > valueAt(right)) swap(valueAt(left), valueAt(right));
    }
  }
}
