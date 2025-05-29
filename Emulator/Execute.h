//
// Created by zackf on 26/05/2025.
//

#ifndef EXECUTE_H
#define EXECUTE_H

#include "Decode.h"
#include "Processor.h"
#include "Execution/DPImmediate.h"

enum EXECUTE_FLAGS {
    EXECUTE_SUCCESS,
    EXECUTE_FAILURE,
};

extern enum EXECUTE_FLAGS executeInstruction(struct System * sys, struct DecodedInstruction * instr);

#endif //EXECUTE_H
