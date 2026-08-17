# Count Inversions

Implement `long long countInversions(const vector<int>& values)`.

Count pairs of indices `(i, j)` where `i < j` and `values[i] > values[j]`.
Equal values are not inversions. Leave the input unchanged and return the
answer as `long long`.

Target `O(n log n)` time and `O(n)` auxiliary space; a quadratic solution will
not scale.
