#include "uarte-commands.h"

#define PIN_TXD 20
#define PIN_RXD 22

nrfx_uarte_t saved_instance;

nrfx_uarte_t get_uarte(){
    return saved_instance;
}

nrfx_uarte_t init_uarte(){
    nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);
    nrfx_uarte_init(&instance, &config, NULL);
    saved_instance = instance;
    return instance;
}

void print_string(char* message){
    char input[256];
    strcat(input, message);
    for(int i = 0; input[i] != '\0'; i++)
        nrfx_uarte_tx(&saved_instance, &input[i], sizeof(input[i]), 0);
}

void print_int(int input){
    char msg[100];
    sprintf(msg, "%d\0", input);
    for(int i = 0; msg[i] != '\0'; i++)
        nrfx_uarte_tx(&saved_instance, &msg[i], sizeof(msg[i]), 0);
}

void read_int(int* output){
    char buffer[100];
    for(int i = 0; i < 100; i++){
        nrfx_uarte_rx(&saved_instance, &buffer[i], sizeof(buffer[i]));
        if(buffer[i] == '\r'){
            buffer[i] = '\0';
            break;
        }
    }
    *output = atoi(buffer);
}