// Trie for lowercase English words.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  bool isWord;
} TrieNode;

static TrieNode *trieNewNode(void) {
  TrieNode *node = (TrieNode *)calloc(1, sizeof(TrieNode));
  return node;
}

bool trieInsert(TrieNode *root, const char *word) {
  TrieNode *node = root;
  for (size_t i = 0; word[i] != '\0'; ++i) {
    if (word[i] < 'a' || word[i] > 'z') return false;
    size_t index = (size_t)(word[i] - 'a');
    if (node->children[index] == NULL) {
      node->children[index] = trieNewNode();
      if (node->children[index] == NULL) return false;
    }
    node = node->children[index];
  }
  node->isWord = true;
  return true;
}

bool trieContains(const TrieNode *root, const char *word) {
  const TrieNode *node = root;
  for (size_t i = 0; word[i] != '\0'; ++i) {
    if (word[i] < 'a' || word[i] > 'z') return false;
    node = node->children[word[i] - 'a'];
    if (node == NULL) return false;
  }
  return node->isWord;
}

bool trieStartsWith(const TrieNode *root, const char *prefix) {
  const TrieNode *node = root;
  for (size_t i = 0; prefix[i] != '\0'; ++i) {
    if (prefix[i] < 'a' || prefix[i] > 'z') return false;
    node = node->children[prefix[i] - 'a'];
    if (node == NULL) return false;
  }
  return true;
}

void trieFree(TrieNode *node) {
  if (node == NULL) return;
  for (int i = 0; i < ALPHABET_SIZE; ++i) trieFree(node->children[i]);
  free(node);
}

int main(void) {
  TrieNode *root = trieNewNode();
  if (root == NULL) return 1;
  trieInsert(root, "cat");
  trieInsert(root, "car");
  printf("Contains cat: %s\n", trieContains(root, "cat") ? "yes" : "no");
  printf("Starts with ca: %s\n", trieStartsWith(root, "ca") ? "yes" : "no");
  trieFree(root);
  return 0;
}

