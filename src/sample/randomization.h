#ifndef RANDOMIZATION_
#define RANDOMIZATION_
#include <stdlib.h>
#include <time.h>
#include "linked-list.h"
#include "sorting-algorithm.h"


void create_random_seed();

void randomize_array(int* array, int size, int min, int max);

void randomize_list(List* list, int size, int min, int max);
#endif