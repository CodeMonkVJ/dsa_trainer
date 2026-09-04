#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << std::endl;
  std::string input = std::string("{\"test\":\"") + name + "\"}";
  dsa_test::emit_case(input, ok ? "true" : "false", ok ? "true" : "false", ok);
}
int main() {
  check(nextGreaterElement({}).empty(),
        "empty array");
  
  check(nextGreaterElement({7}) == vector<int>({-1}),
        "single element");
  
  check(nextGreaterElement({1, 2, 3, 4}) ==
            vector<int>({2, 3, 4, -1}),
        "strictly increasing");
  
  check(nextGreaterElement({4, 3, 2, 1}) ==
            vector<int>({-1, -1, -1, -1}),
        "strictly decreasing");
  
  check(nextGreaterElement({2, 1, 2, 4, 3}) ==
            vector<int>({4, 2, 4, -1, -1}),
        "standard case");
  
  check(nextGreaterElement({5, 5, 5}) ==
            vector<int>({-1, -1, -1}),
        "duplicates require strictly greater");
  
  check(nextGreaterElement({1, 3, 2, 4}) ==
            vector<int>({3, 4, 4, -1}),
        "interleaved values");
  
  check(nextGreaterElement({1, 1, 2, 2, 3}) ==
            vector<int>({2, 2, 3, 3, -1}),
        "duplicate plateaus");
  
  check(nextGreaterElement({5, 1, 4, 2, 3}) ==
            vector<int>({-1, 4, -1, 3, -1}),
        "alternating highs and lows");
  
  check(nextGreaterElement({2, 1, 1, 1, 3}) ==
            vector<int>({3, 3, 3, 3, -1}),
        "next greater far to the right");
  
  check(nextGreaterElement({3, 2, 1, 2, 3, 4}) ==
            vector<int>({4, 3, 2, 3, 4, -1}),
        "requires multiple stack pops");
  
  check(nextGreaterElement({-3, -2, -5, -1}) ==
            vector<int>({-2, -1, -1, -1}),
        "negative values");
  
  check(nextGreaterElement({0, -1, 0, 1}) ==
            vector<int>({1, 0, 1, -1}),
        "mixed zero and negatives");
  
  check(nextGreaterElement({INT_MAX, INT_MIN, INT_MAX}) ==
            vector<int>({-1, INT_MAX, -1}),
        "extreme integer values");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
