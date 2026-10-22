#include <bits/stdc++.h>
using namespace std;

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
  tree->root = nullptr;
  tree->size = 0;
}

void nodeInit(BSTNode *node, int v) {
  node->key = v;
  node->left = nullptr;
  node->right = nullptr;
}

void preOrderClear(BSTNode *root) {
  if (root == nullptr)
    return;
  BSTNode *left = root->left;
  BSTNode *right = root->right;
  free(root);
  preOrderClear(left);
  preOrderClear(right);
}

void bstClear(BSTree *tree) {
  preOrderClear(tree->root);
  tree->size = 0;
  tree->root = nullptr;
}

bool bstInsert(BSTree *tree, int v) {
  BSTNode *parent = tree->root;
  if (parent == nullptr) {
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    if (newNode == nullptr)
      return false;
    nodeInit(newNode, v);
    tree->root = newNode;
    tree->size++;
    return true;
  }
  while (true) {
    if (v == parent->key)
      return false;
    else if (v < parent->key) {
      if (parent->left != nullptr)
        parent = parent->left;
      else {
        BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
        if (newNode == nullptr)
          return false;
        nodeInit(newNode, v);
        parent->left = newNode;
        tree->size++;
        return true;
      }
    } else if (v > parent->key) {
      if (parent->right != nullptr)
        parent = parent->right;
      else {
        BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
        if (newNode == nullptr)
          return false;
        nodeInit(newNode, v);
        parent->right = newNode;
        tree->size++;
        return true;
      }
    }
  }
}

BSTNode *bstFind(BSTree *tree, int v) {
  BSTNode *curr = tree->root;
  while (true) {
    if (curr == nullptr)
      return nullptr;
    if (curr->key == v) {
      return curr;
    }
    if (v < curr->key)
      curr = curr->left;
    if (v > curr->key)
      curr = curr->right;
  }
}

bool bstContains(BSTree *tree, int v) {
  if (bstFind(tree, v) != nullptr) {
    return true;
  }
  return false;
}

BSTNode *bstMin(BSTree *tree) {
  if (tree->root == nullptr)
    return nullptr;
  BSTNode *curr = tree->root;
  while (curr->left != nullptr) {
    curr = curr->left;
  }

  return curr;
}

BSTNode *bstMax(BSTree *tree) {
  if (tree->root == nullptr)
    return nullptr;
  BSTNode *curr = tree->root;
  while (curr->right != nullptr) {
    curr = curr->right;
  }

  return curr;
}

int heightRecHelper(BSTNode *root) {
  if (root == NULL)
    return 0;
  return 1 + max(heightRecHelper(root->left), heightRecHelper(root->right));
}

int bstHeight(BSTree *tree) {
  BSTNode *root = tree->root;
  return heightRecHelper(root);
}

BSTNode *bstRemoveHelper(BSTNode *root, int v, bool &removed) {
  if (root == nullptr)
    return nullptr;

  if (v < root->key) {
    root->left = bstRemoveHelper(root->left, v, removed);
    return root;
  }

  if (v > root->key) {
    root->right = bstRemoveHelper(root->right, v, removed);
    return root;
  }

  // Found the node.
  removed = true;

  // Case 1: no left child
  if (root->left == nullptr) {
    BSTNode *right = root->right;
    free(root);
    return right;
  }

  // Case 2: no right child
  if (root->right == nullptr) {
    BSTNode *left = root->left;
    free(root);
    return left;
  }

  // Case 3: two children
  BSTNode *successor = root->right;

  while (successor->left != nullptr)
    successor = successor->left;

  root->key = successor->key;

  bool ignored = false;
  root->right = bstRemoveHelper(root->right, successor->key, ignored);

  return root;
}

bool bstRemove(BSTree *tree, int v) {
  bool removed = false;
  tree->root = bstRemoveHelper(tree->root, v, removed);

  if (removed)
    tree->size--;

  return removed;
}
