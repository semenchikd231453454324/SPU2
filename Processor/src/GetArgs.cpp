#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../include/GetArgs.h"

int GetPushArg(SPUStruct* Commands,StackStruct* Stack, int arg, int* ip)
{
    assert(Commands);
    assert(Stack);
    assert(ip);

    int result = 0;

    *ip += 1;

    if(arg & 1)     // magic number
    {
        result+=Commands->code[*ip+=1];
    }

    if(arg & 2)
    {
        result+=Commands->registers[Commands->code[*ip+=1]];
    }

    if(arg & 4)
    {
        StackPush(Stack, Commands->RAM[result]);
    }
    else
    {
        StackPush(Stack, result);
    }

    return result;
}

int GetPopArg(SPUStruct* Commands,StackStruct* Stack, int arg, int* ip)
{
    assert(Commands);
    assert(Stack);
    assert(ip);

    if(arg == 1)
    {
        Commands->registers[Commands->code[*ip + 2]] = StackPop(Stack);

        *ip+=2;
    }
    else if(arg == 2)
    {
        Commands->RAM[Commands->registers[Commands->code[*ip + 2]]] = StackPop(Stack);

        *ip+=2;
    }
    else if(arg == 3)
    {
        Commands->RAM[Commands->registers[Commands->code[*ip + 2]] + Commands->code[*ip + 3]] = StackPop(Stack);
    }
    else if(arg == 0)
    {
        StackPop(Stack);

        *ip+=1;
    }

    return 0;
}

