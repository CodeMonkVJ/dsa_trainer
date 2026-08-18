#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;

void check(const string &input, double expected, double actual,
           const char *name) {
  const bool ok = fabs(actual - expected) < 1e-9;
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":" << input << ",\"expected\":" << expected
       << ",\"actual\":" << actual << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  MedianStream stream;
  check("{\"values\":[]}", 0.0, stream.getMedian(),
        "empty stream returns zero");
  stream.addNumber(5);
  check("{\"values\":[5]}", 5.0, stream.getMedian(), "one value");
  stream.addNumber(15);
  check("{\"values\":[5,15]}", 10.0, stream.getMedian(),
        "even count averages middle values");
  stream.addNumber(1);
  check("{\"values\":[5,15,1]}", 5.0, stream.getMedian(),
        "odd count after out-of-order insertion");
  stream.addNumber(3);
  stream.addNumber(8);
  check("{\"values\":[5,15,1,3,8]}", 5.0, stream.getMedian(),
        "maintains median across more insertions");

  MedianStream negatives;
  for (int value : {-10, -4, -7, -20})
    negatives.addNumber(value);
  check("{\"values\":[-10,-4,-7,-20]}", -8.5, negatives.getMedian(),
        "handles negative values");

  MedianStream extremes;
  extremes.addNumber(INT_MIN);
  extremes.addNumber(INT_MAX);
  check("{\"values\":[-2147483648,2147483647]}", -0.5, extremes.getMedian(),
        "avoids integer overflow when averaging");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
