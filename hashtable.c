#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable.h"

// Initiera hashtabellen genom att sätta alla pekare till NULL
void initTable(HashTable* ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ht->table[i] = NULL;
    }
}

// Enkel hashfunktion som beräknar en position i arrayen beroende på key
int hash(int key)
{
    return key % TABLE_SIZE;
}


// Insert
void insert(HashTable* ht, int key, const char* value)
{
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Failed to allocate memory\n");
        return;
    }
    
    newNode->data.key = key;
    strncpy(newNode->data.value, value, sizeof(newNode->data.value) - 1);
    newNode->data.value[sizeof(newNode->data.value) - 1] = '\0';
    
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

// Get
char* get(HashTable* ht, int key)
{
    int index = hash(key);
    Node* current_node = ht->table[index];
    while (current_node != NULL)
    {
        if (current_node->data.key == key)
        {
            return current_node->data.value;
        }
        current_node = current_node->next;
    }
    return NULL;
}

// Remove
int removeKey(HashTable* ht, int key)
{
    int index = hash(key);
    Node* current_node = ht->table[index];
    Node* previous_node = NULL;
    while (current_node != NULL)
    {
        if (current_node->data.key == key)
        {
            if (previous_node == NULL)
            {
                ht->table[index] = current_node->next;
            }
            else
            {
                previous_node->next = current_node->next;
            }
            free(current_node);
            return 1;
        }
        previous_node = current_node;
        current_node = current_node->next;
    }
    return 0;
}

// Debugfunktion som skriver ut allt som finns i tabellen
void printTable(HashTable* ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node* current_node = ht->table[i];
        printf("Index %d: ", i);
        while (current_node != NULL)
        {
            printf("(%d: %s) -> ", current_node->data.key, current_node->data.value);
            current_node = current_node->next;
        }
        printf("NULL\n");
    }  
}