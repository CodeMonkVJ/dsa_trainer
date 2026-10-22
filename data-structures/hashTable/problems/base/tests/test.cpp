#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(const char *name, bool ok) {
  ++total;

  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"case\":\"" << name
       << "\"},\"expected\":true,\"actual\":"
       << (ok ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

struct ForEachData {
  map<string, int> values;
  int calls = 0;
};

void collectEntry(const char *key, int value, void *userData) {
  auto *data = static_cast<ForEachData *>(userData);

  data->values[key] = value;
  data->calls++;
}

int main() {
  // ------------------------------------------------------------
  // Initialization
  // ------------------------------------------------------------
  HashTable table{};

  check(
      "initialize table",
      htInit(&table, 2, 0.75) &&
          table.buckets != nullptr &&
          table.bucketCount == 2 &&
          table.size == 0 &&
          table.maxLoadFactor == 0.75);

  check(
      "initial load factor zero",
      htLoadFactor(&table) == 0.0);

  check(
      "missing key in empty table",
      !htContains(&table, "missing"));

  {
    int value = 123;

    check(
        "get missing key",
        !htGet(&table, "missing", &value));
  }

  check(
      "remove missing key",
      !htRemove(&table, "missing") &&
          table.size == 0);

  // ------------------------------------------------------------
  // Basic insertion
  // ------------------------------------------------------------
  check(
      "insert alpha",
      htPut(&table, "alpha", 1) &&
          table.size == 1 &&
          htContains(&table, "alpha"));

  {
    int value = 0;

    check(
        "get alpha",
        htGet(&table, "alpha", &value) &&
            value == 1);
  }

  // ------------------------------------------------------------
  // Updating existing key should NOT increase size
  // ------------------------------------------------------------
  {
    size_t oldSize = table.size;
    size_t oldBucketCount = table.bucketCount;

    bool updated = htPut(&table, "alpha", 99);

    int value = 0;
    bool found = htGet(&table, "alpha", &value);

    check(
        "update existing key",
        updated &&
            found &&
            value == 99 &&
            table.size == oldSize &&
            table.bucketCount == oldBucketCount);
  }

  // ------------------------------------------------------------
  // Resize
  //
  // Initial capacity 2, max LF .75.
  // Inserting a second unique element would produce load 1.0,
  // so table should grow.
  // ------------------------------------------------------------
  {
    bool inserted = htPut(&table, "beta", 2);

    check(
        "resize on load factor",
        inserted &&
            table.size == 2 &&
            table.bucketCount > 2);
  }

  {
    int alpha = 0;
    int beta = 0;

    check(
        "entries survive resize",
        htGet(&table, "alpha", &alpha) &&
            htGet(&table, "beta", &beta) &&
            alpha == 99 &&
            beta == 2);
  }

  check(
      "insert after resize",
      htPut(&table, "gamma", 3) &&
          table.size == 3);

  // ------------------------------------------------------------
  // Independent key ownership
  //
  // The table must copy the key rather than storing caller memory.
  // ------------------------------------------------------------
  {
    char key[] = "mutable";

    check(
        "insert mutable key",
        htPut(&table, key, 77));

    key[0] = 'X';

    int value = 0;

    check(
        "owns independent key copy",
        htGet(&table, "mutable", &value) &&
            value == 77 &&
            !htContains(&table, "Xutable"));
  }

  // ------------------------------------------------------------
  // ForEach
  // ------------------------------------------------------------
  {
    ForEachData data;

    htForEach(&table, collectEntry, &data);

    check(
        "foreach visits every entry exactly once",
        data.calls == static_cast<int>(table.size) &&
            data.values.size() == table.size &&
            data.values["alpha"] == 99 &&
            data.values["beta"] == 2 &&
            data.values["gamma"] == 3 &&
            data.values["mutable"] == 77);
  }

  // ------------------------------------------------------------
  // Load factor
  // ------------------------------------------------------------
  {
    double expected =
        static_cast<double>(table.size) /
        static_cast<double>(table.bucketCount);

    check(
        "load factor exact",
        abs(htLoadFactor(&table) - expected) < 1e-12);
  }

  // ------------------------------------------------------------
  // Bucket statistics
  // ------------------------------------------------------------
  {
    size_t longest = 0;
    size_t empty = 0;

    size_t nonEmpty =
        htBucketStats(&table, &longest, &empty);

    check(
        "bucket statistics internally consistent",
        nonEmpty + empty == table.bucketCount &&
            nonEmpty <= table.size &&
            longest >= 1 &&
            longest <= table.size);
  }

  // ------------------------------------------------------------
  // Remove existing key
  // ------------------------------------------------------------
  {
    size_t before = table.size;

    bool removed = htRemove(&table, "beta");

    check(
        "remove existing key",
        removed &&
            table.size == before - 1 &&
            !htContains(&table, "beta"));
  }

  {
    int value = 0;

    check(
        "removed key cannot be retrieved",
        !htGet(&table, "beta", &value));
  }

  check(
      "remove same key twice",
      !htRemove(&table, "beta"));

  // Other entries must remain intact.
  {
    int alpha = 0;
    int gamma = 0;

    check(
        "remove does not damage other entries",
        htGet(&table, "alpha", &alpha) &&
            htGet(&table, "gamma", &gamma) &&
            alpha == 99 &&
            gamma == 3);
  }

  // ------------------------------------------------------------
  // Collision-heavy table
  //
  // Use one bucket and a very high load factor so every entry
  // necessarily lands in the same chain without resizing.
  // ------------------------------------------------------------
  {
    HashTable collisions{};

    bool init = htInit(&collisions, 1, 100.0);

    bool a = htPut(&collisions, "one", 1);
    bool b = htPut(&collisions, "two", 2);
    bool c = htPut(&collisions, "three", 3);
    bool d = htPut(&collisions, "four", 4);

    check(
        "separate chaining collisions",
        init &&
            a && b && c && d &&
            collisions.size == 4);

    int one = 0, two = 0, three = 0, four = 0;

    check(
        "lookup through collision chain",
        htGet(&collisions, "one", &one) &&
            htGet(&collisions, "two", &two) &&
            htGet(&collisions, "three", &three) &&
            htGet(&collisions, "four", &four) &&
            one == 1 &&
            two == 2 &&
            three == 3 &&
            four == 4);

    {
      size_t longest = 0;
      size_t empty = 0;

      size_t nonEmpty =
          htBucketStats(&collisions, &longest, &empty);

      check(
          "collision bucket statistics",
          nonEmpty == 1 &&
              longest == 4 &&
              empty == 0);
    }

    // All four nodes are in one linked list.
    // This exercises unlinking somewhere in that chain.
    check(
        "remove from collision chain",
        htRemove(&collisions, "two") &&
            !htContains(&collisions, "two") &&
            collisions.size == 3 &&
            htContains(&collisions, "one") &&
            htContains(&collisions, "three") &&
            htContains(&collisions, "four"));

    check(
        "remove more collision entries",
        htRemove(&collisions, "four") &&
            htRemove(&collisions, "one") &&
            htRemove(&collisions, "three") &&
            collisions.size == 0);

    {
      size_t longest = 999;
      size_t empty = 999;

      size_t nonEmpty =
          htBucketStats(&collisions, &longest, &empty);

      check(
          "empty bucket stats after removals",
          nonEmpty == 0 &&
              longest == 0 &&
              empty == collisions.bucketCount);
    }

    htClear(&collisions);

    check(
        "clear collision table",
        collisions.buckets == nullptr &&
            collisions.size == 0);
  }

  // ------------------------------------------------------------
  // Many inserts / repeated resizing
  // ------------------------------------------------------------
  {
    HashTable large{};

    bool init = htInit(&large, 2, 0.75);
    bool allInserted = init;

    const int count = 100;

    for (int i = 0; i < count; ++i) {
      string key = "key_" + to_string(i);

      if (!htPut(&large, key.c_str(), i * 10)) {
        allInserted = false;
        break;
      }
    }

    bool allFound = true;

    for (int i = 0; i < count; ++i) {
      string key = "key_" + to_string(i);
      int value = -1;

      if (!htGet(&large, key.c_str(), &value) ||
          value != i * 10) {
        allFound = false;
        break;
      }
    }

    check(
        "many inserts survive repeated resizing",
        allInserted &&
            allFound &&
            large.size == count &&
            large.bucketCount > 2);

    htClear(&large);
  }

  // ------------------------------------------------------------
  // Clear
  // ------------------------------------------------------------
  htClear(&table);

  check(
      "clear resets table",
      table.buckets == nullptr &&
          table.size == 0);

  // Ideally clear should also be safe when called again.
  htClear(&table);

  check(
      "clear is idempotent",
      table.buckets == nullptr &&
          table.size == 0);

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}