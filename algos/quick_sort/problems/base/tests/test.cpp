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

int main() {
  vector<int> values{9, 4, 7, 3, 10, 5, 5, -2};
  quickSort(values, 0, static_cast<int>(values.size()) - 1);
  check(values == vector<int>({-2, 3, 4, 5, 5, 7, 9, 10}),
        "[9,4,7,3,10,5,5,-2]", "[-2,3,4,5,5,7,9,10]", values);

  values = {1, 2, 3, 4};
  quickSort(values, 0, static_cast<int>(values.size()) - 1);
  check(values == vector<int>({1, 2, 3, 4}), "[1,2,3,4]", "[1,2,3,4]", values);

  values.clear();
  quickSort(values, 0, -1);
  check(values.empty(), "[]", "[]", values);

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
