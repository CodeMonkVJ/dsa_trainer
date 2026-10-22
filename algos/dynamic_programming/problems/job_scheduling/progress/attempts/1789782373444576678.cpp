#include <bits/stdc++.h>
using namespace std;

struct Job {
  int start;
  int end;
  int profit;
};

int getNext(int curr, const vector<Job> &jobs) {
  int target = jobs[curr].end;
  int n = jobs.size();

  int low = curr + 1;
  int high = n - 1;

  int ans = n;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (jobs[mid].start >= target) {
      ans = mid;
      high = mid - 1;
    } else
      low = mid + 1;
  }

  return ans;
}

int maxJobProfit(vector<Job> jobs) {
  int n = jobs.size();
  vector<int> dp(n + 1);
  sort(jobs.begin(), jobs.end(),
       [](const Job &a, const Job &b) { return a.start < b.start; });

  for (int i = n - 1; i >= 0; i--) {
    dp[i] = max(dp[i + 1], jobs[i].profit + dp[getNext(i, jobs)]);
  }

  return dp[0];
}
