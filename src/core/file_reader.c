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

FileLineResult file_readlines(char* path) {
    FileLineResult result;
    FILE* file;

    file = fopen(path, "rb");
    if (!file) {
        result.valid = false;
        return result;
    }

    int length = 0;
    while(getc(file) != EOF) {
        length++;
    }

    char* buffer = malloc(sizeof(char) * length);

    fseek(file, 0, SEEK_SET);
    fread(buffer, sizeof(char), length, file);

    ArrayList* lines = arraylist_create(20, sizeof(String));

    int line_start = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\r' && i != length-1 && buffer[i] == '\n' ) {
            String* line = string_create(buffer + line_start, i - line_start);
            line_start = i + 1;
            arraylist_add(lines, line);
            free(line);
        }
    }
    
    if (line_start < length) {
        String* line = string_create(buffer + line_start, length - line_start);
        arraylist_add(lines, line);
        free(line);
    }

    result.valid = true;
    result.file_lines = lines;

    free(buffer);

    return result;
}