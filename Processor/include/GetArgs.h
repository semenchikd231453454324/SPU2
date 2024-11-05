#ifndef GETARGS_H
#define GETARGS_H

#include "../../common/include/SPUStruct.h"
#include "../../Stack/include/Stack.h"

int GetPushArg(SPUStruct* Commands,StackStruct* Stack, int arg, int* ip);
int GetPopArg(SPUStruct* Commands,StackStruct* Stack, int arg, int* ip);

#endif