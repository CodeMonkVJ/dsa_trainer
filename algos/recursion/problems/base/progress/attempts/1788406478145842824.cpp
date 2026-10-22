#include <bits/stdc++.h>
using namespace std;

void recHelper(int index, int currentSum, const vector<int> &a,
               vector<int> &ans) {
  if (index == a.size()) {
    ans.push_back(currentSum);
    return;
  }

  recHelper(index + 1, currentSum + a[index], a, ans);
  recHelper(index + 1, currentSum, a, ans);
}

vector<int> subsetSums(const vector<int> &a) {
  vector<int> ans;
  recHelper(0, 0, a, ans);
  return ans;
}
