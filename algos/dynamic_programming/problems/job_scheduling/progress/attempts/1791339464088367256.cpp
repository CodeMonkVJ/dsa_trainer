#include <bits/stdc++.h>
using namespace std;

struct Job {
  int start;
  int end;
  int profit;
  bool operator<(const Job &other) const { return start < other.start; }
};

int nextCompatible(const vector<Job> &jobs, int curr) {
  int left = curr + 1;
  int right = jobs.size() - 1;
  Job currJob = jobs[curr];

  int best = jobs.size();

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (jobs[mid].start >= currJob.end) {
      best = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return best;
}

int maxJobProfit(vector<Job> jobs) {
  int n = jobs.size();
  sort(jobs.begin(), jobs.end());
  vector<int> dp(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    dp[i] = max(dp[i + 1], jobs[i].profit + dp[nextCompatible(jobs, i)]);
  }

  return dp[0];
}
