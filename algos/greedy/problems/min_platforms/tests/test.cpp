#include "../../../../../test_protocol.hpp"

#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(const vector<int> &arrival,
           const vector<int> &departure,
           int expected,
           const char *name) {
  ++total;

  int actual = minPlatforms(arrival, departure);
  bool ok = (actual == expected);

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ")
       << name
       << " expected=" << expected
       << " actual=" << actual
       << '\n';

  string input = "{\"test\":\"" + string(name) + "\"}";

  dsa_test::emit_case(
      input,
      to_string(expected),
      to_string(actual),
      ok);
}

int main() {
  // 1. Classic example.
  check(
      {900, 940, 950, 1100, 1500, 1800},
      {910, 1200, 1120, 1130, 1900, 2000},
      3,
      "classic example");

  // 2. Empty input.
  check(
      {},
      {},
      0,
      "empty input");

  // 3. Single normal train.
  check(
      {900},
      {1000},
      1,
      "single train");

  // 4. Single zero-duration train.
  check(
      {900},
      {900},
      0,
      "single zero duration train");

  // 5. Multiple zero-duration trains.
  check(
      {100, 200, 300},
      {100, 200, 300},
      0,
      "all trains zero duration");

  // 6. No overlaps.
  check(
      {100, 300, 500},
      {200, 400, 600},
      1,
      "no overlapping trains");

  // 7. Exact platform reuse.
  check(
      {100, 200},
      {200, 300},
      1,
      "platform reused at same time");

  // 8. Repeated exact reuse.
  check(
      {100, 200, 300, 400},
      {200, 300, 400, 500},
      1,
      "repeated platform reuse");

  // 9. Simple overlap.
  check(
      {100, 150},
      {200, 250},
      2,
      "simple overlap");

  // 10. All trains overlap.
  check(
      {100, 110, 120, 130},
      {500, 500, 500, 500},
      4,
      "all trains overlap");

  // 11. Same arrival time.
  check(
      {100, 100, 100},
      {200, 300, 400},
      3,
      "same arrival time");

  // 12. Same departure time.
  check(
      {100, 150, 180},
      {300, 300, 300},
      3,
      "same departure time");

  // 13. One train departs exactly when two arrive.
  // At 200, the first platform is freed before the two arrivals.
  check(
      {100, 200, 200},
      {200, 300, 400},
      2,
      "one departure with two arrivals");

  // 14. Two trains depart exactly when two new trains arrive.
  check(
      {100, 120, 300, 300},
      {300, 300, 500, 600},
      2,
      "two departures with two arrivals");

  // 15. Zero-duration trains mixed with normal trains.
  //
  // [100,100] -> ignored
  // [100,200] -> uses one
  // [200,300] -> reuses it
  check(
      {100, 100, 200},
      {100, 200, 300},
      1,
      "zero duration mixed with normal trains");

  // 16. Several equal timestamps with zero-duration trains.
  //
  // [100,100] -> ignored
  // [100,200] -> one platform
  // [200,200] -> ignored
  // [200,300] -> reuses platform
  check(
      {100, 100, 200, 200},
      {100, 200, 200, 300},
      1,
      "multiple equal timestamps");

  // 17. Several zero-duration trains mixed with overlapping trains.
  //
  // [100,100] ignored
  // [100,300]
  // [150,250]
  // [200,200] ignored
  //
  // Peak = 2.
  check(
      {100, 100, 150, 200},
      {100, 300, 250, 200},
      2,
      "zero duration mixed with overlap");

  // 18. Temporary peak.
  //
  // At 140:
  // [100,400], [120,250], [140,200] are all present.
  check(
      {100, 120, 140, 300},
      {400, 250, 200, 500},
      3,
      "temporary peak");

  // 19. Staggered overlap.
  check(
      {100, 150, 200, 250, 300},
      {180, 230, 280, 330, 380},
      2,
      "staggered overlaps");

  // 20. Nested intervals.
  check(
      {100, 150, 200},
      {500, 400, 300},
      3,
      "nested intervals");

  // 21. Peak occurs early.
  check(
      {100, 110, 120, 500},
      {300, 250, 200, 600},
      3,
      "early peak");

  // 22. Peak occurs late.
  check(
      {100, 300, 310, 320},
      {200, 500, 450, 400},
      3,
      "late peak");

  // 23. Large gaps.
  check(
      {100, 1000, 5000},
      {200, 1100, 5100},
      1,
      "large gaps");

  // 24. Unsorted input.
  check(
      {950, 900, 940},
      {1120, 910, 1200},
      2,
      "unsorted input");

  // 25. Unsorted input with exact reuse.
  //
  // Paired intervals:
  // [300,400]
  // [100,200]
  // [200,300]
  check(
      {300, 100, 200},
      {400, 200, 300},
      1,
      "unsorted exact reuse");

  // 26. Mixed overlap and exact reuse.
  //
  // [100,200]
  // [150,300]
  // [200,250]
  // [250,400]
  //
  // Peak is 2.
  check(
      {100, 150, 200, 250},
      {200, 300, 250, 400},
      2,
      "reuse mixed with overlap");

  // 27. Multiple arrivals while one train already occupies a platform.
  check(
      {100, 150, 150, 150},
      {500, 200, 300, 400},
      4,
      "multiple simultaneous arrivals during active train");

  // 28. Multiple departures at same instant free several platforms.
  check(
      {100, 110, 120, 300},
      {200, 200, 200, 400},
      3,
      "multiple simultaneous departures");

  // 29. Departures and arrivals at the same instant.
  //
  // [100,200]
  // [110,200]
  // [200,300]
  // [200,400]
  //
  // Before 200 => 2 platforms.
  // At 200 both old trains leave before both new trains arrive.
  // Still only 2 needed.
  check(
      {100, 110, 200, 200},
      {200, 200, 300, 400},
      2,
      "multiple platform reuse at same timestamp");

  // 30. Zero-duration trains at the same timestamp as real handoff.
  //
  // [100,200]
  // [200,200] ignored
  // [200,300]
  check(
      {100, 200, 200},
      {200, 200, 300},
      1,
      "zero duration during platform handoff");

  // 31. Many identical normal intervals.
  check(
      {100, 100, 100, 100, 100},
      {200, 200, 200, 200, 200},
      5,
      "identical intervals");

  // 32. Combination of identical and zero-duration intervals.
  //
  // Three [100,200] trains + two zero-duration trains.
  check(
      {100, 100, 100, 150, 180},
      {200, 200, 200, 150, 180},
      3,
      "identical intervals with zero duration trains");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}