#include <bits/stdc++.h>
using namespace std;

bool greedyCheck(const vector<int> &stalls, const int &D, const int &cows) {
  int placed = 1;
  int lastPlaced = stalls[0];
  for (int i = 1; i < stalls.size(); i++) {
    if (stalls[i] - lastPlaced >= D) {
      placed++;
      lastPlaced = stalls[i];
    }
  }

  return placed >= cows;
}

int aggressiveCows(const vector<int> &stalls, int cows) {
  vector<int> sortedStalls = stalls;
  int ans = 0;
  int n = stalls.size();
  if (n == 0)
    return 0;
  sort(sortedStalls.begin(), sortedStalls.end());

  int right = sortedStalls[n - 1] - sortedStalls[0];
  int left = 0;

  while (left <= right) {
    int D = left + (right - left) / 2;

    if (greedyCheck(sortedStalls, D, cows)) {
      left = D + 1;
      ans = D;
    } else
      right = D - 1;
  }

  return ans;
}
