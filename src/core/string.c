#include "string.h"

String* string_create(char* characters, uint32_t length) {
    String* str = malloc(sizeof(String));
    str->text = malloc(sizeof(char) * (length + 1));
    str->length = length;
    memcpy(str->text, characters, str->length);
    str->text[length] = '\0';
    return str;
}

String* string_create_empty(uint32_t length) {
    String* str = malloc(sizeof(String));
    str->text = malloc(sizeof(char) * (length + 1));
    str->length = length;
    str->text[length] = '\0';
    return str;
}

String* string_create_lit(char* characters) {
    int length = strlen(characters);
    String* str = string_create_empty(length);
    memcpy(str->text, characters, length);
    return str;
}


b8 string_startswith(char* str, char* lit) {
    int offset = 0;
    while(str[offset] != '\0' && lit[offset] != '\0') {
        if (str[offset] != lit[offset]) {
            return false;
        }

        offset++;
    }

    return str[offset] == lit[offset] || lit[offset] == '\0';
}

void string_free(String* str) {
    free(str->text);
    free(str);
}