#include <algorithm>
#include <limits>
#include <vector>

int matrixMedian(const std::vector<std::vector<int>>& matrix) {
    int low = std::numeric_limits<int>::max();
    int high = std::numeric_limits<int>::min();
    long long elements = 0;
    for (const auto& row : matrix) {
        if (row.empty()) continue;
        low = std::min(low, row.front());
        high = std::max(high, row.back());
        elements += static_cast<long long>(row.size());
    }
    if (elements == 0 || elements % 2 == 0) return 0;
    const long long rank = (elements + 1) / 2;
    while (low <= high) {
        const int middle = low + (high - low) / 2;
        long long count = 0;
        for (const auto& row : matrix) {
            count += std::upper_bound(row.begin(), row.end(), middle) - row.begin();
        }
        if (count < rank) low = middle + 1;
        else high = middle - 1;
    }
    return low;
}
