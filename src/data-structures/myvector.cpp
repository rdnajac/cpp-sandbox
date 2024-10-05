
#include "node.hpp"

// definition for the list
struct List {
    Node* head;
    Node* tail;
};

List* createList();
void destroyList(List* list);
void insert(List* list, void* data);
void remove(List* list, void* data);
void* search(List* list, void* data);

/*
 * @brief create a new list
 * @return a pointer to the new list
 */

List* createList() {
    List* list = new List;  /* malloc(sizeof(List)) */
    list->head = NULL;
    list->tail = NULL;
    return list;
}

/*
 * @brief destroy a list
 * @param list the list to destroy
 */
void destroyList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->right;
        destroyNode(current);
        current = next;
    }
    delete list;  /* free(list) */
}

/*
 * @brief insert a new node into the list
 * @param list the list to insert into
 * @param data the data to insert
 */





