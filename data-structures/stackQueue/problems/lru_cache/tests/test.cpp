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

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';

  string input = string("{\"test\":\"") + name + "\"}";

  dsa_test::emit_case(
      input,
      ok ? "true" : "false",
      ok ? "true" : "false",
      ok);
}

int main() {
  // Basic missing lookup.
  {
    LRUCache cache(2);

    check(
        cache.get(1) == -1,
        "missing key");
  }

  // Basic insertion and retrieval.
  {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    check(
        cache.get(1) == 10 &&
            cache.get(2) == 20,
        "basic put and get");
  }

  // Standard LRU eviction.
  {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    // Access 1, making 2 the LRU.
    check(cache.get(1) == 10,
          "get marks key recently used");

    cache.put(3, 30);

    check(
        cache.get(2) == -1 &&
            cache.get(1) == 10 &&
            cache.get(3) == 30,
        "evicts least recently used key");
  }

  // Updating existing key should change the value
  // and should not increase cache size.
  {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cache.put(1, 99);

    check(
        cache.get(1) == 99,
        "update changes existing value");

    // Since put(1,99) made key 1 most recent,
    // key 2 should be evicted.
    cache.put(3, 30);

    check(
        cache.get(2) == -1 &&
            cache.get(1) == 99 &&
            cache.get(3) == 30,
        "update changes recency without growing size");
  }

  // Capacity one.
  {
    LRUCache cache(1);

    cache.put(1, 10);

    check(
        cache.get(1) == 10,
        "capacity one initial value");

    cache.put(2, 20);

    check(
        cache.get(1) == -1 &&
            cache.get(2) == 20,
        "capacity one eviction");
  }

  // Updating at capacity one should not evict the key.
  {
    LRUCache cache(1);

    cache.put(5, 50);
    cache.put(5, 500);

    check(
        cache.get(5) == 500,
        "capacity one update same key");
  }

  // Repeated get should keep the same key most recent.
  {
    LRUCache cache(3);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    cache.get(1);
    cache.get(1);

    cache.put(4, 40);

    // 2 is least recently used.
    check(
        cache.get(2) == -1 &&
            cache.get(1) == 10 &&
            cache.get(3) == 30 &&
            cache.get(4) == 40,
        "repeated get preserves recency");
  }

  // More complex eviction sequence.
  {
    LRUCache cache(3);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    // Recency: 3,2,1
    cache.get(1);
    // Recency: 1,3,2

    cache.get(3);
    // Recency: 3,1,2

    cache.put(4, 40);
    // Evicts 2.

    check(
        cache.get(2) == -1,
        "complex recency first eviction");

    // get(1) makes 1 most recent.
    cache.get(1);

    cache.put(5, 50);

    // Before insertion:
    // recency should be 1,4,3
    // so 3 gets evicted.
    check(
        cache.get(3) == -1 &&
            cache.get(1) == 10 &&
            cache.get(4) == 40 &&
            cache.get(5) == 50,
        "complex recency second eviction");
  }

  // Same value under different keys.
  // Eviction must be based on key identity, not value.
  {
    LRUCache cache(2);

    cache.put(1, 100);
    cache.put(2, 100);

    cache.get(1);
    cache.put(3, 100);

    check(
        cache.get(2) == -1 &&
            cache.get(1) == 100 &&
            cache.get(3) == 100,
        "same values with different keys");
  }

  // Negative keys and values.
  {
    LRUCache cache(2);

    cache.put(-1, -10);
    cache.put(-2, -20);

    check(
        cache.get(-1) == -10 &&
            cache.get(-2) == -20,
        "negative keys and values");
  }

  // Value -1 is ambiguous with the miss sentinel,
  // but storing it should still behave internally.
  {
    LRUCache cache(2);

    cache.put(1, -1);
    cache.put(2, 20);

    cache.get(1); // make 1 recent
    cache.put(3, 30);

    check(
        cache.get(2) == -1 &&
            cache.get(3) == 30,
        "stored minus one still participates in recency");
  }

  // Reinsert an evicted key.
  {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    // 1 should be gone.
    check(
        cache.get(1) == -1,
        "key was evicted");

    cache.put(1, 100);

    check(
        cache.get(1) == 100,
        "reinsert previously evicted key");
  }

  // Multiple updates to same key.
  {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(1, 20);
    cache.put(1, 30);
    cache.put(1, 40);

    cache.put(2, 50);

    check(
        cache.get(1) == 40 &&
            cache.get(2) == 50,
        "multiple updates same key");
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}