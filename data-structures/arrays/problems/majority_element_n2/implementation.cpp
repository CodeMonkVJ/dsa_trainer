#include <bits/stdc++.h>
using namespace std;

int majorityElement(const vector<int>& nums) {
  int candidate = 0;
  int votes = 0;
  for (int value : nums) {
    if (votes == 0) candidate = value;
    votes += value == candidate ? 1 : -1;
  }
  return candidate;
}

int main() { return 0; }
