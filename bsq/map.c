#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "bsq.h"

#define MAX_LINE_LENGTH 1000

typedef struct {
    int fd;
    int num_lines;
    char empty_char;
    char obstacle_char;
    char full_char;
} MapInfo;

static void read_map_parameters(MapInfo *info) {
    read(info->fd, &(info->empty_char), 1);
    read(info->fd, &(info->obstacle_char), 1);
    read(info->fd, &(info->full_char), 1);
    // Consume the newline character after the declaration
    char c;
    read(info->fd, &c, 1);
}

static void read_map_line(int fd, char *line, int max_length) {
    int i = 0;
    char c;
    // Read until a newline character or the end of the line
    while (i < max_length && read(fd, &c, 1) > 0 && c != '\n') {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    // Consume remaining characters on the line if it exceeds max_length
    while (c != '\n' && read(fd, &c, 1) > 0);
}

static char **allocate_map_memory(int num_lines) {
    char **map = (char **)malloc(num_lines * sizeof(char *));
    if (map == NULL) {
        write(2, "Memory allocation failed\n", 25);
        exit(EXIT_FAILURE);
    }
    return map;
}

static void read_map_data(MapInfo *info, char **map) {
    for (int i = 0; i < info->num_lines; i++) {
        map[i] = (char *)malloc(MAX_LINE_LENGTH + 1);  // +1 for null terminator
        if (map[i] == NULL) {
            write(2, "Memory allocation failed\n", 25);
            exit(EXIT_FAILURE);
        }
        read_map_line(info->fd, map[i], MAX_LINE_LENGTH);  // Pass the allocated char array
    }
}

char **read_map(int fd, int *num_lines, char *empty_char, char *obstacle_char, char *full_char) {
    MapInfo info = {.fd = fd, .num_lines = 0};
    char num_lines_buf[16];
    // Read the number of lines
    read_map_line(fd, num_lines_buf, 16);
    info.num_lines = atoi(num_lines_buf);

    // Read the map parameters
    read_map_parameters(&info);

    // Allocate memory for the 2D map array
    char **map = allocate_map_memory(info.num_lines);

    // Read each line of the map
    read_map_data(&info, map);

    *num_lines = info.num_lines;
    *empty_char = info.empty_char;
    *obstacle_char = info.obstacle_char;
    *full_char = info.full_char;

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

