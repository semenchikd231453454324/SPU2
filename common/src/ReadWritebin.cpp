#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "../include/ReadWritebin.h"

int Readbin(SPUStruct* Commands, char* FileName)
{
    assert(Commands);
    assert(FileName);

    FILE* File = fopen(FileName, "rb");
    if(!File)
    {
        printf("Error with file pointer in Readbin\n");

        return 1;
    }

    fread(&Commands->codeSize, sizeof(int), 1, File);

    fread(Commands->code, sizeof(int), Commands->codeSize, File);

    fclose(File);

    return 0;
}

int Writebin(SPUStruct* Commands, char* FileName)
{
    assert(Commands);
    assert(FileName);

    FILE* File = fopen(FileName, "wsb");
    if(!File)
    {
        printf("Error with file pointer in Readbin\n");

        return 1;
    }

    fwrite(&Commands->codeSize, sizeof(int), 1, File);

    fwrite(Commands->code, sizeof(int), Commands->codeSize, File);

    fclose(File);

    return 0;
}