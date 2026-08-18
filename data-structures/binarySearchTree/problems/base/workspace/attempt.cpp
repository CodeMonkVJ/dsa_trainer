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
void bstClear(BSTree *) {}
bool bstInsert(BSTree *, int) { return false; }
BSTNode *bstFind(BSTree *, int) { return nullptr; }
bool bstContains(BSTree *, int) { return false; }
BSTNode *bstMin(BSTree *) { return nullptr; }
BSTNode *bstMax(BSTree *) { return nullptr; }
int bstHeight(BSTree *) { return 0; }
bool bstRemove(BSTree *, int) { return false; }
