#include <bits/stdc++.h>
using namespace std;

vector<int> zFunction(const string& s) {
    vector<int> z(s.size(), 0);
    int left = 0, right = 0;
    for (int i = 1; i < static_cast<int>(s.size()); ++i) {
        if (i <= right) z[i] = min(right - i + 1, z[i - left]);
        while (i + z[i] < static_cast<int>(s.size()) &&
               s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    for (int value : zFunction("aabcaab")) cout << value << ' ';
    cout << '\n';
    return 0;
}
