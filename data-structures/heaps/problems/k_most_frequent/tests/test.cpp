#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

string json(const vector<int> &values) {
  ostringstream out;
  out << '[';
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      out << ',';
    out << values[i];
  }
  out << ']';
  return out.str();
}

void check(const vector<int> &input, int k, const vector<int> &expected,
           const char *name) {
  const vector<int> actual = topKFrequent(input, k);
  const bool ok = actual == expected;
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"values\":" << json(input) << ",\"k\":" << k
       << "},\"expected\":" << json(expected) << ",\"actual\":" << json(actual)
       << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({1, 1, 1, 2, 2, 3},
        2,
        {1, 2},
        "basic frequencies");
  
  check({4, 4, 5, 5, 6},
        2,
        {4, 5},
        "tie breaks by smaller value");
  
  check({-1, -1, -2, -3, -3, -3, 0},
        3,
        {-3, -1, -2},
        "negative values");
  
  check({7, 7, 7},
        1,
        {7},
        "single distinct value");
  
  check({3, 1, 2, 3, 1, 2},
        3,
        {1, 2, 3},
        "k equals distinct count");
  
  check({8, 8, 8, 1, 1, 2, 2, 2, 3},
        2,
        {2, 8},
        "evicts low frequency candidate");
  
  check({5, 4, 3, 2, 1},
        3,
        {1, 2, 3},
        "all frequencies equal");
  
  check({10, 10, 20, 20, 30, 30, 40, 40},
        2,
        {10, 20},
        "tie at cutoff keeps smaller values");
  
  check({9, 9, 9, 8, 8, 7, 7, 7, 6, 6},
        3,
        {7, 9, 6},
        "frequency tie after highest candidates");
  
  check({0, 0, -1, -1, 1, 1},
        2,
        {-1, 0},
        "ties across negative zero and positive");
  
  check({100, 100, 100, 1, 1, 2, 3, 3, 3, 3},
        1,
        {3},
        "k one returns most frequent");
  
  check({2, 2, 1, 1, 3, 3, 4},
        3,
        {1, 2, 3},
        "multiple equal-frequency winners");
  
  check({6, 6, 6, 5, 5, 4, 4, 4, 3, 3, 2, 2, 2, 2},
        3,
        {2, 4, 6},
        "heap replacement across many candidates");
  
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
