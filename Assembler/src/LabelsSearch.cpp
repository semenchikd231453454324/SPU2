#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../include/LabelsSearch.h"

#define OneCellCommand(commandname, commandEnum)            \
if(!strcmp(CurrentCommand, commandname))                    \
    {                                                       \
                                                            \
        Commands->codeSize = Commands->codeSize + 1;        \
    }                                                       \


    #define JumpCommand(commandname, commandEnum)                                                               \
    if(!strcmp(CurrentCommand, commandname))                                                                    \
        {                                                                                                       \
            Commands->codeSize = Commands->codeSize + 2;                                                        \
        }

int LabelsSearch(AsmStruct* TextData, SPUStruct* Commands)
{
    assert(TextData);
    assert(Commands);

    char CurrentCommand [20] = {};

    for(size_t LineNum = 0; LineNum < TextData->LinesCounter; LineNum++)
    {
        CurrentCommand [20] = {};
        
        sscanf(TextData->CommandsLinePointers[LineNum], "%s", CurrentCommand);

        if(!strcmp(CurrentCommand, "push"))
        {
            int ArgForCommand = 0;
            
            sscanf(TextData->CommandsLinePointers[LineNum] + strlen("push"), "%s", CurrentCommand); // FIXME sizeof("push")

            ArgForCommand = atoi(CurrentCommand);  // FIXME safety func

            if(ArgForCommand == 1 || ArgForCommand == 2 || ArgForCommand == 5 || ArgForCommand == 6) // FIXME magic numbers
            {
                Commands->codeSize = Commands->codeSize + 3;
            }

            if(ArgForCommand == 3 || ArgForCommand == 7)
            {
                Commands->codeSize+=4;
            }
        }
        else if(!strcmp(CurrentCommand, "pop"))
        {

            int ArgForCommand = 0;
            
            sscanf(TextData->CommandsLinePointers[LineNum] + strlen("pop"), "%s", CurrentCommand);

            ArgForCommand = atoi(CurrentCommand);

            if(ArgForCommand == 1 || ArgForCommand == 2)
            {
                Commands->codeSize+=1;

            }else if (ArgForCommand == 3)
            {
                Commands->codeSize+=2;
            }

            Commands->codeSize = Commands->codeSize + 2;
        }
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
        else OneCellCommand("regdump", Instruction_regdump)
        else OneCellCommand("ramdump", Instruction_ramdump)
        else OneCellCommand("codedump", Instruction_codedump)
        else OneCellCommand("hlt", Instruction_hlt)
        else JumpCommand("jmp", Instruction_jmp)
        else JumpCommand("ja", Instruction_ja)
        else JumpCommand("jae", Instruction_jae)
        else JumpCommand("jb", Instruction_jb)
        else JumpCommand("jbe", Instruction_jbe)
        else JumpCommand("je", Instruction_je)
        else JumpCommand("jne", Instruction_jne)
        else if(strchr(CurrentCommand, ':'))
        {                  
            int CurrentCharacterNum = 0;                             
            
            char TemporraryBuf [15] ={};

            while (CurrentCommand[CurrentCharacterNum] != ':')
            {
                TemporraryBuf[CurrentCharacterNum] = CurrentCommand[CurrentCharacterNum];

                CurrentCharacterNum++;
            }
            
            CurrentCharacterNum++;

            TemporraryBuf[CurrentCharacterNum] = '\0';

            (Commands->Labels[Commands->CurrentLabelsQuantity]).LabelIp = (int) Commands->codeSize;

            for(int CurrentLabelCharacter = 0; CurrentLabelCharacter < CurrentCharacterNum; CurrentLabelCharacter++)
            {
                (Commands->Labels[Commands->CurrentLabelsQuantity]).CurrentLabelName[CurrentLabelCharacter] = TemporraryBuf[CurrentLabelCharacter];
            }
         
            Commands->CurrentLabelsQuantity++;
        }
        else if(!strcmp(CurrentCommand, "call"))
        {
            Commands->codeSize += 2;
        }
        else if(!strcmp(CurrentCommand, "ret"))
        {
            Commands->codeSize+=1;
        }
        else
        {
            printf("Assembler doesn't know this command\n");

            return 1;
        }
    }

    Commands->codeSize = 0;

    return 0;
}