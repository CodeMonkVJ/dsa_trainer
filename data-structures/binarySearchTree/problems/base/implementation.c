// Binary Search Tree implementation in C

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct BSTNode {
  int key;
  struct BSTNode *left;
  struct BSTNode *right;
} BSTNode;

typedef struct {
  BSTNode *root;
  size_t size;
} BSTree;

void bstInit(BSTree *tree) {
  tree->root = NULL;
  tree->size = 0;
}

static void bstFreeNodes(BSTNode *node) {
  if (node == NULL) return;
  if (node->left != NULL) bstFreeNodes(node->left);
  if (node->right != NULL) bstFreeNodes(node->right);
  free(node);
}

void bstClear(BSTree *tree) {
  if (tree->root != NULL) {
    bstFreeNodes(tree->root);
    tree->root = NULL;
  }
  tree->size = 0;
}

static BSTNode* bstCreateNode(int key) {
  BSTNode *ptr = (BSTNode *)malloc(sizeof(BSTNode));
  if (ptr == NULL) return NULL;
  ptr->key = key;
  ptr->left = NULL;
  ptr->right = NULL;
  return ptr;
}

bool bstInsert(BSTree *tree, int key) {
  BSTNode *curr = tree->root;
  BSTNode *parent = NULL;

  while (curr != NULL) {
    parent = curr;
    if (key < curr->key) {
      curr = curr->left;
    } else if (key > curr->key) {
      curr = curr->right;
    } else {
      return false;
    }
  }

  BSTNode *newNode = bstCreateNode(key);
  if (newNode == NULL) return false;

  if (parent == NULL) {
    tree->root = newNode;
  } else if (key < parent->key) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  tree->size++;
  return true;
}

static BSTNode* bstFindRec(BSTNode *node, int key) {
  if (node == NULL) return NULL;

  if (node->key == key) return node;
  else if (key < node->key) return bstFindRec(node->left, key);
  else return bstFindRec(node->right, key);
}

BSTNode* bstFind(BSTree *tree, int key) {
  BSTNode *curr = tree->root;
  return bstFindRec(curr, key);
}

bool bstContains(BSTree *tree, int key) {
  return bstFind(tree, key) != NULL;
}

BSTNode* bstMin(BSTree *tree) {
  BSTNode *curr = tree->root;
  BSTNode *parent = NULL;
  while (curr != NULL) {
    parent = curr;
    curr = curr->left;
  }
  return parent;
}

BSTNode* bstMax(BSTree *tree) {
  BSTNode *curr = tree->root;
  BSTNode *parent = NULL;
  while (curr != NULL) {
    parent = curr;
    curr = curr->right;
  }
  return parent;
}

int bstHeightRec(BSTNode *node, int height) {
  int left = height, right = height;
  if (node->left != NULL) {
    left = bstHeightRec(node->left, height+1);
  } else if (node->right != NULL) {
    right = bstHeightRec(node->right, height+1);
  } else return height;

  if (right >= height) {
    if (left >= right) {
      return left;
    } return right;
  } else {
    if (left >= height) {
      return left;
    } else return height;
  }
}

int bstHeight(BSTree *tree) {
  if (tree->root == NULL) return 0; // empty tree height is zero
  return bstHeightRec(tree->root, 1);
}

static BSTNode* bstRemoveNodeRec(BSTNode *node, int key, bool *removed) {
  if (node == NULL) return NULL;

  if (key < node->key) {
    node->left = bstRemoveNodeRec(node->left, key, removed);
  } else if (key > node->key) {
    node->right = bstRemoveNodeRec(node->right, key, removed);
  } else {
    *removed = true;
    if (node->left == NULL) {
      BSTNode *right = node->right;
      free(node);
      return right;
    } else if (node->right == NULL) {
      BSTNode *left = node->left;
      free(node);
      return left;
    } else {
      BSTNode *succ = node->right;
      while (succ->left != NULL) succ = succ->left;
      node->key = succ->key;
      bool dummy = false;
      node->right = bstRemoveNodeRec(node->right, succ->key, &dummy);
    }
  }

  return node;
}

bool bstRemove(BSTree *tree, int key) {
  bool removed = false;
  tree->root = bstRemoveNodeRec(tree->root, key, &removed);
  if (removed) {
    tree->size--;
  }
  return removed;
}


// helpers and test code

static void bstPrintInOrderNode(const BSTNode *node) {
  if (node == NULL) return;
  bstPrintInOrderNode(node->left);
  printf("%d ", node->key);
  bstPrintInOrderNode(node->right);
}

static void bstPrintStructure(const BSTNode *node, int depth) {
  if (node == NULL) {
    printf("%*s-\n", depth * 2, "");
    return;
  }
  bstPrintStructure(node->right, depth + 1);
  printf("%*s%d\n", depth * 2, "", node->key);
  bstPrintStructure(node->left, depth + 1);
}

static void bstPrint(const BSTree *tree) {
  printf("Current BST (sideways, right child up):\n");
  bstPrintStructure(tree->root, 0);
  printf("In-order traversal: ");
  bstPrintInOrderNode(tree->root);
  printf("\n\n");
}

int main(void) {
  BSTree tree;
  bstInit(&tree);

  int values[] = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };
  size_t valueCount = sizeof values / sizeof values[0];
  printf("Inserting values:");
  for (size_t i = 0; i < valueCount; ++i) {
    printf(" %d", values[i]);
    bstInsert(&tree, values[i]);
  }
  printf("\n");
  bstPrint(&tree);

  int lookupKeys[] = { 4, 2 };
  for (size_t i = 0; i < sizeof lookupKeys / sizeof lookupKeys[0]; ++i) {
    printf("Contains %d? %s\n", lookupKeys[i], bstContains(&tree, lookupKeys[i]) ? "yes" : "no");
  }

  BSTNode *minNode = bstMin(&tree);
  BSTNode *maxNode = bstMax(&tree);
  if (minNode != NULL && maxNode != NULL) {
    printf("Min key: %d, Max key: %d\n", minNode->key, maxNode->key);
  }

  printf("Current tree height: %d\n\n", bstHeight(&tree));

  int removals[] = { 1, 14, 8 };
  for (size_t i = 0; i < sizeof removals / sizeof removals[0]; ++i) {
    printf("Removing %d: %s\n", removals[i], bstRemove(&tree, removals[i]) ? "removed" : "not found");
    bstPrint(&tree);
  }

  BSTNode *found = bstFind(&tree, 6);
  printf("bstFind(6) => %s\n\n", found ? "found node" : "not found");

  printf("Clearing tree...\n");
  bstClear(&tree);
  bstPrint(&tree);

  return 0;
}

