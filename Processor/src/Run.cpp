#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../include/Run.h"
#include "../../Stack/include/Stack.h"
#include "../../common/include/SPUStructFuncs.h"
#include "../include/GetArgs.h"

#define conditionaljump( signs )                \
    int SecondNum = StackPop(Stack);            \
    int FirstNum = StackPop(Stack);             \
                                                \
    if(FirstNum signs SecondNum)                \
    {                                           \
        ip = Commands->code[ip + 1];            \
    }                                           \
    else                                        \
    {                                           \
        ip = ip + 2;                            \
    }                                           \
                                                \
    break

#define TWOELEMENTSOPERATION( sign )                \
    int FirstNum = 0, SecondNum = 0, Result = 0;    \
                                                    \
    FirstNum = StackPop(Stack);                     \
    SecondNum = StackPop(Stack);                    \
                                                    \
    Result = SecondNum sign FirstNum;               \
                                                    \
    StackPush(Stack, Result);                       \
                                                    \
    ip = ip + 1;                                    \
                                                    \
    break


void Run(SPUStruct* Commands, StackStruct* Stack)
{
    assert(Commands);

    StackStruct retstk = {};

    int ip = 0;
    int WorkStatus = 1;

    StackCtor(&retstk);

    int pis = 0;

    while (WorkStatus)
    {
        printf("Command number = %d\n\n", pis);
        pis++;

        switch (Commands->code[ip])
        {
        case Instruction_push:                                             //Кладем в стэк
        {                                             
            GetPushArg(Commands, Stack, Commands->code[ip + 1], &ip);

            ip = ip + 1;

            break;
        }

        case Instruction_pop:                                             //Достаем из стэка
        {
            GetPopArg(Commands, Stack, Commands->code[ip + 1], &ip);

            ip+=1;

            break;
        }

        case Instruction_in:                                               //Кладем в стэк + ввод с клавы
        {
            int PushValue = 0;

            printf("Enter new Stack element\n");
            scanf("%d", &PushValue);

            StackPush(Stack, PushValue);

            ip = ip + 1;

            break;
        }                                             

        case Instruction_out:                                             //Достаем из стэка + печатаем
        {
            int PopValue = 0;

            PopValue = StackPop(Stack);

            printf("Upper Stack element = %d\n", PopValue);

            ip = ip + 1;

            break;
        }

        case Instruction_add:                                             //Cложение двух верхних элементов
        {
            TWOELEMENTSOPERATION( + );
        }

        case Instruction_subtr:                                              //Вычитание двух верхних элементов(верхний это вычитаемое)
        {
            TWOELEMENTSOPERATION( - );
        }

        case Instruction_multipl:                                             //Умножение
        {
            TWOELEMENTSOPERATION( * );
        }

        case Instruction_div:                                             //Деление
        {
            TWOELEMENTSOPERATION( / );
        }

        case Instruction_SQRT:                                             //sqrt
        {
            int TemporaryBuf = 0;

            TemporaryBuf = StackPop(Stack);

            StackPush(Stack, (int) sqrt(TemporaryBuf));

            ip = ip + 1;

            break;
        }

        case Instruction_SIN:                                               //sin
        {
            StackPush(Stack, (int) sin(StackPop(Stack)));

            ip = ip + 1;

            break;
        }

        case Instruction_COS:                                               //cos
        {
            StackPush(Stack, (int) cos(StackPop(Stack)));

            ip = ip + 1;

            break;
        }

        case Instruction_stkdump:                                              //dump
        {
            DUMP(Stack);

            ip = ip + 1;

            break;
        }

        case Instruction_hlt:                                               //hlt
        {
            WorkStatus = 0;

            ip = ip + 1;

            break;
        }

        case Instruction_jmp:                                               //jump
        {
            ip = Commands->code[ip + 1];

            break;
        }

        case Instruction_ja:
        {
            conditionaljump( > );
        }

        case Instruction_jae:
        {
            conditionaljump( >= );
        }

        case Instruction_jb:
        {
            conditionaljump( < );
        }

        case Instruction_jbe:
        {
            conditionaljump( <= );
        }

        case Instruction_je:
        {
            conditionaljump( == );
        }

        case Instruction_jne:
        {
            conditionaljump( != );
        }

        case Instruction_sfudump:
        {
            printf("\n\n\n SFUDUMP\n");
            printf("Current ip = %d\n", ip);

            SPUStructDump(Commands);

            ip = ip + 1;

            break;
        }

        case Instruction_codedump:
        {
            SPUStructDumpcode(Commands);

            ip+=1;

            break;
        }

        case Instruction_lbldump:
        {
            SPUStructDumplbls(Commands);
            
            ip = ip + 1;
            
            break;
        }

        case Instruction_regdump:
        {
            SPUStructDumpregs(Commands);
            
            ip = ip + 1;
            
            break;
        }

        case Instruction_ramdump:
        {
            SPUStructDumpRAM(Commands);
            
            ip = ip + 1;
            
            break;
        }

        case Instruction_call:
        {
            StackPush(&retstk, ip + 2);

            ip =  Commands->code[ip + 1];

            break;
        }

        case Instruction_ret:
        {
            ip = StackPop(&retstk);

            break;
        }
        
        default:
        {
            printf("Syntax error, entered Invalid command\n");

            WorkStatus = 0;

            break;
        }
        }
    }

    StackDestruct(&retstk);

    #undef conditionaljump
    #undef TWOELEMENTSOPERATION
}