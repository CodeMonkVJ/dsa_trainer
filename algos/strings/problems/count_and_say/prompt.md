# Count and Say

Implement `countAndSay(n)` to return the n-th term of the count-and-say sequence.

The sequence starts with `"1"`. To produce the next term, read the previous
term from left to right and describe each consecutive run as its count followed
by its digit:

```text
1 → 11 → 21 → 1211 → 111221 → ...
```

Requirements:

- Return `""` when `n <= 0`.
- Treat each maximal run of equal digits as one group.
- Preserve the order of groups from the previous term.
- Use an iterative solution with `O(n * L)` time, where `L` is the length of
  the generated terms.
