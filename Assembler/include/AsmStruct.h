#ifndef ASMSTRUCT_H
#define ASMSTRUCT_H

#include <stdlib.h>
#include <stdio.h>

#include "../../common/include/SPUStruct.h"

struct AsmStruct
{
    size_t LinesCounter, TextSize;

    char* CommandsTextBuffer;

    char** CommandsLinePointers;
};

#endif