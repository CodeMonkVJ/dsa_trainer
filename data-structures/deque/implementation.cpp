/**
 * Double-Ended Queue (Deque)
 *
 * A deque supports insertion and removal at both ends in O(1).  This
 * implementation uses a doubly linked list internally so the ownership and edge
 * cases remain easy to study; the public operations are the same ones
 * normally implemented with a doubly linked list.
 */
#include <bits/stdc++.h>
using namespace std;

class Deque {
    struct Node {
        int value;
        Node* previous;
        Node* next;
    };

    Node* front_ = nullptr;
    Node* back_ = nullptr;
    size_t size_ = 0;

public:
    ~Deque() { clear(); }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

    void pushFront(int value) {
        Node* node = new Node{value, nullptr, front_};
        if (front_) front_->previous = node;
        else back_ = node;
        front_ = node;
        ++size_;
    }

    void pushBack(int value) {
        Node* node = new Node{value, back_, nullptr};
        if (back_) back_->next = node;
        else front_ = node;
        back_ = node;
        ++size_;
    }

    bool popFront(int& out) {
        if (empty()) return false;
        Node* node = front_;
        out = node->value;
        front_ = node->next;
        if (front_) front_->previous = nullptr;
        else back_ = nullptr;
        delete node;
        --size_;
        return true;
    }

    bool popBack(int& out) {
        if (empty()) return false;
        Node* node = back_;
        out = node->value;
        back_ = node->previous;
        if (back_) back_->next = nullptr;
        else front_ = nullptr;
        delete node;
        --size_;
        return true;
    }

    void clear() {
        int ignored;
        while (popFront(ignored)) {}
    }
};

int main() {
    Deque deque;
    deque.pushBack(20);
    deque.pushFront(10);
    deque.pushBack(30);

    int value;
    deque.popFront(value);
    cout << "Front pop: " << value << '\n';
    deque.popBack(value);
    cout << "Back pop: " << value << '\n';
    return 0;
}
