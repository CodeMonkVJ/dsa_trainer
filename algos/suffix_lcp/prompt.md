# Suffix Array and LCP

Implement the `SuffixArray` class so its `sa` field contains suffix starting indexes in lexicographic order and its `lcp` field contains the longest common prefix length of each neighboring pair.

Requirements:

- Handle empty and repeated-character strings.
- Keep `lcp.size() == max(0, text.size() - 1)`.
- Target construction complexity should be better than comparing every suffix pair from scratch.
