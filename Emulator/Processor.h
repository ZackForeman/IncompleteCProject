//
// Created by zackf on 24/05/2025.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H

#define MEMORY_SIZE (2 << 20)

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

struct Pstate {
    bool n; // N
    bool z; // Z
    bool c; // C
    bool v; // V
};

struct RegStore {
    int64_t gReg[31];
    int64_t zr;
    int64_t pc;
    struct Pstate pstate;
};

enum Register {
    ZR = 31, // 11111
};

enum AccessType {
    W, // 32 bit
    X, // 64 bit
};

struct System {
    struct RegStore regStore;
    int8_t * memory;
};

enum REGISTER_FLAGS {
    REGISTER_SUCCESS, // 0 falsy
    REGISTER_NOT_VALID, // 1 truthy
    WRITING_64_TO_32, // 2 truthy
};

enum MEMORY_FLAGS {
    MEMORY_SUCCESS,
    MEMORY_OUT_OF_BOUNDS,
};

extern enum REGISTER_FLAGS rReg(struct System * sys, enum AccessType aType, enum Register reg, int64_t * result);
extern enum REGISTER_FLAGS wReg(struct System * sys, enum AccessType aType, enum Register reg, int64_t   newVal);
extern enum MEMORY_FLAGS rMem(struct System * sys, int32_t address, int64_t * value);
extern enum MEMORY_FLAGS wMem(struct System * sys, int32_t address, int64_t * value);
extern enum MEMORY_FLAGS fetchInstruction(struct System * sys, int32_t address, int32_t * instr);

extern int8_t * constructMemory();

#endif //PROCESSOR_H
