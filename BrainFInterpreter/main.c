#include <stdio.h>
#include <string.h>

#define MEMORY_SIZE 30000

int run(unsigned char *memory, unsigned int *pointer, const char *code);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("Missing argument: target file\n", stderr);
        return -1;
    }

    unsigned char memory[MEMORY_SIZE];
    unsigned int pointer = 0;

    int file_size;
    FILE *file_ptr = fopen(argv[1], "r");

    if (file_ptr == NULL) {
        fprintf(stderr, "Failed to open %s\n", argv[1]);
        return -1;
    }

    fseek(file_ptr, 0, SEEK_END);
    file_size = ftell(file_ptr);
    rewind(file_ptr);

    char code[file_size];
    memset(code, 0, sizeof(char) * file_size);
    fread(code, sizeof(char), file_size, file_ptr);

    fclose(file_ptr);

    return run(memory, &pointer, code);
}

int run(unsigned char *memory, unsigned int *pointer, const char *code) {
    while (*code != '\0') {
        switch (*code) {
            case '+':
                memory[*pointer]++;
                break;
            case '-':
                if (0 < memory[*pointer]) {
                    memory[*pointer]--;
                } else {
                    fputs("Value below 0 is not allowed\n", stderr);
                    return -1;
                }
                break;
            case '>':
                if (*pointer < MEMORY_SIZE - 1) {
                    (*pointer)++;
                } else {
                    fputs("Pointer reached max\n", stderr);
                    return -1;
                }
                break;
            case '<':
                if (0 < *pointer) {
                    (*pointer)--;
                } else {
                    fputs("Pointer reached minimum\n", stderr);
                    return -1;
                }
                break;
            case ',':
                memory[*pointer] = getchar();
                break;
            case '.':
                putchar(memory[*pointer]);
                break;
            case '[':
                if (memory[*pointer] == 0) {
                    int brackets = 0;
                    while (1) {
                        code++;
                        if (*code == '[') {
                            brackets++;
                        } else if (*code == ']') {
                            if (brackets > 0) {
                                brackets--;
                            } else {
                                break;
                            }
                        } else if (*code == '\0') {
                            fputs("Syntax error, missing closing bracket\n", stderr);
                            return -1;
                        }
                    }
                }
                break;
            case ']':
                if (memory[*pointer] > 0) {
                    int brackets = 0;
                    while (1) {
                        code--;
                        if (*code == ']') {
                            brackets++;
                        } else if (*code == '[') {
                            if (brackets > 0) {
                                brackets--;
                            } else {
                                break;
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
        code++;
    }
    return 0;
}
