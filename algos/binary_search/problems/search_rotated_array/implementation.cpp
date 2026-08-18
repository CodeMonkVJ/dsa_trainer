#include <vector>

int searchRotatedArray(const std::vector<int>& values, int target) {
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;

    while (left <= right) {
        const int middle = left + (right - left) / 2;
        if (values[middle] == target) {
            return middle;
        }

        if (values[left] <= values[middle]) {
            if (values[left] <= target && target < values[middle]) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        } else if (values[middle] < target && target <= values[right]) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}
