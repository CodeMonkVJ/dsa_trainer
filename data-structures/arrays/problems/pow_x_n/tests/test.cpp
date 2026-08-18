#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
bool closeEnough(double actual, double expected) {
  return fabs(actual - expected) <= 1e-9 * max(1.0, fabs(expected));
}

void check(double base, long long exponent, double expected, const char *name) {
  const double actual = myPow(base, exponent);
  ++total;
  const bool ok = closeEnough(actual, expected);
  cout << "DSA_CASE {\"input\":{\"base\":" << base
       << ",\"exponent\":" << exponent << "},\"expected\":" << expected
       << ",\"actual\":" << actual << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check(2.0, 10, 1024.0, "raises a positive exponent");
  check(2.5, 0, 1.0, "handles a zero exponent");
  check(2.0, -3, 0.125, "handles a negative exponent");
  check(-2.0, 5, -32.0, "preserves a negative base sign");
  check(1.0, LLONG_MIN, 1.0, "handles the minimum long long exponent");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
