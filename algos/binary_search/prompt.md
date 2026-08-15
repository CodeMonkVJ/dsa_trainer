Implement this function:

`int binarySearch(const std::vector<int>& values, int target);`

`values` is sorted in nondecreasing order. Return the index of the first element equal to `target`. Return `-1` when the target is absent.

Requirements:

- Use binary search.
- Handle empty arrays and duplicate values.
- Do not call `std::lower_bound`, `std::binary_search`, or another library search implementation.
- Target complexity: `O(log n)` time and `O(1)` auxiliary space.
