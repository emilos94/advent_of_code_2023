#include "../core/file_reader.h"

struct SchematicNumber {
    int number, x_min, x_max, y;
};
typedef struct SchematicNumber SchematicNumber;

b8 is_digit(char c);
ArrayList* parse_schematic_numbers(ArrayList* file_lines);
b8 is_symbol_adjacent(SchematicNumber* schematic_number, ArrayList* files_lines);
b8 is_symbol(ArrayList* file_lines, int x, int y);
int gear_ratio_if_two_adjacent(ArrayList* schematic_numbers, int gear_x, int gear_y);
int part_one_solve(ArrayList* schematic_numbers, ArrayList* file_lines);
int part_two_solve(ArrayList* schematic_numbers, ArrayList* file_lines);

int main(void) {
    FileLineResult result = file_readlines("res/day03.txt");

    ArrayList* schematic_numbers = parse_schematic_numbers(result.file_lines);

    int part_one = part_one_solve(schematic_numbers, result.file_lines);
    printf("part one: %d\n", part_one);

    int part_two = part_two_solve(schematic_numbers, result.file_lines);
    printf("part two: %d\n", part_two);

    arraylist_free(schematic_numbers);  
    string_arraylist_free(result.file_lines);

    return 0;
}


int part_one_solve(ArrayList* schematic_numbers, ArrayList* file_lines) {
    int sum = 0;
    ARRAYLIST_FOREACH(schematic_numbers, SchematicNumber, number) {
        if (is_symbol_adjacent(number, file_lines)) {
            sum += number->number;
        }
    }

    return sum;
}

int part_two_solve(ArrayList* schematic_numbers, ArrayList* file_lines) {
    int gear_ratio_sum = 0;
    ARRAYLIST_FOREACHI(file_lines, line_num, String, line) {
        for (int i = 0; i < line->length; i++) {
            if (line->text[i] == '*') {
                gear_ratio_sum += gear_ratio_if_two_adjacent(schematic_numbers, i, line_num);
            }
        }
    }
    return gear_ratio_sum;
}

int gear_ratio_if_two_adjacent(ArrayList* schematic_numbers, int gear_x, int gear_y) {
    int count = 0, gear_ratio = 1;
    ARRAYLIST_FOREACH(schematic_numbers, SchematicNumber, number) {
        b8 is_adjacent = gear_x >= number->x_min - 1 && gear_x <= number->x_max + 1 &&
            gear_y >= number->y - 1 && gear_y <= number->y + 1;
        if (is_adjacent) {
            count++;
            gear_ratio *= number->number;
        }
    }

    if (count == 2) {
        return gear_ratio;
    }

    return 0;
}

b8 is_symbol_adjacent(SchematicNumber* schematic_number, ArrayList* files_lines) {
    for (int y = schematic_number->y - 1; y < schematic_number->y + 2; y++) {
        for(int x = schematic_number->x_min - 1; x < schematic_number->x_max + 2; x++) {
            if (is_symbol(files_lines, x, y)) {
                return true;
            }
        } 
    }

    return false;
}


b8 is_symbol(ArrayList* file_lines, int x, int y) {
    int width = ((String*)arraylist_get(file_lines, 0))->length;
    if (x < 0 || x >= width || y < 0 || y >= file_lines->count) {
        return false;
    }

    String* line = arraylist_get(file_lines, y);
    char c = line->text[x];
    return c != '.' && !is_digit(c);
}

b8 is_digit(char c) {
    return c >= '0' && c <= '9';
}

ArrayList* parse_schematic_numbers(ArrayList* file_lines) {
    ArrayList* schematic_numbers = arraylist_create(10, sizeof(SchematicNumber));

    ARRAYLIST_FOREACHI(file_lines, line_index, String, line) {
        b8 number_active = false;
        int multiplier = 1;
        SchematicNumber schematic_number;
        schematic_number.number = 0;

        for (int i = line->length - 1; i >= 0; i--) {
            if (is_digit(line->text[i])) {
                if (!number_active) {
                    number_active = true;
                    multiplier = 1;
                    schematic_number.x_max = i;
                    schematic_number.y = line_index;
                }

                schematic_number.number += (line->text[i] - '0') * multiplier;
                multiplier *= 10;

                if (i == 0) {
                    number_active = false;
                    schematic_number.x_min = i;
                    arraylist_add(schematic_numbers, &schematic_number);
                }
            }
            else if(number_active) {
                number_active = false;
                schematic_number.x_min = i + 1;
                arraylist_add(schematic_numbers, &schematic_number);
                schematic_number.number = 0;
            }
        }
    }

    return schematic_numbers;
}
