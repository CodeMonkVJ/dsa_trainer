#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  int key;
  struct Node *prev;
  struct Node *next;
  Node(int k, int v) {
    value = v;
    key = k;
    prev = nullptr;
    next = nullptr;
  }
};

class LRUCache {
public:
  unordered_map<int, Node *> map;
  Node *head = nullptr;
  Node *tail = nullptr;
  int capacity = 0;
  int size = 0;
  explicit LRUCache(int cap) {
    capacity = cap;
    head = new Node(-1, -1);
    tail = new Node(-1, -1);
    head->next = tail;
    tail->prev = head;
  }
  int get(int key) {
    if (map.find(key) == map.end())
      return -1;

    Node *node = map[key];
    Node *prev = node->prev;
    Node *next = node->next;
    prev->next = next;
    next->prev = prev;

    next = head->next;
    head->next = node;
    node->prev = head;
    node->next = next;
    next->prev = node;

    return node->value;
  }

  void put(int key, int value) {
    if (map.find(key) == map.end()) {
      if (size == capacity) {
        Node *newPrev = tail->prev->prev;
        Node *oldPrev = tail->prev;
        newPrev->next = tail;
        tail->prev = newPrev;
        map.erase(oldPrev->key);
        delete oldPrev;
        size--;
      }
      Node *newNode = new Node(key, value);
      map[key] = newNode;
      Node *oldNext = head->next;
      head->next = newNode;
      newNode->prev = head;
      newNode->next = oldNext;
      oldNext->prev = newNode;
      size++;
    } else {
      Node *newNode = map[key];
      newNode->value = value;
      newNode->prev->next = newNode->next;
      newNode->next->prev = newNode->prev;
      Node *oldNext = head->next;
      head->next = newNode;
      newNode->prev = head;
      newNode->next = oldNext;
      oldNext->prev = newNode;
    }
  }
  ~LRUCache() {
    Node *curr = head;

    while (curr != nullptr) {
      Node *next = curr->next;
      delete curr;
      curr = next;
    }
  }
};
