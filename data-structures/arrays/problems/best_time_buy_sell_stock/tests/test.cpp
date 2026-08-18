#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &prices, int expected, const char *name) {
  const int actual = maxProfit(prices);
  ++total;
  cout << "DSA_CASE {\"input\":{\"prices\":[";
  for (size_t i = 0; i < prices.size(); ++i) {
    if (i)
      cout << ',';
    cout << prices[i];
  }
  cout << "]},\"expected\":" << expected << ",\"actual\":" << actual
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({7, 1, 5, 3, 6, 4}, 5, "chooses the best later sale");
  check({7, 6, 4, 3, 1}, 0, "returns zero when prices only fall");
  check({2, 4, 1, 7}, 6, "updates the minimum buy price");
  check({}, 0, "handles an empty input");
  check({5}, 0, "handles a single value");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
