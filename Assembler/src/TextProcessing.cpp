#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../include/AsmStruct.h"
#include "../include/TextProcessing.h"

int TextProcessing(AsmStruct* TextData, char** argv)
{
    assert(TextData);

    FILE *MoyText = fopen(argv[1], "r");
    if (!MoyText)
    {
        printf("pointer moytext failure");
        return 1;
    }

    fread(TextData->CommandsTextBuffer, sizeof(char), TextData->TextSize, MoyText);

    for(size_t ElemNum = 0; ElemNum < TextData->TextSize; ElemNum++)                
    {
        if(TextData->CommandsTextBuffer[ElemNum] == '\n')
        {
            TextData->LinesCounter++;
        }
    }
    
    TextData->LinesCounter+=1;

    TextData->CommandsLinePointers = (char**) calloc(TextData->LinesCounter, sizeof(char*));
    if(!TextData->CommandsLinePointers)
    {
        printf("TextData->CommandsLinePointers = nullptr\n");

        return 1;
    }

    char* CurrentLinePointer = TextData->CommandsTextBuffer;
    int CurrentTextDataNum = 0, CurrentElemInLineNumber = 0;

    for(size_t i = 0; i < TextData->LinesCounter; i++)
    {   
        TextData->CommandsLinePointers[i] = CurrentLinePointer;

        CurrentElemInLineNumber = 0;

        while(TextData->CommandsTextBuffer[CurrentTextDataNum] != '\n' && TextData->CommandsTextBuffer[CurrentTextDataNum])
        {
            CurrentTextDataNum++;
            CurrentElemInLineNumber++;
        }

        TextData->CommandsTextBuffer[CurrentTextDataNum] = '\0';
        CurrentElemInLineNumber++;
        CurrentTextDataNum++;
        CurrentLinePointer = CurrentLinePointer + CurrentElemInLineNumber;
    }


    // for(size_t i = 0; i < TextData->TextSize; i++)
    // {
    //     printf("%c", TextData->CommandsTextBuffer[i]);
    // }

    fclose(MoyText);

    return 0;  //FIXME
}