#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <stdio.h>

nrfx_uarte_t get_uarte();

nrfx_uarte_t init_uarte();

void read_int(int* output);

void print_string(char* message);

void print_int(int input);