/**
 * Knuth-Morris-Pratt (KMP) String Search
 *
 * Finds every occurrence of a pattern in a text without restarting the
 * pattern comparison after a mismatch. The prefix table records the
 * longest proper prefix that is also a suffix for each pattern prefix.
 *
 * Time: O(text length + pattern length)
 * Extra space: O(pattern length)
 */
#include <bits/stdc++.h>
using namespace std;

static vector<int> buildPrefixTable(const string& pattern) {
    vector<int> prefix(pattern.size(), 0);

    for (int i = 1, matched = 0; i < static_cast<int>(pattern.size()); ++i) {
        while (matched > 0 && pattern[i] != pattern[matched])
            matched = prefix[matched - 1];
        if (pattern[i] == pattern[matched]) ++matched;
        prefix[i] = matched;
    }
    return prefix;
}

static vector<int> findOccurrences(const string& text, const string& pattern) {
    if (pattern.empty()) return {};

    vector<int> prefix = buildPrefixTable(pattern);
    vector<int> occurrences;

    for (int i = 0, matched = 0; i < static_cast<int>(text.size()); ++i) {
        while (matched > 0 && text[i] != pattern[matched])
            matched = prefix[matched - 1];

        if (text[i] == pattern[matched]) ++matched;
        if (matched == static_cast<int>(pattern.size())) {
            occurrences.push_back(i - matched + 1);
            matched = prefix[matched - 1];
        }
    }
    return occurrences;
}

int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";

    cout << "Pattern found at indices: ";
    for (int index : findOccurrences(text, pattern)) cout << index << ' ';
    cout << '\n';
    return 0;
}
