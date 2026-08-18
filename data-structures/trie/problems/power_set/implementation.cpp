#include <bits/stdc++.h>
using namespace std;

vector<string> powerSet(const string& text) {
    set<string> unique;
    for (size_t mask = 0; mask < (size_t{1} << text.size()); ++mask) {
        string value;
        for (size_t i = 0; i < text.size(); ++i) if (mask & (size_t{1} << i)) value += text[i];
        unique.insert(value);
    }
    return {unique.begin(), unique.end()};
}

int main() { return 0; }

