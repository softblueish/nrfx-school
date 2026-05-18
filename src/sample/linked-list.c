#include "linked-list.h"

// I realized double linked lists suck so I made a single linked list instead.
// It's better to just not make my life hell
// Sorry -Ashley

void initList(List* list) {
    *list = NULL;
}

void insert(List* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    Node *temp = *list;
    if(temp == NULL){
        *list = newNode;
        newNode->next = NULL;
        return;
    }
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = NULL;
}

void removeNode(List* list, int position) {
    if (*list == NULL) 
        return;

    Node* temp = *list;
    if (position == 0) {
        *list = temp->next;
        free(temp);
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL)
        return;
    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

int get(List* list, int position) {
    Node* temp = *list;
    for (int i = 0; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        print_string("Position out of bounds\n");
        return -2147483648;
    }
    return temp->data;
}

// I know this isnt the pseudocode i used for labb 3.1, but i made a single linked list instead so i rewrote it
void swap(List* list, Node* target) {
    if (*list == NULL) 
        return;
    Node* current = *list;
    Node* previous = NULL;
    while (current != NULL && current != target) {
        previous = current;
        current = current->next;
    }
    if (current == NULL || current->next == NULL)
        return;
    Node* next = current->next;
    current->next = next->next;
    next->next = current;
    if (previous != NULL) {
        previous->next = next;
    } else {
        *list = next;
    }
}