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

void string_free(String* str) {
    free(str->text);
    free(str);
}