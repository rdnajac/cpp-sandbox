#include "note.hpp"

// struct Node {
//     void* data;
//     Node* left;  /* previous node */
//     Node* right; /* next node */
// };

Node* createNode(void* data)
{
    Node* node = new Node;  /* malloc(sizeof(Node)) */
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroyNode(Node* node)
{
    delete node;  /* free(node) */
}
