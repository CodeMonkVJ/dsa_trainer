#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  Queue queue; queueInit(&queue); int value = 0;
  check(queueIsEmpty(&queue) && !queuePeek(&queue, &value), "empty queue");
  queueEnqueue(&queue, 10); queueEnqueue(&queue, 20); queueEnqueue(&queue, 30);
  check(queue.size == 3 && queuePeek(&queue, &value) && value == 10, "enqueue and peek");
  check(queueDequeue(&queue, &value) && value == 10, "FIFO dequeue");
  queueDequeue(&queue, &value); queueDequeue(&queue, &value); check(queueIsEmpty(&queue) && !queueDequeue(&queue, &value), "drain and empty dequeue");
  queueClear(&queue); cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
