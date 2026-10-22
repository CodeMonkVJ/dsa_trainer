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
      "true",
      ok ? "true" : "false",
      ok);
}

int main() {
  // Starts empty.
  {
    MinStack s;

    check(
        s.empty(),
        "starts empty");
  }

  // Single element.
  {
    MinStack s;

    s.push(42);

    check(
        !s.empty() &&
        s.top() == 42 &&
        s.getMin() == 42,
        "single element");

    s.pop();

    check(
        s.empty(),
        "single element pop");
  }

  // Duplicate minimum handling.
  {
    MinStack s;

    s.push(3);
    s.push(1);
    s.push(2);
    s.push(1);

    check(
        s.top() == 1 &&
        s.getMin() == 1,
        "tracks duplicate minimum");

    s.pop();

    check(
        s.top() == 2 &&
        s.getMin() == 1,
        "retains earlier duplicate minimum");

    s.pop();

    check(
        s.top() == 1 &&
        s.getMin() == 1,
        "restores previous minimum node");

    s.pop();

    check(
        s.top() == 3 &&
        s.getMin() == 3,
        "restores larger minimum");

    s.pop();

    check(
        s.empty(),
        "duplicate minimum sequence empties");
  }

  // Increasing values.
  {
    MinStack s;

    for (int x : {1, 2, 3, 4, 5})
      s.push(x);

    check(
        s.top() == 5 &&
        s.getMin() == 1,
        "increasing pushes");

    s.pop();
    s.pop();

    check(
        s.top() == 3 &&
        s.getMin() == 1,
        "increasing pops keep minimum");
  }

  // Decreasing values.
  {
    MinStack s;

    for (int x : {5, 4, 3, 2, 1})
      s.push(x);

    check(
        s.top() == 1 &&
        s.getMin() == 1,
        "decreasing pushes");

    s.pop();

    check(
        s.top() == 2 &&
        s.getMin() == 2,
        "decreasing pop restores minimum");

    s.pop();

    check(
        s.top() == 3 &&
        s.getMin() == 3,
        "decreasing second pop restores minimum");
  }

  // All equal values.
  {
    MinStack s;

    for (int x : {7, 7, 7, 7})
      s.push(x);

    check(
        s.getMin() == 7 &&
        s.top() == 7,
        "all equal values");

    s.pop();
    s.pop();
    s.pop();

    check(
        s.getMin() == 7 &&
        s.top() == 7,
        "equal values survive repeated pops");
  }

  // Negative values.
  {
    MinStack s;

    for (int x : {-2, -5, -1, -7, -3})
      s.push(x);

    check(
        s.top() == -3 &&
        s.getMin() == -7,
        "negative values");

    s.pop();

    check(
        s.getMin() == -7,
        "negative minimum retained");

    s.pop();

    check(
        s.getMin() == -5,
        "negative minimum restored");
  }

  // Extreme integer values.
  {
    MinStack s;

    s.push(INT_MAX);
    s.push(0);
    s.push(INT_MIN);

    check(
        s.top() == INT_MIN &&
        s.getMin() == INT_MIN,
        "integer minimum extreme");

    s.pop();

    check(
        s.top() == 0 &&
        s.getMin() == 0,
        "minimum after removing INT_MIN");

    s.pop();

    check(
        s.top() == INT_MAX &&
        s.getMin() == INT_MAX,
        "integer maximum remains");
  }

  // Repeated reads should not mutate state.
  {
    MinStack s;

    s.push(4);
    s.push(2);
    s.push(6);

    int top1 = s.top();
    int min1 = s.getMin();

    int top2 = s.top();
    int min2 = s.getMin();

    check(
        top1 == 6 &&
        top2 == 6 &&
        min1 == 2 &&
        min2 == 2,
        "repeated reads do not mutate");
  }

  // Alternating push/pop.
  {
    MinStack s;

    s.push(10);
    s.push(5);

    check(
        s.getMin() == 5,
        "alternating first minimum");

    s.pop();
    s.push(7);
    s.push(3);

    check(
        s.top() == 3 &&
        s.getMin() == 3,
        "alternating new minimum");

    s.pop();

    check(
        s.top() == 7 &&
        s.getMin() == 7,
        "alternating minimum restored");

    s.pop();

    check(
        s.top() == 10 &&
        s.getMin() == 10,
        "alternating returns to original");
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}