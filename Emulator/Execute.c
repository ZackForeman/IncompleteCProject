//
// Created by zackf on 26/05/2025.
//

#include "Execute.h"

enum EXECUTE_FLAGS executeDPImm(struct System * sys, struct DPImmInstr instr) {
    // rd destination register 11111 encodes zero register
    // sf bit width of all the registers 0 -> 32, 1 -> 64
    // opc operation code
    // operand the value to be saved into Rd
    // opi type of data processing operation 010 -> arithmetic, 101 wide move

    if(instr.opi == 0x2) { // 010
        int32_t sh = maskInstruction(instr.operand, 22, 22);
        // I know this is supposed to be unsigned but it will fit in the range with the same bit pattern so should be fine
        int32_t imm12 = maskInstruction(instr.operand, 21, 10);
        int32_t rn = maskInstruction(instr.operand, 9, 5);
        int64_t mask;
        if(instr.sf) {
            mask = 0xFFFFFFFFFFFFFFFF;
        } else {
            mask = 0x00000000FFFFFFFF;
        }

        if(sh) {
            imm12 = imm12 << 12;
        }

        if(instr.opc == 0) { // add
            return add(sys, instr.rd, rn, imm12, instr.sf, mask);
        }

        if(instr.opc == 1) { // adds
            return adds(sys, instr.rd, rn, imm12, instr.sf, mask);
        }

        if(instr.opc == 2) {

        }

        if(instr.opc == 3) {

        }


    } else if(instr.opi == 0x5) { // 101

    } else {
        return UNHANDLED_CASE;
    }

    return EXECUTE_SUCCESS;
}


enum EXECUTE_FLAGS executeInstruction(struct System * sys, struct DecodedInstruction * instr) {
    switch (instr->instrType) {
        case DPImm:

            break;
        case DPReg:

            break;
        case SDT:

            break;
        case LDLit:

            break;
        case Brnch:

            break;
        default:
            return UNHANDLED_CASE;
            break;
    }

    return EXECUTE_SUCCESS;
}
