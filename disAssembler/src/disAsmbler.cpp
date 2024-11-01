#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../include/disAssembler.h"

int disAssembler(SPUStruct* Commands, char** argv)
{
    assert(Commands);

    FILE* CommmandsTextout = fopen(argv[2], "r");
    if(!CommmandsTextout)
    {
        
    }

    size_t ip = 0;

    for(size_t LineNum = 0; LineNum < (TextStruct->LinesCounter - Commands->CurrentLabelsQuantity); LineNum++)
    {
        switch (Commands->code[ip])
        {
            case Instruction_push:
            {
                fprintf(CommmandsTextout, "push %d\n", Commands->code[ip + 1]);

                ip += 2;
        
                break;
            }
            OneCellCommandOut(Instruction_pop, "pop")
            OneCellCommandOut(Instruction_in, "in")
            OneCellCommandOut(Instruction_out, "out")
            OneCellCommandOut(Instruction_add, "add")
            OneCellCommandOut(Instruction_subtr, "subtr")
            OneCellCommandOut(Instruction_multipl, "multipl")
            OneCellCommandOut(Instruction_div, "div")
            OneCellCommandOut(Instruction_SQRT, "SQRT")
            OneCellCommandOut(Instruction_SIN, "SIN")
            OneCellCommandOut(Instruction_COS, "COS")
            OneCellCommandOut(Instruction_stkdump, "stkdump")
            OneCellCommandOut(Instruction_sfudump, "sfudump")
            OneCellCommandOut(Instruction_lbldump, "lbldump")
            OneCellCommandOut(Instruction_hlt, "hlt")
            JumpCommandOut(Instruction_jmp, "jmp")
            JumpCommandOut(Instruction_ja, "ja")
            JumpCommandOut(Instruction_jae, "jae")
            JumpCommandOut(Instruction_jb, "jb")
            JumpCommandOut(Instruction_jbe, "jbe")
            JumpCommandOut(Instruction_je, "je")
            JumpCommandOut(Instruction_jne, "jne")

            default:
            {
                fprintf(CommmandsTextout, "unknown instruction %d\n", Commands->code[ip]);
                
                LineNum = TextStruct->LinesCounter;

                break;
            }
        }
    }

    #undef OneCellCommandOut
    #undef JumpCommandOut

    AsmStructDtor(TextStruct);

    return 0;
}