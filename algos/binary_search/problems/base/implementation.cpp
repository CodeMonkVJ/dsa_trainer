#include <vector>

int binarySearch(const std::vector<int>& values, int target) {
    int left = 0;
    int right = static_cast<int>(values.size());

    while (left < right) {
        const int middle = left + (right - left) / 2;
        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    if (left < static_cast<int>(values.size()) && values[left] == target) {
        return left;
    }
    return -1;
}
