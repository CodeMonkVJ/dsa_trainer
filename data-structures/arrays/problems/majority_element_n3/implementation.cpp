#include <bits/stdc++.h>
using namespace std;

vector<int> majorityElements(const vector<int>& nums) {
  int first = 0, second = 0;
  int firstCount = 0, secondCount = 0;
  for (int value : nums) {
    if (firstCount > 0 && value == first) ++firstCount;
    else if (secondCount > 0 && value == second) ++secondCount;
    else if (firstCount == 0) first = value, firstCount = 1;
    else if (secondCount == 0) second = value, secondCount = 1;
    else --firstCount, --secondCount;
  }

  firstCount = secondCount = 0;
  for (int value : nums) {
    if (value == first) ++firstCount;
    else if (value == second) ++secondCount;
  }
  vector<int> result;
  if (firstCount > static_cast<int>(nums.size() / 3)) result.push_back(first);
  if (second != first && secondCount > static_cast<int>(nums.size() / 3)) result.push_back(second);
  sort(result.begin(), result.end());
  return result;
}

int main() { return 0; }
