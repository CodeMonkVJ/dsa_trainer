// Undirected graph using an adjacency list and breadth-first traversal.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
  int to;
  struct Edge *next;
} Edge;

typedef struct {
  int vertices;
  Edge **adj;
} Graph;

bool graphInit(Graph *graph, int vertices) {
  if (vertices <= 0) return false;
  graph->vertices = vertices;
  graph->adj = (Edge **)calloc((size_t)vertices, sizeof(Edge *));
  return graph->adj != NULL;
}

bool graphAddEdge(Graph *graph, int from, int to) {
  if (from < 0 || from >= graph->vertices || to < 0 || to >= graph->vertices)
    return false;
  Edge *a = (Edge *)malloc(sizeof(Edge));
  Edge *b = (Edge *)malloc(sizeof(Edge));
  if (!a || !b) {
    free(a); free(b);
    return false;
  }
  a->to = to; a->next = graph->adj[from]; graph->adj[from] = a;
  b->to = from; b->next = graph->adj[to]; graph->adj[to] = b;
  return true;
}

void graphBfs(const Graph *graph, int start) {
  if (start < 0 || start >= graph->vertices) return;
  bool *visited = (bool *)calloc((size_t)graph->vertices, sizeof(bool));
  int *queue = (int *)malloc((size_t)graph->vertices * sizeof(int));
  if (!visited || !queue) { free(visited); free(queue); return; }
  int head = 0, tail = 0;
  queue[tail++] = start; visited[start] = true;
  while (head < tail) {
    int vertex = queue[head++];
    printf("%d ", vertex);
    for (Edge *edge = graph->adj[vertex]; edge; edge = edge->next) {
      if (!visited[edge->to]) {
        visited[edge->to] = true;
        queue[tail++] = edge->to;
      }
    }
  }
  printf("\n");
  free(visited); free(queue);
}

void graphFree(Graph *graph) {
  for (int i = 0; i < graph->vertices; ++i) {
    Edge *edge = graph->adj[i];
    while (edge) {
      Edge *next = edge->next;
      free(edge);
      edge = next;
    }
  }
  free(graph->adj);
  graph->adj = NULL;
  graph->vertices = 0;
}

int main(void) {
  Graph graph;
  if (!graphInit(&graph, 5)) return 1;
  graphAddEdge(&graph, 0, 1);
  graphAddEdge(&graph, 0, 2);
  graphAddEdge(&graph, 1, 3);
  graphAddEdge(&graph, 2, 4);
  printf("BFS from 0: ");
  graphBfs(&graph, 0);
  graphFree(&graph);
  return 0;
}

