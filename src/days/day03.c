#include "../core/file_reader.h"

struct SchematicNumber {
    int number, x_min, x_max, y;
};
typedef struct SchematicNumber SchematicNumber;

b8 is_digit(char c);
ArrayList* parse_schematic_numbers(ArrayList* file_lines);
b8 is_symbol_adjacent(SchematicNumber* schematic_number, ArrayList* files_lines);
b8 is_symbol(ArrayList* file_lines, int x, int y);
int part_one_solve(ArrayList* schematic_numbers, ArrayList* file_lines);
int part_two_solve();

int main(void) {
    FileLineResult result = file_readlines("res/day03.txt");

    ArrayList* schematic_numbers = parse_schematic_numbers(result.file_lines);

    int part_one = part_one_solve(schematic_numbers, result.file_lines);

    printf("part one: %d\n", part_one);

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
