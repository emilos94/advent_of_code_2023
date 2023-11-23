#include "string.h"

String* string_create(char* characters, uint32_t length);

String* string_create_empty(uint32_t length) {
    String* str = malloc(sizeof(String));
    str->text = malloc(sizeof(char) * length);
    str->length = length;
    return str;
}

String* string_create_lit(char* characters);
void string_free(String* str);