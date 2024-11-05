#ifndef READDWRITEBIN_H
#define READDWRITEBIN_H

#include <stdlib.h>

#include "SPUStruct.h"

int Readbin(SPUStruct* Commands, char* FileName);
int Writebin(SPUStruct* Commands, char* FileName);

#endif