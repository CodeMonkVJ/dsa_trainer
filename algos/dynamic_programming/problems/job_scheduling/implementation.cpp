#include <bits/stdc++.h>
using namespace std;

struct Job { int start; int end; int profit; };

int maxJobProfit(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end(), [](const Job& left, const Job& right) { return left.end < right.end; });
    vector<int> dp(jobs.size() + 1);
    for (size_t i = 1; i <= jobs.size(); ++i) {
        const Job& current = jobs[i - 1];
        auto it = upper_bound(jobs.begin(), jobs.begin() + static_cast<ptrdiff_t>(i - 1), current.start,
            [](int time, const Job& job) { return time < job.end; });
        const size_t previous = static_cast<size_t>(it - jobs.begin());
        dp[i] = max(dp[i - 1], dp[previous] + current.profit);
    }
    return dp.back();
}

int main() { return 0; }

