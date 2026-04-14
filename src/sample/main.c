#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <stdio.h>

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

#define PIN_TXD 20
#define PIN_RXD 22
#define CLEAR_SCREEN "\033c"

nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

void read_int(int* output, int lengthCieling){
    char buffer[lengthCieling];
    for(int i = 0; i < lengthCieling; i++){
        nrfx_uarte_rx(&instance, &buffer[i], sizeof(buffer[i]));
        if(buffer[i] == '\r'){
            buffer[i] = '\0';
            break;
        }
    }
    *output = atoi(buffer);
}

void print_string(char* input){
    for(int i = 0; input[i] != '\0'; i++)
        nrfx_uarte_tx(&instance, &input[i], sizeof(input[i]), 0);
}

void send_int(int input){
    char buffer[15]; // UINT_MAX < 10^15
    sprintf(buffer, "%d", input);
    print_string(buffer);
}

int main(void){
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);
    nrfx_systick_init();
    nrfx_uarte_init(&instance, &config, NULL);
    char clearScreen[] = CLEAR_SCREEN;
    nrfx_uarte_tx(&instance, &clearScreen, sizeof(clearScreen), 0);
    char msg1[] = "Program started, please write the wait time as an integer.\r\n";
    print_string(msg1);
    int input1;
    read_int(&input1, 100);
    if(input1 > 15) {
        char msg[] = "\r\nWait time too long (> 15). Skipping wait.\r\n";
        print_string(msg);
        input1 = 0;
    }
    else {
        char msg2[] = "\r\nWaiting for ";
        print_string(msg2);
        send_int(input1);
        char msg3[] = " seconds...\r\n";
        print_string(msg3);
    }
    nrfx_systick_delay_ms(input1 * 1000);
    char msg4[] = "Done! Program ended.";
    print_string(msg4);
}
