#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../include/Run.h"
#include "../../Stack/include/Stack.h"

void Run(SPUStruct* Commands, StackStruct* Stack)
{
    assert(Commands);

    int ip = 0;
    int WorkStatus = 1;

    while (WorkStatus)
    {
        switch (Commands->code[ip])
        {
        case Instruction_push:                                             //Кладем в стэк
        {                                             
            StackPush(Stack, Commands->code[ip + 1]);
            ip = ip + 2;

            break;
        }

        case Instruction_pop:                                             //Достаем из стэка
        {
            StackPop(Stack);

            ip = ip + 1;

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
            int Result = 0;
        
            Result = StackPop(Stack) + StackPop(Stack);

            StackPush(Stack, Result);

            ip = ip + 1;

            break;
        }

        case Instruction_subtr:                                              //Вычитание двух верхних элементов(верхний это вычитаемое)
        {
            int Minued = 0, Subtrahend = 0, Result = 0;

            Subtrahend = StackPop(Stack);
            Minued     = StackPop(Stack);

            Result = Minued - Subtrahend;

            StackPush(Stack, Result);

            ip = ip + 1;

            break;
        }

        case Instruction_multipl:                                             //Умножение
        {
            int FirstFactor = 0, SecondFactor = 0, Result = 0;

            FirstFactor  = StackPop(Stack);
            SecondFactor = StackPop(Stack);

            Result = FirstFactor*SecondFactor;

            StackPush(Stack, Result);

            ip = ip + 1;

            break;
        }

        case Instruction_div:                                             //Деление
        {
            int Dividend = 0, Divider = 0, Result = 0;

            Divider  = StackPop(Stack);
            Dividend = StackPop(Stack);

            Result = Dividend / Divider;

            StackPush(Stack, Result);

            ip = ip + 1;

            break;
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
            int SecondNum = StackPop(Stack);
            int FirstNum = StackPop(Stack);

            if(FirstNum > SecondNum)
            {
                ip = Commands->code[ip + 1];
            }
            else
            {
                ip = ip + 2;
            }

            break;
        }

        case Instruction_jae:
        {
            int SecondNum = StackPop(Stack);
            int FirstNum = StackPop(Stack);

            if(FirstNum >= SecondNum)
            {
                ip = Commands->code[ip + 1];
            }
            else
            {
                ip = ip + 2;
            }

            break;
        }

        case Instruction_jb:
        {
            int SecondNum = StackPop(Stack);
            int FirstNum = StackPop(Stack);

            if(FirstNum < SecondNum)
            {
                ip = Commands->code[ip + 1];
            }
            else
            {
                ip = ip + 2;
            }

            break;
        }

        case Instruction_jbe:
        {
            int SecondNum = StackPop(Stack);
            int FirstNum = StackPop(Stack);

            if(FirstNum <= SecondNum)
            {
                ip = Commands->code[ip + 1];
            }
            else
            {
                ip = ip + 2;
            }

            break;
        }

        case Instruction_je:
        {
            int SecondNum = StackPop(Stack);
            int FirstNum = StackPop(Stack);

            if(FirstNum == SecondNum)
            {
                ip = Commands->code[ip + 1];
            }
            else
            {
                ip = ip + 2;
            }

            break;
        }

        case Instruction_jne:
        {
            int SecondNum = StackPop(Stack);
            int FirstNum = StackPop(Stack);

            if(FirstNum != SecondNum)
            {
                ip = Commands->code[ip + 1];
            }
            else
            {
                ip = ip + 2;
            }

            break;
        }

        case Instruction_sfudump:
        {
            printf("\n\n\n SFUDUMP\n");

            printf("Codesize = %d\n", Commands->codeSize);

            for(size_t CodeElemNum = 0; CodeElemNum < Commands->codeSize; CodeElemNum++)
            {
                printf("code[%d] = %d\n", CodeElemNum, Commands->code[CodeElemNum]);
            }

            printf("Current ip = %d\n", ip);

            ip = ip + 1;

            break;
        }

        case Instruction_lbldump:
        {
            for (int i = 0; i < LabelsQuantity; i++)
            {
                printf("Label[%d]: Labelname: %s LabelIP: %d\n", i, Commands->Labels[i].CurrentLabelName, Commands->Labels[i].LabelIp);
            }
            
            ip = ip + 1;
            
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
}