#include <bits/stdc++.h>
using namespace std;

#include DSA_IMPLEMENTATION

int passed = 0, total = 0;

void check(const string &input,
           double expected,
           double actual,
           const char *name) {
  const bool ok = fabs(actual - expected) < 1e-9;

  ++total;
  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":"
       << input
       << ",\"expected\":"
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
  // Empty stream.
  {
    MedianStream stream;

    check(
        "{\"values\":[]}",
        0.0,
        stream.getMedian(),
        "empty stream returns zero");
  }

  // Single value.
  {
    MedianStream stream;
    stream.addNumber(5);

    check(
        "{\"values\":[5]}",
        5.0,
        stream.getMedian(),
        "single value");
  }

  // Basic odd/even transitions.
  {
    MedianStream stream;

    stream.addNumber(5);
    check(
        "{\"values\":[5]}",
        5.0,
        stream.getMedian(),
        "odd count one");

    stream.addNumber(15);
    check(
        "{\"values\":[5,15]}",
        10.0,
        stream.getMedian(),
        "even count two");

    stream.addNumber(1);
    check(
        "{\"values\":[5,15,1]}",
        5.0,
        stream.getMedian(),
        "odd count three");

    stream.addNumber(3);
    check(
        "{\"values\":[5,15,1,3]}",
        4.0,
        stream.getMedian(),
        "even count four");

    stream.addNumber(8);
    check(
        "{\"values\":[5,15,1,3,8]}",
        5.0,
        stream.getMedian(),
        "odd count five");
  }

  // Increasing input.
  {
    MedianStream stream;

    for (int value : {1, 2, 3, 4, 5, 6})
      stream.addNumber(value);

    check(
        "{\"values\":[1,2,3,4,5,6]}",
        3.5,
        stream.getMedian(),
        "increasing sequence");
  }

  // Decreasing input.
  {
    MedianStream stream;

    for (int value : {6, 5, 4, 3, 2, 1})
      stream.addNumber(value);

    check(
        "{\"values\":[6,5,4,3,2,1]}",
        3.5,
        stream.getMedian(),
        "decreasing sequence");
  }

  // Alternating high/low values.
  {
    MedianStream stream;

    for (int value : {100, 1, 99, 2, 98, 3, 97})
      stream.addNumber(value);

    check(
        "{\"values\":[100,1,99,2,98,3,97]}",
        97.0,
        stream.getMedian(),
        "alternating high low values");
  }

  // Duplicate values.
  {
    MedianStream stream;

    for (int value : {5, 5, 5, 5})
      stream.addNumber(value);

    check(
        "{\"values\":[5,5,5,5]}",
        5.0,
        stream.getMedian(),
        "all duplicate values");
  }

  // Duplicates mixed with other values.
  {
    MedianStream stream;

    for (int value : {2, 2, 2, 10, 10})
      stream.addNumber(value);

    check(
        "{\"values\":[2,2,2,10,10]}",
        2.0,
        stream.getMedian(),
        "duplicate values mixed");
  }

  // Negative values.
  {
    MedianStream stream;

    for (int value : {-10, -4, -7, -20})
      stream.addNumber(value);

    check(
        "{\"values\":[-10,-4,-7,-20]}",
        -8.5,
        stream.getMedian(),
        "negative values");
  }

  // Mixed negative, zero, positive.
  {
    MedianStream stream;

    for (int value : {-5, 0, 5, -10, 10})
      stream.addNumber(value);

    check(
        "{\"values\":[-5,0,5,-10,10]}",
        0.0,
        stream.getMedian(),
        "mixed signs");
  }

  // Even-sized mixed-sign stream.
  {
    MedianStream stream;

    for (int value : {-10, -1, 4, 20})
      stream.addNumber(value);

    check(
        "{\"values\":[-10,-1,4,20]}",
        1.5,
        stream.getMedian(),
        "even mixed signs");
  }

  // Extreme integers.
  {
    MedianStream stream;

    stream.addNumber(INT_MIN);
    stream.addNumber(INT_MAX);

    check(
        "{\"values\":[-2147483648,2147483647]}",
        -0.5,
        stream.getMedian(),
        "extreme integer average");
  }

  // Extreme values with a middle element.
  {
    MedianStream stream;

    stream.addNumber(INT_MIN);
    stream.addNumber(0);
    stream.addNumber(INT_MAX);

    check(
        "{\"values\":[-2147483648,0,2147483647]}",
        0.0,
        stream.getMedian(),
        "extremes with middle zero");
  }

  // Repeated getMedian() should not modify state.
  {
    MedianStream stream;

    for (int value : {3, 1, 2})
      stream.addNumber(value);

    double a = stream.getMedian();
    double b = stream.getMedian();
    double c = stream.getMedian();

    check(
        "{\"values\":[3,1,2]}",
        2.0,
        a,
        "first repeated median query");

    check(
        "{\"values\":[3,1,2]}",
        2.0,
        b,
        "second repeated median query");

    check(
        "{\"values\":[3,1,2]}",
        2.0,
        c,
        "third repeated median query");
  }

  // Large imbalance-triggering insertion order.
  {
    MedianStream stream;

    for (int value : {50, 40, 30, 20, 10, 60, 70, 80, 90})
      stream.addNumber(value);

    check(
        "{\"values\":[50,40,30,20,10,60,70,80,90]}",
        50.0,
        stream.getMedian(),
        "many rebalances");
  }

  // Zeroes.
  {
    MedianStream stream;

    for (int value : {0, 0, 0, 0, 0})
      stream.addNumber(value);

    check(
        "{\"values\":[0,0,0,0,0]}",
        0.0,
        stream.getMedian(),
        "all zero values");
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}