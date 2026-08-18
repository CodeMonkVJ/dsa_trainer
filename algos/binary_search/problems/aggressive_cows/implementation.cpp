#include <algorithm>
#include <vector>

int aggressiveCows(const std::vector<int>& stalls, int cows) {
    if (stalls.empty() || cows <= 0 || cows > static_cast<int>(stalls.size()) || cows == 1) return 0;
    std::vector<int> sorted = stalls;
    std::sort(sorted.begin(), sorted.end());
    auto feasible = [&](int distance) {
        int placed = 1, last = sorted.front();
        for (int position : sorted) {
            if (position - last >= distance) {
                ++placed;
                last = position;
            }
        }
        return placed >= cows;
    };
    int lo = 0, hi = sorted.back() - sorted.front();
    while (lo < hi) {
        const int middle = lo + (hi - lo + 1) / 2;
        if (feasible(middle)) lo = middle;
        else hi = middle - 1;
    }
    return lo;
}
