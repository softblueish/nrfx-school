#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <math.h>
#include <nrfx_uarte.h>
#include "BSTree.h"
#include "uarte-commands.h"

// Serial communication 115200 baud

/*By Daniel Morberg*/
/*'Requires 'NRFX_SYSTICK_ENABLED 1' in nrfx_config_nrf5340_application.h and nrfx_systic.c included*/
/*Ni kan behöva köra en "make clean" efter ni inkluderat en ny .c fil. */

/*
From the NRF5340DK documentation:

Button 1    P0.23   i.e. 23
Button 2    P0.24
Button 3    P0.08
Button 4    P0.09
LED 1       P0.28   i.e. 28
LED 2       P0.29
LED 3       P0.30
LED 4       P0.31

*/

#define TEST_SIZE 6
const int tree_size[] = {3, 7, 15, 31, 63, 127};

int main(void){
    init_uarte();
    nrfx_systick_init();
    clear_screen();
    BSTree tree = create_empty_tree();
    int first = 0;
    int unbalanced_speed[TEST_SIZE] = {0, 0, 0, 0, 0, 0};
    print_string("Testing unbalanced trees of values ");
    for(int i = 0; i < TEST_SIZE; i++) {
        print_int(tree_size[i]);
        if(i != TEST_SIZE - 1)
            print_string(", ");
        else
            print_string(".");
    }
    print_newline();
    for(int i = 0; i < TEST_SIZE; i++) {
        print_string("Creating tree for tree size: ");
        print_int(tree_size[i]);
        print_newline();
        for(int j = 1; j <= tree_size[i]; j++) {
            insert_sorted(&tree, j);
        }
        print_string("Starting search for ");
        print_int(tree_size[i]);
        print_string(" in tree...");
        print_newline();
        nrf_systick_val_clear();
        unsigned int pretime = nrf_systick_val_get();
        find(tree, tree_size[i]);
        unsigned int posttime = nrf_systick_val_get();
        print_string("Value found after ");
        print_int((pretime - posttime));
        print_string(" ticks!");
        unbalanced_speed[i] = (pretime - posttime);
        if(first == 0)
        {
            first = (pretime - posttime);
        }
        else
        {
            print_string(" ... which is around ");
            print_int(ceil((pretime - posttime)/(double)first));
            print_string("x slower compared to the first (unbalanced) measurment.");
        }
        print_newline();
        free_tree(&tree);
    }
    print_newline();
    print_string("Testing balanced trees of values ");
    for(int i = 0; i < TEST_SIZE; i++) {
        print_int(tree_size[i]);
        if(i != TEST_SIZE - 1)
            print_string(", ");
        else
            print_string(".");
    }
    print_newline();
    first = 0;
    for(int i = 0; i < TEST_SIZE; i++) {
        print_string("Creating tree for tree size: ");
        print_int(tree_size[i]);
        print_newline();
        for(int j = 1; j <= tree_size[i]; j++) {
            insert_sorted(&tree, j);
        }
        print_string("Balancing tree...");
        print_newline();
        balance_tree(&tree);
        print_string("Starting search for ");
        print_int(tree_size[i]);
        print_string(" in tree...");
        print_newline();
        nrf_systick_val_clear();
        unsigned int pretime = nrf_systick_val_get();
        find(tree, tree_size[i]);
        unsigned int posttime = nrf_systick_val_get();
        print_string("Value found after ");
        print_int((pretime - posttime));
        print_string(" ticks!");
        if(first == 0)
        {
            first = (pretime - posttime);
            print_string(" ... which is around ");
            print_int((unbalanced_speed[i])/(int)(pretime - posttime));
            print_string("x faster than the unbalanced counterpart of the same tree.");
        }
        else
        {
            print_string(" ... which is around ");
            print_int(ceil((pretime - posttime)/(double)first));
            print_string("x slower compared to the first (balanced) measurment and ");
            print_int((unbalanced_speed[i])/(int)(pretime - posttime));
            print_string("x faster than the unbalanced counterpart of the same tree.");
        }
        print_newline();
        free_tree(&tree);
    }
    print_newline();
}
