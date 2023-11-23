#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct String {
    char* text;
    uint32_t length;
};
typedef struct String String;

String* string_create(char* characters, uint32_t length);
String* string_create_empty(uint32_t length);
String* string_create_lit(char* characters);
void string_free(String* str);


#endif