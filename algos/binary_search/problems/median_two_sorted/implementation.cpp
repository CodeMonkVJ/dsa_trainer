#include <algorithm>
#include <limits>
#include <vector>

double findMedianSortedArrays(const std::vector<int>& first,
                              const std::vector<int>& second) {
    const std::vector<int>* a = &first;
    const std::vector<int>* b = &second;
    if (a->size() > b->size()) std::swap(a, b);
    const int m = static_cast<int>(a->size());
    const int n = static_cast<int>(b->size());
    const int leftSize = (m + n + 1) / 2;
    int lo = 0, hi = m;
    while (lo <= hi) {
        const int cutA = lo + (hi - lo) / 2;
        const int cutB = leftSize - cutA;
        const int leftA = cutA == 0 ? std::numeric_limits<int>::min() : (*a)[cutA - 1];
        const int rightA = cutA == m ? std::numeric_limits<int>::max() : (*a)[cutA];
        const int leftB = cutB == 0 ? std::numeric_limits<int>::min() : (*b)[cutB - 1];
        const int rightB = cutB == n ? std::numeric_limits<int>::max() : (*b)[cutB];
        if (leftA <= rightB && leftB <= rightA) {
            const int left = std::max(leftA, leftB);
            if ((m + n) % 2 == 1) return left;
            return (static_cast<double>(left) + std::min(rightA, rightB)) / 2.0;
        }
        if (leftA > rightB) hi = cutA - 1;
        else lo = cutA + 1;
    }
    return 0.0;
}
