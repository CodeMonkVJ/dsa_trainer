#include <bits/stdc++.h>
using namespace std;

bool checkGreedy(const vector<int> &stalls, int dist, int cows) {
  int placedCows = 1, lastCowPos = stalls[0];

  for (int i = 1; i < stalls.size(); i++) {
    int stall = stalls[i];
    if (stall - lastCowPos >= dist) {
      lastCowPos = stall;
      placedCows++;
    }

    if (placedCows >= cows)
      return true;
  }

  return false;
}

int aggressiveCows(const vector<int> &stalls, int cows) {
  int n = stalls.size();
  if (n == 0 || cows <= 1)
    return -1;

  vector<int> sortedStalls = stalls;
  sort(sortedStalls.begin(), sortedStalls.end());

  int low = 0;
  int high = sortedStalls[n - 1] - sortedStalls[0];
  int ans = 0;

  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (checkGreedy(sortedStalls, mid, cows)) {
      low = mid + 1;
      ans = mid;
    } else {
      high = mid - 1;
    }
  }

  return ans;
}
