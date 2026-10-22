#include <bits/stdc++.h>
#include <vector>
using namespace std;

void recHelper(int index, vector<int> &curr, const vector<int> &values,
               vector<vector<int>> &ans, vector<int> &visited) {
  if (index == values.size()) {
    ans.push_back(curr);
    return;
  }

  for (int i = 0; i < values.size(); i++) {
    if (i > 0 && values[i] == values[i - 1] && visited[i - 1] == -1)
      continue;
    if (visited[i] == -1) {
      curr.push_back(values[i]);
      visited[i] = 1;
      recHelper(index + 1, curr, values, ans, visited);
      curr.pop_back();
      visited[i] = -1;
    }
  }
}

vector<vector<int>> permutations(vector<int> values) {
  vector<vector<int>> ans;
  vector<int> curr;
  vector<int> visited(values.size(), -1);

  sort(values.begin(), values.end());

  recHelper(0, curr, values, ans, visited);

  return ans;
}
