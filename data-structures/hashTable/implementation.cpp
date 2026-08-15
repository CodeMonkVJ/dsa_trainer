/**
 * Separate-chaining hash table for string keys and integer values.
 *
 * A hash table first turns a key such as "beta" into a number (the hash),
 * then maps that number to one bucket with `% bucketCount`. Different keys
 * can land in the same bucket; that is a collision. We handle collisions by
 * keeping a linked list (a "chain") in every bucket:
 *
 *   buckets[3] -> ["cat", 4] -> ["dog", 7] -> null
 *
 * Lookup, insertion, and removal are expected O(1). A single operation is
 * O(length of one chain), so keeping chains short with resizing matters.
 */

#include <bits/stdc++.h>
using namespace std;

typedef struct Entry {
  char *key;           // This table owns a heap-allocated copy of the key.
  int value;
  struct Entry *next;  // Next entry that collided into the same bucket.
} Entry;

typedef struct {
  // An array of linked-list heads. `buckets[i]` is null when bucket i is empty.
  Entry **buckets;
  size_t bucketCount;    // Number of available buckets, not number of entries.
  size_t size;           // Total key/value pairs across every bucket.
  double maxLoadFactor;  // Resize before `size / bucketCount` exceeds this.
} HashTable;

bool htInit(HashTable *ht, size_t bucketCount, double maxLoadFactor) {
  // Defaults keep callers from creating a zero-sized table by accident.
  if (bucketCount == 0) bucketCount = 8;
  if (maxLoadFactor <= 0.0) maxLoadFactor = 0.75;

  // calloc makes every bucket head start as NULL.
  ht->buckets = (Entry **)calloc(bucketCount, sizeof(Entry *));
  if (ht->buckets == NULL) return false;

  ht->bucketCount = bucketCount;
  ht->maxLoadFactor = maxLoadFactor;
  ht->size = 0;
  return true;
}

static void htFreeEntryList(Entry *node) {
  // Free one collision chain. Save `next` before freeing the current node,
  // because the current node cannot be accessed after free().
  while (node != NULL) {
    Entry *next = node->next;
    free(node->key);
    free(node);
    node = next;
  }
}

void htClear(HashTable *ht) {
  if (ht->buckets == NULL) return;

  // Each bucket owns the head of a separate collision chain.
  for (size_t i = 0; i < ht->bucketCount; ++i) {
    htFreeEntryList(ht->buckets[i]);
    ht->buckets[i] = NULL;
  }

  // Once every chain is gone, free the array that held their heads.
  free(ht->buckets);
  ht->buckets = NULL;
  ht->bucketCount = 0;
  ht->size = 0;
  ht->maxLoadFactor = 0.0;
}

static size_t htHash(const char *key) {
    // djb2-style hash: mix every character into a running value. We do not
    // need the exact hash to be small; `% bucketCount` handles that later.
    size_t hash = 5381;                // djb2 seed
    unsigned char c;

    while ((c = (unsigned char)*key++) != 0) {
        hash = ((hash << 5) + hash) ^ c;   // hash * 33 ^ c
    }

    return hash;
}

static size_t htBucketIndex(const HashTable *ht, const char *key) {
  // Valid indexes are 0 through bucketCount - 1.
  return htHash(key) % ht->bucketCount;
}

static char *htDupKey(const char *key) {
  // Do not store the caller's pointer directly: the caller could later
  // change or destroy that string. The table owns this duplicate instead.
  size_t len = strlen(key) + 1;
  char *copy = (char *)malloc(len);
  if (copy != NULL) {
    memcpy(copy, key, len);
  }
  return copy;
}

static Entry* htFindNode(HashTable *ht, const char *key, size_t bucketIdx, Entry ***prevNextPtr) {
  // `link` points to the pointer that leads to `node`:
  //   - initially it is &buckets[bucketIdx]
  //   - later it is &previousNode->next
  // This is useful for removal: changing *link can bypass the found node,
  // without needing a special case for the first node in the chain.
  Entry **link = &ht->buckets[bucketIdx];
  Entry *node = *link;

  // Search only this bucket's chain, not every entry in the table.
  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      if (prevNextPtr != NULL) {
        *prevNextPtr = link;
      }
      return node;
    }
    link = &node->next;  // The next pointer is what leads to the next node.
    node = node->next;
  }

  if (prevNextPtr != NULL) {
    // If not found, expose where a new node would be attached (the null tail).
    *prevNextPtr = link;
  }
  return NULL;
}

static bool htResize(HashTable *ht, size_t newBucketCount) {
  // Resizing needs a new bucket array. Existing Entry nodes are reused;
  // only their `next` links are rearranged.
  Entry **newBuckets = (Entry **)calloc(newBucketCount, sizeof(Entry *));
  if (newBuckets == NULL) return false;

  for (size_t i = 0; i < ht->bucketCount; ++i) {
    Entry *node = ht->buckets[i];
    while (node != NULL) {
      // Save this before overwriting node->next below.
      Entry *next = node->next;

      // Bucket indexes depend on bucket count, so every existing key must be
      // rehashed for the new array. This is called rehashing.
      size_t idx = htHash(node->key) % newBucketCount;

      // Insert at the front of its new collision chain (O(1)).
      node->next = newBuckets[idx];
      newBuckets[idx] = node;
      node = next;
    }
  }

  // Entries have moved into newBuckets, so only the old array of head
  // pointers is freed here.
  free(ht->buckets);
  ht->buckets = newBuckets;
  ht->bucketCount = newBucketCount;
  return true;
}

bool htContains(HashTable *ht, const char *key) {
  if (ht->bucketCount == 0) return false;
  // Contains and get both start by choosing exactly one bucket.
  size_t idx = htBucketIndex(ht, key);
  return htFindNode(ht, key, idx, NULL) != NULL;
}

bool htGet(HashTable *ht, const char *key, int *outValue) {
  if (ht->bucketCount == 0) return false;
  size_t idx = htBucketIndex(ht, key);
  Entry *node = htFindNode(ht, key, idx, NULL);
  if (node == NULL) return false;
  // `outValue` is optional, so callers can use get purely as an existence check.
  if (outValue != NULL) *outValue = node->value;
  return true;
}

bool htPut(HashTable *ht, const char *key, int value) {
  if (ht->bucketCount == 0) return false;
  size_t idx = htBucketIndex(ht, key);
  Entry *node = htFindNode(ht, key, idx, NULL);
  if (node != NULL) {
    // Hash tables generally have one value per key: inserting the same key
    // updates its existing value rather than adding a duplicate Entry.
    node->value = value;
    return true;
  }

  // Check the *future* load factor because this call will add one new entry.
  // For example, 6 entries / 8 buckets = 0.75.
  double projected = (double)(ht->size + 1) / (double)ht->bucketCount;
  if (projected > ht->maxLoadFactor) {
    if (!htResize(ht, ht->bucketCount * 2)) {
      // Keep the existing table usable if allocation fails. The insertion can
      // still succeed, but chains may grow longer than the desired limit.
    } else {
      idx = htBucketIndex(ht, key);
    }
  }

  // Make the new Entry and its independent key copy before changing a bucket.
  Entry *newNode = (Entry *)malloc(sizeof(Entry));
  if (newNode == NULL) return false;
  char *dup = htDupKey(key);
  if (dup == NULL) {
    free(newNode);
    return false;
  }

  newNode->key = dup;
  newNode->value = value;
  // Add at the front of the selected collision chain. No traversal is needed
  // because we already confirmed this key is not present.
  newNode->next = ht->buckets[idx];
  ht->buckets[idx] = newNode;
  ht->size++;

  return true;
}

bool htRemove(HashTable *ht, const char *key) {
  if (ht->bucketCount == 0) return false;
  size_t idx = htBucketIndex(ht, key);
  Entry **link = NULL;  // Will receive the pointer that currently points at node.
  Entry *node = htFindNode(ht, key, idx, &link);
  if (node == NULL) return false;

  // Bypass `node`. This works for both cases:
  //   *link is buckets[idx]       when node is first in the chain
  //   *link is previous->next     when node is later in the chain
  if (link != NULL) *link = node->next;

  // The table owns both allocations made in htPut.
  free(node->key);
  free(node);
  ht->size--;
  return true;
}

void htForEach(const HashTable *ht, void (*visit)(const char *key, int value, void *ctx), void *ctx) {
  if (ht->bucketCount == 0 || visit == NULL) return;
  // Walk every chain. Order is bucket-dependent and is not insertion order.
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
  // Average number of entries per bucket; it is not the longest chain length.
  return (double)ht->size / (double)ht->bucketCount;
}

size_t htBucketStats(const HashTable *ht, size_t *longest, size_t *emptyCount) {
  size_t maxLen = 0;
  size_t empties = 0;
  size_t nonEmpty = 0;

  for (size_t i = 0; i < ht->bucketCount; ++i) {
    size_t len = 0;
    // Count this bucket's collision chain.
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
