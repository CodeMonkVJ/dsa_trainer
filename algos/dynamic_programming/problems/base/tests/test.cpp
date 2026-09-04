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
  {
    vector<Item> items{{2, 12}, {1, 10}, {3, 20}, {2, 15}};

    int actual = maximumValue(items, 5);
    check(actual == 37,
          "choose best combination once",
          items, 5, 37, actual);

    actual = maximumValue(items, 0);
    check(actual == 0,
          "zero capacity",
          items, 0, 0, actual);

    actual = maximumValue(items, 1);
    check(actual == 10,
          "single fitting item",
          items, 1, 10, actual);

    actual = maximumValue(items, 100);
    check(actual == 57,
          "capacity above total weight",
          items, 100, 57, actual);
  }

  {
    vector<Item> items{};

    int actual = maximumValue(items, 10);
    check(actual == 0,
          "empty item list",
          items, 10, 0, actual);
  }

  {
    vector<Item> items{{5, 100}, {6, 200}};

    int actual = maximumValue(items, 4);
    check(actual == 0,
          "no items fit",
          items, 4, 0, actual);
  }

  {
    vector<Item> items{{2, 10}};

    int actual = maximumValue(items, 4);
    check(actual == 10,
          "does not reuse a single item",
          items, 4, 10, actual);
  }

  {
    vector<Item> items{{2, 10}, {2, 10}};

    int actual = maximumValue(items, 4);
    check(actual == 20,
          "distinct equal items may both be used",
          items, 4, 20, actual);
  }

  {
    vector<Item> items{{3, 14}, {4, 16}, {2, 9}};

    int actual = maximumValue(items, 6);
    check(actual == 25,
          "exact capacity combination",
          items, 6, 25, actual);
  }

  {
    vector<Item> items{{4, 40}, {5, 50}, {6, 100}};

    int actual = maximumValue(items, 10);
    check(actual == 140,
          "best solution is a combination",
          items, 10, 140, actual);
  }

  {
    vector<Item> items{{1, 15}, {3, 20}, {4, 30}};

    int actual = maximumValue(items, 4);
    check(actual == 35,
          "greedy by single highest value fails",
          items, 4, 35, actual);
  }

  {
    vector<Item> items{{2, 20}, {3, 30}, {4, 65}};

    int actual = maximumValue(items, 5);
    check(actual == 65,
          "chooses one better item over two weaker ones",
          items, 5, 65, actual);
  }

  {
    vector<Item> items{{1, 1}, {1, 2}, {1, 3}, {1, 4}};

    int actual = maximumValue(items, 2);
    check(actual == 7,
          "multiple same-weight items",
          items, 2, 7, actual);
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}