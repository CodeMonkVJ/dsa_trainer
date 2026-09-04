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
  SinglyLinkedList list;
  
  check(list.size() == 0 &&
            !list.contains(1) &&
            !list.removeFirst(1),
        "empty list");
  
  list.reverse();
  check(list.size() == 0,
        "reverse empty list");
  
  list.pushFront(10);
  check(list.size() == 1 &&
            list.contains(10),
        "push single element");
  
  list.reverse();
  check(list.size() == 1 &&
            list.contains(10),
        "reverse single element");
  
  check(!list.insertAfter(99, 20) &&
            list.size() == 1,
        "insert after missing value");
  
  check(list.insertAfter(10, 20) &&
            list.size() == 2 &&
            list.contains(20),
        "insert after existing value");
  
  list.pushFront(5);
  list.pushFront(1);
  
  check(list.size() == 4 &&
            list.contains(1) &&
            list.contains(5) &&
            list.contains(10) &&
            list.contains(20),
        "multiple pushes");
  
  check(list.removeFirst(1) &&
            list.size() == 3 &&
            !list.contains(1),
        "remove head");
  
  check(list.removeFirst(10) &&
            list.size() == 2 &&
            !list.contains(10),
        "remove middle");
  
  check(list.removeFirst(20) &&
            list.size() == 1 &&
            !list.contains(20),
        "remove tail");
  
  check(!list.removeFirst(999) &&
            list.size() == 1,
        "remove missing value");
  
  list.pushFront(3);
  list.pushFront(2);
  list.pushFront(1);
  
  list.reverse();
  
  check(list.size() == 4 &&
            list.contains(1) &&
            list.contains(2) &&
            list.contains(3) &&
            list.contains(5),
        "reverse preserves nodes");
  
  list.clear();
  
  check(list.size() == 0 &&
            !list.contains(1) &&
            !list.contains(5) &&
            !list.removeFirst(1),
        "clear empties list");
  
  list.pushFront(42);
  
  check(list.size() == 1 &&
            list.contains(42),
        "list reusable after clear");
  
  list.clear();
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
