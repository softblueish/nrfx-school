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

#define BUTTON1 (23)
#define BUTTON2 (24)
#define BUTTON3 (8)
#define BUTTON4 (9)

nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

const nrfx_rtc_t rtc = NRFX_RTC_INSTANCE(0);

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
    nrfx_uarte_init(&instance, &config, NULL);
    nrfx_rtc_config_t rtc_config = NRFX_RTC_DEFAULT_CONFIG;
    nrfx_rtc_init(&rtc_instance, &rtc_config, NULL);
    nrfx_rtc_enable(&rtc_instance);

    char clearScreen[] = CLEAR_SCREEN;
    nrfx_uarte_tx(&instance, &clearScreen, sizeof(clearScreen), 0);
    char msg1[] = "Program started, please press any button to generate a random number.\r\n";
    print_string(msg1);
    
}
