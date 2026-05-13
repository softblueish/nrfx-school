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

#define LED1 (28)
#define LED2 (29)
#define LED3 (30)
#define LED4 (31)
#define BUTTON1 (23)
#define BUTTON2 (24)
#define BUTTON3 (8)
#define BUTTON4 (9)
#define LED_ON 0
#define LED_OFF 1

const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);

const int LED[] = {LED1, LED2, LED3, LED4};

int main(void){
    int srandUsed = 0;
    init_uarte();
    nrfx_rtc_config_t rtc_config = NRFX_RTC_DEFAULT_CONFIG;
    nrfx_rtc_init(&rtc_instance, &rtc_config, NULL);
    nrfx_rtc_enable(&rtc_instance);
    nrfx_systick_init();

    nrf_gpio_cfg_output(LED1);
    nrf_gpio_cfg_output(LED2);
    nrf_gpio_cfg_output(LED3);
    nrf_gpio_cfg_output(LED4);
    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);

    clear_screen();
    print_string("Program started, please press any button to initialize the program.\r\n");
    
    for(int i = 0 ; i < 4; i++)
        nrf_gpio_pin_write(LED[i], LED_OFF);
    while(1){
        if(!nrf_gpio_pin_read(BUTTON1) || !nrf_gpio_pin_read(BUTTON2) || !nrf_gpio_pin_read(BUTTON3) || !nrf_gpio_pin_read(BUTTON4)){
            if(!srandUsed){
                srand(nrfx_rtc_counter_get(&rtc_instance));
                srandUsed = 1;
                break;
            }
        }
    }
    print_string("Program initialized with a seed value.\r\n");
    while(1){
        int amount = 0;
        int delay = 0;
        print_string("Enter an amount: ");
        read_int(&amount);
        print_newline();
        print_string("Enter a delay: ");
        read_int(&delay);
        print_newline();
        print_string("Executing program, it'll take ~");
        print_int(amount * delay);
        print_string("ms\r\n");
        for(int i = 0; i < amount; i++){
            int selected_led = rand() % 4;
            nrf_gpio_pin_write(LED[selected_led], LED_ON);
            nrfx_systick_delay_ms(delay);
            nrf_gpio_pin_write(LED[selected_led], LED_OFF);
        }
    }
}
