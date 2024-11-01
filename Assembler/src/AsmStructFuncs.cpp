#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>

#include "../include/AsmStruct.h"
#include "../include/AsmStructFuncs.h"
#include "../include/TextProcessing.h"

int AsmStructCtor(AsmStruct* TextData, char** argv)
{
    assert(TextData);

    struct stat FileInf = {};
    stat(argv[1], &FileInf);

    TextData->TextSize = FileInf.st_size;

    TextData->CommandsTextBuffer = (char*) calloc(TextData->TextSize, sizeof(char));
    if (!TextData->CommandsTextBuffer)
    {
        printf("pointer textdata failure");
        return 0;
    }

    TextProcessing(TextData, argv);

    return 0;  //FIXME
}

int AsmStructDtor(AsmStruct* TextData)
{
    assert(TextData);

    free(TextData->CommandsTextBuffer);
    free(TextData->CommandsLinePointers);

    TextData = {};

    return 0;
}

int AsmDump(AsmStruct* TextData)
{
    assert(TextData);

    printf("Text size = %d\nLinesNumber = %d\n\n TextBuffer('%'c):\n", TextData->TextSize, TextData->LinesCounter);

    for(size_t i = 0; i < TextData->TextSize; i++)
    {   
        printf("%c", TextData->CommandsTextBuffer[i]);
    }

    printf("\nTextPrint by LinePointers:\n");

    for (size_t LineNumber = 0; LineNumber < TextData->LinesCounter; LineNumber++)
    {
        printf("%s\n", TextData->CommandsLinePointers[LineNumber]);
    }

    return 0;
}