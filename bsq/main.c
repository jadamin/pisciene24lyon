#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "bsq.h"

#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Read from standard input
        int num_lines = 0;
        int width = 0;
        int num_chars_read = 0;
        char c;

        // Read the header line
        while (read(0, &c, 1) > 0 && c != '\n') {
            if (c >= '0' && c <= '9') {
                width = width * 10 + (c - '0');
                num_chars_read++;
            }
        }
        
        num_lines = width;

        // Allocate memory for the 2D map array
        char **map = (char **)malloc(num_lines * sizeof(char *));
        if (map == NULL) {
            write(2, "Memory allocation failed\n", 25);
            exit(EXIT_FAILURE);
        }

        // Read and process each line of the map
        for (int i = 0; i < num_lines; i++) {
            int j = 0;
            map[i] = (char *)malloc(MAX_LINE_LENGTH + 1);
            if (map[i] == NULL) {
                write(2, "Memory allocation failed\n", 25);
                exit(EXIT_FAILURE);
            }

            while (j < MAX_LINE_LENGTH && read(0, &c, 1) > 0 && c != '\n') {
                map[i][j] = c;
                j++;
            }
            map[i][j] = '\0';
        }

        // Process the map (Add your map processing logic here)
        int max_x, max_y, max_size;
        find_largest_square(map, num_lines, '.', 'x', &max_x, &max_y, &max_size);

        // Print the marked map
        print_map(map, num_lines, max_y, max_x, max_size, 'o');

        // Free allocated memory for the map
        for (int i = 0; i < num_lines; i++) {
            free(map[i]);
        }
        free(map);
    } else {
        // Code for handling file input remains the same as before
        for (int i = 1; i < argc; i++) {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                // Handle file opening error
                continue;
            }

            int num_lines;
            char empty_char, obstacle_char, full_char;
            char **map = read_map(fd, &num_lines, &empty_char, &obstacle_char, &full_char);
            close(fd);

            if (map == NULL) {
                // Handle map reading error
                continue;
            }

            // Validate the map
            validate_map(map, num_lines, empty_char, obstacle_char, full_char);

            // Find and mark the largest square
            int max_x, max_y, max_size;
            find_largest_square(map, num_lines, empty_char, obstacle_char, &max_x, &max_y, &max_size);

            // Print the marked map
            print_map(map, num_lines, max_y, max_x, max_size, full_char);

            // Print a separator
            print_separator(num_lines);

            // Free allocated memory for the map
            free_map(map, num_lines);
        }
    }

    return 0;
}

