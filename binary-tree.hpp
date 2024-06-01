#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <stdexcept>
#include <vector>

template <typename T> class BinaryTree {
    struct Node {
        T val;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(const T &val, std::unique_ptr<Node> left = nullptr,
             std::unique_ptr<Node> right = nullptr)
            : val(val), left(std::move(left)), right(std::move(right)) {}
    };

  public:
    BinaryTree();
    ~BinaryTree();
    void print_preorder();  // TODO
    void print_inorder();   // TODO
    void print_postorder(); // TODO
    void print_levelorder();

    void insert_levelorder(const std::vector<std::optional<T>> &vals);

  private:
    std::unique_ptr<Node> root;
};

template <typename T> BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <typename T> BinaryTree<T>::~BinaryTree() {}

template <typename T>
void BinaryTree<T>::insert_levelorder(
    const std::vector<std::optional<T>> &vals) {
    if (vals.empty()) {
        return;
    }

    if (root != nullptr) {
        throw std::runtime_error("Tree is not empty");
    }

    if (vals.front().has_value()) {
        root = std::make_unique<Node>(vals.front().value());
    } else {
        root = nullptr;
    }
    std::queue<Node *> q;
    q.push(root.get());

    uint32_t i = 1;
    while (i < vals.size()) {
        Node *node = q.front();
        q.pop();

        if (node == nullptr) {
            q.push(nullptr);
            q.push(nullptr);
            i += 2;
            continue;
        }

        if (vals[i].has_value()) {
            node->left = std::make_unique<Node>(vals[i].value());
        } else {
            node->left = nullptr;
        }
        q.push(node->left.get());
        i++;

        if (i < vals.size()) {
            if (vals[i].has_value()) {
                node->right = std::make_unique<Node>(vals[i].value());
            } else {
                node->right = nullptr;
            }

            q.push(node->right.get());
            i++;
        }
    }
}

// TODO: can improve this implementation
template <typename T> void BinaryTree<T>::print_levelorder() {
    if (root == nullptr) {
        return;
    }

    std::queue<Node *> q;
    q.push(root.get());

    while (!q.empty()) {
        uint32_t level_size = q.size();
        bool not_null = false;

        while (level_size > 0) {
            Node *curr = q.front();
            q.pop();
            level_size--;

            if (curr == nullptr) {
                std::cout << "null"
                          << " ";
                q.push(nullptr);
                q.push(nullptr);
            } else {
                not_null = true;
                std::cout << curr->val << " ";
                q.push(curr->left.get());
                q.push(curr->right.get());
            }
        }

        if (!not_null) {
            break;
        }
    }
}
