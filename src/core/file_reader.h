#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include "string.h"
#include "core.h"

struct FileResult {
    String* file_text;
    b8 valid;
};
typedef struct FileResult FileResult;

FileResult file_readstring(char* path);

#endif