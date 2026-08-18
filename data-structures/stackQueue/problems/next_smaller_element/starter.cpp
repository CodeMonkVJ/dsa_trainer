#include <bits/stdc++.h>
using namespace std;

vector<int> nextSmallerElements(const vector<int> &values) {
  return vector<int>(values.size(), -1);
}

int main() {
  for (int value : nextSmallerElements({4, 8, 5, 2, 25}))
    cout << value << ' ';
  cout << '\n';
}
