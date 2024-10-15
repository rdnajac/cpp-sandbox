#include "rng.hpp"   // Include RNG library
#include "timer.hpp" // Include Timer library
#include <compare>   // For three-way comparison (C++20)
#include <iostream>
#include <queue> // For breadth-first traversal

using namespace std;

// Node structure representing each node in the BST
class Node {
public:
    int data;    // Value stored in the node
    Node *left;  // Pointer to the left child
    Node *right; // Pointer to the right child

    // Constructor to initialize a new node
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Class representing the Binary Search Tree
class BinarySearchTree {
private:
    Node *root; // Root node of the BST

    // Helper function to insert a value recursively
    Node *insertHelper(Node *node, int value) {
        // If the current node is null, create a new node
        if (node == nullptr) {
            return new Node(value);
        }

        // Compare value with the current node's data
        auto cmp = value <=> node->data;
        if (cmp < 0) {
            node->left = insertHelper(node->left, value); // Insert in the left subtree
        } else if (cmp > 0) {
            node->right = insertHelper(node->right, value); // Insert in the right subtree
        }
        // Duplicates are implicitly skipped (cmp == 0)

        return node;
    }

    // Helper function for in-order traversal
    void inOrderTraversal(Node *node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);  // Visit left subtree
            cout << node->data << " ";     // Visit node
            inOrderTraversal(node->right); // Visit right subtree
        }
    }

    // Helper function for pre-order traversal
    void preOrderTraversal(Node *node) {
        if (node != nullptr) {
            cout << node->data << " ";      // Visit node
            preOrderTraversal(node->left);  // Visit left subtree
            preOrderTraversal(node->right); // Visit right subtree
        }
    }

    // Helper function for post-order traversal
    void postOrderTraversal(Node *node) {
        if (node != nullptr) {
            postOrderTraversal(node->left);  // Visit left subtree
            postOrderTraversal(node->right); // Visit right subtree
            cout << node->data << " ";       // Visit node
        }
    }

    // Helper function for breadth-first traversal
    void breadthFirstTraversal(Node *node) {
        if (!node)
            return;

        queue<Node *> q;
        q.push(node);

        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            cout << current->data << " "; // Visit node

            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
    }

    // Helper function to invert the BST
    void invert(Node *node) {
        if (node == nullptr)
            return;

        std::swap(node->left, node->right);

        // Recursively invert the children
        invert(node->left);
        invert(node->right);
    }

public:
    // Constructor to initialize an empty BST
    BinarySearchTree() : root(nullptr) {}

    /**
     * @brief Inserts a value into the BST.
     * @param value The value to insert.
     */
    void insert(int value) { root = insertHelper(root, value); }

    /**
     * @brief Performs in-order traversal of the BST.
     * Outputs the values in ascending order.
     */
    void inOrderTraversal() {
        cout << "In-Order Traversal: ";
        inOrderTraversal(root);
        cout << endl; // Print a newline after traversal
    }

    /**
     * @brief Performs pre-order traversal of the BST.
     * Outputs the values in pre-order.
     */
    void preOrderTraversal() {
        cout << "Pre-Order Traversal: ";
        preOrderTraversal(root);
        cout << endl;
    }

    /**
     * @brief Performs post-order traversal of the BST.
     * Outputs the values in post-order.
     */
    void postOrderTraversal() {
        cout << "Post-Order Traversal: ";
        postOrderTraversal(root);
        cout << endl;
    }

    /**
     * @brief Performs breadth-first traversal of the BST.
     * Outputs the values level by level.
     */
    void breadthFirstTraversal() {
        cout << "Breadth-First Traversal: ";
        breadthFirstTraversal(root);
        cout << endl;
    }

    /**
     * @brief Inverts the BST.
     * This swaps the left and right children of all nodes.
     */
    void invert() { invert(root); }

    /**
     * @brief Generates a random BST with N nodes.
     * @param n The number of nodes to generate.
     */
    void generateRandomBST(int n) {
        RandomNumberGenerator rng; // Create RNG instance
        // Timer timer;               // Create Timer instance

        // timer.start();
        for (int i = 0; i < n; ++i)
            insert(rng.getRandomNumber() % 100);

        // timer.logTime("Generate Random BST Time");
        // timer.printResults();
    }

    // Helper function to print the tree in a pretty format
    void prettyPrintHelper(Node *node, string prefix, bool isLeft) {
        if (node == nullptr)
            return;

        cout << prefix;
        cout << (isLeft ? "├── " : "└── "); // Use different symbols for left and right children
        cout << node->data << endl;

        prettyPrintHelper(node->left, prefix + (isLeft ? "│   " : "    "), true);
        prettyPrintHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    // Public function to start pretty printing from the root
    void prettyPrint() { prettyPrintHelper(root, "", false); }
};

int main() {
    BinarySearchTree bst;

    int size = 13;
    cout << "Generating a random BST with " << size << " nodes..." << endl;
    bst.generateRandomBST(size);
    bst.prettyPrint();

    bst.inOrderTraversal();
    bst.preOrderTraversal();
    bst.postOrderTraversal();

    cout << "Inverting the BST..." << endl;
    bst.invert();

    bst.inOrderTraversal();
    bst.breadthFirstTraversal();

    return 0;
}
