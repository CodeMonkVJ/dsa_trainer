/**
 * 0/1 Knapsack
 *
 * Chooses each item at most once while maximizing value under a capacity
 * limit. The one-dimensional DP table is iterated backwards so an item
 * cannot accidentally be selected more than once.
 *
 * Time: O(number of items * capacity)
 * Extra space: O(capacity)
 */
#include <bits/stdc++.h>
using namespace std;

struct Item {
    int weight;
    int value;
};

static int maximumValue(const vector<Item>& items, int capacity) {
    vector<int> best(capacity + 1, 0);

    for (const Item& item : items) {
        for (int current = capacity; current >= item.weight; --current) {
            best[current] = max(best[current],
                                best[current - item.weight] + item.value);
        }
    }
    return best[capacity];
}

int main() {
    vector<Item> items{{2, 12}, {1, 10}, {3, 20}, {2, 15}};
    cout << "Maximum value: " << maximumValue(items, 5) << '\n';
    return 0;
}
