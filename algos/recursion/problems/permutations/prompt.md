# Permutations

Given a vector of integers, return all of its distinct permutations. If a value appears more than once, duplicate permutations must not be returned.

The order of the returned permutations does not matter. The input may be empty; in that case return one permutation: the empty permutation.

Implement:

```cpp
std::vector<std::vector<int>> permutations(std::vector<int> values);
```

Aim for backtracking with duplicate branches skipped. The expected time is proportional to the number of generated permutations, with sorting allowed up front.
