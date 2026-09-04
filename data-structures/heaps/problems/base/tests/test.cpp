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
// 
// int main() {
//   const vector<int> values = {5, 1, 4, 1, 3};
//   PQueue minQueue{};
//   pqInit(&minQueue, 1, true);
//   for (int value : values)
//     pqPush(&minQueue, value);
//   int peek = 0;
//   const bool peeked = pqPeek(&minQueue, &peek);
//   check("{\"heap\":\"min\",\"capacity\":1,\"values\":" + json(values) + "}",
//         "1", to_string(peeked ? peek : 0), peeked && peek == 1,
//         "min-heap peek");
//   const vector<int> minOrder = drain(&minQueue);
//   check("{\"heap\":\"min\",\"values\":" + json(values) + "}", "[1,1,3,4,5]",
//         json(minOrder), minOrder == vector<int>({1, 1, 3, 4, 5}),
//         "min-heap order");
//   pqClear(&minQueue);
// 
//   PQueue maxQueue{};
//   pqInit(&maxQueue, 2, false);
//   for (int value : values)
//     pqPush(&maxQueue, value);
//   const vector<int> maxOrder = drain(&maxQueue);
//   check("{\"heap\":\"max\",\"capacity\":2,\"values\":" + json(values) + "}",
//         "[5,4,3,1,1]", json(maxOrder), maxOrder == vector<int>({5, 4, 3, 1, 1}),
//         "max-heap order");
//   const bool poppedEmpty = pqPop(&maxQueue, nullptr);
//   const bool empty = pqIsEmpty(&maxQueue);
//   check("{\"heap\":\"max\",\"operation\":\"pop-empty\"}",
//         "{\"popped\":false,\"empty\":true}",
//         string("{\"popped\":") + (poppedEmpty ? "true" : "false") +
//             ",\"empty\":" + (empty ? "true}" : "false}"),
//         !poppedEmpty && empty, "empty pop");
//   pqClear(&maxQueue);
//   cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
//        << "}\n";
//   return passed == total ? 0 : 1;
// }
// 



int main() {
  {
    PQueue q{};
    
    bool initOk = pqInit(&q, 1, true);
    
    check("{\"case\":\"init-min\"}",
          "true",
          initOk ? "true" : "false",
          initOk && q.data != nullptr && q.size == 0,
          "initialize min heap");
    
    pqClear(&q);
  }

  {
    PQueue q{};
    pqInit(&q, 1, true);

    int value = 0;

    check("{\"case\":\"empty-peek\"}",
          "false",
          pqPeek(&q, &value) ? "true" : "false",
          !pqPeek(&q, &value),
          "peek empty heap");

    check("{\"case\":\"empty-pop\"}",
          "false",
          pqPop(&q, &value) ? "true" : "false",
          !pqPop(&q, &value),
          "pop empty heap");

    check("{\"case\":\"empty-state\"}",
          "true",
          pqIsEmpty(&q) ? "true" : "false",
          pqIsEmpty(&q),
          "empty heap state");

    pqClear(&q);
  }

  {
    PQueue q{};
    pqInit(&q, 1, true);

    pqPush(&q, 42);

    int value = 0;

    bool peekOk = pqPeek(&q, &value);
    check("{\"case\":\"single-peek\"}",
          "42",
          peekOk ? to_string(value) : "null",
          peekOk && value == 42 && q.size == 1,
          "single element peek");

    bool popOk = pqPop(&q, &value);
    check("{\"case\":\"single-pop\"}",
          "42",
          popOk ? to_string(value) : "null",
          popOk && value == 42 && q.size == 0 && pqIsEmpty(&q),
          "single element pop");

    pqClear(&q);
  }

  {
    const vector<int> values = {5, 1, 4, 1, 3};

    PQueue q{};
    pqInit(&q, 1, true);

    for (int v : values)
      pqPush(&q, v);

    const auto order = drain(&q);

    check("{\"heap\":\"min\",\"values\":" + json(values) + "}",
          "[1,1,3,4,5]",
          json(order),
          order == vector<int>({1, 1, 3, 4, 5}),
          "min heap order");

    pqClear(&q);
  }

  {
    const vector<int> values = {5, 1, 4, 1, 3};

    PQueue q{};
    pqInit(&q, 2, false);

    for (int v : values)
      pqPush(&q, v);

    const auto order = drain(&q);

    check("{\"heap\":\"max\",\"values\":" + json(values) + "}",
          "[5,4,3,1,1]",
          json(order),
          order == vector<int>({5, 4, 3, 1, 1}),
          "max heap order");

    pqClear(&q);
  }

  {
    const vector<int> values = {-5, -1, -10, 0, 7, 3};

    PQueue q{};
    pqInit(&q, 1, true);

    for (int v : values)
      pqPush(&q, v);

    const auto order = drain(&q);

    check("{\"heap\":\"min\",\"values\":" + json(values) + "}",
          "[-10,-5,-1,0,3,7]",
          json(order),
          order == vector<int>({-10, -5, -1, 0, 3, 7}),
          "min heap negative values");

    pqClear(&q);
  }

  {
    const vector<int> values = {INT_MIN, 0, INT_MAX, -1, 1};

    PQueue q{};
    pqInit(&q, 1, false);

    for (int v : values)
      pqPush(&q, v);

    const auto order = drain(&q);

    check("{\"heap\":\"max\",\"case\":\"extremes\"}",
          "[" + to_string(INT_MAX) + ",1,0,-1," +
              to_string(INT_MIN) + "]",
          json(order),
          order == vector<int>({INT_MAX, 1, 0, -1, INT_MIN}),
          "max heap extreme values");

    pqClear(&q);
  }

  {
    PQueue q{};
    pqInit(&q, 1, true);

    for (int i = 100; i >= 0; --i)
      pqPush(&q, i);

    bool ok = true;
    int prev = INT_MIN;
    int curr = 0;

    while (pqPop(&q, &curr)) {
      if (curr < prev) {
        ok = false;
        break;
      }
      prev = curr;
    }

    check("{\"case\":\"many-elements-growth\"}",
          "true",
          ok ? "true" : "false",
          ok,
          "grows storage across many pushes");

    pqClear(&q);
  }

  {
    PQueue q{};
    pqInit(&q, 2, true);

    for (int v : {8, 3, 10, 1, 6})
      pqPush(&q, v);

    int value = 0;
    bool ok = pqPop(&q, &value) && value == 1;

    pqPush(&q, 2);
    pqPush(&q, 0);

    vector<int> rest = drain(&q);

    ok = ok && rest == vector<int>({0, 2, 3, 6, 8, 10});

    check("{\"case\":\"push-after-pop\"}",
          "[0,2,3,6,8,10]",
          json(rest),
          ok,
          "heap remains valid after interleaved operations");

    pqClear(&q);
  }

  {
    PQueue q{};
    pqInit(&q, 2, true);

    pqPush(&q, 5);
    pqPush(&q, 1);

    pqClear(&q);

    bool cleared =
        q.data == nullptr &&
        q.size == 0 &&
        pqIsEmpty(&q);

    check("{\"case\":\"clear\"}",
          "true",
          cleared ? "true" : "false",
          cleared,
          "clear resets heap");
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}