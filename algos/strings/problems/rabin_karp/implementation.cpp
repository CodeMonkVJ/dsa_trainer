/**
 * Rabin-Karp search with a rolling hash and exact verification.
 *
 * Time: O(text length + pattern length) expected, O(text length * pattern length) worst case
 * Extra space: O(1), excluding the returned indexes
 */
#include <bits/stdc++.h>
using namespace std;

static vector<int> rabinKarpSearch(const string& text, const string& pattern) {
    vector<int> matches;
    if (pattern.empty() || pattern.size() > text.size()) return matches;

    constexpr long long base = 257;
    constexpr long long modulus = 1000000007;
    const size_t length = pattern.size();
    long long patternHash = 0;
    long long windowHash = 0;
    long long highestPower = 1;
    for (size_t i = 0; i < length; ++i) {
        patternHash = (patternHash * base + static_cast<unsigned char>(pattern[i])) % modulus;
        windowHash = (windowHash * base + static_cast<unsigned char>(text[i])) % modulus;
        if (i + 1 < length) highestPower = (highestPower * base) % modulus;
    }

    for (size_t start = 0; start + length <= text.size(); ++start) {
        if (patternHash == windowHash && text.compare(start, length, pattern) == 0)
            matches.push_back(static_cast<int>(start));

        if (start + length < text.size()) {
            long long outgoing = static_cast<unsigned char>(text[start]);
            long long incoming = static_cast<unsigned char>(text[start + length]);
            windowHash = (windowHash - outgoing * highestPower) % modulus;
            if (windowHash < 0) windowHash += modulus;
            windowHash = (windowHash * base + incoming) % modulus;
        }
    }
    return matches;
}

int main() {
    for (int index : rabinKarpSearch("ababcabcabababd", "ababd")) cout << index << ' ';
    cout << '\n';
    return 0;
}
