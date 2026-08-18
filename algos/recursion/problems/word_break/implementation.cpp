#include <bits/stdc++.h>
using namespace std;

static bool canBreak(const string& text, const unordered_set<string>& words,
                    int start, vector<int8_t>& memo) {
    if (start == static_cast<int>(text.size())) return true;
    if (memo[start] != -1) return memo[start];

    for (int end = start + 1; end <= static_cast<int>(text.size()); ++end) {
        if (words.count(text.substr(start, end - start)) &&
            canBreak(text, words, end, memo)) {
            memo[start] = 1;
            return true;
        }
    }
    memo[start] = 0;
    return false;
}

bool wordBreak(string s, vector<string> dictionary) {
    unordered_set<string> words;
    for (const string& word : dictionary) {
        if (!word.empty()) words.insert(word);
    }
    if (s.empty()) return true;
    if (words.empty()) return false;
    vector<int8_t> memo(s.size(), -1);
    return canBreak(s, words, 0, memo);
}

int main() {
    cout << wordBreak("leetcode", {"leet", "code"}) << '\n';
    return 0;
}
