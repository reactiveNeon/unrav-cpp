#include <algorithm>
#include <cstddef>

template <typename T> class AVLTree {
    struct Node {
        T val;
        int bf; // balance factor (rh - lh)
        int height;
        Node *left, *right;

        Node(const T &val, Node *left = nullptr, Node *right = nullptr)
            : val(val), left(left), right(right), height(0) {}
    };

  public:
    AVLTree() : size(0), root(nullptr) {}
    ~AVLTree() {} // TODO
    bool insert(T val);
    bool erase(T val);
    bool contains(T val);

    size_t getSize();
    size_t getHeight(); 

  private:
    size_t size;
    Node *root;

    Node* insert(const Node *node, T val);
    Node* erase(const Node *node, T val);
    bool contains(const Node *node, T val);
    void update(const Node *node);
    Node* balance(const Node *node);

    Node* leftLeftCase(const Node *node);
    Node* leftRightCase(const Node *node);
    Node* rightRightCase(const Node *node);
    Node* rightLeftCase(const Node *node);

    Node* leftRotation(const Node *node);
    Node* rightRotation(const Node *node);

    T find_min(const Node *node);
    T find_max(const Node *node);
};

template <typename T> bool AVLTree<T>::insert(T val) {
    if (contains(root, val)) {
        return false;
    }

    root = insert(root, val);
    size++;
    return true;
}

template<typename T> AVLTree<T>::Node* AVLTree<T>::insert(const Node *node, T val) {
    if(node == nullptr) {
        return new Node(val);
    }

    if(val < node->val) {
        node->left = insert(node->left, val);
    } else {
        node->right = insert(node->right, val);
    }

    update(node);
    return balance(node);
}

template <typename T> void AVLTree<T>::update(const Node *node) {
    int lh = (node->left) ? node->left->height : -1;
    int rh = (node->right) ? node->right->height : -1;

    node->height = 1 + std::max(lh, rh);
    node->bf = rh - lh;
}

template <typename T> AVLTree<T>::Node* AVLTree<T>::balance(const Node *node) {
    if(node->bf == -2) {
        if(node->left->bf <= 0) {
            return leftLeftCase(node);
        } else {
            return leftRightCase(node);
        }
    } else if(node->bf == 2) {
        if(node->bf >= 0) {
            return rightRightCase(node);
        } else {
            return rightLeftCase(node);
        }
    }

    return node;
}

template <typename T> AVLTree<T>::Node* AVLTree<T>::leftLeftCase(const Node *node) {
    return rightRotation(node);
}

template <typename T> AVLTree<T>::Node* AVLTree<T>::leftRightCase(const Node *node) {
    node->left = leftRotation(node);
    return leftLeftCase(node);
}

template <typename T> AVLTree<T>::Node* AVLTree<T>::rightRightCase(const Node *node) {
    return leftRotation(node);
}

template <typename T> AVLTree<T>::Node* AVLTree<T>::rightLeftCase(const Node *node) {
    node->right = rightRotation(node);
    return rightRightCase(node);
}

template <typename T> AVLTree<T>::Node* AVLTree<T>::leftRotation(const Node *node) {
    Node *new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template <typename T> AVLTree<T>::Node* AVLTree<T>::rightRotation(const Node *node) {
    Node *new_parent = node->left;
    node->left = new_parent->right;
    node->right = node;
    update(node);
    update(new_parent);
    return new_parent;
}

template <typename T> bool AVLTree<T>::contains(T val) {
    return contains(root, val);
}

template <typename T> bool AVLTree<T>::contains(const Node *node, T val) {
    if(!node) {
        return false;
    }

    if(val < node->val) {
        return contains(node->left, val);
    }

    if(val > node->val) {
        return contains(node->right, val);
    }

    return true;
}

template <typename T> bool AVLTree<T>::erase(T elem) {
    if(contains(root, elem)) {
        root = erase(root, elem);
        size--;
        return true;
    }

    return false;
}

template <typename T> AVLTree<T>::Node* AVLTree<T>::erase(const Node* node, T val) {
    if(val < node->val) {
        node->left = erase(node->left, val);
    } else if(val > node->val) {
        node->right = erase(node->right, val);
    } else {
        if(!node->left) {
            return node->right;
        } else if(!node->right) {
            return node->left;
        } else {
            if(node->left->height > node->right->height) {
                T next_val = find_max(node->left);                
                node->val = next_val;
                node->left = erase(node->left, next_val);
            } else {
                T next_val = find_min(node->right);
                node->val = next_val;
                node->right = erase(node->right, next_val);
            }
        }
    }

    update(node);
    return balance(node);
}

template <typename T> T AVLTree<T>::find_min(const Node *node) {
    while(!node->left) {
        node = node->left;
    }

    return node->val;
}

template <typename T> T AVLTree<T>::find_max(const Node *node) {
    while(!node->right) {
        node = node->right;
    }

    return node->val;
}