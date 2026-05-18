#ifndef LINKED_LIST_
#define LINKED_LIST_
#include <stdio.h>
#include <stdlib.h>
#include "uarte-commands.h"


typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Node* List;

void initList(List* list);

void insert(List* list, int data);

void removeNode(List* list, int position);

int get(List* list, int position);

void swap(List* list, Node* target);
#endif