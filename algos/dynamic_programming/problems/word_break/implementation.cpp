#include <bits/stdc++.h>
using namespace std;

bool wordBreak(const string& text, const vector<string>& dictionary) {
    unordered_set<string> words(dictionary.begin(), dictionary.end());
    vector<bool> possible(text.size() + 1);
    possible[0] = true;
    for (size_t end = 1; end <= text.size(); ++end) {
        for (size_t start = 0; start < end; ++start) {
            if (possible[start] && words.contains(text.substr(start, end - start))) {
                possible[end] = true;
                break;
            }
        }
    }
    return possible.back();
}

int main() { return 0; }

