// Hash Table implementation in C

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

bool htInit(HashTable *ht, size_t bucketCount, double maxLoadFactor) {
  if (bucketCount == 0) bucketCount = 8;
  if (maxLoadFactor <= 0.0) maxLoadFactor = 0.75;

  ht->buckets = calloc(bucketCount, sizeof(Entry *));
  if (ht->buckets == NULL) return false;

  ht->bucketCount = bucketCount;
  ht->maxLoadFactor = maxLoadFactor;
  ht->size = 0;
  return true;
}

static void htFreeEntryList(Entry *node) {
  while (node != NULL) {
    Entry *next = node->next;
    free(node->key);
    free(node);
    node = next;
  }
}

void htClear(HashTable *ht) {
  if (ht->buckets == NULL) return;

  for (size_t i = 0; i < ht->bucketCount; ++i) {
    htFreeEntryList(ht->buckets[i]);
    ht->buckets[i] = NULL;
  }

  free(ht->buckets);
  ht->buckets = NULL;
  ht->bucketCount = 0;
  ht->size = 0;
  ht->maxLoadFactor = 0.0;
}

static size_t htHash(const char *key) {
    size_t hash = 5381;                // djb2 seed
    unsigned char c;

    while ((c = (unsigned char)*key++) != 0) {
        hash = ((hash << 5) + hash) ^ c;   // hash * 33 ^ c
    }

    return hash;
}

static size_t htBucketIndex(const HashTable *ht, const char *key) {
  return htHash(key) % ht->bucketCount;
}

static char *htDupKey(const char *key) {
  size_t len = strlen(key) + 1;
  char *copy = (char *)malloc(len);
  if (copy != NULL) {
    memcpy(copy, key, len);
  }
  return copy;
}

static Entry* htFindNode(HashTable *ht, const char *key, size_t bucketIdx, Entry ***prevNextPtr) {
  Entry **link = &ht->buckets[bucketIdx];
  Entry *node = *link;

  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      if (prevNextPtr != NULL) {
        *prevNextPtr = link;
      }
      return node;
    }
    link = &node->next;
    node = node->next;
  }

  if (prevNextPtr != NULL) {
    *prevNextPtr = link;
  }
  return NULL;
}

static bool htResize(HashTable *ht, size_t newBucketCount) {
  Entry **newBuckets = calloc(newBucketCount, sizeof(Entry *));
  if (newBuckets == NULL) return false;

  for (size_t i = 0; i < ht->bucketCount; ++i) {
    Entry *node = ht->buckets[i];
    while (node != NULL) {
      Entry *next = node->next;
      size_t idx = htHash(node->key) % newBucketCount;
      node->next = newBuckets[idx];
      newBuckets[idx] = node;
      node = next;
    }
  }

  free(ht->buckets);
  ht->buckets = newBuckets;
  ht->bucketCount = newBucketCount;
  return true;
}

bool htContains(HashTable *ht, const char *key) {
  if (ht->bucketCount == 0) return false;
  size_t idx = htBucketIndex(ht, key);
  return htFindNode(ht, key, idx, NULL) != NULL;
}

bool htGet(HashTable *ht, const char *key, int *outValue) {
  if (ht->bucketCount == 0) return false;
  size_t idx = htBucketIndex(ht, key);
  Entry *node = htFindNode(ht, key, idx, NULL);
  if (node == NULL) return false;
  if (outValue != NULL) *outValue = node->value;
  return true;
}

bool htPut(HashTable *ht, const char *key, int value) {
  if (ht->bucketCount == 0) return false;
  size_t idx = htBucketIndex(ht, key);
  Entry *node = htFindNode(ht, key, idx, NULL);
  if (node != NULL) {
    node->value = value;
    return true;
  }

  double projected = (double)(ht->size + 1) / (double)ht->bucketCount;
  if (projected > ht->maxLoadFactor) {
    if (!htResize(ht, ht->bucketCount * 2)) {
      // resize failed; continue insert without resizing to preserve data
    } else {
      idx = htBucketIndex(ht, key);
    }
  }

  Entry *newNode = (Entry *)malloc(sizeof(Entry));
  if (newNode == NULL) return false;
  char *dup = htDupKey(key);
  if (dup == NULL) {
    free(newNode);
    return false;
  }

  newNode->key = dup;
  newNode->value = value;
  newNode->next = ht->buckets[idx];
  ht->buckets[idx] = newNode;
  ht->size++;

  return true;
}

bool htRemove(HashTable *ht, const char *key) {
  if (ht->bucketCount == 0) return false;
  size_t idx = htBucketIndex(ht, key);
  Entry **link = NULL;
  Entry *node = htFindNode(ht, key, idx, &link);
  if (node == NULL) return false;

  if (link != NULL) {
    *link = node->next;
  }
  free(node->key);
  free(node);
  ht->size--;
  return true;
}

void htForEach(const HashTable *ht, void (*visit)(const char *key, int value, void *ctx), void *ctx) {
  if (ht->bucketCount == 0 || visit == NULL) return;
  for (size_t i = 0; i < ht->bucketCount; ++i) {
    Entry *node = ht->buckets[i];
    while (node != NULL) {
      visit(node->key, node->value, ctx);
      node = node->next;
    }
  }
}

double htLoadFactor(const HashTable *ht) {
  if (ht->bucketCount == 0) return 0.0;
  return (double)ht->size / (double)ht->bucketCount;
}

size_t htBucketStats(const HashTable *ht, size_t *longest, size_t *emptyCount) {
  size_t maxLen = 0;
  size_t empties = 0;
  size_t nonEmpty = 0;

  for (size_t i = 0; i < ht->bucketCount; ++i) {
    size_t len = 0;
    for (Entry *node = ht->buckets[i]; node != NULL; node = node->next) {
      ++len;
    }
    if (len == 0) {
      ++empties;
    } else {
      ++nonEmpty;
      if (len > maxLen) maxLen = len;
    }
  }

  if (longest != NULL) *longest = maxLen;
  if (emptyCount != NULL) *emptyCount = empties;
  return nonEmpty;
}

static void printKV(const char *key, int value, void *ctx) {
  (void)ctx;
  printf("%s => %d\n", key, value);
}

int main(void) {
  HashTable ht;
  if (!htInit(&ht, 8, 0.75)) {
    fprintf(stderr, "Failed to init hash table\n");
    return 1;
  }

  htPut(&ht, "alpha", 1);
  htPut(&ht, "beta", 2);
  htPut(&ht, "gamma", 3);
  htPut(&ht, "delta", 4);
  htPut(&ht, "epsilon", 5);

  int value = 0;
  if (htGet(&ht, "beta", &value)) {
    printf("beta -> %d\n", value);
  }

  printf("Contains 'omega'? %s\n", htContains(&ht, "omega") ? "yes" : "no");
  printf("Contains 'gamma'? %s\n", htContains(&ht, "gamma") ? "yes" : "no");

  htRemove(&ht, "alpha");
  htRemove(&ht, "gamma");

  printf("\nAll entries:\n");
  htForEach(&ht, printKV, NULL);

  size_t longest = 0, emptyBuckets = 0;
  size_t nonEmpty = htBucketStats(&ht, &longest, &emptyBuckets);
  printf("\nBuckets: %zu total, %zu non-empty, %zu empty, longest chain %zu\n",
         ht.bucketCount, nonEmpty, emptyBuckets, longest);
  printf("Current load factor: %.2f\n", htLoadFactor(&ht));

  htClear(&ht);

  return 0;
}

