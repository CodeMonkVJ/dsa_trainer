/**
 * Longest Increasing Subsequence (LIS)
 *
 * Maintains the smallest possible tail value for increasing subsequences
 * of each length. Binary search lets us replace a tail in O(log n), while
 * predecessor indices reconstruct one actual subsequence.
 *
 * Time: O(n log n)
 * Extra space: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

static vector<int> longestIncreasingSubsequence(const vector<int>& values) {
    if (values.empty()) return {};

    vector<int> tails;
    vector<int> tailIndices;
    vector<int> previous(values.size(), -1);

    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        auto position = lower_bound(tails.begin(), tails.end(), values[i]);
        int length = static_cast<int>(position - tails.begin());

        if (length == static_cast<int>(tails.size())) {
            tails.push_back(values[i]);
            tailIndices.push_back(i);
        } else {
            tails[length] = values[i];
            tailIndices[length] = i;
        }

        if (length > 0) previous[i] = tailIndices[length - 1];
    }

    vector<int> result;
    for (int index = tailIndices.back(); index != -1; index = previous[index])
        result.push_back(values[index]);
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    vector<int> values{10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> result = longestIncreasingSubsequence(values);

    cout << "LIS: ";
    for (int value : result) cout << value << ' ';
    cout << '\n';
    return 0;
}
