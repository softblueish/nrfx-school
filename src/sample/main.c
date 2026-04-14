#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <nrfx_uarte.h>

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

#define LED1 (28)
#define LED2 (29)
#define LED3 (30)
#define LED4 (31)
#define BUTTON1 (23)
#define BUTTON2 (24)
#define BUTTON3 (8)
#define BUTTON4 (9)

void getButtonState(int outputState[]){
    outputState[0] = !nrf_gpio_pin_read(BUTTON1);
    outputState[1] = !nrf_gpio_pin_read(BUTTON2);
    outputState[2] = !nrf_gpio_pin_read(BUTTON3);
    outputState[3] = !nrf_gpio_pin_read(BUTTON4);
}

void updateLEDState(int inputState[]){
    nrf_gpio_pin_write(LED1, !inputState[0]);
    nrf_gpio_pin_write(LED2, !inputState[1]);
    nrf_gpio_pin_write(LED3, !inputState[2]);
    nrf_gpio_pin_write(LED4, !inputState[3]);
}

int main(void){
    int pastButtonState[4] = {0, 0, 0, 0,};
    int currentButtonState[4] = {0, 0, 0, 0};
    int LEDstate[4] = {0, 0, 0, 0};

    // Set I/O
    nrf_gpio_cfg_output(LED1);
    nrf_gpio_cfg_output(LED2);
    nrf_gpio_cfg_output(LED3);
    nrf_gpio_cfg_output(LED4);
    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);

    // Set LEDs to off
    nrf_gpio_pin_write(LED1, 1);
    nrf_gpio_pin_write(LED2, 1);
    nrf_gpio_pin_write(LED3, 1);
    nrf_gpio_pin_write(LED4, 1);
    
    while(1){
        getButtonState(currentButtonState);
        for(int i = 0; i < 4; i++){
            if(currentButtonState[i] != pastButtonState[i] && currentButtonState[i] == 1){
                LEDstate[i] = !LEDstate[i];
            }
        }
        updateLEDState(LEDstate);
        for(int i = 0; i < 4; i++){
            pastButtonState[i] = currentButtonState[i];
        }
    }
}
