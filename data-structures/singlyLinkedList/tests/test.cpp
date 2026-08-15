#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  SinglyLinkedList list; list.pushFront(30); list.pushFront(20); list.pushFront(10);
  check(list.size() == 3 && list.contains(20) && !list.contains(99), "push and search");
  check(list.insertAfter(20, 25) && list.size() == 4, "insert after");
  list.reverse(); check(list.removeFirst(10) && list.size() == 3 && !list.removeFirst(99), "reverse and remove");
  list.clear(); check(list.size() == 0 && !list.contains(25), "clear");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
