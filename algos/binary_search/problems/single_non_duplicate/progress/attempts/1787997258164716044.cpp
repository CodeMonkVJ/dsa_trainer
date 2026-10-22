#include <vector>

int singleNonDuplicate(const std::vector<int> &values) {
  // Return the only value that appears once.
  int n = values.size();

  int left = 0;
  int right = n - 1;
  int mid = (left + right) / 2;

  while (left < right) {
    mid = (left + right) / 2;
    if (mid % 2 == 1)
      mid--;

    if (values[mid] == values[mid + 1]) {
      left = mid + 2;
    } else {
      right = mid;
    }
  }

  return values[left];
}
