#include <algorithm>
#include <limits>
#include <vector>

int kthElement(const std::vector<int>& first, const std::vector<int>& second, int k) {
    const std::vector<int>* a = &first;
    const std::vector<int>* b = &second;
    if (a->size() > b->size()) std::swap(a, b);
    const int m = static_cast<int>(a->size()), n = static_cast<int>(b->size());
    int lo = std::max(0, k - n), hi = std::min(k, m);
    while (lo <= hi) {
        const int cutA = lo + (hi - lo) / 2, cutB = k - cutA;
        const int leftA = cutA == 0 ? std::numeric_limits<int>::min() : (*a)[cutA - 1];
        const int rightA = cutA == m ? std::numeric_limits<int>::max() : (*a)[cutA];
        const int leftB = cutB == 0 ? std::numeric_limits<int>::min() : (*b)[cutB - 1];
        const int rightB = cutB == n ? std::numeric_limits<int>::max() : (*b)[cutB];
        if (leftA <= rightB && leftB <= rightA) return std::max(leftA, leftB);
        if (leftA > rightB) hi = cutA - 1;
        else lo = cutA + 1;
    }
    return 0;
}
