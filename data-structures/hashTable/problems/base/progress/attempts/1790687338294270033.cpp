#include <bits/stdc++.h>
using namespace std;

#define MIN_LF 0.25

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
  if (table == nullptr || bucketCount == 0)
    return false;
  table->buckets = (Entry **)calloc(bucketCount, sizeof(Entry *));
  if (table->buckets == nullptr)
    return false;
  table->bucketCount = bucketCount;
  table->maxLoadFactor = maxLoadFactor;
  table->size = 0;
  return true;
}

void htClear(HashTable *table) {
  free(table->buckets);
  table->buckets = nullptr;
  table->size = 0;
  table->bucketCount = 0;
}

size_t hashKey(const char *key) {
  size_t hash = 0;

  while (*key != '\0') {
    hash = hash * 31 + static_cast<unsigned char>(*key);
    ++key;
  }

  return hash;
}

bool htContains(HashTable *table, const char *key) {
  if (table == nullptr || key == nullptr || table->bucketCount == 0)
    return false;

  size_t index = hashKey(key) % table->bucketCount;
  Entry *curr = table->buckets[index];

  while (curr != nullptr) {
    if (strcmp(curr->key, key) == 0)
      return true;
    curr = curr->next;
  }

  return false;
}

bool htGet(HashTable *table, const char *key, int *outValue) {
  if (table == nullptr || key == nullptr || table->bucketCount == 0 ||
      outValue == nullptr)
    return false;

  size_t index = hashKey(key) % table->bucketCount;
  Entry *curr = table->buckets[index];

  while (curr != nullptr) {
    if (strcmp(curr->key, key) == 0) {
      *outValue = curr->value;
      return true;
    }
    curr = curr->next;
  }

  return false;
}

bool htResize(HashTable *table, size_t newBucketCount) {
  Entry **newBuckets = (Entry **)calloc(newBucketCount, sizeof(Entry *));
  if (newBuckets == nullptr)
    return false;

  for (size_t i = 0; i < table->bucketCount; i++) {
    Entry *curr = table->buckets[i];
    while (curr != nullptr) {
      Entry *next = curr->next;
      size_t newIndex = hashKey(curr->key) % newBucketCount;
      curr->next = newBuckets[newIndex];
      newBuckets[newIndex] = curr;

      curr = next;
    }
  }

  free(table->buckets);
  table->buckets = newBuckets;
  table->bucketCount = newBucketCount;

  return true;
}

bool htPut(HashTable *table, const char *key, int value) {
  if (table == nullptr || key == nullptr || table->bucketCount == 0)
    return false;

  size_t index = hashKey(key) % table->bucketCount;

  Entry *curr = table->buckets[index];

  while (curr != nullptr) {
    if (strcmp(curr->key, key) == 0) {
      curr->value = value;
      return true;
    }
    curr = curr->next;
  }

  double newLoad = static_cast<double>(table->size + 1) / table->bucketCount;

  if (newLoad > table->maxLoadFactor) {
    if (!htResize(table, table->bucketCount * 2))
      return false;

    index = hashKey(key) % table->bucketCount;
  }

  char *keyCopy = (char *)malloc(strlen(key) + 1);
  strcpy(keyCopy, key);

  Entry *entry = (Entry *)malloc(sizeof(Entry));

  entry->key = keyCopy;
  entry->value = value;
  entry->next = table->buckets[index];

  table->buckets[index] = entry;
  table->size++;

  return true;
}

bool htRemove(HashTable *table, const char *key) {
  if (table == nullptr || key == nullptr || table->bucketCount == 0)
    return false;

  size_t index = hashKey(key) % table->bucketCount;

  Entry *curr = table->buckets[index];
  Entry *prev = nullptr;

  while (curr != nullptr) {
    if (strcmp(curr->key, key) == 0) {
      if (prev == nullptr)
        table->buckets[index] = curr->next;
      else
        prev->next = curr->next;

      free(curr->key);
      free(curr);
      table->size--;

      return true;
    }

    prev = curr;
    curr = curr->next;
  }

  return false;
}

void htForEach(const HashTable *table,
               void (*callback)(const char *, int, void *), void *userData) {
  if (table == nullptr || callback == nullptr)
    return;

  for (size_t i = 0; i < table->bucketCount; i++) {
    Entry *curr = table->buckets[i];

    while (curr != nullptr) {
      callback(curr->key, curr->value, userData);
      curr = curr->next;
    }
  }
}

double htLoadFactor(const HashTable *table) {
  if (table == nullptr || table->bucketCount == 0)
    return 0.0;

  return static_cast<double>(table->size) /
         static_cast<double>(table->bucketCount);
}

size_t htBucketStats(const HashTable *table, size_t *maxChainLength,
                     size_t *emptyBuckets) {
  int longest = 0;
  int nonEmptyBuckets = 0;

  if (table == nullptr)
    return 0;

  for (size_t i = 0; i < table->bucketCount; i++) {
    Entry *curr = table->buckets[i];

    if (curr == nullptr)
      continue;

    nonEmptyBuckets++;

    int chainLength = 0;

    while (curr != nullptr) {
      chainLength++;
      curr = curr->next;
    }

    longest = max(longest, chainLength);
  }

  if (emptyBuckets != nullptr)
    *emptyBuckets = table->bucketCount - nonEmptyBuckets;

  if (maxChainLength != nullptr)
    *maxChainLength = longest;

  return nonEmptyBuckets;
}
