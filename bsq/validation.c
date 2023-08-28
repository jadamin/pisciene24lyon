#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include "bsq.h"  // Include your project-specific header

static int line_length(char *line) {
    int length = 0;
    while (line[length] != '\0') {
        length++;
    }
    return length;
}

int is_valid_map(char **map, int num_lines, char empty_char, char obstacle_char, char full_char) {
    if (num_lines <= 0) {
        write(2, "Invalid number of lines\n", 24);
        return 0;  // Invalid if there are no lines
    }

    int first_line_length = line_length(map[0]);

    for (int i = 0; i < num_lines; i++) {
        int current_line_length = line_length(map[i]);

        if (current_line_length != first_line_length) {
            write(2, "Lines have different lengths\n", 30);
            return 0;  // Invalid if lines have different lengths
        }

        for (int j = 0; j < current_line_length; j++) {
            if (map[i][j] != empty_char && map[i][j] != obstacle_char && map[i][j] != full_char) {
                write(2, "Invalid character detected\n", 27);
                return 0;  // Invalid if a character is not one of the defined characters
            }
        }
    }

    return 1;  // Map is valid
}

void validate_map(char **map, int num_lines, char empty_char, char obstacle_char, char full_char) {
    if (!is_valid_map(map, num_lines, empty_char, obstacle_char, full_char)) {
        write(2, "Invalid map detected!\n", 23);
        // Handle the error or exit the program as needed
    }
}
