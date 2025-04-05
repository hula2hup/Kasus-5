#ifndef LINKED_H
#define LINKED_H

// Node structure for the linked list
typedef struct Node {
    char data[50];  // Assuming max name length of 50 characters
    struct Node* next;
} Node;

// Function prototypes for linked list operations
Node* createNode(const char* data);
void insertFirst(Node** head, const char* data);
void insertLast(Node** head, const char* data);
int deleteNode(Node** head, const char* data);
void deleteAllNodes(Node** head);
void displayList(Node* head);
int searchNode(Node* head, const char* data);
int getListLength(Node* head);

#endif