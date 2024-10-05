#ifndef NODE_H
#define NODE_H
// definition for the node
struct Node {
    void* data;
    Node* left;  /* previous node */
    Node* right; /* next node */
};

Node* createNode(void* data);
void destroyNode(Node* node);

#endif /* NODE_H */
