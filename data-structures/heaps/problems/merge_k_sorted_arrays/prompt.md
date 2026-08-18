# Merge K Sorted Arrays

Given `k` arrays, each sorted in non-decreasing order, merge them into one sorted array.

Implement `mergeKSortedArrays`. Empty input arrays are valid and should be ignored. Return an empty vector when there are no values. Use a min-heap to keep the next candidate from each array, giving `O(N log k)` time for `N` total values and `O(k)` auxiliary heap space.
