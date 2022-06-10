#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Map constants
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define MAP_SIZE MAP_WIDTH * MAP_HEIGHT

// Cell status
#define ALIVE '1'
#define DEAD '0'

// Representative characters
#define REPR_ALIVE '0'
#define REPR_DEAD ' '


int readfile(const char *filename, char *map);

void print_map(const char *map);

void next_generation(char *map);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("Missing argument\n", stderr);
        return -1;
    }

    char map[MAP_SIZE];
    if (readfile(argv[1], map) != 0) {
        return -1;
    }

    // Run forever until user closes window or Ctrl-C
    while (1) {
        puts("\033[H\033[2J");
        puts("Use CTRL-C combination to stop generation\n");
        print_map(map);
        usleep(350000);
        next_generation(map);
    }
    return 0;
}

/*
 * Read map file -> has to be exactly MAP_WIDTHxMAP_HEIGHT big, else returns failure code
 * */
int readfile(const char *filename, char *map) {
    FILE *file_ptr;
#ifdef _WIN32
    fopen_s(&file_ptr, filename, "r");
#else
    file_ptr = fopen(filename, "r");
#endif

    if (file_ptr == NULL) {
        fprintf(stderr, "Failed to open %s\n", filename);
        return -1;
    }

    int ch;
    int index = 0;
    while ((ch = fgetc(file_ptr)) != EOF && index < MAP_SIZE) {
        if ((char) ch == DEAD || (char) ch == ALIVE) {
            map[index++] = (char) ch;
        }
    }
    fclose(file_ptr);

    map[index] = '\0';
    if (index + 1 < MAP_SIZE) {
        fprintf(stderr, "Map is not fully filled. Required map size: %d\n", MAP_SIZE);
        return -1;
    }
    return 0;
}

/*
 * Print current map / generation
 * */
void print_map(const char *map) {
    // Print top border
    putchar(' ');
    for (int i = 0; i < MAP_WIDTH; i++) {
        putchar('-');
        putchar('-');
    }
    putchar('\n');
    for (int i = 0; i < MAP_SIZE; i++) {
        int x = i % MAP_WIDTH;
        // Print left border
        if (x == 0) {
            putchar('|');
            putchar(' ');
        }

        if (map[i] == ALIVE) {
            putchar(REPR_ALIVE);
        } else {
            putchar(REPR_DEAD);
        }

        // Print right border
        if (x == MAP_WIDTH - 1) {
            putchar('|');
            putchar('\n');
        }
        // Spacing between each character
        else {
            putchar(' ');
        }
    }

    // Print bottom border
    putchar(' ');
    for (int i = 0; i < MAP_WIDTH; i++) {
        putchar('-');
        putchar('-');
    }
    putchar('\n');
}

void next_generation(char *map) {
    /*
     * Generate the next cells on the map
     * */

    char next[MAP_SIZE];
    memset(next, 0, MAP_SIZE * sizeof(char));

    // Iterate through all cells
    for (int i = 0; i < MAP_SIZE; i++) {
        const char cell = map[i];
        int x = i % MAP_WIDTH;
        int y = (i - x) / MAP_WIDTH;

        int live_neighbours = 0;
        int neighbour_indices[] = {
                i - 1, i + 1, i - MAP_WIDTH, i + MAP_WIDTH,
                i - 1 - MAP_WIDTH, i - 1 + MAP_WIDTH, i + 1 - MAP_WIDTH, i + 1 + MAP_WIDTH
        };
        // Count live neighbours
        for (int n = 0; n < 8; n++) {
            int n_x = neighbour_indices[n] % MAP_WIDTH;
            int n_y = (neighbour_indices[n] - n_x) / MAP_WIDTH;
            if (((0 <= n_x && n_x <= x) || (x <= n_x && n_x < MAP_WIDTH)) &&
                ((0 <= n_y && n_y <= y) || (y <= n_y && n_y < MAP_HEIGHT))) {
                if (map[neighbour_indices[n]] == ALIVE) {
                    live_neighbours++;
                }
            }
        }

        // Any live cell with fewer than 2 live neighbours dies, as if by underpopulation
        if (cell == ALIVE && live_neighbours < 2) {
            next[i] = DEAD;
        }
            // Any live cell with more than 3 live neighbours dies, as if by overpopulation
        else if (cell == ALIVE && live_neighbours > 3) {
            next[i] = DEAD;
        }
            // Any dead cell with exactly 3 live neighbours becomes a live cell, as if by reproduction
        else if (cell == DEAD && live_neighbours == 3) {
            next[i] = ALIVE;
        }
            // Any live cell with two or three live neighbours lives on to the next generation.
        else {
            next[i] = map[i];
        }
    }

    // Copy new generation to map
    strcpy(map, next);
}
