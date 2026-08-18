# Median from Data Stream

Design a data structure that receives integers one at a time and can return the median of all values seen so far.

Implement `MedianStream::addNumber(int value)` and `MedianStream::getMedian()`. `getMedian` should return `0.0` when the stream is empty. For an even number of values, return the arithmetic mean of the two middle values. The implementation should use two heaps so insertion is `O(log n)` and median lookup is `O(1)`.
