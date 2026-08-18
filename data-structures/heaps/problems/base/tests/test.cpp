#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

string json(const vector<int> &values) {
  ostringstream out;
  out << '[';
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      out << ',';
    out << values[i];
  }
  out << ']';
  return out.str();
}

vector<int> drain(PQueue *queue) {
  vector<int> values;
  int value;
  while (pqPop(queue, &value))
    values.push_back(value);
  return values;
}

void check(const string &input, const string &expected, const string &actual,
           bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":" << input << ",\"expected\":" << expected
       << ",\"actual\":" << actual << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  const vector<int> values = {5, 1, 4, 1, 3};
  PQueue minQueue{};
  pqInit(&minQueue, 1, true);
  for (int value : values)
    pqPush(&minQueue, value);
  int peek = 0;
  const bool peeked = pqPeek(&minQueue, &peek);
  check("{\"heap\":\"min\",\"capacity\":1,\"values\":" + json(values) + "}",
        "1", to_string(peeked ? peek : 0), peeked && peek == 1,
        "min-heap peek");
  const vector<int> minOrder = drain(&minQueue);
  check("{\"heap\":\"min\",\"values\":" + json(values) + "}", "[1,1,3,4,5]",
        json(minOrder), minOrder == vector<int>({1, 1, 3, 4, 5}),
        "min-heap order");
  pqClear(&minQueue);

  PQueue maxQueue{};
  pqInit(&maxQueue, 2, false);
  for (int value : values)
    pqPush(&maxQueue, value);
  const vector<int> maxOrder = drain(&maxQueue);
  check("{\"heap\":\"max\",\"capacity\":2,\"values\":" + json(values) + "}",
        "[5,4,3,1,1]", json(maxOrder), maxOrder == vector<int>({5, 4, 3, 1, 1}),
        "max-heap order");
  const bool poppedEmpty = pqPop(&maxQueue, nullptr);
  const bool empty = pqIsEmpty(&maxQueue);
  check("{\"heap\":\"max\",\"operation\":\"pop-empty\"}",
        "{\"popped\":false,\"empty\":true}",
        string("{\"popped\":") + (poppedEmpty ? "true" : "false") +
            ",\"empty\":" + (empty ? "true}" : "false}"),
        !poppedEmpty && empty, "empty pop");
  pqClear(&maxQueue);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
