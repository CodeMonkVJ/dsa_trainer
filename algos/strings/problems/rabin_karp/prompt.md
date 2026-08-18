# Rabin-Karp String Search

Implement `rabinKarpSearch` to return the starting index of every occurrence of `pattern` in `text`, including overlapping matches.

Return an empty vector when the pattern is empty, longer than the text, or absent. Use a rolling hash to identify candidate windows and verify matching characters so hash collisions cannot produce false positives.
