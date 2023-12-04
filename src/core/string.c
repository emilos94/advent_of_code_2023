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


ArrayList* string_split(String* str, char c) {
    ArrayList* split_results = arraylist_create(10, sizeof(String));

    int last_split_index = 0;
    for (int i = 0; i < str->length; i++) {
        if (str->text[i] == c && last_split_index < i) {
            String* new_str = string_create(str->text + last_split_index, i - last_split_index);
            arraylist_add(split_results, new_str);
            last_split_index = i + 1;
            free(new_str);
        }
    }

    if (last_split_index < str->length - 1) {
        String* new_str = string_create(str->text + last_split_index, str->length - last_split_index);
        arraylist_add(split_results, new_str);
        free(new_str);
    }

    return split_results;
}


b8 string_contains(String* str, char* lit) {
    for(int i = 0; i < str->length; i++) {
        if (string_startswith(str->text + i, lit)) {
            return true;
        }
    }

    return false;
}

void string_free(String* str) {
    free(str->text);
    free(str);
}

void string_arraylist_free(ArrayList* str_list) {
    ARRAYLIST_FOREACH(str_list, String, str) {
        free(str->text);
    }

    free(str_list);
}