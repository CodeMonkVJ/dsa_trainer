#include <bits/stdc++.h>
using namespace std;

int findDuplicate(const vector<int>& values) {
  if (values.size() < 2) return -1;

  int slow = values[0];
  int fast = values[values[0]];
  while (slow != fast) {
    slow = values[slow];
    fast = values[values[fast]];
  }

  slow = 0;
  while (slow != fast) {
    slow = values[slow];
    fast = values[fast];
  }
  return slow;
}
