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

void bubble_sort_list(List* list){
    if(*list == NULL){
        return;
    }
    int keep_going = 0;
    Node* temp;
    do{
        keep_going = 0;
        temp = *list;
        while(temp != NULL && temp->next != NULL){
            if(temp->data > temp->next->data){
                print_string("Swapping ");
                print_int(temp->data);
                print_string(" and ");
                print_int(temp->next->data);
                print_newline();
                swap(list, temp);
                keep_going = 1;
            }
            temp = temp->next;
        }
    } while(keep_going);
}