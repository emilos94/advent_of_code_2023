#include "file_reader.h"

FileResult file_readstring(char* path) {
    FileResult result;
    FILE* file;

    file = fopen(path, "r");
    if (!file) {
        result.valid = false;
        return result;
    }

    fseek(file, 0, SEEK_END);
    uint32_t length = ftell(file);
    result.file_text = string_create_empty(length);

    fseek(file, 0, SEEK_SET);
    fread(result.file_text, sizeof(char), length, file);
    result.valid = true;
    return result;
}