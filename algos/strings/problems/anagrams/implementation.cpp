#include <bits/stdc++.h>
using namespace std;

bool areAnagrams(const string& first, const string& second) {
    if (first.size() != second.size()) return false;
    array<int, 256> counts{};
    for (unsigned char c : first) ++counts[c];
    for (unsigned char c : second) {
        if (--counts[c] < 0) return false;
    }
    return all_of(counts.begin(), counts.end(), [](int count) { return count == 0; });
}

int main() {
    cout << boolalpha << areAnagrams("listen", "silent") << '\n';
    return 0;
}
