#include <bits/stdc++.h>
#include <vector>
using namespace std;

void computeFactorials(vector<int> &facts) {
  facts[0] = 1;
  for (int i = 1; i <= 9; i++) {
    facts[i] = facts[i - 1] * i;
  }
}

string getPermutation(int n, int k) {
  string ans;
  vector<int> facts(10);
  computeFactorials(facts);

  if (n > 9 || n < 1 || k < 1 || k > facts[n])
    return "";

  vector<int> available;
  for (int i = 1; i <= n; i++)
    available.push_back(i);

  int remaining = n;

  while (remaining > 0) {
    int blockSize = facts[remaining - 1];
    int index = (k - 1) / blockSize;
    int chosen = available[index];
    ans.push_back('0' + chosen);

    k = (k - 1) % blockSize + 1;
    auto it = find(available.begin(), available.end(), chosen);

    if (it != available.end()) {
      available.erase(it);
    }

    remaining--;
  }

  return ans;
}
