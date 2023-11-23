#include <stdio.h>

#include "core/file_reader.h"

int main(void) {
    FileResult result = file_readstring("res/test.txt");

    if (result.valid) {
        printf("Read file!\n\n%s\n", result.file_text);
    }
    else {
        printf("Failed to read file");
    }

    return 0;
}
