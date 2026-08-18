# K Most Frequent Elements

Given an integer array `nums` and an integer `k`, return the `k` distinct values that appear most frequently.

Order the result by decreasing frequency. When two values have the same frequency, put the smaller value first. You may assume `1 <= k <=` the number of distinct values in `nums`.

Your solution should use a heap or priority queue and should run in approximately `O(n log k)` time after counting frequencies, where `n` is the number of input values.

## Examples

```text
nums = [1,1,1,2,2,3], k = 2 -> [1,2]
nums = [4,4,5,5,6], k = 2 -> [4,5]
```
