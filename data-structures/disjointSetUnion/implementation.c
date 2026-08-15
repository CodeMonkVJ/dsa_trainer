// Disjoint Set Union (Union-Find) with path compression and union by rank.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *parent;
  int *rank;
  int count;
} DSU;

bool dsuInit(DSU *dsu, int count) {
  if (count <= 0) return false;
  dsu->parent = (int *)malloc((size_t)count * sizeof(int));
  dsu->rank = (int *)calloc((size_t)count, sizeof(int));
  if (!dsu->parent || !dsu->rank) {
    free(dsu->parent);
    free(dsu->rank);
    return false;
  }
  dsu->count = count;
  for (int i = 0; i < count; ++i) dsu->parent[i] = i;
  return true;
}

int dsuFind(DSU *dsu, int value) {
  if (value < 0 || value >= dsu->count) return -1;
  if (dsu->parent[value] != value)
    dsu->parent[value] = dsuFind(dsu, dsu->parent[value]);
  return dsu->parent[value];
}

bool dsuUnion(DSU *dsu, int a, int b) {
  int rootA = dsuFind(dsu, a), rootB = dsuFind(dsu, b);
  if (rootA < 0 || rootB < 0) return false;
  if (rootA == rootB) return false;
  if (dsu->rank[rootA] < dsu->rank[rootB]) {
    int temp = rootA; rootA = rootB; rootB = temp;
  }
  dsu->parent[rootB] = rootA;
  if (dsu->rank[rootA] == dsu->rank[rootB]) dsu->rank[rootA]++;
  return true;
}

bool dsuConnected(DSU *dsu, int a, int b) {
  return dsuFind(dsu, a) >= 0 && dsuFind(dsu, a) == dsuFind(dsu, b);
}

void dsuFree(DSU *dsu) {
  free(dsu->parent);
  free(dsu->rank);
  dsu->parent = dsu->rank = NULL;
  dsu->count = 0;
}

int main(void) {
  DSU dsu;
  if (!dsuInit(&dsu, 5)) return 1;
  dsuUnion(&dsu, 0, 1);
  dsuUnion(&dsu, 1, 2);
  printf("0 and 2 connected: %s\n", dsuConnected(&dsu, 0, 2) ? "yes" : "no");
  printf("0 and 3 connected: %s\n", dsuConnected(&dsu, 0, 3) ? "yes" : "no");
  dsuFree(&dsu);
  return 0;
}

