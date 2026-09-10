#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int minPlatforms(const vector<int> &a, const vector<int> &d) {
  if (a.empty())
    return 0;
  vector<int> arrivals, departures;
  for (int k = 0; k < a.size(); ++k) {
    if (a[k] < d[k]) {
      arrivals.push_back(a[k]);
      departures.push_back(d[k]);
    }
  }
  sort(arrivals.begin(), arrivals.end());
  sort(departures.begin(), departures.end());

  int curr = 0, ans = 0;
  int n = arrivals.size();
  int i = 0, j = 0;
  while (i < n && j < n) {
    if (arrivals[i] < departures[j]) {
      curr++;
      i++;
      ans = max(ans, curr);
    } else {
      if (curr > 0)
        curr--;
      j++;
    }
  }

  while (i < n) {
    curr++;
    i++;
    ans = max(ans, curr);
  }

  return ans;
}
