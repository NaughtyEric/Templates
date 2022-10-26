//
// Created by Haolin  Jia on 2022/10/26.
//

#ifndef TEMPLATES_BINARY_TREE_H
#define TEMPLATES_BINARY_TREE_H
#include <stack>
#include <vector>
#include <queue>
template<typename T>
class BinaryTree {
    class Node {
    public:
        T data;
        int depth, size;
        Node *left, *right, *parent;
        Node(const T &data, int depth=0, Node *left=nullptr, Node *right=nullptr) :
            depth(depth), data(data), left(left), right(right) {
            size = 0;
            if (left) { left->parent = this; size += left->size; }
            if (right) { right->parent = this; size += right->size; }
            size++;
        }
        Node(const Node &node) : depth(node.depth), data(node.data), left(node.left), right(node.right) {}
        ~Node() {
            delete left;
            delete right;
        }

        Node* getLeft() const {
            return left;
        }
        Node* getRight() const {
            return right;
        }
        Node* getParent() const {
            return parent;
        }
        Node* getSibling() const {
            if (parent == nullptr) return nullptr;
            if (parent->left == this) return parent->right;
            else return parent->left;
        }
    };

    void copy(Node *cur, Node* src) {
        if (src == nullptr) return;
        cur = new Node(src->data, src->depth);
        // to left
        if (src->left != nullptr) {
            cur->left = new Node(src->left->data, src->left->depth);
            cur->left->parent = cur;
            copy(cur->left, src->left);
        }
        // to right
        if (src->right != nullptr) {
            cur->right = new Node(src->right->data, src->right->depth);
            cur->right->parent = cur;
            copy(cur->right, src->right);
        }
    }

    /// Preorder traversal without recursion
    /// \return a pointer to the vector of data
    [[nodiscard]] std::vector<T>* preorder_NRecursion() {
        auto* res = new std::vector<T>;
        Node* ptr;
        std::stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            ptr = s.top();
            s.pop();
            res->push_back(ptr->data);
            if (ptr->right) s.push(ptr->right);
            if (ptr->left) s.push(ptr->left);
        }
        return *res;
    }

    /// Preorder traversal with recursion
    /// \return a pointer to the vector of data
    void preorder_Recursion(Node* cur, std::vector<T>* res) {
        if (cur == nullptr) return;
        res->push_back(cur->data);
        preorder_Recursion(cur->left, res);
        preorder_Recursion(cur->right, res);
    }

    /// Inorder traversal without recursion
    /// \return a pointer to the vector of data
    [[nodiscard]] std::vector<T>* inorder_NRecursion() {
        auto* res = new std::vector<T>;
        Node* ptr = root;
        std::stack<Node*> s;
        while (ptr || !s.empty()) {
            while (ptr) {
                s.push(ptr);
                ptr = ptr->left;
            }
            ptr = s.top();
            s.pop();
            res->push_back(ptr->data);
            ptr = ptr->right;
        }
        return *res;
    }

    /// Inorder traversal with recursion
    void inorder_Recursion(Node* cur, std::vector<T>* res) {
        if (cur == nullptr) return;
        inorder_Recursion(cur->left, res);
        res->push_back(cur->data);
        inorder_Recursion(cur->right, res);
    }

    /// Postorder traversal without recursion
    /// \return a pointer to the vector of data
    [[nodiscard]] std::vector<T>* postorder_NRecursion() {
        auto* res = new std::vector<T>;
        Node* ptr = root;
        std::stack<Node*> s;
        while (ptr || !s.empty()) {
            while (ptr) {
                s.push(ptr);
                ptr = ptr->left;
            }
            ptr = s.top();
            s.pop();
            if (ptr->right) {
                s.push(ptr->right);
                ptr = ptr->right;
            } else {
                res->push_back(ptr->data);
                ptr = nullptr;
            }
        }
        return *res;
    }

    /// Postorder traversal with recursion
    void postorder_Recursion(Node* cur, std::vector<T>* res) {
        if (cur == nullptr) return;
        postorder_Recursion(cur->left, res);
        postorder_Recursion(cur->right, res);
        res->push_back(cur->data);
    }

    int leafCount(Node *cur) {
        if (cur == nullptr) return 0;
        if (cur->left == nullptr && cur->right == nullptr) return 1;
        return leafCount(cur->left) + leafCount(cur->right);
    }

    Node *root;
public:
    BinaryTree() : root(nullptr) {}
    BinaryTree(const T &data) : root(new Node(data)) {}

    BinaryTree(const BinaryTree &other) {
        root = new Node(other.root->data);
        copy(root, other.root);
    }

    ~BinaryTree() {
        Node* ptr;
        std::stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            ptr = s.top();
            s.pop();
            if (ptr->left) s.push(ptr->left);
            if (ptr->right) s.push(ptr->right);
            delete ptr;
        }
    }

    /// Preorder traversal
    /// \return a pointer to the vector of data
    [[nodiscard]] std::vector<T>* preorder(bool useRecursion = false) {
        if (useRecursion) {
            auto* res = new std::vector<T>;
            preorder_Recursion(root, res);
            return res;
        } else {
            return preorder_NRecursion();
        }
    }

    /// Inorder traversal
    /// \return a pointer to the vector of data
    [[nodiscard]] std::vector<T>* inorder(bool useRecursion = false) {
        if (useRecursion) {
            auto* res = new std::vector<T>;
            inorder_Recursion(root, res);
            return res;
        } else {
            return inorder_NRecursion();
        }
    }

    /// Postorder traversal
    /// \return a pointer to the vector of data
    [[nodiscard]] std::vector<T>* postorder(bool useRecursion = false) {
        if (useRecursion) {
            auto* res = new std::vector<T>;
            postorder_Recursion(root, res);
            return res;
        } else {
            return postorder_NRecursion();
        }
    }

    /// hierarchical traversal
    /// \return a pointer to the vector of data
    [[nodiscard]] std::vector<T>* levelOrder() {
        auto* res = new std::vector<T>;
        Node* ptr;
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            ptr = q.front();
            q.pop();
            res->push_back(ptr->data);
            if (ptr->left) q.push(ptr->left);
            if (ptr->right) q.push(ptr->right);
        }
        return *res;
    }

    int getLeafCount() {
        return leafCount(root);
    }

    int getSize() {
        return root->size;
    }

    [[nodiscard]] BinaryTree* getSubtree(Node *subRoot) {
        auto* res = new BinaryTree;
        res->root = subRoot;
        return res;
    }

    /// Get all ancestors of a node
    /// \return a pointer to vector of nodes, stored from low to high
    [[nodiscard]] std::vector<T> getAncestors(Node *node) {
        std::vector<T> res;
        Node *ptr = root;
        while (ptr != node) {
            res.push_back(ptr->data);
            if (node->data < ptr->data) ptr = ptr->left;
            else ptr = ptr->right;
        }
        return res;
    }

};
#endif //TEMPLATES_BINARY_TREE_H
