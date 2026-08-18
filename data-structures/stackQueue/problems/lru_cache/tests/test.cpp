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
  LRUCache cache(2);
  check(cache.get(1) == -1, "missing key");
  cache.put(1, 10);
  cache.put(2, 20);
  check(cache.get(1) == 10, "get existing key");
  cache.put(3, 30);
  check(cache.get(2) == -1 && cache.get(3) == 30, "evict least recently used");
  cache.put(1, 11);
  check(cache.get(1) == 11, "update existing key");
  cache.put(4, 40);
  check(cache.get(3) == -1 && cache.get(4) == 40,
        "updated key changes recency");
  LRUCache zero(0);
  zero.put(1, 1);
  check(zero.get(1) == -1, "zero capacity");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
