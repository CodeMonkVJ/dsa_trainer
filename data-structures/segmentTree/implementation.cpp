/**
 * Segment Tree for Range Sum
 *
 * A segment tree stores aggregate information for intervals.  This
 * version supports point assignment and inclusive range-sum queries.
 *
 * Build: O(n), update: O(log n), query: O(log n), memory: O(n).
 * Invalid ranges throw exceptions so mistakes are visible while learning.
 */
#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    int size_;
    vector<long long> tree_;

    void build(const vector<int>& values, int node, int left, int right) {
        if (left == right) {
            tree_[node] = values[left];
            return;
        }
        int middle = left + (right - left) / 2;
        build(values, node * 2, left, middle);
        build(values, node * 2 + 1, middle + 1, right);
        tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
    }

    long long query(int node, int left, int right, int queryLeft, int queryRight) const {
        if (queryRight < left || right < queryLeft) return 0;
        if (queryLeft <= left && right <= queryRight) return tree_[node];
        int middle = left + (right - left) / 2;
        return query(node * 2, left, middle, queryLeft, queryRight) +
               query(node * 2 + 1, middle + 1, right, queryLeft, queryRight);
    }

    void update(int node, int left, int right, int index, int value) {
        if (left == right) {
            tree_[node] = value;
            return;
        }
        int middle = left + (right - left) / 2;
        if (index <= middle) update(node * 2, left, middle, index, value);
        else update(node * 2 + 1, middle + 1, right, index, value);
        tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
    }

public:
    explicit SegmentTree(const vector<int>& values)
        : size_(static_cast<int>(values.size())), tree_(values.size() * 4) {
        if (values.empty()) throw invalid_argument("values cannot be empty");
        build(values, 1, 0, size_ - 1);
    }

    long long query(int left, int right) const {
        if (left < 0 || right >= size_ || left > right)
            throw out_of_range("invalid segment range");
        return query(1, 0, size_ - 1, left, right);
    }

    void update(int index, int value) {
        if (index < 0 || index >= size_) throw out_of_range("invalid index");
        update(1, 0, size_ - 1, index, value);
    }
};

int main() {
    SegmentTree tree({1, 3, 5, 7, 9, 11});
    cout << "Sum [1, 4]: " << tree.query(1, 4) << '\n';
    tree.update(2, 10);
    cout << "After update, sum [1, 4]: " << tree.query(1, 4) << '\n';
    return 0;
}
