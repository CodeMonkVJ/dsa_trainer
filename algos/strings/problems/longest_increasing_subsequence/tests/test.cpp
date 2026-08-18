#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const string &input, const string &expected,
           const string &actual) {
  ++total;
  if (ok)
    ++passed;
  dsa_test::emit_case(input, expected, actual, ok);
}

bool increasing(const vector<int> &values) {
  for (size_t i = 1; i < values.size(); ++i)
    if (values[i - 1] >= values[i])
      return false;
  return true;
}
int main() {
  auto result = longestIncreasingSubsequence({10, 9, 2, 5, 3, 7, 101, 18});
  check(result.size() == 4 && increasing(result), "[10,9,2,5,3,7,101,18]",
        "{\"length\":4,\"strictly_increasing\":true}",
        "{\"length\":" + to_string(result.size()) +
            ",\"strictly_increasing\":" +
            string(increasing(result) ? "true" : "false") + "}");
  result = longestIncreasingSubsequence({2, 2, 2});
  check(result.size() == 1, "[2,2,2]", "{\"length\":1}",
        "{\"length\":" + to_string(result.size()) + "}");
  result = longestIncreasingSubsequence({});
  check(result.empty(), "[]", "{\"length\":0}",
        "{\"length\":" + to_string(result.size()) + "}");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
