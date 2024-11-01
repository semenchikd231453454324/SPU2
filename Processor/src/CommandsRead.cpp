#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../include/CommandsRead.h"

int CommandsRead(SPUStruct* Commands, char** argv)
{
    assert(Commands);

    FILE* CommandsText = fopen(argv[1], "rb");
    if(!CommandsText)
    {
        printf("fopen returned nullptr in CommandsRead\n");

        return 1;
    }

    fread(&Commands->codeSize, sizeof(char), 1, CommandsText);

    fread(Commands->code, sizeof(int), Commands->codeSize, CommandsText);

    return 0;
}