#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../../common/include/SPUStruct.h"
#include "../../common/include/SPUStructFuncs.h"
#include "../../Stack/include/Stack.h"
#include "../include/Run.h"

int main(int argc, char* argv[])
{
    SPUStruct Commands = {};
    StackStruct Stack = {};

    SPUStructCtor(&Commands);
    StackCtor(&Stack);

    Run(&Commands, &Stack);

    SPUStructDtor(&Commands);
    StackDestruct(&Stack);

    return 0;
}