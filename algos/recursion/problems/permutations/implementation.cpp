#include <bits/stdc++.h>
using namespace std;

static void build(const vector<int>& values, vector<bool>& used,
                  vector<int>& current, vector<vector<int>>& result) {
    if (current.size() == values.size()) {
        result.push_back(current);
        return;
    }

    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        if (used[i] || (i > 0 && values[i] == values[i - 1] && !used[i - 1])) {
            continue;
        }
        used[i] = true;
        current.push_back(values[i]);
        build(values, used, current, result);
        current.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permutations(vector<int> values) {
    sort(values.begin(), values.end());
    vector<vector<int>> result;
    vector<int> current;
    vector<bool> used(values.size(), false);
    build(values, used, current, result);
    return result;
}

int main() {
    cout << permutations({1, 2, 3}).size() << '\n';
    return 0;
}
