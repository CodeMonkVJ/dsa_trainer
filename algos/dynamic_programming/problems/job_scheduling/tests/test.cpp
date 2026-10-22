#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(const vector<Job> &jobs,
           int expected,
           const char *name) {
  int actual = maxJobProfit(jobs);
  bool ok = actual == expected;

  ++total;
  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"jobs\":[";

  for (size_t i = 0; i < jobs.size(); ++i) {
    if (i)
      cout << ',';

    cout << '['
         << jobs[i].start << ','
         << jobs[i].end << ','
         << jobs[i].profit
         << ']';
  }

  cout << "]},\"expected\":"
       << expected
       << ",\"actual\":"
       << actual
       << ",\"passed\":"
       << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

int main() {
  check(
      {},
      0,
      "empty jobs");

  check(
      {{1, 3, 50}},
      50,
      "single job");

  check(
      {
          {1, 3, 50},
          {2, 4, 10},
          {3, 5, 40},
          {3, 6, 70},
      },
      120,
      "classic overlapping jobs");

  check(
      {
          {1, 2, 10},
          {2, 3, 20},
          {3, 4, 30},
          {4, 5, 40},
      },
      100,
      "touching jobs are compatible");

  check(
      {
          {1, 3, 20},
          {4, 6, 30},
          {7, 9, 40},
      },
      90,
      "all jobs non overlapping");

  check(
      {
          {1, 10, 20},
          {2, 9, 50},
          {3, 8, 40},
          {4, 7, 100},
      },
      100,
      "all jobs overlap");

  check(
      {
          {1, 4, 100},
          {1, 2, 60},
          {2, 3, 60},
          {3, 4, 60},
      },
      180,
      "multiple smaller jobs beat one large job");

  check(
      {
          {1, 2, 5},
          {2, 3, 5},
          {1, 3, 100},
      },
      100,
      "earliest finish greedy fails");

  check(
      {
          {6, 7, 60},
          {1, 3, 20},
          {5, 8, 30},
          {4, 6, 70},
          {2, 5, 20},
      },
      150,
      "unsorted input");

  check(
      {
          {1, 3, 50},
          {1, 4, 60},
          {1, 5, 70},
      },
      70,
      "same start time");

  check(
      {
          {1, 5, 20},
          {2, 5, 40},
          {3, 5, 60},
          {5, 6, 50},
      },
      110,
      "same end time with follow up");

  check(
      {
          {1, 2, 50},
          {2, 4, 10},
          {2, 5, 100},
          {5, 6, 20},
      },
      170,
      "choose best among same start boundary");

  check(
      {
          {1, 3, 20},
          {3, 5, 20},
          {5, 7, 20},
          {1, 7, 55},
      },
      60,
      "chain beats long interval");

  check(
      {
          {1, 4, 70},
          {2, 6, 100},
          {4, 7, 60},
          {6, 8, 80},
          {7, 9, 30},
      },
      180,
      "mixed overlapping schedule");

  check(
      {
          {1, 2, 10},
          {2, 3, 10},
          {3, 4, 10},
          {1, 4, 29},
      },
      30,
      "three jobs narrowly beat one");

  check(
      {
          {1, 3, 0},
          {3, 5, 20},
      },
      20,
      "zero profit job");

  check(
      {
          {1, 2, 5},
          {2, 10, 100},
          {3, 4, 60},
          {4, 5, 60},
          {5, 6, 60},
      },
      185,
      "skip tempting long job for profitable chain");

  check(
      {
          {1, 2, 20},
          {2, 5, 20},
          {4, 6, 70},
          {5, 8, 30},
          {6, 7, 60},
      },
      150,
      "dp recurrence example");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}