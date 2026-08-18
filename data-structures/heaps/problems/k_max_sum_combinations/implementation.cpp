#include <bits/stdc++.h>
using namespace std;

vector<int> kMaxSumCombinations(vector<int> A, vector<int> B, int k) {
  sort(A.begin(), A.end(), greater<int>());
  sort(B.begin(), B.end(), greater<int>());
  using Node = tuple<int, int, int>;
  priority_queue<Node> heap;
  set<pair<int, int>> seen;
  heap.emplace(A[0] + B[0], 0, 0);
  seen.emplace(0, 0);
  vector<int> result;
  while (!heap.empty() && (int)result.size() < k) {
    auto [sum, i, j] = heap.top();
    heap.pop();
    result.push_back(sum);
    if (i + 1 < (int)A.size() && seen.emplace(i + 1, j).second)
      heap.emplace(A[i + 1] + B[j], i + 1, j);
    if (j + 1 < (int)B.size() && seen.emplace(i, j + 1).second)
      heap.emplace(A[i] + B[j + 1], i, j + 1);
  }
  return result;
}

int main() { return 0; }
