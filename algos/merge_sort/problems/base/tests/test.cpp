#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
string jsonValues(const vector<int> &values) {
  string result = "[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      result += ",";
    result += to_string(values[i]);
  }
  return result + "]";
}

void check(bool ok, const string &input, const string &expected,
           const vector<int> &actual) {
  ++total;
  if (ok)
    ++passed;
  dsa_test::emit_case(input, expected, jsonValues(actual), ok);
}

bool sorted(const vector<int> &values) {
  return is_sorted(values.begin(), values.end());
}
int main() {
  vector<int> values{5, 1, 4, 2, 8, 5, -1};
  mergeSort(values.data(), values.size());
  check(sorted(values) && values == vector<int>({-1, 1, 2, 4, 5, 5, 8}),
        "[5,1,4,2,8,5,-1]", "[-1,1,2,4,5,5,8]", values);
  mergeSort(nullptr, 0);
  check(true, "[]", "[]", {});
  values = {7};
  mergeSort(values.data(), 1);
  check(values == vector<int>({7}), "[7]", "[7]", values);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
