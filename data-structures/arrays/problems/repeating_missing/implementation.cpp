#include <bits/stdc++.h>
using namespace std;

pair<int, int> findRepeatingMissing(const vector<int>& values) {
  const long long n = static_cast<long long>(values.size());
  long long actualSum = 0;
  long long actualSquares = 0;
  for (int value : values) {
    actualSum += value;
    actualSquares += static_cast<long long>(value) * value;
  }

  const long long expectedSum = n * (n + 1) / 2;
  const long long expectedSquares = n * (n + 1) * (2 * n + 1) / 6;
  const long long difference = actualSum - expectedSum; // repeating - missing
  if (difference == 0) return {-1, -1};
  const long long sum = (actualSquares - expectedSquares) / difference;
  const long long repeating = (difference + sum) / 2;
  const long long missing = sum - repeating;
  return {static_cast<int>(repeating), static_cast<int>(missing)};
}
