#include <bits/stdc++.h>
using namespace std;
typedef struct Entry {
  char *key;
  int value;
  struct Entry *next;
} Entry;
typedef struct {
  Entry **buckets;
  size_t bucketCount;
  size_t size;
  double maxLoadFactor;
} HashTable;
bool htInit(HashTable *, size_t, double) { return false; }
void htClear(HashTable *) {}
bool htContains(HashTable *, const char *) { return false; }
bool htGet(HashTable *, const char *, int *) { return false; }
bool htPut(HashTable *, const char *, int) { return false; }
bool htRemove(HashTable *, const char *) { return false; }
void htForEach(const HashTable *, void (*)(const char *, int, void *), void *) {
}
double htLoadFactor(const HashTable *) { return 0; }
size_t htBucketStats(const HashTable *, size_t *, size_t *) { return 0; }
