#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <nrfx_uarte.h>

// Serial port 115200

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

void read_string(char* output, int lengthCieling){
    for(int i = 0; i < lengthCieling; i++){
        nrfx_uarte_rx(&instance, &output[i], sizeof(output[i]));
        if(output[i] == '\r'){
            output[i] = '\0';
            break;
        }
    }
}

void print_string(char* input){
    for(int i = 0; input[i] != '\0'; i++)
        nrfx_uarte_tx(&instance, &input[i], sizeof(input[i]), 0);
}

int main(void){
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);
    nrfx_uarte_init(&instance, &config, NULL);
    char clearScreen[] = CLEAR_SCREEN;
    nrfx_uarte_tx(&instance, &clearScreen, sizeof(clearScreen), 0);
    char msg1[100] = "Program started\r\n";
    print_string(msg1);
    char input1[100];
    read_string(input1, 100);
    char msg2[100] = "\r\nProgram ended with string ";
    print_string(msg2);
    print_string(input1);
}
