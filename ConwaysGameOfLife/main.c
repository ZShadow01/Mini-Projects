#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define MAP_SIZE MAP_WIDTH * MAP_HEIGHT

#define ALIVE '1'
#define DEAD '0'

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

    int generation = 0;
    while (generation < 10) {
        print_map(map);
        sleep(1);
        next_generation(map);
        generation++;
        puts("\033[H\033[2J");
    }
    return 0;
}

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
        if ((char) ch == '\n' || ch == ' ') {
            continue;
        }

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

void print_map(const char *map) {
    for (int i = 0; i < MAP_SIZE; i++) {
        putchar(map[i]);
        if (i % MAP_WIDTH == MAP_WIDTH - 1) {
            putchar('\n');
        } else {
            putchar(' ');
        }
    }
}

void next_generation(char *map) {
    char next[MAP_SIZE];
    memset(next, 0, MAP_SIZE * sizeof(char));

    for (int i = 0; i < MAP_SIZE; i++) {
        const char cell = map[i];
        int x = i % MAP_WIDTH;
        int y = (i - x) / MAP_WIDTH;

        int live_neighbours = 0;
        int neighbour_indices[] = {
                i - 1, i + 1, i - MAP_WIDTH, i + MAP_WIDTH,
                i - 1 - MAP_WIDTH, i - 1 + MAP_WIDTH, i + 1 - MAP_WIDTH, i + 1 + MAP_WIDTH
        };
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

        // Underpopulation
        if (cell == ALIVE && live_neighbours < 2) {
            next[i] = DEAD;
        }
        // Overpopulation
        else if (cell == ALIVE && live_neighbours > 3) {
            next[i] = DEAD;
        }
        // Reproduction
        else if (cell == DEAD && live_neighbours == 3) {
            next[i] = ALIVE;
        }
        // Live on
        else {
            next[i] = map[i];
        }
    }

    strcpy(map, next);
}
