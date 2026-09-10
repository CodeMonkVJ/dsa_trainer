#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int maxMeetings(const vector<int> &start, const vector<int> &finish) {
  int n = start.size();
  if (n == 0)
    return 0;
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) {
    pairs.push_back({finish[i], start[i]});
  }

  sort(pairs.begin(), pairs.end());

  int count = 1, lastFinish = pairs[0].first;
  for (int i = 1; i < n; i++) {
    if (pairs[i].second >= lastFinish) {
      count++;
      lastFinish = pairs[i].first;
    }
  }

  return count;
}

int main() {
  cout << maxMeetings({1, 3, 0, 5, 8, 5}, {2, 4, 5, 7, 9, 9}) << '\n';
}
