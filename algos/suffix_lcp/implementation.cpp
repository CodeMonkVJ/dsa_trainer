#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    string text;
    vector<int> sa;   // sorted suffix indexes
    vector<int> lcp;  // longest common prefix between neighbors

    explicit SuffixArray(const string &s) : text(s) {
        buildSuffixArray();
        buildLCP();
    }

private:
    void buildSuffixArray() {
        int n = static_cast<int>(text.size());
        sa.resize(n);
        vector<int> rank(n), tmp(n);

        for (int i = 0; i < n; ++i) {
            sa[i] = i;
            rank[i] = static_cast<unsigned char>(text[i]);
        }

        for (int k = 1; k < n; k <<= 1) {
            auto cmp = [&](int i, int j) {
                if (rank[i] != rank[j]) return rank[i] < rank[j];
                int ri = i + k < n ? rank[i + k] : -1;
                int rj = j + k < n ? rank[j + k] : -1;
                return ri < rj;
            };
            sort(sa.begin(), sa.end(), cmp);

            tmp[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            }
            rank = tmp;
            if (rank[sa.back()] == n - 1) break; // all ranks unique
        }
    }

    void buildLCP() {
        int n = static_cast<int>(text.size());
        lcp.assign(n ? n - 1 : 0, 0);
        if (n == 0) return;

        vector<int> rank(n);
        for (int i = 0; i < n; ++i) {
            rank[sa[i]] = i;
        }

        int h = 0;
        for (int i = 0; i < n; ++i) {
            int r = rank[i];
            if (r == 0) continue;
            int j = sa[r - 1];
            while (i + h < n && j + h < n && text[i + h] == text[j + h]) {
                ++h;
            }
            lcp[r - 1] = h;
            if (h > 0) --h;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    if (!getline(cin, input)) {
        cerr << "Failed to read input string.\n";
        return 1;
    }

    SuffixArray sa(input);

    cout << "Suffix Array (index : suffix)\n";
    for (size_t i = 0; i < sa.sa.size(); ++i) {
        cout << sa.sa[i] << " : " << input.substr(sa.sa[i]) << '\n';
    }

    if (!sa.lcp.empty()) {
        cout << "\nLCP array (between sa[i] and sa[i+1]):\n";
        for (size_t i = 0; i < sa.lcp.size(); ++i) {
            cout << sa.lcp[i] << (i + 1 == sa.lcp.size() ? '\n' : ' ');
        }
    }

    return 0;
}
