/**
 * Find the longest prefix shared by all strings.
 *
 * Time: O(total number of characters inspected)
 * Extra space: O(1), excluding the returned string
 */
#include <bits/stdc++.h>
using namespace std;

static string longestCommonPrefix(const vector<string>& words) {
    if (words.empty()) return "";

    size_t commonLength = words[0].size();
    for (size_t wordIndex = 1; wordIndex < words.size(); ++wordIndex) {
        commonLength = min(commonLength, words[wordIndex].size());
        size_t matched = 0;
        while (matched < commonLength && words[0][matched] == words[wordIndex][matched]) ++matched;
        commonLength = matched;
        if (commonLength == 0) return "";
    }
    return words[0].substr(0, commonLength);
}

int main() {
    cout << longestCommonPrefix({"flower", "flow", "flight"}) << '\n';
    return 0;
}
