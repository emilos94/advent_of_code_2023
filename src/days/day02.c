#include "../core/file_reader.h"

struct CubeSet {
    int red, green, blue;
};
typedef struct CubeSet CubeSet;

struct Game {
    int id;
    ArrayList* cubesets;
};
typedef struct Game Game;

int parse_cubeset_number(String* str) {
    ArrayList* split = string_split(str, ' ');
    String* num_str = arraylist_get(split, 0);
    int result = atoi(num_str->text);
    string_arraylist_free(split);
    return result;
}

ArrayList* parse_cubeset_list(String* game_cubesets_str) {
    ArrayList* cubeset_results = arraylist_create(10, sizeof(CubeSet));
    ArrayList* game_cubesets = string_split(game_cubesets_str, ';');
    ARRAYLIST_FOREACH(game_cubesets, String, cubeset_str) {
        CubeSet result;
        ArrayList* cubesets = string_split(cubeset_str, ',');

        ARRAYLIST_FOREACHI(cubesets, idx, String, cubeset) {
            int amount = parse_cubeset_number(cubeset);
            if (string_contains(cubeset, "red")) {
                result.red = amount;
            }
            else if(string_contains(cubeset, "blue")) {
                result.blue = amount;
            }
            else if(string_contains(cubeset, "green")) {
                result.green = amount;
            }
        }

        arraylist_add(cubeset_results, &result);
        string_arraylist_free(cubesets);
    }
    
    string_arraylist_free(game_cubesets);

    return cubeset_results;
}

b8 is_impossible(CubeSet* cube_set, int red, int blue, int green) {
    return cube_set->red > red || cube_set->blue > blue || cube_set->green > green;
}

b8 is_impossible_partone(void* cube_set_ptr) {
    CubeSet* cube_set = cube_set_ptr;
    return cube_set->red > 12 || cube_set->green > 13 || cube_set->blue > 14;
}

int part_one_solve(ArrayList* games) {
    int total = 0;
    ARRAYLIST_FOREACH(games, Game, game) {
        if (!arraylist_anymatch(game->cubesets, is_impossible_partone)) {
            total += game->id;
        }
    }
    return total;
}

int main(void) {
    FileLineResult result = file_readlines("res/day02.txt");

    ArrayList* games = arraylist_create(10, sizeof(Game));

    ARRAYLIST_FOREACH(result.file_lines, String, line) {
        ArrayList* game_split = string_split(line, ':');
        String* game_id_str = arraylist_get(game_split, 0);
        String* game_cubesets_str = arraylist_get(game_split, 1);

        Game game;
        game.id = atoi(game_id_str->text + 5);
        game.cubesets = parse_cubeset_list(game_cubesets_str);

        arraylist_add(games, &game);
    }

    int part_one = part_one_solve(games);

    printf("part one: %d\n", part_one);
}