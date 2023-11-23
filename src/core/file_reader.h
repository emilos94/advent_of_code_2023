#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include "string.h"
#include "core.h"
#include "../datastructures/arraylist.h"

struct FileResult {
    String* file_text;
    b8 valid;
};
typedef struct FileResult FileResult;

struct FileLineResult {
    ArrayList* file_lines;
    b8 valid;
};
typedef struct FileLineResult FileLineResult;

FileResult file_readstring(char* path);
FileLineResult file_readlines(char* path);

#endif