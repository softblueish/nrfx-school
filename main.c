#include <stdio.h>
#include "hashtable.h"
#include "uarte-commands.h"

int main(){
    HashTable ht;
    initTable(&ht);
    insert(&ht, 1, "One");
    insert(&ht, 11, "Eleven");
    printTable(&ht);
    printf("Key 1: %s\n", get(&ht, 1));
    printf("Key 11: %s\n", get(&ht, 11));
    printf("Removing key 1: %d\n", removeKey(&ht, 1));
    printf("Key 1 after removal: %s\n", get(&ht, 1));
    printTable(&ht);
    return 0;
}