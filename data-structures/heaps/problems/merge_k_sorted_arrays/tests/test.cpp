#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;

string json(const vector<vector<int>> &arrays) {
  ostringstream out;
  out << '[';
  for (size_t i = 0; i < arrays.size(); ++i) {
    if (i)
      out << ',';
    out << '[';
    for (size_t j = 0; j < arrays[i].size(); ++j) {
      if (j)
        out << ',';
      out << arrays[i][j];
    }
    out << ']';
  }
  out << ']';
  return out.str();
}

void check(const vector<vector<int>> &input, const vector<int> &expected,
           const char *name) {
  const vector<int> actual = mergeKSortedArrays(input);
  const bool ok = actual == expected;
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"arrays\":" << json(input)
       << "},\"expected\":[";
  for (size_t i = 0; i < expected.size(); ++i) {
    if (i)
      cout << ',';
    cout << expected[i];
  }
  cout << "],\"actual\":[";
  for (size_t i = 0; i < actual.size(); ++i) {
    if (i)
      cout << ',';
    cout << actual[i];
  }
  cout << "],\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({}, {}, "handles no arrays");
  check({{}, {}}, {}, "handles only empty arrays");
  check({{1, 4, 7}, {2, 5, 8}, {3, 6, 9}}, {1, 2, 3, 4, 5, 6, 7, 8, 9},
        "merges several arrays");
  check({{-5, -1, 0}, {-4, -4, 2}, {0, 3}}, {-5, -4, -4, -1, 0, 0, 2, 3},
        "preserves duplicates and negatives");
  check({{42}}, {42}, "handles one value");
  check({{1, 2}, {}, {3}, {}, {4, 5, 6}}, {1, 2, 3, 4, 5, 6},
        "skips empty arrays");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
