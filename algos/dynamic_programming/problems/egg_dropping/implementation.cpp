#include <bits/stdc++.h>
using namespace std;

int minEggDrops(int eggs, int floors) {
    if (eggs <= 0) throw invalid_argument("eggs must be positive");
    vector<int> reachable(eggs + 1);
    int trials = 0;
    int covered = 0;
    while (covered < floors) {
        ++trials;
        for (int egg = eggs; egg >= 1; --egg) reachable[egg] += reachable[egg - 1] + 1;
        covered = reachable[eggs];
    }
    return trials;
}

int main() { return 0; }

