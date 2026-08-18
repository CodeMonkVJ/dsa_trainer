#include <bits/stdc++.h>
using namespace std;

vector<int> zFunction(const string &s) { return vector<int>(s.size(), 0); }

int main() {
  for (int value : zFunction("aabcaab"))
    cout << value << ' ';
  cout << '\n';
  return 0;
}
