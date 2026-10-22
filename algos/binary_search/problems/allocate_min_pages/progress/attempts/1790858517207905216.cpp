#include <bits/stdc++.h>
using namespace std;

bool feasible(const vector<int> &pages, long long val, int students) {
  long long curr = 0;

  int count = 1;
  for (auto page : pages) {
    if (curr + page <= val) {
      curr += page;
    } else {
      curr = page;

      count++;
    }
  }
  return count <= students;
}

long long allocateMinimumPages(const vector<int> &pages, int students) {
  int n = pages.size();

  if (students > n)
    return -1LL;

  long long left = *max_element(pages.begin(), pages.end());
  long long right = accumulate(pages.begin(), pages.end(), 0LL);

  while (left < right) {
    long long mid = left + (right - left) / 2;

    if (feasible(pages, mid, students)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  return left;
}
