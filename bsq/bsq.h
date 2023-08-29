#ifndef BSQ_H
#define BSQ_H

// Include necessary header files
#include <stddef.h>

// Function prototypes for map-related functions
char **read_map(int fd, int *num_lines, char *empty_char, char *obstacle_char, char *full_char);
void free_map(char **map, int num_lines);
void print_map(char **map, int num_lines, int square_top, int square_left, int square_size, char full_char);
void print_separator(int num_chars);

// Function prototypes for square-related functions
void find_largest_square(char **map, int num_lines, char empty_char, char obstacle_char, int *max_x, int *max_y, int *max_size);
int is_valid_map(char **map, int num_lines, char empty_char, char obstacle_char, char full_char);

// Function prototypes for validation-related functions
void validate_map(char **map, int num_lines, char empty_char, char obstacle_char, char full_char);

#endif
