#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
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

int main(void){
    init_uarte();
    clear_screen();
    BSTree tree = create_empty_tree();
    insert_sorted(&tree, 1);
    insert_sorted(&tree, 2);
    insert_sorted(&tree, 3);
    insert_sorted(&tree, 4);
    insert_sorted(&tree, 5);
    insert_sorted(&tree, 6);
    insert_sorted(&tree, 7);
    print_string("Preorder: ");
    print_preorder(tree);
    print_newline();
    print_string("Depth: ");
    print_int(depth(tree));
    print_newline();
    print_string("Min Depth: ");
    print_int(min_depth(tree));
    print_newline();
    balance_tree(&tree);
    print_string("Preorder: ");
    print_preorder(tree);
    print_newline();
    print_string("Depth: ");
    print_int(depth(tree));
    print_newline();
    print_string("Min Depth: ");
    print_int(min_depth(tree));
    print_newline();
}
