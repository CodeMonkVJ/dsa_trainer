/**
 * Sliding-Window Maximum
 *
 * Computes the maximum value in every window of width k. A monotonic
 * deque stores candidate indices: values leave the back when they are
 * smaller than the new value, and expired indices leave the front.
 *
 * Time: O(n), because every index enters and leaves the deque at most once
 * Extra space: O(k)
 */
#include <bits/stdc++.h>
using namespace std;

static vector<int> slidingWindowMaximum(const vector<int>& values, int windowSize) {
    if (windowSize <= 0 || windowSize > static_cast<int>(values.size()))
        throw invalid_argument("window size must be between 1 and n");

    deque<int> candidates;
    vector<int> result;

    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        while (!candidates.empty() && candidates.front() <= i - windowSize)
            candidates.pop_front();

        while (!candidates.empty() && values[candidates.back()] <= values[i])
            candidates.pop_back();

        candidates.push_back(i);
        if (i >= windowSize - 1) result.push_back(values[candidates.front()]);
    }

    return result;
}

int main() {
    vector<int> values{1, 3, -1, -3, 5, 3, 6, 7};
    for (int maximum : slidingWindowMaximum(values, 3)) cout << maximum << ' ';
    cout << '\n';
    return 0;
}
