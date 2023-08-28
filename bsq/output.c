#include <unistd.h>
#include "bsq.h"

void print_map(char **map, int num_lines, int square_top, int square_left, int square_size, char full_char) {
    for (int i = 0; i < num_lines; i++) {
        int j = 0;
        while (map[i][j] != '\0') {
            if (i >= square_top && i < square_top + square_size && j >= square_left && j < square_left + square_size) {
                write(1, &full_char, 1);  // Print the full_char for cells within the square
            } else {
                write(1, &map[i][j], 1);  // Print the map character
            }
            j++;
        }
        write(1, "\n", 1);  // Write a newline character to separate lines
    }
}

// Function to print a separator line
void print_separator(int num_chars) {
    char separator[num_chars + 1];
    for (int i = 0; i < num_chars; i++) {
        separator[i] = '-';
    }
    separator[num_chars] = '\n';
    write(1, separator, num_chars + 1);
}
