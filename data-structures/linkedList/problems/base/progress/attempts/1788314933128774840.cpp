#include <bits/stdc++.h>
using namespace std;

typedef struct Node {
  int value;
  struct Node *next;
} Node;

class SinglyLinkedList {
  size_t size_ = 0;
  Node *head = nullptr;

public:
  ~SinglyLinkedList() { clear(); }

  void pushFront(int v) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = head;
    newNode->value = v;
    head = newNode;
    size_++;
  }

  bool insertAfter(int currVal, int newVal) {
    Node *curr = head;
    while (curr != nullptr) {
      if (curr->value == currVal) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->value = newVal;
        Node *nextNode = curr->next;
        newNode->next = nextNode;
        curr->next = newNode;
        size_++;
        return true;
      } else {
        curr = curr->next;
      }
    }
    return false;
  }

  bool removeFirst(int val) {
    Node *prev = nullptr;
    Node *curr = head;
    while (curr != nullptr) {
      if (curr->value == val) {
        if (prev == nullptr)
          head = head->next;
        else {
          prev->next = curr->next;
        }
        free(curr);
        size_--;
        return true;
      } else {
        prev = curr;
        curr = curr->next;
      }
    }
    return false;
  }

  void reverse() {
    if (size_ <= 1)
      return;
    Node *prev = nullptr, *curr = head, *next = curr->next;
    while (curr != nullptr) {
      curr->next = prev;
      prev = curr;
      curr = next;
      if (next != nullptr)
        next = next->next;
    }
    head = prev;
  }

  bool contains(int v) const {
    Node *curr = head;
    while (curr != nullptr) {
      if (curr->value == v) {
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  void print() const {
    Node *curr = head;
    while (curr != NULL) {
      cout << curr->value << " ";
      curr = curr->next;
    }
    cout << endl;
  }

  void clear() {
    Node *curr = head;
    while (curr != NULL) {
      Node *next = curr->next;
      free(curr);
      curr = next;
    }
    size_ = 0;
    head = nullptr;
  }

  size_t size() const { return size_; }
};
