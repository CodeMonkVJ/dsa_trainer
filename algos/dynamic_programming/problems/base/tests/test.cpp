#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *name, const vector<Item> &items, int capacity,
           int expected, int actual) {
  (void)items;
  ++total;
  if (ok)
    ++passed;
  dsa_test::emit_case(
      "{\"items\":[{\"weight\":2,\"value\":12},{\"weight\":1,\"value\":10},{"
      "\"weight\":3,\"value\":20},{\"weight\":2,\"value\":15}],\"capacity\":" +
          to_string(capacity) + "}",
      to_string(expected), to_string(actual), ok);
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}
int main() {
  vector<Item> items{{2, 12}, {1, 10}, {3, 20}, {2, 15}};
  int actual = maximumValue(items, 5);
  check(actual == 37, "choose best combination once", items, 5, 37, actual);
  actual = maximumValue(items, 0);
  check(actual == 0, "zero capacity", items, 0, 0, actual);
  actual = maximumValue(items, 1);
  check(actual == 10, "single fitting item", items, 1, 10, actual);
  actual = maximumValue(items, 100);
  check(actual == 57, "capacity above total weight", items, 100, 57, actual);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
