#pragma once

#include <optional>
#include <string>
#include <unordered_map>

class Trie {
    class TrieNode {
      public:
        bool is_complete;
        std::unordered_map<char, TrieNode *> children;

        TrieNode() : is_complete(false) {}
    };

    void delete_trie(TrieNode *node) {
        for (auto &[c, child] : node->children) {
            delete_trie(child);
        }

        delete node;
    }

    TrieNode *root;

  public:
    Trie() : root(new TrieNode) {}

    ~Trie() { delete_trie(root); }

    class Iterator {
        friend class Trie;
        TrieNode *curr;

      public:
        Iterator(TrieNode *curr) : curr(curr) {}

        bool is_complete() const { return curr->is_complete; }

        bool operator==(const Iterator &other) const {
            return curr == other.curr;
        }

        bool operator!=(const Iterator &other) const {
            return curr != other.curr;
        }
    };

    Iterator begin() const { return Iterator(root); }

    std::optional<Iterator> check_next_and_get(const Iterator &it,
                                               char c) const {
        if (it.curr->children.contains(c)) {
            return Iterator(it.curr->children[c]);
        } else {
            return std::nullopt;
        }
    }

    void insert(std::string word) {
        TrieNode *curr = root;

        for (char c : word) {
            if (curr->children.contains(c)) {
                curr = curr->children[c];
            } else {
                TrieNode *new_node = new TrieNode();
                curr->children[c] = new_node;
                curr = new_node;
            }
        }

        curr->is_complete = true;
    }

    bool search(std::string word) const {
        TrieNode *curr = root;

        for (char c : word) {
            if (curr->children.contains(c)) {
                curr = curr->children[c];
            } else {
                return false;
            }
        }

        return curr->is_complete;
    }

    bool starts_with(std::string prefix) const {
        TrieNode *curr = root;

        for (char c : prefix) {
            if (curr->children.contains(c)) {
                curr = curr->children[c];
            } else {
                return false;
            }
        }

        return true;
    }
};
