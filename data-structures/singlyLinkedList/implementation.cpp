/**
 * Singly Linked List
 *
 * Stores elements in nodes connected in one direction.  Push-front,
 * search, and removal by value are demonstrated below.
 *
 * Complexity: pushFront O(1), find/remove O(n), reverse O(n), extra space O(1).
 */
#include <bits/stdc++.h>
using namespace std;

class SinglyLinkedList {
    struct Node {
        int value;
        Node* next;

        explicit Node(int value) : value(value), next(nullptr) {}
    };

    Node* head_ = nullptr;
    size_t size_ = 0;

public:
    ~SinglyLinkedList() { clear(); }

    void pushFront(int value) {
        Node* node = new Node(value);
        node->next = head_;
        head_ = node;
        ++size_;
    }

    bool insertAfter(int target, int value) {
        for (Node* node = head_; node; node = node->next) {
            if (node->value == target) {
                Node* inserted = new Node(value);
                inserted->next = node->next;
                node->next = inserted;
                ++size_;
                return true;
            }
        }
        return false;
    }

    bool removeFirst(int value) {
        Node* node = head_;
        if (!node) return false;
        if (node->value == value) {
            head_ = head_->next;
            delete node;
            --size_;
            return true;
        }
        while (node->next && node->next->value != value) node = node->next;
        if (!node->next) return false;
        Node* removed = node->next;
        node->next = removed->next;
        delete removed;
        --size_;
        return true;
    }

    void reverse() {
        Node* previous = nullptr;
        Node* current = head_;
        while (current) {
            Node* next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head_ = previous;
    }

    bool contains(int value) const {
        for (const Node* node = head_; node; node = node->next)
            if (node->value == value) return true;
        return false;
    }

    void print() const {
        for (const Node* node = head_; node; node = node->next) {
            cout << node->value << (node->next ? " -> " : "\n");
        }
    }

    void clear() {
        while (head_) {
            Node* next = head_->next;
            delete head_;
            head_ = next;
        }
        size_ = 0;
    }

    size_t size() const { return size_; }
};

int main() {
    SinglyLinkedList list;
    list.pushFront(30);
    list.pushFront(20);
    list.pushFront(10);
    list.insertAfter(20, 25);
    cout << "List: "; list.print();
    list.reverse();
    cout << "Reversed: "; list.print();
    cout << "Contains 25: " << (list.contains(25) ? "yes" : "no") << '\n';
    return 0;
}
