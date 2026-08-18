#include <bits/stdc++.h>
using namespace std;

static string reverseWords(const string& input) {
    vector<string> words;
    string word;
    for (char ch : input) {
        if (isspace(static_cast<unsigned char>(ch))) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word.push_back(ch);
        }
    }
    if (!word.empty()) words.push_back(word);

    reverse(words.begin(), words.end());
    string result;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) result += ' ';
        result += words[i];
    }
    return result;
}

int main() {
    cout << reverseWords("  the sky is blue  ") << '\n';
    return 0;
}
