#include <algorithm>
#include <vector>

long long allocateMinimumPages(const std::vector<int>& pages, int students) {
    if (students <= 0 || students > static_cast<int>(pages.size())) return -1;
    long long lo = *std::max_element(pages.begin(), pages.end());
    long long hi = 0;
    for (int pageCount : pages) hi += pageCount;
    auto feasible = [&](long long limit) {
        int used = 1;
        long long current = 0;
        for (int pageCount : pages) {
            if (current + pageCount > limit) {
                ++used;
                current = pageCount;
            } else {
                current += pageCount;
            }
        }
        return used <= students;
    };
    while (lo < hi) {
        const long long middle = lo + (hi - lo) / 2;
        if (feasible(middle)) hi = middle;
        else lo = middle + 1;
    }
    return lo;
}
