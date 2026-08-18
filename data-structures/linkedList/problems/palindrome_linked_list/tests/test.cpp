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
  check(isPalindrome(nullptr), "empty list");
  auto *a = makeList({1});
  check(isPalindrome(a), "single node");
  freeList(a);
  a = makeList({1, 2, 2, 1});
  check(isPalindrome(a), "even palindrome");
  freeList(a);
  a = makeList({1, 2, 3, 2, 1});
  check(isPalindrome(a), "odd palindrome");
  freeList(a);
  a = makeList({1, 2, 3, 4});
  check(!isPalindrome(a), "non-palindrome");
  freeList(a);
  a = makeList({1, 2, 3, 2, 1});
  vector<int> before;
  for (auto *p = a; p; p = p->next)
    before.push_back(p->value);
  bool answer = isPalindrome(a);
  vector<int> after;
  for (auto *p = a; p; p = p->next)
    after.push_back(p->value);
  check(answer && before == after, "restores values and links");
  freeList(a);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
