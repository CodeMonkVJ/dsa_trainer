/**
 * Quick Sort
 *
 * Partitions the array around a pivot, then recursively sorts the two
 * partitions. This version uses the last element as the pivot and places
 * values smaller than the pivot on its left.
 *
 * Average time: O(n log n)
 * Worst-case time: O(n^2) when partitions are repeatedly unbalanced
 * Extra space: O(log n) average recursion stack
 */
#include <bits/stdc++.h>
using namespace std;

static int partition(vector<int>& values, int left, int right) {
    int pivot = values[right];
    int smaller = left;

    for (int i = left; i < right; ++i) {
        if (values[i] < pivot) {
            swap(values[i], values[smaller]);
            ++smaller;
        }
    }
    swap(values[smaller], values[right]);
    return smaller;
}

static void quickSort(vector<int>& values, int left, int right) {
    if (left >= right) return;

    int pivotIndex = partition(values, left, right);
    quickSort(values, left, pivotIndex - 1);
    quickSort(values, pivotIndex + 1, right);
}

int main() {
    vector<int> values{9, 4, 7, 3, 10, 5};
    quickSort(values, 0, static_cast<int>(values.size()) - 1);

    for (int value : values) cout << value << ' ';
    cout << '\n';
    return 0;
}
