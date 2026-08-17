# Merge Sorted Arrays

Implement `void mergeSortedArrays(vector<int>& first, vector<int>& second)`.

Both inputs are sorted in non-decreasing order. Rearrange their existing
elements in place so that every element in `first` is less than or equal to
every element in `second`, while each vector remains sorted. Do not allocate a
third array and do not change either vector's size.

Handle empty vectors. Target `O((n + m) log(n + m))` time and `O(1)` extra space.
