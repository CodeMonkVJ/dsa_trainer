/**
 * Trie (Prefix Tree)
 *
 * A trie stores strings one character per level.  It is useful for
 * prefix search, autocomplete, and dictionary problems.
 *
 * For a lowercase alphabet, insert/search/prefix operations are O(L),
 * where L is the word or prefix length.  The destructor recursively
 * releases every node.
 */
#include <bits/stdc++.h>
using namespace std;

class Trie {
    struct Node {
        array<unique_ptr<Node>, 26> children{};
        bool isWord = false;
    };

    Node root_;

    static int index(char c) {
        return (c >= 'a' && c <= 'z') ? c - 'a' : -1;
    }

public:
    bool insert(const string& word) {
        Node* node = &root_;
        for (char c : word) {
            int i = index(c);
            if (i < 0) return false;
            if (!node->children[i]) node->children[i] = make_unique<Node>();
            node = node->children[i].get();
        }
        node->isWord = true;
        return true;
    }

    bool contains(const string& word) const {
        const Node* node = &root_;
        for (char c : word) {
            int i = index(c);
            if (i < 0 || !node->children[i]) return false;
            node = node->children[i].get();
        }
        return node->isWord;
    }

    bool startsWith(const string& prefix) const {
        const Node* node = &root_;
        for (char c : prefix) {
            int i = index(c);
            if (i < 0 || !node->children[i]) return false;
            node = node->children[i].get();
        }
        return true;
    }
};

int main() {
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    cout << "Contains cat: " << (trie.contains("cat") ? "yes" : "no") << '\n';
    cout << "Starts with ca: " << (trie.startsWith("ca") ? "yes" : "no") << '\n';
    return 0;
}
