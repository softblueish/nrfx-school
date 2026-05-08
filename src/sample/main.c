#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <math.h>
#include <nrfx_uarte.h>
#include "hashtable.h"
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
    nrfx_systick_init();
    clear_screen();
    HashTable ht;
    int keys1[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    char values[10][20] = {"meow1", "meow2", "meow3", "meow4", "meow5", "meow6", "meow7", "meow8", "meow9", "meow10"};
    print_string("Creating a perfect hashtable...");
    for(int i = 0; i < 10; i++){
        insert(&ht, keys1[i], values[i]);
    }
    print_newline();
    print_string("Done!");
    print_newline();
    print_string("Measuring the amount of ticks it takes to find three elements selected by the programmer (first, fifth and last)...");
    int searchValues1[3] = {10, 14, 19};
    for(int i = 0; i < 3; i++){
        nrf_systick_val_clear();
        long unsigned pretime = nrf_systick_val_get();
        get(&ht, searchValues1[i]);
        long unsigned posttime = nrf_systick_val_get();
        print_newline();
        print_string("Found the "); 
        print_int(i);
        print_string("# value after ");
        print_int(pretime - posttime);
        print_string(" ticks!");
    }
    print_newline();
    
    int keys2[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    print_string("Creating a perfectly non-ideal hashtable...");
    for(int i = 0; i < 10; i++){
        insert(&ht, keys2[i], values[i]);
    }
    print_newline();
    print_string("Done!");
    print_newline();
    print_string("Measuring the amount of ticks it takes to find three elements selected by the programmer (first, fifth and last)...");
    for(int i = 0; i < 3; i++){
        nrf_systick_val_clear();
        long unsigned pretime = nrf_systick_val_get();
        get(&ht, searchValues1[i]);
        long unsigned posttime = nrf_systick_val_get();
        print_newline();
        print_string("Found the "); 
        print_int(i);
        print_string("# value after ");
        print_int(pretime - posttime);
        print_string(" ticks!");
    }
}
