#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"
#include "../datastructures/arraylist.h"

struct String {
    char* text;
    uint32_t length;
};
typedef struct String String;

String* string_create(char* characters, uint32_t length);
String* string_create_empty(uint32_t length);
String* string_create_lit(char* characters);
b8 string_startswith(char* str, char* lit);
b8 string_contains(String* str, char* lit);
ArrayList* string_split(String* str, char c);
void string_free(String* str);
void string_arraylist_free(ArrayList* str_list);


#endif