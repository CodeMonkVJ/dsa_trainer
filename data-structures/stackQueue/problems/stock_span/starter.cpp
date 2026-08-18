#include <bits/stdc++.h>
using namespace std;

vector<int> stockSpan(const vector<int> &prices) {
  return vector<int>(prices.size(), 1);
}

int main() {
  for (int value : stockSpan({100, 80, 60, 70, 60, 75, 85}))
    cout << value << ' ';
  cout << '\n';
}
