# Nth Root of a Number

Given positive integers `n` and `m`, return the integer `x` such that `x^n == m`.
If `m` is not a perfect nth power, return `-1`.

Your solution should use binary search over the possible answer range. Avoid
floating-point rounding when checking whether a candidate power equals `m`,
and stop early if the candidate power exceeds `m`.

Assume `n >= 1` and `m >= 1`. For `n == 1`, the answer is `m`.
