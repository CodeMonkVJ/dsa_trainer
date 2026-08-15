#include <bits/stdc++.h>
using namespace std;
struct SubarrayResult { long long sum; int left; int right; };
static SubarrayResult maximumSubarray(const vector<int>&) { return {0, 0, -1}; }
