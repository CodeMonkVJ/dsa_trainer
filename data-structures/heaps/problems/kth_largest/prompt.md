# K-th Largest Element

Given an unsorted array of integers and an integer `k`, return the k-th largest element.

The largest element has rank 1. Duplicate values count as separate elements. You may
rearrange the input array, and the input is guaranteed to be non-empty with
`1 <= k <= nums.size()`.

Aim for better than sorting the entire array by maintaining a min-heap of at most `k`
values.
