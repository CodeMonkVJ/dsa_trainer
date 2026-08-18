#include <cstdint>

namespace {

int comparePower(int base, int exponent, std::int64_t target) {
    std::int64_t value = 1;
    for (int i = 0; i < exponent; ++i) {
        if (value > target / base) return 1;
        value *= base;
    }
    return value == target ? 0 : -1;
}

}  // namespace

int nthRoot(int n, std::int64_t m) {
    if (n < 1 || m < 1) return -1;
    int low = 1;
    int high = m < 2147483647LL ? static_cast<int>(m) : 2147483647;
    while (low <= high) {
        const int middle = low + (high - low) / 2;
        const int comparison = comparePower(middle, n, m);
        if (comparison == 0) return middle;
        if (comparison > 0) high = middle - 1;
        else low = middle + 1;
    }
    return -1;
}
