# Compare Version Numbers

Implement `compareVersion(version1, version2)` and return:

- `-1` if `version1` is smaller;
- `0` if both versions are equal;
- `1` if `version1` is larger.

Versions consist of non-negative integer components separated by dots. Compare
components from left to right numerically, not lexicographically. Missing
components are treated as zero, and leading zeroes do not change a component's
value.

Requirements:

- Handle components too large for built-in integer types without converting the
  whole component to an integer.
- Ignore trailing zero-valued components.
- Use `O(n + m)` time and `O(1)` auxiliary space, excluding the input strings.
