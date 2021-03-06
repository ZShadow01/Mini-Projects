#include <stdio.h>

// Define the sudoku sizes
#define GROUP_WIDTH 3
#define GROUP_HEIGHT 3
#define GROUP_SIZE GROUP_WIDTH * GROUP_HEIGHT
#define GRID_WIDTH 9
#define GRID_HEIGHT 9
#define GRID_SIZE GRID_WIDTH * GRID_HEIGHT


void error(const char *message) {
    fputs(message, stderr);
}
int readfile(const char *filename, int *grid);
void print_grid(const int *grid);
int solve(int *grid, int index);


int main(int argc, char *argv[]) {
    if (argc == 1) {
        return -1;
    }

    int grid[GRID_SIZE] = {0};

    if (readfile(argv[1], grid) != 0) {
        return -1;
    }

    if (!solve(grid, 0)) {
        print_grid(grid);
    } else {
        printf("No result\n");
    }

    return 0;
}

int is_number(char ch) {
    /*
    * Check if given character is a number
    * */
    return ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' ||
        ch == '8' || ch == '9';
}

int find(const int *arr, size_t size, int target) {
    /*
    * Find the target integer in the given array and return the index (linear search)
    * */
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

void get_row(const int *grid, int *dest_row, int y) {
    /*
     * Get the row without fail
     * */
    for (int x = 0; x < GRID_WIDTH; x++) {
        dest_row[x] = grid[x + y * GRID_WIDTH];
    }
}

void get_column(const int *grid, int *dest_col, int x) {
    /*
     * Get the column without fail
     * */
    for (int y = 0; y < GRID_HEIGHT; y++) {
        dest_col[y] = grid[x + y * GRID_WIDTH];
    }
}
void get_group(const int *grid, int *group, int index) {
    /*
     * Get the group the number is in
     * */
    int x = index % GRID_WIDTH;
    int y = (index - x) / GRID_WIDTH;

    int start_x = x - x % GROUP_WIDTH;
    int start_y = y - y % GROUP_HEIGHT;

    int i = 0;
    for (int ty = 0; ty < GROUP_HEIGHT; ty++) {
        for (int tx = 0; tx < GROUP_WIDTH; tx++) {
            group[i++] = grid[start_x + tx + (start_y + ty) * GRID_WIDTH];
        }
    }
}

int check_intersections(const int *grid, int index, int target) {
    /*
     * Check for intersections in the row, column and within its group
     * */
    int x = index % GRID_WIDTH;
    int y = (index - x) / GRID_WIDTH;

    int row[GRID_WIDTH];
    get_row(grid, row, y);
    if (find(row, GRID_WIDTH, target) != -1) {
        return 1;
    }

    int col[GRID_HEIGHT];
    get_column(grid, col, x);
    if (find(col, GRID_HEIGHT, target) != -1) {
        return 1;
    }

    int flat_group[GROUP_SIZE];
    get_group(grid, flat_group, index);
    if (find(flat_group, GROUP_SIZE, target) != -1) {
        return 1;
    }
    return 0;
}

int readfile(const char *filename, int *grid) {
    /*
     * Read the file and fill the grid. Returns -1 if character is not a number and ignores newlines and spaces.
     * */
    FILE *file_ptr = fopen(filename, "r");

    if (file_ptr == NULL) {
        fprintf(stderr, "Failed to open %s\n", filename);
        return -1;
    }

    int ch;
    int i = 0;
    while ((ch = fgetc(file_ptr)) != EOF) {
        // Ignore any character that is not a number
        if ((char) ch == '\n') {
            continue;
        }

        if (is_number((char) ch) && i < GRID_SIZE) {
            grid[i++] = ch - 48;  // Convert char number to int (ASCII value)
        } else {
            fclose(file_ptr);
            error("Invalid sudoku format: Too many given numbers / characters\n");
            return -1;
        }
    }

    fclose(file_ptr);
    return 0;
}

void print_grid(const int *grid) {
    /*
     * Print the grid appropriately
     * */
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%d", grid[i]);

        int x = i % GRID_WIDTH;
        if (x == GRID_WIDTH - 1) {
            if ((i - x) / GRID_WIDTH % GROUP_HEIGHT == GROUP_HEIGHT - 1) {
                putchar('\n');
            }
            putchar('\n');
        } else {
            if (x % GROUP_WIDTH == GROUP_WIDTH - 1) {
                putchar(' ');
            }
            putchar(' ');
        }
    }
}

int solve(int *grid, int index) {
    /*
     * Solve sudoku through recursive call
     * Try all possible number candidates and eliminate all intersections within the row, column and group.
     * If it leads to an error, backtrack and try different numbers
     * If no error is found till the end, the sudoku is solved
     * */
    if (index == GRID_SIZE) {
        return 0;
    }

    // Skip if the cell already has a value
    if (grid[index] > 0) {
        return solve(grid, index + 1);
    }

    // Try different values
    for (int n = 1; n < GROUP_SIZE + 1; n++) {
        if (!check_intersections(grid, index, n)) {
            grid[index] = n;

            if (!solve(grid, index + 1)) {
                return 0;
            }
        }
        grid[index] = 0;
    }
    return 1;
}
