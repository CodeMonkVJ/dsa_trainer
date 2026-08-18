#include <bits/stdc++.h>
using namespace std;

static string longestPalindromicSubstring(const string& text) {
    if (text.empty()) return {};
    int bestStart = 0, bestLength = 1;

    auto expand = [&](int left, int right) {
        while (left >= 0 && right < static_cast<int>(text.size()) &&
               text[left] == text[right]) {
            int length = right - left + 1;
            if (length > bestLength) {
                bestStart = left;
                bestLength = length;
            }
            --left;
            ++right;
        }
    };

    for (int center = 0; center < static_cast<int>(text.size()); ++center) {
        expand(center, center);
        expand(center, center + 1);
    }
    return text.substr(bestStart, bestLength);
}

int main() {
    cout << longestPalindromicSubstring("babad") << '\n';
    return 0;
}
