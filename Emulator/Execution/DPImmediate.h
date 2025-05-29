//
// Created by zackf on 29/05/2025.
//

#ifndef DPIMMEDIATE_H
#define DPIMMEDIATE_H

#include "../Execute.h"
#include "../Processor.h"

extern enum EXECUTE_FLAGS add(struct System *sys, enum Register rd, enum Register rn, int32_t imm12, int32_t sf, int64_t mask);
extern enum EXECUTE_FLAGS adds(struct System *sys, enum Register rd, enum Register rn, int32_t imm12, int32_t sf, int64_t mask);
extern enum EXECUTE_FLAGS sub(struct System *sys, enum Register rd, enum Register rn, int32_t imm12, int32_t sf, int64_t mask);
extern enum EXECUTE_FLAGS subs(struct System *sys, enum Register rd, enum Register rn, int32_t imm12, int32_t sf, int64_t mask);

extern enum EXECUTE_FLAGS movn(struct System *sys, enum Register rd, int32_t hw, int32_t imm16, int32_t sf, int64_t mask);
extern enum EXECUTE_FLAGS movz(struct System *sys, enum Register rd, int32_t hw, int32_t imm16, int32_t sf, int64_t mask);
extern enum EXECUTE_FLAGS movk(struct System *sys, enum Register rd, int32_t hw, int32_t imm16, int32_t sf, int64_t mask);

#endif //DPIMMEDIATE_H
