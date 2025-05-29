//
// Created by kavyas on 24/05/2025.
//

#include "Processor.h"

enum REGISTER_FLAGS rReg(struct System * sys, enum AccessType aType, enum Register reg, int64_t * result) {
    int64_t mask;

    if(aType == W) {
        mask = 0x00000000FFFFFFFF;
    } else {
        mask = 0xFFFFFFFFFFFFFFFF;
    }

    if(reg == ZR) {
        * result = 0 & mask;
    } else if(reg >= 0 && reg < 31) {
        * result = (sys->regStore.gReg[reg] & mask);
    } else {
        printf("Invalid Register:%" PRId32 "\n", reg);
        return REGISTER_NOT_VALID;
    }

    return REGISTER_SUCCESS;
}

enum REGISTER_FLAGS wReg(struct System * sys, enum AccessType aType, enum Register reg, int64_t newVal) {
    int64_t mask;

    if(aType == W) {
        mask = 0x0000FFFF;
    } else {
        mask = 0xFFFFFFFF;
    }

    if(newVal & mask != newVal) {
        return WRITING_64_TO_32;
    }

    if(reg == ZR) {
        // writes to ZR are ignored
    } else if(reg >= 0 && reg < 31) {
        sys->regStore.gReg[reg] = newVal;
    } else {
        printf("Invalid Register:%" PRId32 "\n", reg);
        return REGISTER_NOT_VALID;
    }
    return REGISTER_SUCCESS;
}

enum MEMORY_FLAGS rMem(struct System * sys, int32_t address, int64_t * value) {
    *value = __bswap_64(*(int64_t *) (sys->memory + address)); // (*sys).memory
    return MEMORY_SUCCESS;
}

enum MEMORY_FLAGS wMem(struct System * sys, int32_t address, int64_t * value) {
    *(int64_t *) (sys->memory + address) = __bswap_64(*value);
    return MEMORY_SUCCESS;
}

enum MEMORY_FLAGS fetchInstruction(struct System * sys, int32_t address, int32_t * instr) {
    *instr = __bswap_32(*(int32_t * )(sys->memory + address));
    return MEMORY_SUCCESS;
}


int8_t * constructMemory() {
    int8_t * memPointer = malloc(MEMORY_SIZE);
    memset(memPointer, 0, MEMORY_SIZE);
    return memPointer;
}
