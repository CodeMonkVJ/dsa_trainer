/**
 * Disjoint Set Union / Union-Find
 *
 * Maintains a partition of numbered elements.  find() uses path
 * compression and unite() uses union by rank, giving an amortized
 * O(alpha(n)) cost per operation (effectively constant in practice).
 *
 * Typical uses include connectivity queries, cycle detection, and
 * Kruskal's minimum spanning tree algorithm.
 */
#include <bits/stdc++.h>
using namespace std;

class DisjointSetUnion {
    vector<int> parent_;
    vector<int> rank_;

public:
    explicit DisjointSetUnion(int count) : parent_(count), rank_(count, 0) {
        if (count <= 0) throw invalid_argument("count must be positive");
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int value) {
        if (value < 0 || value >= static_cast<int>(parent_.size()))
            throw out_of_range("DSU index");
        if (parent_[value] != value) parent_[value] = find(parent_[value]);
        return parent_[value];
    }

    bool unite(int first, int second) {
        int rootFirst = find(first);
        int rootSecond = find(second);
        if (rootFirst == rootSecond) return false;

        if (rank_[rootFirst] < rank_[rootSecond]) swap(rootFirst, rootSecond);
        parent_[rootSecond] = rootFirst;
        if (rank_[rootFirst] == rank_[rootSecond]) ++rank_[rootFirst];
        return true;
    }

    bool connected(int first, int second) {
        return find(first) == find(second);
    }
};

int main() {
    DisjointSetUnion dsu(5);
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    cout << "0 and 2 connected: " << (dsu.connected(0, 2) ? "yes" : "no") << '\n';
    cout << "0 and 3 connected: " << (dsu.connected(0, 3) ? "yes" : "no") << '\n';
    return 0;
}
