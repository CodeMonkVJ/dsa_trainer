#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(const char *name, const string &input, const string &expected,
           const string &actual, bool ok) {
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":" << input << ",\"expected\":" << expected
       << ",\"actual\":" << actual << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

string jsonBool(bool value) { return value ? "true" : "false"; }

int main() {

  HashTable table{};
  const bool initialized = htInit(&table, 2, 0.75);
  check("initialize table", "{\"bucket_count\":2,\"max_load_factor\":0.75}",
        "{\"initialized\":true,\"bucket_count\":2,\"size\":0}",
        string("{\"initialized\":") + jsonBool(initialized) +
            ",\"bucket_count\":" + to_string(table.bucketCount) +
            ",\"size\":" + to_string(table.size) + "}",
        initialized);

  const bool alphaInserted = htPut(&table, "alpha", 1);
  const bool betaInserted = htPut(&table, "beta", 2);
  const bool gammaInserted = htPut(&table, "gamma", 3);
  check("insert and resize",
        "{\"operations\":[[\"put\",\"alpha\",1],[\"put\",\"beta\",2],[\"put\","
        "\"gamma\",3]]}",
        "{\"inserted\":[true,true,true],\"size\":3,\"bucket_count\":4}",
        string("{\"inserted\":[") + jsonBool(alphaInserted) + "," +
            jsonBool(betaInserted) + "," + jsonBool(gammaInserted) +
            "],\"size\":" + to_string(table.size) +
            ",\"bucket_count\":" + to_string(table.bucketCount) + "}",
        alphaInserted && betaInserted && gammaInserted);

  int value = 0;
  const bool foundBeta = htGet(&table, "beta", &value);
  check("lookup value", "{\"operation\":[\"get\",\"beta\"]}",
        "{\"found\":true,\"value\":2}",
        string("{\"found\":") + jsonBool(foundBeta) +
            ",\"value\":" + to_string(value) + "}",
        foundBeta && value == 2);

  const bool updatedBeta = htPut(&table, "beta", 20);
  const bool foundUpdatedBeta = htGet(&table, "beta", &value);
  check("update existing key",
        "{\"operations\":[[\"put\",\"beta\",20],[\"get\",\"beta\"]]}",
        "{\"updated\":true,\"found\":true,\"value\":20}",
        string("{\"updated\":") + jsonBool(updatedBeta) + ",\"found\":" +
            jsonBool(foundUpdatedBeta) + ",\"value\":" + to_string(value) + "}",
        updatedBeta && foundUpdatedBeta && value == 20);

  const bool hasAlpha = htContains(&table, "alpha");
  const bool hasMissing = htContains(&table, "missing");
  check(
      "contains",
      "{\"operations\":[[\"contains\",\"alpha\"],[\"contains\",\"missing\"]]}",
      "{\"contains\":[true,false]}",
      string("{\"contains\":[") + jsonBool(hasAlpha) + "," +
          jsonBool(hasMissing) + "]}",
      hasAlpha && !hasMissing);

  const bool removedAlpha = htRemove(&table, "alpha");
  const bool alphaAfterRemove = htContains(&table, "alpha");
  const bool removedAlphaAgain = htRemove(&table, "alpha");
  check("remove",
        "{\"operations\":[[\"remove\",\"alpha\"],[\"contains\",\"alpha\"],["
        "\"remove\",\"alpha\"]]}",
        "{\"removed\":true,\"contains_after\":false,\"removed_again\":false}",
        string("{\"removed\":") + jsonBool(removedAlpha) +
            ",\"contains_after\":" + jsonBool(alphaAfterRemove) +
            ",\"removed_again\":" + jsonBool(removedAlphaAgain) + "}",
        removedAlpha && !alphaAfterRemove && !removedAlphaAgain);

  size_t longest = 0;
  size_t empty = 0;
  const size_t nonEmpty = htBucketStats(&table, &longest, &empty);
  const double loadFactor = htLoadFactor(&table);
  check("bucket statistics", "{\"operation\":\"bucket_stats\"}",
        "{\"non_empty\":2,\"longest\":1,\"empty\":2,\"load_factor\":0.5}",
        string("{\"non_empty\":") + to_string(nonEmpty) + ",\"longest\":" +
            to_string(longest) + ",\"empty\":" + to_string(empty) +
            ",\"load_factor\":" + to_string(loadFactor) + "}",
        nonEmpty > 0 && loadFactor > 0);

  htClear(&table);
  const bool cleared = table.buckets == nullptr && table.size == 0;
  check("clear and ownership", "{\"operation\":\"clear\"}",
        "{\"buckets\":null,\"size\":0}",
        string("{\"buckets\":") +
            (table.buckets == nullptr ? "null" : "present") +
            ",\"size\":" + to_string(table.size) + "}",
        cleared);

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
