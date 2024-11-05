#ifndef SPUSTRUCT_H
#define SPUSTRUCT_H

#include <stdlib.h>

enum ComandsValue {myau, Instruction_push, Instruction_pop, Instruction_in, Instruction_out,  Instruction_add, Instruction_subtr, Instruction_multipl, Instruction_div, Instruction_SQRT, Instruction_SIN, Instruction_COS, Instruction_stkdump, Instruction_hlt, Instruction_jmp, Instruction_ja, Instruction_jae, Instruction_jb, Instruction_jbe, Instruction_je, Instruction_jne, Instruction_sfudump, Instruction_lbldump, Instruction_call, Instruction_ret, Instruction_regdump, Instruction_ramdump, Instruction_codedump};
enum RegistersName {ax, bx, cx, dx, ex, fx, gx, hx, ix, jx};

#define ConstCommandsSize 100
#define RegisterQuantity 10
#define LabelsQuantity 10
#define RAMSize 100

struct LabelStruct
{
    char CurrentLabelName [15];

    int LabelIp;
};

struct SPUStruct                //TODO читалка и писалка в коммон
{
    int* code;
    size_t codeSize;

    int* registers;

    LabelStruct* Labels;

    int CurrentLabelsQuantity;

    int* RAM;
};

#endif