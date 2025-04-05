#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked.h"

// Create a new node
Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    
    strncpy(newNode->data, data, sizeof(newNode->data) - 1);
    newNode->data[sizeof(newNode->data) - 1] = '\0';  // Ensure null-termination
    newNode->next = NULL;
    
    return newNode;
}

// Insert node at the beginning of the list
void insertFirst(Node** head, const char* data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    newNode->next = *head;
    *head = newNode;
}

// Insert node at the end of the list
void insertLast(Node** head, const char* data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Delete a node with specific data
int deleteNode(Node** head, const char* data) {
    if (*head == NULL) return 0;
    
    Node* current = *head;
    Node* prev = NULL;
    
    // Check first node
    if (strcmp(current->data, data) == 0) {
        *head = current->next;
        free(current);
        return 1;
    }
    
    // Search in remaining nodes
    while (current != NULL && strcmp(current->data, data) != 0) {
        prev = current;
        current = current->next;
    }
    
    // Node not found
    if (current == NULL) return 0;
    
    // Remove the node
    prev->next = current->next;
    free(current);
    return 1;
}

// Delete all nodes in the list
void deleteAllNodes(Node** head) {
    Node* current = *head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}

// Display all nodes in the list
void displayList(Node* head) {
    int count = 1;
    Node* current = head;
    
    while (current != NULL) {
        printf("%d. %s\n", count++, current->data);
        current = current->next;
    }
    
    if (count == 1) {
        printf("List is empty.\n");
    }
}

// Search for a node with specific data
int searchNode(Node* head, const char* data) {
    Node* current = head;
    
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return 1;  // Node found
        }
        current = current->next;
    }
    
    return 0;  // Node not found
}

// Get the length of the list
int getListLength(Node* head) {
    int count = 0;
    Node* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}