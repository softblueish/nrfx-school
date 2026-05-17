#include "sorting-algorithm.h"

int is_sorted_list(List* list){
    Node* temp = *list;
    while(temp != NULL && temp->next != NULL){
        if(temp->data > temp->next->data){
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

int is_sorted_array(int* array, int size){
    for(int i = 0; i < size - 1; i++){
        if(array[i] > array[i + 1]){
            return 0;
        }
    }
    return 1;
}