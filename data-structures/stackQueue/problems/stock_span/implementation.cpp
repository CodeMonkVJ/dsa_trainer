#include <bits/stdc++.h>
using namespace std;

vector<int> stockSpan(const vector<int>& prices) {
  vector<int> spans(prices.size());
  vector<int> indices;
  for (int i = 0; i < static_cast<int>(prices.size()); ++i) {
    while (!indices.empty() && prices[indices.back()] <= prices[i]) indices.pop_back();
    spans[i] = indices.empty() ? i + 1 : i - indices.back();
    indices.push_back(i);
  }
  return spans;
}

int main() {
  for (int value : stockSpan({100, 80, 60, 70, 60, 75, 85})) cout << value << ' ';
  cout << '\n';
  return 0;
}
