#include "randomization.h"

void create_random_seed() { // Only works on PC sadly
    srand((unsigned int)time(NULL));
}

int get_random_number(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void randomize_array(int* array, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        array[i] = get_random_number(min, max);
    }
}

void randomize_list(List* list, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        insert(list, get_random_number(min, max));
    }
}