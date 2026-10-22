#include <bits/stdc++.h>
using namespace std;

struct Entry {
  char *key;
  int value;
  Entry *next;
};

struct HashTable {
  Entry **buckets;
  size_t bucketCount;
  size_t size;
  double maxLoadFactor;
};

bool htInit(HashTable *table, size_t bucketCount, double maxLoadFactor) {
  return false;
}

void htClear(HashTable *table) {}

bool htContains(HashTable *table, const char *key) {
  return false;
}

bool htGet(HashTable *table, const char *key, int *outValue) {
  return false;
}

bool htPut(HashTable *table, const char *key, int value) {
  return false;
}

bool htRemove(HashTable *table, const char *key) {
  return false;
}

void htForEach(const HashTable *table,
               void (*callback)(const char *, int, void *),
               void *userData) {}

double htLoadFactor(const HashTable *table) {
  return 0;
}

size_t htBucketStats(const HashTable *table,
                     size_t *nonEmptyBuckets,
                     size_t *maxChainLength) {
  return 0;
}