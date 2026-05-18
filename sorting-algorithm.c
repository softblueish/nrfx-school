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

void merge_sort_array(int* array, int size){
    if(size < 2){
        return;
    }
    int mid = size / 2;
    int* left = (int*)malloc(mid * sizeof(int));
    int* right = (int*)malloc((size - mid) * sizeof(int));
    for(int i = 0; i < mid; i++){
        left[i] = array[i];
    }
    for(int i = mid; i < size; i++){
        right[i - mid] = array[i];
    }
    merge_sort_array(left, mid);
    merge_sort_array(right, size - mid);
    int i = 0, j = 0, k = 0;
    while(i < mid && j < size - mid){
        if(left[i] < right[j]){
            array[k] = left[i];
            i++;
            k++;
        } else {
            array[k] = right[j];
            j++;
            k++;
        }
    }
    while(i < mid){
        array[k] = left[i];
        i++;
        k++;
    }
    while(j < size - mid){
        array[k] = right[j];
        j++;
        k++;
    }
    free(left);
    free(right);
}

void quick_sort_array(int* array, int size){
    if(size < 2){
        return;
    }
    int pivot = array[(int)floor((double)size / 2)];
    int* left = (int*)malloc(size * sizeof(int));
    int* right = (int*)malloc(size * sizeof(int));
    int left_count = 0;
    int right_count = 0;
    for(int i = 0; i < size; i++){
        if(array[i] < pivot){
            left[left_count] = array[i];
            left_count++;
        } else
        if(array[i] > pivot){
            right[right_count] = array[i];
            right_count++;
        }
    }
    for(int i = 0; i < size; i++){
        if(array[i] == pivot){
            if(left_count < right_count){
            left[left_count] = pivot;
            left_count++;
        } else {
            right[right_count] = pivot;
            right_count++;
        }
        }
    }
    print_string("Pivot: ");
    print_int(pivot);
    print_newline();
    print_string("Left: ");
    for(int i = 0; i < left_count; i++){
        print_int(left[i]);
        print_string(" ");
    }
    print_newline();
    print_string("Right: ");
    for(int i = 0; i < right_count; i++){
        print_int(right[i]);
        print_string(" ");
    }
    print_newline();
    quick_sort_array(left, left_count);
    quick_sort_array(right, right_count);
    for(int i = 0; i < left_count; i++){
        array[i] = left[i];
    }
    for(int i = 0; i < right_count; i++){
        array[left_count + i] = right[i];
    }
    free(left);
    free(right);
}
