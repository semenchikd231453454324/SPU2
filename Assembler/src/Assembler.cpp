#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../include/AsmStruct.h"
#include "../include/AsmStructFuncs.h"
#include "../include/Assembler.h"
#include "../../common/include/SPUStruct.h"
#include "../../common/include/SPUStructFuncs.h"

#define NumSearch strchr(TextData->CommandsLinePointers[LineNum], '0') || strchr(TextData->CommandsLinePointers[LineNum], '1') || strchr(TextData->CommandsLinePointers[LineNum], '2') || strchr(TextData->CommandsLinePointers[LineNum], '3') || strchr(TextData->CommandsLinePointers[LineNum], '4') || strchr(TextData->CommandsLinePointers[LineNum], '5') || strchr(TextData->CommandsLinePointers[LineNum], '6') || strchr(TextData->CommandsLinePointers[LineNum], '7') || strchr(TextData->CommandsLinePointers[LineNum], '8') || strchr(TextData->CommandsLinePointers[LineNum], '9')

#define OneCellCommand(commandname, commandEnum)            \
if(!strcmp(CurrentCommand, commandname))                    \
    {                                                       \
        Commands.code[Commands.codeSize] = commandEnum;     \
                                                            \
        Commands.codeSize = Commands.codeSize + 1;          \
    }                                                       \


    #define JumpCommand(commandname, commandEnum)                                                               \
    if(!strcmp(CurrentCommand, commandname))                                                                    \
        {                                                                                                       \
            Commands.code[Commands.codeSize] = commandEnum;                                                     \
                                                                                                                \
            if (NumSearch)                                                                                      \
            {                                                                                                   \
                int ValueForCommand = 0;                                                                        \
                sscanf(TextData->CommandsLinePointers[LineNum] + strlen(commandname),"%s", CurrentCommand);     \
                                                                                                                \
                ValueForCommand = atoi(CurrentCommand);                                                         \
                                                                                                                \
                Commands.code[Commands.codeSize + 1] = ValueForCommand;                                         \
            }                                                                                                   \
            else                                                                                                \
            {                                                                                                   \
                sscanf(TextData->CommandsLinePointers[LineNum] + strlen(commandname),"%s", CurrentCommand);     \
                                                                                                                \
                for (int i = 0; i < Commands.CurrentLabelsQuantity; i++)                                        \
                {                                                                                               \
                    if (!strcmp(Commands.Labels[i].CurrentLabelName, CurrentCommand))                           \
                    {                                                                                           \
                        Commands.code[Commands.codeSize + 1] = Commands.Labels[i].LabelIp;                      \
                                                                                                                \
                        break;                                                                                  \
                    }                                                                                           \
                }                                                                                               \
            }                                                                                                   \
                                                                                                                \
            Commands.codeSize = Commands.codeSize + 2;                                                          \
        }


int Assembler(AsmStruct* TextData, char** argv) 
{
    assert(TextData);
    
    SPUStruct Commands = {};

    SPUStructCtor(&Commands);

    SPUStructDumpcode(&Commands);

    char CurrentCommand [20] = {};

    for(size_t LineNum = 0; LineNum < TextData->LinesCounter; LineNum++)
    {
        CurrentCommand [20] = {};

        printf("%ld\n", LineNum);
        
        AsmDump(TextData);

        sscanf(TextData->CommandsLinePointers[LineNum], "%s", CurrentCommand);

        if(!strcmp(CurrentCommand, "push"))
        {
            Commands.code[Commands.codeSize] = Instruction_push;

            int ValueForCommand = 0;
            
            sscanf(TextData->CommandsLinePointers[LineNum] + strlen("push"), "%s", CurrentCommand);

            printf("%s\n", CurrentCommand);

            ValueForCommand = atoi(CurrentCommand);

            Commands.code[Commands.codeSize + 1] = ValueForCommand;

            Commands.codeSize = Commands.codeSize + 2;
        }
        else OneCellCommand("pop", Instruction_pop)
        else OneCellCommand("in", Instruction_in)
        else OneCellCommand("out", Instruction_out)
        else OneCellCommand("add", Instruction_add)
        else OneCellCommand("subtr", Instruction_subtr)
        else OneCellCommand("multipl", Instruction_multipl)
        else OneCellCommand("div", Instruction_div)
        else OneCellCommand("SQRT", Instruction_SQRT)
        else OneCellCommand("SIN", Instruction_SIN)
        else OneCellCommand("COS", Instruction_COS)
        else OneCellCommand("stkdump", Instruction_stkdump)
        else OneCellCommand("sfudump", Instruction_sfudump)
        else OneCellCommand("lbldump", Instruction_lbldump)
        else OneCellCommand("hlt", Instruction_hlt)
        else JumpCommand("jmp", Instruction_jmp)
        else JumpCommand("ja", Instruction_ja)
        else JumpCommand("jae", Instruction_jae)
        else JumpCommand("jb", Instruction_jb)
        else JumpCommand("jbe", Instruction_jbe)
        else JumpCommand("je", Instruction_je)
        else JumpCommand("jne", Instruction_jne)
        else if(strchr(CurrentCommand, ':'))
        {                                               //TODO rename all
            int i = 0;                             
            
            char TemporraryBuf [15] ={};

            while (CurrentCommand[i] != ':')
            {
                TemporraryBuf[i] = CurrentCommand[i];

                i++;
            }
            
            i++;

            TemporraryBuf[i] = '\0';

            (Commands.Labels[Commands.CurrentLabelsQuantity]).LabelIp = (int) Commands.codeSize;     //эээ сомнительно

            for(int j = 0; j < i; j++)
            {
                (Commands.Labels[Commands.CurrentLabelsQuantity]).CurrentLabelName[j] = TemporraryBuf[j];             //TODO норм ли?
            }
         
            Commands.CurrentLabelsQuantity++;
        }
        else
        {
            printf("Assembler doesn't know this command\n");

            return 0;
        }
    }   

    FILE* Binary = fopen(argv[3], "wb");

    fwrite(&Commands.codeSize, sizeof(int), 1, Binary);

    fwrite(Commands.code, sizeof(int), Commands.codeSize, Binary);

    fclose(Binary);

    #undef OneCellCommand
    #undef JumpCommand
    #undef NumSearch

    return 0;
}