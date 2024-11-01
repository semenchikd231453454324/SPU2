#ifndef ASMSTRUCTFUNCS_H
#define ASMSTRUCTFUNCS_H

#include <stdlib.h>
#include <stdio.h>

#include "AsmStruct.h"

int AsmStructCtor(AsmStruct* TextData, char**);
int AsmStructDtor(AsmStruct* TextData);
int AsmDump(AsmStruct* TextData);

#endif