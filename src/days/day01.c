#include "../core/file_reader.h"

static char* digit_str[10];

void populate_digit_array(void) {
    digit_str[0] = "zero";
    digit_str[1] = "one";
    digit_str[2] = "two";
    digit_str[3] = "three";
    digit_str[4] = "four";
    digit_str[5] = "five";
    digit_str[6] = "six";
    digit_str[7] = "seven";
    digit_str[8] = "eight";
    digit_str[9] = "nine";
}

b8 to_digit_partone(char c, int* destination) {
    b8 is_digit =  c >= '0' && c <= '9';

    if (is_digit) {
        *destination = (int)c - (int)'0';
    }
    
    return is_digit;
}

b8 to_digit_parttwo(String* s, int offset, int* destination) {
    char c = s->text[offset];
    b8 is_digit =  c >= '0' && c <= '9';
    if (is_digit) {
        *destination = (int)c - (int)'0';
        return is_digit;
    }
    else {
        for (int i = 0; i < 10; i++) {
            if (string_startswith(s->text + offset, digit_str[i])) {
                is_digit = true;
                *destination = i;
            }
        }
    } 

    return is_digit;
}

int part_one_solve(FileLineResult result) {
    int total = 0;
    ARRAYLIST_FOREACH(result.file_lines, String, line) {
        int digit;
        b8 first_digit = true;
        for(int i = 0; i < line->length; i++) {
            if (to_digit_partone(line->text[i], &digit) && first_digit) {
                total += digit * 10;
                first_digit = false;
            }
        }
        
        total += digit;
    }

    return total;
}

int part_two_solve(FileLineResult result) {
    int total = 0;
    ARRAYLIST_FOREACH(result.file_lines, String, line) {
        int digit;
        b8 first_digit = true;
        for(int i = 0; i < line->length; i++) {
            if (to_digit_parttwo(line, i, &digit) && first_digit) {
                total += digit * 10;
                first_digit = false;
            }
        }
        
        total += digit;
    }

    return total;
}

int main(void) {
    FileLineResult result = file_readlines("res/day01.txt");
    populate_digit_array();

    int part_one = part_one_solve(result);
    int part_two = part_two_solve(result);

    printf("part 1: %d\n", part_one);
    printf("part 2: %d\n", part_two);
}