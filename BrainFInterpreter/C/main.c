#include <stdio.h>
#include <string.h>

#define MEMORY_SIZE 30000

int run(const char *code);
void error(const char *message) {
    fputs(message, stderr);
}

int main(int argc, char *argv[]) {
    // File argument is the target .bf file
    if (argc < 2) {
        error("Missing argument: target file\n");
        return -1;
    } 
    // Check file type -> return error if file name does not end with .bf
    else if (strcmp(argv[1] + strlen(argv[1]) - 3, ".bf") != 0) {
        error("Incorrect file type: file type has to be .bf\n");
        return -1;
    }

    int file_size;
    FILE *file_ptr = fopen(argv[1], "r");

    if (file_ptr == NULL) {
        fprintf(stderr, "Failed to open %s\n", argv[1]);
        return -1;
    }

    // Get file size
    fseek(file_ptr, 0, SEEK_END);
    file_size = ftell(file_ptr);
    rewind(file_ptr);

    // Set code size to file size and fill
    char code[file_size];
    memset(code, 0, sizeof(char) * file_size);
    fread(code, sizeof(char), file_size, file_ptr);

    // Close file
    fclose(file_ptr);

    // Run the file
    return run(code);
}

int run(const char *code) {
    // Declare necessary variables
    unsigned char memory[MEMORY_SIZE];
    unsigned int pointer = 0;
    const char *start_ptr = code;

    // Go through each character until it reaches the null terminator / the end
    while (*code != '\0') {
        // Check character
        switch (*code) {
            case '+':
                memory[pointer]++;
                break;
            case '-':
                if (0 < memory[pointer]) {
                    memory[pointer]--;
                } else {
                    error("Value below 0 is not allowed\n");
                    return -1;
                }
                break;
            case '>':
                if (pointer < MEMORY_SIZE - 1) {
                    pointer++;
                } else {
                    error("Pointer reached maximum\n");
                    return -1;
                }
                break;
            case '<':
                if (0 < pointer) {
                    pointer--;
                } else {
                    error("Pointer reached minimum\n");
                    return -1;
                }
                break;
            case ',':
                memory[pointer] = getchar();
                break;
            case '.':
                putchar(memory[pointer]);
                break;
            case '[':
                // If value is 0, skip the loop
                if (memory[pointer] == 0) {
                    int brackets = 0;
                    while (1) {
                        code++;
                        if (*code == '\0') {
                            error("Syntax error: missing closing bracket");
                            return -1;
                        }
                        else if (*code == '[') {
                            brackets++;
                        }
                        else if (*code == ']') {
                            if (brackets > 0) {
                                brackets--;
                            } else {
                                break;
                            }
                        }
                    }
                }
                break;
            case ']':
                // If value is not 0, go back to the beginning of the loop
                if (memory[pointer] > 0) {
                    int brackets = 0;
                    while (1) {
                        code--;
                        if (code == start_ptr) {
                            error("Syntax error: missing opening bracket");
                        }
                        else if (*code == ']') {
                            brackets++;
                        }
                        else if (*code == '[') {
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
