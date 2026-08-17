#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char* name) {
  ++total;
  if (ok) ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}
bool closeEnough(double actual, double expected) {
  return fabs(actual - expected) <= 1e-9 * max(1.0, fabs(expected));
}

int main() {
  check(closeEnough(myPow(2.0, 10), 1024.0), "raises a positive exponent");
  check(closeEnough(myPow(2.5, 0), 1.0), "handles a zero exponent");
  check(closeEnough(myPow(2.0, -3), 0.125), "handles a negative exponent");
  check(closeEnough(myPow(-2.0, 5), -32.0), "preserves a negative base sign");
  check(closeEnough(myPow(1.0, LLONG_MIN), 1.0), "handles the minimum long long exponent");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
