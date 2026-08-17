#include <bits/stdc++.h>
using namespace std;

double myPow(double x, long long n) {
  unsigned long long exponent;
  bool negative = n < 0;
  if (negative) exponent = static_cast<unsigned long long>(-(n + 1)) + 1;
  else exponent = static_cast<unsigned long long>(n);

  double result = 1.0;
  while (exponent != 0) {
    if (exponent & 1ULL) result *= x;
    x *= x;
    exponent >>= 1;
  }
  return negative ? 1.0 / result : result;
}

int main() { return 0; }
