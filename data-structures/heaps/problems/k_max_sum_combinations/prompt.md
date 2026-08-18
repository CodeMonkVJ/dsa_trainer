# K Maximum Sum Combinations

Given two integer arrays `A` and `B` of equal length `n`, return the `k` largest
values of `A[i] + B[j]`, where each pair of indices may be used independently.

Return the sums in non-increasing order. Duplicate sums should appear as many times
as they occur among the selected combinations. The inputs are non-empty and
`1 <= k <= n`.

Design an efficient solution using sorting and a max-heap rather than enumerating
all `n * n` pairs.
