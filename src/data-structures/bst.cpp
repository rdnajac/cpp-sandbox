// Binary search tree implementation
#include <iostream>
using namespace std;


class BinarySearchTree {
private:
    Node* root;

    Node* insertHelper(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);

        // blast off!
        auto cmp = value <=> node->data;
        if (cmp < 0)
            node->left = insertHelper(node->left, value);
        else if (cmp > 0)
            node->right = insertHelper(node->right, value);
        // implicitly skips duplicate values (cmp == 0)
        
        return node;
    }

    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

    void breadthFirstTraversal(Node* node) {
        if (node != nullptr) {
            breadthFirstTraversal(node->left);
            breadthFirstTraversal(node->right);
            cout << node->data << " ";
        }
    }

    void postOrderTraversal(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
        }
    }

    void preOrderTraversal(Node* node) {
        if (node != nullptr) {
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
            cout << node->data << " ";
        }
    }

    // same as inOrderTraversal
    void depthFirstTraversal(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            depthFirstTraversal(node->left);
            depthFirstTraversal(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Insert a value into the BST
    void insert(int value)
        root = insertHelper(root, value);

    // Perform in-order traversal
    void inOrderTraversal() {
        inOrderTraversal(root);
        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    cout << "In-order traversal of the BST: ";
    bst.inOrderTraversal();

    return 0;
}
