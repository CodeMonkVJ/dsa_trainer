# Merge Intervals

Implement `vector<vector<int>> mergeIntervals(vector<vector<int>> intervals)`.

Each inner vector contains `[start, end]` for a closed interval. Return all
overlapping intervals merged, ordered by start, with no two returned intervals
overlapping. Intervals that only touch at an endpoint should be merged.

Handle an empty input. Target `O(n log n)` time and `O(n)` output space.
