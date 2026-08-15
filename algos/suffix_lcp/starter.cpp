#include <bits/stdc++.h>
using namespace std;
struct SuffixArray { string text; vector<int> sa; vector<int> lcp; explicit SuffixArray(const string& value) : text(value) {} };
