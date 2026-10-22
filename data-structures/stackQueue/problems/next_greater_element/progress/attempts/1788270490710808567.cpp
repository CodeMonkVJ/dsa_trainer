#include <bits/stdc++.h>
using namespace std;

vector<int> nextGreaterElement(const vector<int> &values) {
  int n = values.size();
  vector<int> ans(n, -1);
  stack<int> st;

  for (int i = n - 1; i >= 0; i--) {
    if (st.empty()) {
      st.push(values[i]);
    } else {
      while (!st.empty() && st.top() <= values[i])
        st.pop();
      if (!st.empty())
        ans[i] = st.top();
      st.push(values[i]);
    }
  }

  return ans;
}
