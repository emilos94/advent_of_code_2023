#include "../core/file_reader.h"

struct Card {
    int id;
    ArrayList* my_numbers;
    ArrayList* winning_numbers;
};
typedef struct Card Card;

// forward declarations
int part_one_solve(ArrayList* cards);
int part_two_solve(ArrayList* cards);
ArrayList* parse_cards(ArrayList* file_lines);
ArrayList* numbers_str_to_int_list(String* numbers_string);

int main(void) {
    FileLineResult result = file_readlines("res/day04.txt");

    ArrayList* cards = parse_cards(result.file_lines);

    int part_one = part_one_solve(cards);
    printf("part one: %d\n", part_one);

    return 1;
}

int part_one_solve(ArrayList* cards) {
    int sum_points = 0;

    ARRAYLIST_FOREACH(cards, Card, card) {
        int card_points = 0;
        ARRAYLIST_FOREACHI(card->my_numbers, j, int, my_number) {
            ARRAYLIST_FOREACHI(card->winning_numbers, k, int, winning_number) {
                if (*my_number == *winning_number) {
                    if (card_points == 0) {
                        card_points = 1;
                    }
                    else {
                        card_points *= 2;
                    }
                }
            }
        }
        sum_points += card_points;
    }

    return sum_points;
}


ArrayList* parse_cards(ArrayList* file_lines) {
    ArrayList* cards = arraylist_create(file_lines->count, sizeof(Card));

    ARRAYLIST_FOREACH(file_lines, String, line) {
        ArrayList* card_numbers_split = string_split(line, ':');

        String* game_id_str = arraylist_get(card_numbers_split, 0);
        String* numbers_str = arraylist_get(card_numbers_split, 1);

        Card card;
        card.id = atoi(game_id_str->text + 5);

        ArrayList* numbers_split = string_split(numbers_str, '|');
        card.winning_numbers = numbers_str_to_int_list(arraylist_get(numbers_split, 0));
        card.my_numbers = numbers_str_to_int_list(arraylist_get(numbers_split, 1));
        
        arraylist_add(cards, &card);
        string_arraylist_free(card_numbers_split);
        string_arraylist_free(numbers_split);
    }

    return cards;
}  

ArrayList* numbers_str_to_int_list(String* numbers_string) {
    ArrayList* numbers = arraylist_create(10, sizeof(int));
    ArrayList* numbers_split = string_split(numbers_string, ' ');

    ARRAYLIST_FOREACH(numbers_split, String, number_str) {
        int num = atoi(number_str->text);
        arraylist_add(numbers, &num);
    }

    string_arraylist_free(numbers_split);

    return numbers;
}
