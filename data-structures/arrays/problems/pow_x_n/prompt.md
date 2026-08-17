# Pow(x, n)

Implement the following function:

```cpp
double myPow(double x, long long n);
```

Return `x` raised to the integer power `n`. The exponent may be negative,
zero, or as small as `LLONG_MIN`. Inputs satisfy `x != 0` when `n` is negative.

Use exponentiation by squaring so the running time is `O(log |n|)` and use
`O(1)` extra space. Standard floating-point error within `1e-9` relative or
absolute tolerance is accepted.
