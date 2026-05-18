#include <stdio.h>
#include "uarte-commands.h"
#include "linked-list.h"
#include "sorting-algorithm.h"
#include "randomization.h"

int main(){
    create_random_seed();

    int test_array_random[5];
    const int test_array_size = 5;
    randomize_array(test_array_random, test_array_size, 0, 100);
    print_string("Testing is_sorted_array with a random array (1 = success, 0 = failure): ");
    print_int(is_sorted_array(test_array_random, test_array_size));
    print_newline();
    print_string("Random array: ");
    for(int i = 0; i < test_array_size; i++){
        print_int(test_array_random[i]);
        print_string(" ");
    }
    print_newline();

    List test_list_random;
    initList(&test_list_random);
    randomize_list(&test_list_random, test_array_size, 0, 100);
    print_string("Testing is_sorted_list with a random list (1 = success, 0 = failure): ");
    print_int(is_sorted_list(&test_list_random));
    print_newline();
    print_string("Random list: ");
    for(int i = 0; i < test_array_size; i++){
        print_int(get(&test_list_random, i));
        print_string(" ");
    }
    print_newline();

    print_string("Sorting the random list...\n");
    bubble_sort_list(&test_list_random);
    print_string("Testing is_sorted_list with the sorted list (1 = success, 0 = failure): ");
    print_int(is_sorted_list(&test_list_random));
    print_newline();
    for(int i = 0; i < test_array_size; i++){
        print_int(get(&test_list_random, i));
        print_string(" ");
    }
    print_newline();

    print_string("Sorting the random array...\n");
    merge_sort_array(test_array_random, test_array_size);
    print_string("Testing is_sorted_array with the sorted array (1 = success, 0 = failure): ");
    print_int(is_sorted_array(test_array_random, test_array_size));
    print_newline();
    print_string("Sorted array: ");
    for(int i = 0; i < test_array_size; i++){
        print_int(test_array_random[i]);
        print_string(" ");
    }
    print_newline();

    return 0;
}