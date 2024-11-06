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
#include "../../common/include/ReadWritebin.h"
#include "../include/LabelsSearch.h"

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

    char CurrentCommand [20] = {};

    SPUStructDumpcode(&Commands);

    LabelsSearch(TextData, &Commands);

    SPUStructDumpcode(&Commands);

    SPUStructDumplbls(&Commands);

    for(size_t LineNum = 0; LineNum < TextData->LinesCounter; LineNum++)
    {
        CurrentCommand [20] = {};
        
        sscanf(TextData->CommandsLinePointers[LineNum], "%s", CurrentCommand);

        if(!strcmp(CurrentCommand, "push"))
        {
            Commands.code[Commands.codeSize] = Instruction_push;

            int ArgForCommand = 0;
            
            sscanf(TextData->CommandsLinePointers[LineNum] + strlen("push"), "%s", CurrentCommand); // FIXME sizeof("push")

            ArgForCommand = atoi(CurrentCommand);  // FIXME safety func

            Commands.code[Commands.codeSize + 1] = ArgForCommand;

            if(ArgForCommand == 1 || ArgForCommand == 2 || ArgForCommand == 5 || ArgForCommand == 6) // FIXME magic numbers
            {

            sscanf(TextData->CommandsLinePointers[LineNum] + strlen("push") + 2, "%s", CurrentCommand);

            int ValueForCommand = 0;

            ValueForCommand = atoi(CurrentCommand);

            Commands.code[Commands.codeSize + 2] = ValueForCommand;

            Commands.codeSize = Commands.codeSize + 3;
            }

            if(ArgForCommand == 3 || ArgForCommand == 7)
            {
                int PushNum = 0, PushRegNum = 0;

                sscanf(TextData->CommandsLinePointers[LineNum] + strlen("push") + 2, "%s", CurrentCommand);

                PushNum = atoi(CurrentCommand);

                Commands.code[Commands.codeSize + 2] = PushNum;
                
                sscanf(TextData->CommandsLinePointers[LineNum] + strlen("push") + 2 + strlen(CurrentCommand), "%s", CurrentCommand);

                PushRegNum = atoi(CurrentCommand);

                Commands.code[Commands.codeSize + 3] = PushRegNum;

                Commands.codeSize+=4;
            }
        }
        else if(!strcmp(CurrentCommand, "pop"))
        {
            Commands.code[Commands.codeSize] = Instruction_pop;

            int ArgForCommand = 0;
            
            sscanf(TextData->CommandsLinePointers[LineNum] + strlen("pop"), "%s", CurrentCommand);

            ArgForCommand = atoi(CurrentCommand);

            Commands.code[Commands.codeSize + 1] = ArgForCommand;

            if(ArgForCommand == 1 || ArgForCommand == 2)
            {
                int registernum = 0;

                sscanf(TextData->CommandsLinePointers[LineNum] + strlen("pop") + 2, "%s", CurrentCommand);

                registernum = atoi(CurrentCommand);

                Commands.code[Commands.codeSize + 2] = registernum;

                Commands.codeSize+=1;

            }else if (ArgForCommand == 3)
            {
                int PushNum = 0, PushRegNum = 0;

                sscanf(TextData->CommandsLinePointers[LineNum] + strlen("pop") + 2, "%s", CurrentCommand);

                PushNum = atoi(CurrentCommand);

                Commands.code[Commands.codeSize + 2] = PushNum;
                
                sscanf(TextData->CommandsLinePointers[LineNum] + strlen("pop") + 2 + strlen(CurrentCommand), "%s", CurrentCommand);

                PushRegNum = atoi(CurrentCommand);

                Commands.code[Commands.codeSize + 3] = PushRegNum;

                Commands.codeSize+=2;
            }

            Commands.codeSize = Commands.codeSize + 2;
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
        }
        else if(!strcmp(CurrentCommand, "call"))
        {
            Commands.code[Commands.codeSize] = Instruction_call;

            sscanf(TextData->CommandsLinePointers[LineNum] + strlen("call"),"%s", CurrentCommand);
                                                                                                                
            for (int i = 0; i < Commands.CurrentLabelsQuantity; i++)                                        
            {                                                                                               
                if (!strcmp(Commands.Labels[i].CurrentLabelName, CurrentCommand))                           
                {                                                                                           
                    Commands.code[Commands.codeSize + 1] = Commands.Labels[i].LabelIp;                      
                                                                                                           
                    break;                                                                                  
                }                                                                                           
            }

            Commands.codeSize += 2;
        }
        else if(!strcmp(CurrentCommand, "ret"))
        {
            Commands.code[Commands.codeSize] = Instruction_ret;

            Commands.codeSize+=1;
        }
        else
        {
            printf("Assembler doesn't know this command\n");

            return 0;
        }
    }   

    SPUStructDumpcode(&Commands);

    Writebin(&Commands, argv[3]);

    SPUStructCtor(&Commands);

    #undef OneCellCommand
    #undef JumpCommand
    #undef NumSearch

    return 0;
}