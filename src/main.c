#include <stdio.h>

#include "core/file_reader.h"

int main(void) {
    FileLineResult result = file_readlines("res/test.txt");

    if (result.valid) {
        String* line1 = arraylist_get(result.file_lines, 0);
        String* line2 = arraylist_get(result.file_lines, 1);
        int x = 10;
        ARRAYLIST_FOREACH(result.file_lines, String, line) {
            printf("%s\n", line->text);
        }
    }
    else {
        printf("Failed to read file");
    }

    return 0;
}
