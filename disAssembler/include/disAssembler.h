#ifndef DISASSEMBLER_H
#define DISASSEMBLER

#include "../../common/include/SPUStruct.h"

int disAssembler(SPUStruct* Commands, char** argv);

#define OneCellCommandOut(commandEnum, commandname)                         \
    case commandEnum:                                                       \
    {                                                                       \
        fprintf(CommmandsTextout, commandname "\n");                        \
                                                                            \
        ip += 1;                                                            \
                                                                            \
        break;                                                              \
    }

    #define JumpCommandOut(commandEnum, commandname)                            \
    case commandEnum:                                                           \
    {                                                                           \
        fprintf(CommmandsTextout, commandname " %d\n", Commands->code[ip + 1]); \
                                                                                \
        ip = ip + 2;                                                            \
                                                                                \
        break;                                                                  \
    }

#endif