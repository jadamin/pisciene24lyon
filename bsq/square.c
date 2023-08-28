#include "bsq.h"

static int min(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

void find_largest_square(char **map, int num_lines, char empty_char, char obstacle_char, int *max_x, int *max_y, int *max_size) {
    *max_size = 0; // Size of the largest square found
    *max_x = 0;    // X-coordinate of the top-left corner of the largest square
    *max_y = 0;    // Y-coordinate of the top-left corner of the largest square

    // Create a 2D array to store the sizes of squares ending at each position
    int sizes[num_lines][num_lines];

    // Initialize the first row and column of the sizes array
    for (int i = 0; i < num_lines; i++) {
        sizes[0][i] = (map[0][i] == empty_char) ? 1 : 0;
        sizes[i][0] = (map[i][0] == empty_char) ? 1 : 0;
    }

    // Fill the sizes array and update the largest square info
    for (int i = 1; i < num_lines; i++) {
        for (int j = 1; j < num_lines; j++) {
            if (map[i][j] == obstacle_char) {
                sizes[i][j] = 0;
            } else {
                sizes[i][j] = min(sizes[i-1][j], sizes[i][j-1], sizes[i-1][j-1]) + 1;
                if (sizes[i][j] > *max_size) {
                    *max_size = sizes[i][j];
                    *max_x = j - *max_size + 1;
                    *max_y = i - *max_size + 1;
                }
            }
        }
    }

    // Mark the largest square on the map
    for (int i = *max_y; i < *max_y + *max_size; i++) {
        for (int j = *max_x; j < *max_x + *max_size; j++) {
            map[i][j] = 'x';
        }
    }
}

