#include <bits/stdc++.h>
using namespace std;

int minCharsForPalindrome(const string& s) {
    string reversed = s;
    reverse(reversed.begin(), reversed.end());
    vector<int> combined;
    combined.reserve(s.size() * 2 + 1);
    for (unsigned char c : s) combined.push_back(c);
    combined.push_back(-1);
    for (unsigned char c : reversed) combined.push_back(c);

    vector<int> prefix(combined.size(), 0);
    for (int i = 1; i < static_cast<int>(combined.size()); ++i) {
        int j = prefix[i - 1];
        while (j > 0 && combined[i] != combined[j]) j = prefix[j - 1];
        if (combined[i] == combined[j]) ++j;
        prefix[i] = j;
    }
    return static_cast<int>(s.size()) - prefix.back();
}

int main() {
    cout << minCharsForPalindrome("AACECAAAA") << '\n';
    return 0;
}
