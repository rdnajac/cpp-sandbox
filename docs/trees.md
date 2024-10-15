# Trees in Data Structures and Algorithms

Trees are hierarchical data structures consisting of nodes connected by edges.

- **root**: The topmost node in a tree.
- **parent**: A node that has child nodes.
- **child**: A node directly connected to another node when moving away from the
  root.
- **leaf**: A node with no children.
- **subtree**: A tree consisting of a node and all its descendants.
- **level**: The level of a node is the number of edges on the path from the root
  node to that node.
- **height**: The height of a tree is the max level of any node in the tree.

## Binary Trees

A binary tree is a tree data structure in which each node has at most two
children, referred to as the left child and the right child.

### Basic Structure

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

## Tree Traversals

Tree traversals are methods of visiting all nodes in a tree in a specific order.

- Pre-order Traversal
- In-order Traversal
- Post-order Traversal

### Pre-order Traversal

1. Visit the root.
2. Traverse the left subtree.
3. Traverse the right subtree.

```cpp
void preorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    cout << root->val << " ";           // Visit the root
    preorderTraversal(root->left);      // Traverse left subtree
    preorderTraversal(root->right);     // Traverse right subtree
}
```

### In-order Traversal

In in-order traversal, we visit the left subtree first,
then the root node, and finally the right subtree.

```cpp
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    inorderTraversal(root->left);  // Traverse left subtree
    cout << root->val << " ";  // Visit the root
    inorderTraversal(root->right);  // Traverse right subtree
}
```

### Post-order Traversal

In post-order traversal, we visit the left subtree first,
then the right subtree, and finally the root node.

```cpp
void postorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    postorderTraversal(root->left);     // Traverse left subtree
    postorderTraversal(root->right);    // Traverse right subtree
    cout << root->val << " ";           // Visit the root
}
```

## Array Implementation of Binary Trees

Binary trees can be represented using arrays, especially for complete binary trees.
In this representation, for a node at index i:

- Its left child is at index 2i + 1
- Its right child is at index 2i + 2
- Its parent is at index (i - 1) / 2

```cpp
class ArrayBinaryTree {
private:
    vector<int> tree;

public:
    void insert(int value) {
        tree.push_back(value);
    }

    int getLeft(int index) {
        int leftIndex = 2 * index + 1;
        return (leftIndex < tree.size()) ? tree[leftIndex] : -1;
    }

    int getRight(int index) {
        int rightIndex = 2 * index + 2;
        return (rightIndex < tree.size()) ? tree[rightIndex] : -1;
    }

    int getParent(int index) {
        if (index <= 0 || index >= tree.size()) return -1;
        return tree[(index - 1) / 2];
    }
};
```

## Binary Search Trees (BST)

A Binary Search Tree is a binary tree with the property that the left subtree
of a node contains only nodes with keys less than the node's key, and the
right subtree contains only nodes with keys greater than the node's key.

### Basic BST Operations

```cpp
class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int value) {
        if (node == nullptr) return new TreeNode(value);

        if (value < node->val)
            node->left = insert(node->left, value);
        else if (value > node->val)
            node->right = insert(node->right, value);

        return node;
    }

    TreeNode* search(TreeNode* node, int value) {
        if (node == nullptr || node->val == value)
            return node;

        if (value < node->val)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

public:
    BST() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    bool search(int value) {
        return search(root, value) != nullptr;
    }
};
```

## AVL Trees

AVL trees are self-balancing binary search trees. In an AVL tree, the heights
of the two child subtrees of any node differ by at most one.

### AVL Tree Node

```cpp
struct AVLNode {
    int val;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
};
```

### Basic AVL Tree Operations

```cpp
class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    int balanceFactor(AVLNode* node) {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode* insert(AVLNode* node, int value) {
        if (node == nullptr) return new AVLNode(value);

        if (value < node->val)
            node->left = insert(node->left, value);
        else if (value > node->val)
            node->right = insert(node->right, value);
        else
            return node;  // Duplicate values not allowed

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        // Left Left Case
        if (balance > 1 && value < node->left->val)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && value > node->right->val)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && value > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }
};
```
