# Z Function

Given a string `s`, return its Z-array. `z[i]` is the length of the longest substring beginning at `i` that is also a prefix of `s`. Define `z[0]` as `0`.

Implement:

```cpp
std::vector<int> zFunction(const std::string& s);
```

Use the linear-time Z algorithm. An empty string should return an empty vector.
