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
  LFUCache cache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  check(cache.get(1) == 1, "get increases frequency");
  cache.put(3, 3);
  check(cache.get(2) == -1 && cache.get(3) == 3, "evict least frequent");
  cache.put(4, 4);
  check(cache.get(1) == -1 && cache.get(3) == 3 && cache.get(4) == 4,
        "frequency ordering");
  LFUCache ties(2);
  ties.put(1, 10);
  ties.put(2, 20);
  ties.put(3, 30);
  check(ties.get(1) == -1 && ties.get(2) == 20, "oldest on frequency tie");
  ties.put(2, 22);
  check(ties.get(2) == 22, "update existing key");
  LFUCache zero(0);
  zero.put(1, 1);
  check(zero.get(1) == -1, "zero capacity");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
