/**
 * Count and Say
 *
 * Builds each term by scanning the previous term and emitting the length and
 * digit of every maximal run.
 *
 * Time: O(n * L), where L is the length of the generated terms
 * Extra space: O(L)
 */
#include <bits/stdc++.h>
using namespace std;

static string countAndSay(int n) {
    if (n <= 0) return "";

    string term = "1";
    for (int step = 1; step < n; ++step) {
        string next;
        for (size_t i = 0; i < term.size();) {
            size_t end = i + 1;
            while (end < term.size() && term[end] == term[i]) ++end;
            next += to_string(end - i);
            next.push_back(term[i]);
            i = end;
        }
        term = move(next);
    }
    return term;
}

int main() {
    cout << countAndSay(5) << '\n';
    return 0;
}
