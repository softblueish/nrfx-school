/*#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <nrfx_uarte.h>*/

#include "list.h"

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
    // Test a list
    List list = create_empty_list();
    while(1) {
        int command;
        printf("Enter command (int): ");
        scanf("%d", &command);
        switch(command) {
            case 1: {
                int data;
                printf("Enter data to add first (int): ");
                scanf("%d", &data);
                add_first(&list, data);
                break;
            }
            case 2: {
                int data;
                printf("Enter data to add last (int): ");
                scanf("%d", &data);
                add_last(&list, data);
                break;
            }
            case 3:
                remove_first(&list);
                break;
            case 4:
                remove_last(&list);
                break;
            case 5:
                print_list(list);
                break;
            case 6: {
                int data;
                printf("Enter data to search for (int): ");
                scanf("%d", &data);
                if(search(list, data)) {
                    printf("Data found in list.\n");
                } else {
                    printf("Data not found in list.\n");
                }
                break;
            }
            case 7:
                printf("First element: %d\n", get_first_element(list));
                break;
            case 8:
                printf("Last element: %d\n", get_last_element(list));
                break;
            case 9:
                printf("Number of nodes: %d\n", number_of_nodes(list));
                break;
            default:
                printf("Invalid command.\n");
        }
    }
}
