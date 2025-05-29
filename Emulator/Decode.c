//
// Created by zackf on 25/05/2025.
//

#include "Decode.h"

int32_t maskRange(int32_t val, int32_t start, int32_t end) {
    const int64_t mask = (1 << start - end + 1) - 1 << end;
    return (val & (int32_t) mask ) >> end;
}

enum DECODE_FLAGS decodeInstruction(int32_t in, struct DecodedInstruction * out) {
    // first check what type of instruction
    int32_t op0 = maskRange(in, 28, 25);
    if((op0 & 0xE) == 0x8) { // 100x
        // Data Processing (Immediate)
        out->instrType = DPImm;
        out->instr.dp_imm_instr = (struct DPImmInstr) {
            .sf = maskRange(in, 31, 31),
            .opc = maskRange(in, 30, 29),
            .opi = maskRange(in, 25, 23),
            .operand = maskRange(in, 22, 5),
            .rd = maskRange(in, 4 ,0),
        };
    } else if ((op0 & 0x7) == 0x5) { // x101
        // Data Processing (Register)
        out->instrType = DPReg;
        out->instr.dp_reg_instr = (struct DPRegInstr) {
            .sf = maskRange(in, 31, 31),
            .opc = maskRange(in, 30, 29),
            .M = maskRange(in, 28, 28),
            .opr = maskRange(in, 24, 21),
            .rm = maskRange(in, 20, 16),
            .operand = maskRange(in, 15, 10),
            .rn = maskRange(in, 9, 5),
            .rd = maskRange(in, 4, 0),
        };
    } else if ((op0 & 0x5) == 0x4) { // x1x0
        // Loads and Stores
        if(maskRange(in, 29, 29)) {
            out->instrType = SDT;
            out->instr.sdt_instr = (struct SDTInstr) {
                .sf = maskRange(in,1,1),
                .L = maskRange(in, 22, 22),
                .offset = maskRange(in, 21, 10),
                .xn = maskRange(in, 9,5),
                .rt = maskRange(in, 4, 0),
            };
        } else {
            out->instrType = LDLit;
            out->instr.ld_lit_instr = (struct LdLitInstr) {
                .sf = maskRange(in, 30, 30),
                .simm19 = maskRange(in, 23, 5),
                .rt = maskRange(in, 4, 0),
            };
        }
    } else if ((op0 & 0xE) == 0xA) { // 101x
        // Branches
        out->instrType = Brnch;
        out->instr.branch_instr = (struct BranchInstr) {
            .operand = maskRange(in, 32, 0)
        };
    } else {
        printf("Invalid Register:%" PRId32 "\n", in);
        return UNKNOWN_INSTRUCTION;
    }

    return DECODE_SUCCESS;

}