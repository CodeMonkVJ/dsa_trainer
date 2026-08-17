#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;
void check(bool ok, const char* name) {
  ++total;
  if (ok) ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  vector<int> first{1, 4, 7, 8, 10}, second{2, 3, 9};
  mergeSortedArrays(first, second);
  check(first == vector<int>({1, 2, 3, 4, 7}) && second == vector<int>({8, 9, 10}),
        "merges unequal lengths");

  first = {-3, 0, 0, 8}; second = {-4, 0, 9, 11};
  mergeSortedArrays(first, second);
  check(first == vector<int>({-4, -3, 0, 0}) && second == vector<int>({0, 8, 9, 11}),
        "handles duplicates and negative values");

  first = {}; second = {1, 2};
  mergeSortedArrays(first, second);
  check(first.empty() && second == vector<int>({1, 2}), "handles an empty first vector");

  first = {5, 6}; second = {};
  mergeSortedArrays(first, second);
  check(first == vector<int>({5, 6}) && second.empty(), "handles an empty second vector");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
