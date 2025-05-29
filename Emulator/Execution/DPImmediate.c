//
// Created by zackf on 29/05/2025.
//

#include "DPImmediate.h"

enum EXECUTE_FLAGS add(
    struct System *sys,
    enum Register rd,
    enum Register rn,
    int32_t imm12,
    int32_t sf,
    int64_t mask
    ) { // add

    int64_t rnValue = 0;
    if(!rReg(sys, sf, rn, &rnValue)) {
        return EXECUTE_FAILURE;
    }
    int64_t result = (rnValue + imm12) & mask;
    if(!wReg(sys, sf, rd, result)) {
        return EXECUTE_FAILURE;
    }

    return EXECUTE_SUCCESS;
}

enum EXECUTE_FLAGS adds(
    struct System *sys,
    enum Register rd,
    enum Register rn,
    int32_t imm12,
    int32_t sf,
    int64_t mask
    ) { // adds

    int64_t rnValue = 0;
    if(!rReg(sys, sf, rn, &rnValue)) {
        return EXECUTE_FAILURE;
    }
    int64_t result = (rnValue + imm12) & mask;
    if(!wReg(sys, sf, rd, result)) {
        return EXECUTE_FAILURE;
    }

    // setting N register
    if(result < 0 ) {
        sys->regStore.pstate.n = true;
    } else {
        sys->regStore.pstate.n = false;
    }

    // setting Z register
    if(result == 0) {
        sys->regStore.pstate.z = true;
    } else {
        sys->regStore.pstate.z = false;
    }

    // setting C register
    if(result < rnValue || (!sf && result > INT32_MAX)) {
        //    ^ 64 bit overflow           ^ 32 bit overflow
        sys->regStore.pstate.c = true;
    } else {
        sys->regStore.pstate.c = false;
    }

    if(sys->regStore.pstate.c) {
        // can addition cause a signed underflow when at least one is positive??
        sys->regStore.pstate.v = true;
    } else {
        sys->regStore.pstate.v = false;
    }

    return EXECUTE_SUCCESS;
}

enum EXECUTE_FLAGS sub(
    struct System *sys,
    enum Register rd,
    enum Register rn,
    int32_t imm12,
    int32_t sf,
    int64_t mask
    ) {

    int64_t rnValue = 0;
    if(!rReg(sys, sf, rn, &rnValue)) {
        return EXECUTE_FAILURE;
    }
    int64_t result = (rnValue - imm12) & mask;
    if(!wReg(sys, sf, rd, result)) {
        return EXECUTE_FAILURE;
    }

    return EXECUTE_SUCCESS;
}

enum EXECUTE_FLAGS subs(
    struct System *sys,
    enum Register rd,
    enum Register rn,
    int32_t imm12,
    int32_t sf,
    int64_t mask
    ) { // subs

    int64_t rnValue = 0;
    if(!rReg(sys, sf, rn, &rnValue)) {
        return EXECUTE_FAILURE;
    }
    int64_t result = (rnValue + imm12) & mask ;
    if(!wReg(sys, sf, rd, result)) {
        return EXECUTE_FAILURE;
    }

    // setting N register
    if(result < 0 ) {
        sys->regStore.pstate.n = true;
    } else {
        sys->regStore.pstate.n = false;
    }

    // setting Z register
    if(result == 0) {
        sys->regStore.pstate.z = true;
    } else {
        sys->regStore.pstate.z = false;
    }

    // setting C register
    if(result > rnValue || (!sf && result < INT32_MIN)) {
        //    ^ 64 bit underflow          ^ 32 bit underflow
        sys->regStore.pstate.c = true;
    } else {
        sys->regStore.pstate.c = false;
    }

    if(sys->regStore.pstate.c) {
        // can subtraction cause a signed overflow flow when the subtractand is positive??
        sys->regStore.pstate.v = true;
    } else {
        sys->regStore.pstate.v = false;
    }

    return EXECUTE_SUCCESS;
}

enum EXECUTE_FLAGS movn(struct System *sys, enum Register rd, int32_t hw, int32_t imm16, int32_t sf, int64_t mask) {
    int64_t result = (imm16 << (hw * 16)) & mask ;
    if(!sf && hw > 1) {
        printf("Not allowed this value of hw in 32 bits");
    }

    if(!wReg(sys, sf, rd, ~result)) {
        return EXECUTE_FAILURE;
    }

    return EXECUTE_SUCCESS;
}

enum EXECUTE_FLAGS movz(struct System *sys, enum Register rd, int32_t hw, int32_t imm16, int32_t sf, int64_t mask) {
    int64_t result = (imm16 << (hw * 16)) & mask ;
    if(!sf && hw > 1) {
        printf("Not allowed this value of hw in 32 bits");
    }

    if(!wReg(sys, sf, rd, result)) {
        return EXECUTE_FAILURE;
    }

    return EXECUTE_SUCCESS;
}

enum EXECUTE_FLAGS movk(struct System *sys, enum Register rd, int32_t hw, int32_t imm16, int32_t sf, int64_t mask) {
    int64_t rdValue = 0;
    if(!rReg(sys, sf, rd, &rdValue)) {
        return EXECUTE_FAILURE;
    }
    int64_t result = ((rdValue & ~((int64_t) 0xFFFFFFFF << hw*16)) | (imm16 << hw*16)) & mask ;
    if(!wReg(sys, sf, rd, result)) {
        return EXECUTE_FAILURE;
    }

    return EXECUTE_SUCCESS;
}
