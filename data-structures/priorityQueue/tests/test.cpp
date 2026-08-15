#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
vector<int> drain(PQueue* queue) { vector<int> values; int value; while (pqPop(queue, &value)) values.push_back(value); return values; }
int main() {
  PQueue minQueue{}; pqInit(&minQueue, 1, true); for (int value : {5, 1, 4, 1, 3}) pqPush(&minQueue, value);
  int peek = 0; check(pqPeek(&minQueue, &peek) && peek == 1, "min-heap peek");
  check(drain(&minQueue) == vector<int>({1, 1, 3, 4, 5}), "min-heap order"); pqClear(&minQueue);
  PQueue maxQueue{}; pqInit(&maxQueue, 2, false); for (int value : {5, 1, 4, 1, 3}) pqPush(&maxQueue, value);
  check(drain(&maxQueue) == vector<int>({5, 4, 3, 1, 1}), "max-heap order");
  check(!pqPop(&maxQueue, nullptr) && pqIsEmpty(&maxQueue), "empty pop"); pqClear(&maxQueue);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
