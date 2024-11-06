#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "../include/SPUStruct.h"
#include "../include/SPUStructFuncs.h"

int SPUStructCtor(SPUStruct* Commands)
{
    assert(Commands);           // FIXME calloc check

    Commands->code = (int*) calloc(ConstCommandsSize, sizeof(int));
    Commands->registers = (int*) calloc(RegisterQuantity, sizeof(int));
    Commands->Labels = (LabelStruct*) calloc(LabelsQuantity, sizeof(LabelStruct));
    Commands->RAM = (int*) calloc(RAMSize, sizeof(int));

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
    free(Commands->RAM);
    
    Commands = {};

    return 0;
}

int SPUStructDumpcode(SPUStruct* Commands)
{
    assert(Commands);

    printf("CODEDUMP\n\n CodeSize = %ld\n", Commands->codeSize);

    for (size_t i = 0; i < Commands->codeSize; i++)
    {
        printf("CodeElem[%ld] = %d\n", i, Commands->code[i]);
    }
    
    return 0;
}

int SPUStructDumpregs(SPUStruct* Commands)
{
    assert(Commands);

    printf("\nRegisters data\n\n");

    for(int i = 0; i < RegisterQuantity; i++)
    {    
        printf("Registers[%d] = %d\n", i, Commands->registers[i]);
    }

    return 0;
}

int SPUStructDumplbls(SPUStruct* Commands)
{
    assert(Commands);

    printf("\nLabels data\n\n");

    for(int i = 0; i < LabelsQuantity; i++)
    {
        printf("Label %d: ip = %d, name = %s\n", i, Commands->Labels[i].LabelIp, Commands->Labels[i].CurrentLabelName);
    }

    return 0;
}

int SPUStructDumpRAM(SPUStruct* Commands)
{
    assert(Commands);

    printf("\nRAM Dump\n\n");

    for(int i = 0; i < RAMSize/2; i++)
    {
        printf("RAM[%d] = %d   RAM[%d] = %d\n", i, Commands->RAM[i], i + 50, Commands->RAM[i + 50]);
    }

    return 0;
}

int SPUStructDump(SPUStruct* Commands)
{
    assert(Commands);

    SPUStructDumpcode(Commands);

    SPUStructDumpregs(Commands);

    SPUStructDumplbls(Commands);

    SPUStructDumpRAM(Commands);

    return 0;
}
