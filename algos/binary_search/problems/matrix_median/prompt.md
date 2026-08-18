# Matrix Median

Given a matrix whose rows are sorted in non-decreasing order, return its
median. The matrix contains an odd number of elements, and the median is the
element that has at least half of the elements less than or equal to it and at
least half greater than or equal to it.

Use binary search over the value range, counting elements less than or equal
to each candidate with an upper-bound search in every row. The rows may have
different lengths, but the matrix must be non-empty and contain an odd number
of elements.
