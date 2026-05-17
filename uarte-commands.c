#include "uarte-commands.h"

// Testing version of uarte-commands.c, which just uses standard input and output instead of the actual uarte commands. This is to make it easier to test the BSTree implementation on a regular computer without needing to flash it to the microcontroller.

#define PIN_TXD 20
#define PIN_RXD 22

void get_uarte(){
    return;
}

void init_uarte(){
    return;
}

void print_string(char* message){
    printf("%s", message);
}

void print_int(int input){
    printf("%d", input);
}

void print_newline(){
    printf("\n");
}

void read_int(int* output){
    char buffer[100];
    scanf("%s", buffer);
    *output = atoi(buffer);
}