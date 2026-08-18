#include <vector>

int singleNonDuplicate(const std::vector<int>& values) {
    int left = 0;
    int right = static_cast<int>(values.size()) - 1;

    while (left < right) {
        int middle = left + (right - left) / 2;
        if ((middle & 1) != 0) {
            --middle;
        }

        if (values[middle] == values[middle + 1]) {
            left = middle + 2;
        } else {
            right = middle;
        }
    }

    return values[left];
}
