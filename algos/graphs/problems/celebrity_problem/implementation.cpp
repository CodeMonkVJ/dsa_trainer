#include <bits/stdc++.h>
using namespace std;

int findCelebrity(const vector<vector<int>>& knows) {
  int n = static_cast<int>(knows.size());
  if (n == 0) return -1;
  int candidate = 0;
  for (int person = 1; person < n; ++person) {
    if (knows[candidate][person]) candidate = person;
  }
  for (int person = 0; person < n; ++person) {
    if (person == candidate) continue;
    if (knows[candidate][person] || !knows[person][candidate]) return -1;
  }
  return candidate;
}
