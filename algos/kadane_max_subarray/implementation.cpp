/**
 * Kadane's Algorithm: Maximum Subarray Sum
 *
 * Finds the contiguous subarray with the largest sum in one pass. At each
 * position, either extend the current subarray or start a new one there.
 *
 * Time: O(n)
 * Extra space: O(1)
 *
 * The implementation also returns the subarray boundaries, which is useful
 * in interview follow-up questions.
 */
#include <bits/stdc++.h>
using namespace std;

struct SubarrayResult {
    long long sum;
    int left;
    int right;
};

static SubarrayResult maximumSubarray(const vector<int>& values) {
    if (values.empty()) throw invalid_argument("array must not be empty");

    long long bestSum = values[0];
    long long currentSum = values[0];
    int bestLeft = 0;
    int bestRight = 0;
    int currentLeft = 0;

    for (int i = 1; i < static_cast<int>(values.size()); ++i) {
        if (currentSum < 0) {
            currentSum = values[i];
            currentLeft = i;
        } else {
            currentSum += values[i];
        }

        if (currentSum > bestSum) {
            bestSum = currentSum;
            bestLeft = currentLeft;
            bestRight = i;
        }
    }

    return {bestSum, bestLeft, bestRight};
}

int main() {
    vector<int> values{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    SubarrayResult result = maximumSubarray(values);

    cout << "Maximum sum: " << result.sum << '\n';
    cout << "Subarray: ";
    for (int i = result.left; i <= result.right; ++i) cout << values[i] << ' ';
    cout << '\n';
    return 0;
}
