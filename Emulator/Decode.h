//
// Created by zackf on 25/05/2025.
//

#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

enum InstrTypes {
    DPImm,
    DPReg,
    SDT,
    LDLit,
    Brnch,
};

struct DPImmInstr {
    int32_t sf;
    int32_t opc;
    int32_t opi;
    int32_t operand;
    int32_t rd;
};

struct DPRegInstr {
    int32_t sf;
    int32_t opc;
    int32_t M;
    int32_t opr;
    int32_t rm;
    int32_t operand;
    int32_t rn;
    int32_t rd;
};

struct SDTInstr {
    int32_t sf;
    int32_t L;
    int32_t offset;
    int32_t xn;
    int32_t rt;
};

struct LdLitInstr {
    int32_t sf;
    int32_t simm19;
    int32_t rt;
};

struct BranchInstr {
    int32_t operand;
};

union decInstr {
    struct DPImmInstr dp_imm_instr;
    struct DPRegInstr dp_reg_instr;
    struct SDTInstr sdt_instr;
    struct LdLitInstr ld_lit_instr;
    struct BranchInstr branch_instr;
};

struct DecodedInstruction {
    enum InstrTypes instrType;
    union decInstr instr;
};

enum DECODE_FLAGS {
    DECODE_SUCCESS,
    UNKNOWN_INSTRUCTION,
    UNHANDLED_CASE,

};

extern int32_t maskRange(int32_t val, int32_t start, int32_t end);
extern enum DECODE_FLAGS decodeInstruction(int32_t in, struct DecodedInstruction * out);


#endif //DECODE_H
