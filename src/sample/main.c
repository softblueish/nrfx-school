#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <nrfx_uarte.h>
#include <nrfx_rtc.h>
#include <stdlib.h>
#include <stdio.h>
#include "uarte-commands.h"
#include "linked-list.h"
#include "sorting-algorithm.h"
#include "randomization.h"


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

#define BUTTON1 (23)
#define BUTTON2 (24)
#define BUTTON3 (8)
#define BUTTON4 (9)

const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);

int main(void){
    init_uarte();
    nrfx_systick_init();
    clear_screen();
    
    nrfx_rtc_config_t rtc_config = NRFX_RTC_DEFAULT_CONFIG;
    nrfx_rtc_init(&rtc_instance, &rtc_config, NULL);
    nrfx_rtc_enable(&rtc_instance);

    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);

    // Generate a seed
    print_string("Press a button to initialize randomization.");
    print_newline();
    while(0){
        if(!nrf_gpio_pin_read(BUTTON1) || !nrf_gpio_pin_read(BUTTON2) || !nrf_gpio_pin_read(BUTTON3) || !nrf_gpio_pin_read(BUTTON4)){
            srand(nrfx_rtc_counter_get(&rtc_instance));
            break;
        }
    }


    // Test bubble sort
    int sizes[6] = {8, 64, 200, 256, 400, 512};
    for(int i = 0; i < 6; i++) {
        List list;
        initList(&list);
        randomize_list(&list, sizes[i], 0, 100);
        print_string("List created for size ");
        print_int(sizes[i]);
        print_string(" (ints).");
        print_newline();
        print_string("Sorting through bubble sort...");
        nrf_systick_val_clear();
        long unsigned int pretime = nrf_systick_val_get();
        bubble_sort_list(&list);
        long unsigned int posttime = nrf_systick_val_get();
        print_string(" Done!");
        print_newline();
        print_string("Took ");
        print_int(pretime-posttime);
        print_string(" ticks! ");
        if(is_sorted_list(&list)){
            print_string("... and it's sorted! ");
        } else {
            print_string("... and it's NOT sorted! ");
        }
        print_newline();
    }

    /*for(int i = 0; i < 4; i++) {
        int *array = malloc((int)sizes[i]*sizeof(int));
        randomize_array(array, sizes[i], 0, 100);
        print_string("Array created for size ");
        print_int(sizes[i]);
        print_string(" (ints).");
        print_newline();
        print_string("Sorting through merge sort...");
        nrf_systick_val_clear();
        long unsigned int pretime = nrf_systick_val_get();
        merge_sort_array(array, sizes[i]);
        long unsigned int posttime = nrf_systick_val_get();
        print_string(" Done!");
        print_newline();
        print_string("Took ");
        print_int(pretime-posttime);
        print_string(" ticks! ");
        if(is_sorted_array(array, sizes[i])){
            print_string("... and it's sorted! ");
        } else {
            print_string("... and it's NOT sorted! ");
        }
        print_newline();
        free(array);
    }

    for(int i = 0; i < 4; i++) {
        int *array = malloc((int)sizes[i]*sizeof(int));
        randomize_array(array, sizes[i], 0, 100);
        print_string("Array created for size ");
        print_int(sizes[i]);
        print_string(" (ints).");
        print_newline();
        print_string("Sorting through quick sort...");
        nrf_systick_val_clear();
        long unsigned int pretime = nrf_systick_val_get();
        quick_sort_array(array, sizes[i]);
        long unsigned int posttime = nrf_systick_val_get();
        print_string(" Done!");
        print_newline();
        print_string("Took ");
        print_int(pretime-posttime);
        print_string(" ticks! ");
        if(is_sorted_array(array, sizes[i])){
            print_string("... and it's sorted! ");
        } else {
            print_string("... and it's NOT sorted! ");
        }
        print_newline();
        free(array);
    }*/

    print_string("Program finished.");
    print_newline();

    return 0;
}
