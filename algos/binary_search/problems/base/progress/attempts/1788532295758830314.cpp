#include <vector>

int binarySearch(const std::vector<int> &values, int target) {
  // Return the first index containing target, or -1 when target is absent.
  int n = values.size();
  int left = 0;
  int right = n;

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (values[mid] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  if (left < n && values[left] == target) {
    return left;
  }

  return -1;
}
