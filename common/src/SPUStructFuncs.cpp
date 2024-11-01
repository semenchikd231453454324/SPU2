#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "../include/SPUStruct.h"
#include "../include/SPUStructFuncs.h"

int SPUStructCtor(SPUStruct* Commands)
{
    assert(Commands);

    Commands->code = (int*) calloc(ConstCommandsSize, sizeof(int));
    Commands->registers = (int*) calloc(RegisterQuantity, sizeof(int));
    Commands->Labels = (LabelStruct*) calloc(LabelsQuantity, sizeof(LabelStruct));

    Commands->codeSize = 0;
    Commands->CurrentLabelsQuantity = 0;

    return 0;
}

int SPUStructDtor(SPUStruct* Commands)
{
    assert(Commands);

    free(Commands->code);
    free(Commands->registers);
    free(Commands->Labels);
    
    Commands = {};

    return 0;
}

int SPUStructDumpcode(SPUStruct* Commands)
{
    printf("CODEDUMP\n\n CodeSize = %d\n", Commands->codeSize);

    for (size_t i = 0; i < Commands->codeSize; i++)
    {
        printf("CodeElem[%d] = %d\n", i, Commands->code[i]);
    }
    
    return 0;
}