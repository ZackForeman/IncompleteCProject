//
// Created by zackf on 24/05/2025.
//


#include "Processor.h"

int main(void) {
    // Allocate 2MB of Memory on the Heap
    int8_t * memory = constructMemory();


    free(memory);
    return 0;
}
