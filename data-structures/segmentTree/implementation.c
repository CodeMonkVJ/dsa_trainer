// Segment tree for range-sum queries and point updates.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *tree;
  int size;
} SegmentTree;

static void build(const int *values, int *tree, int node, int left, int right) {
  if (left == right) { tree[node] = values[left]; return; }
  int middle = left + (right - left) / 2;
  build(values, tree, node * 2, left, middle);
  build(values, tree, node * 2 + 1, middle + 1, right);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

bool segmentTreeInit(SegmentTree *segmentTree, const int *values, int size) {
  if (size <= 0) return false;
  segmentTree->tree = (int *)calloc((size_t)size * 4, sizeof(int));
  if (!segmentTree->tree) return false;
  segmentTree->size = size;
  build(values, segmentTree->tree, 1, 0, size - 1);
  return true;
}

static int query(const int *tree, int node, int left, int right, int ql, int qr) {
  if (qr < left || right < ql) return 0;
  if (ql <= left && right <= qr) return tree[node];
  int middle = left + (right - left) / 2;
  return query(tree, node * 2, left, middle, ql, qr) +
         query(tree, node * 2 + 1, middle + 1, right, ql, qr);
}

int segmentTreeQuery(const SegmentTree *segmentTree, int left, int right) {
  if (left < 0 || right >= segmentTree->size || left > right) return 0;
  return query(segmentTree->tree, 1, 0, segmentTree->size - 1, left, right);
}

static void update(int *tree, int node, int left, int right, int index, int value) {
  if (left == right) { tree[node] = value; return; }
  int middle = left + (right - left) / 2;
  if (index <= middle) update(tree, node * 2, left, middle, index, value);
  else update(tree, node * 2 + 1, middle + 1, right, index, value);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

bool segmentTreeUpdate(SegmentTree *segmentTree, int index, int value) {
  if (index < 0 || index >= segmentTree->size) return false;
  update(segmentTree->tree, 1, 0, segmentTree->size - 1, index, value);
  return true;
}

void segmentTreeFree(SegmentTree *segmentTree) {
  free(segmentTree->tree);
  segmentTree->tree = NULL;
  segmentTree->size = 0;
}

int main(void) {
  int values[] = {1, 3, 5, 7, 9, 11};
  SegmentTree tree;
  if (!segmentTreeInit(&tree, values, 6)) return 1;
  printf("Sum [1, 4]: %d\n", segmentTreeQuery(&tree, 1, 4));
  segmentTreeUpdate(&tree, 2, 10);
  printf("After update, sum [1, 4]: %d\n", segmentTreeQuery(&tree, 1, 4));
  segmentTreeFree(&tree);
  return 0;
}

