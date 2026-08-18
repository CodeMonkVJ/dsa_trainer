Implement this function:

`int searchRotatedArray(const std::vector<int>& values, int target);`

`values` contains distinct values from an ascending array rotated at an unknown pivot. Return the index of `target`, or `-1` when it is absent. A fully sorted array is also valid.

Requirements:

- Use binary search and identify which half remains sorted at each step.
- Handle empty arrays, no rotation, and a rotation at either end.
- Target complexity: `O(log n)` time and `O(1)` auxiliary space.
