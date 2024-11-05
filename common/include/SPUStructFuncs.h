#ifndef SPUSTRUCTFUNCS_H
#define SPUSTRUCTFUNCS_H

#include "SPUStruct.h"

int SPUStructCtor(SPUStruct* Commands);
int SPUStructDtor(SPUStruct* Commands);
int SPUStructDumpcode(SPUStruct* Commands);
int SPUStructDumpregs(SPUStruct* Commands);
int SPUStructDumplbls(SPUStruct* Commands);
int SPUStructDumpRAM(SPUStruct* Commands);
int SPUStructDump(SPUStruct* Commands);

#endif