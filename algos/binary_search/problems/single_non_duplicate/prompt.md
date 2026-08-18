Implement this function:

`int singleNonDuplicate(const std::vector<int>& values);`

`values` is sorted in nondecreasing order. Exactly one value appears once, and every other value appears exactly twice. Return the value that appears once.

Requirements:

- Use binary search rather than scanning the whole array.
- Handle a singleton array and the unique value at either end.
- Target complexity: `O(log n)` time and `O(1)` auxiliary space.
