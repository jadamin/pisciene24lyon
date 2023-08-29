#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "bsq.h"

#define MAX_LINE_LENGTH 1000

char **read_map(int fd, int *num_lines, char *empty_char, char *obstacle_char, char *full_char) {
    char num_lines_buf[16];
    int i = 0;
    char c;

    while (read(fd, &c, 1) > 0 && c != '\n') {
        num_lines_buf[i] = c;
        i++;
    }
    num_lines_buf[i] = '\0';
    *num_lines = atoi(num_lines_buf);

    read(fd, empty_char, 1);
    read(fd, obstacle_char, 1);
    read(fd, full_char, 1);

    read(fd, &c, 1);

    char **map = (char **)malloc(*num_lines * sizeof(char *));
    if (map == NULL) {
        write(2, "Memory allocation failed\n", 25);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *num_lines; i++) {
        int j = 0;
        map[i] = (char *)malloc(MAX_LINE_LENGTH + 1);  
        if (map[i] == NULL) {
            write(2, "Memory allocation failed\n", 25);
            exit(EXIT_FAILURE);
        }

        while (j < MAX_LINE_LENGTH && read(fd, &c, 1) > 0 && c != '\n') {
            map[i][j] = c;
            j++;
        }
        map[i][j] = '\0';

        while (read(fd, &c, 1) > 0 && c != '\n');
    }

    return map;
}

void free_map(char **map, int num_lines) {
    if (map) {
        for (int i = 0; i < num_lines; i++) {
            if (map[i]) {
                free(map[i]);
            }
        }
        free(map);
    }
}
