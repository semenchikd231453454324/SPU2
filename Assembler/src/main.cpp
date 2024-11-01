#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h> 

#include "../include/AsmStruct.h"
#include "../include/AsmStructFuncs.h"
#include "../include/Assembler.h"

int main(int argc, char* argv[])
{
    AsmStruct TextData = {};

    AsmStructCtor(&TextData, argv);

    Assembler(&TextData, argv);

    AsmStructDtor(&TextData);

    return 0;
}