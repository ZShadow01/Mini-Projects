/*
 * BRAINF*CK INTERPRETER WITHOUT DYNAMIC MEMORY ALLOCATION
 */

#include <stdio.h>
#include <string.h>

#define MEMORY_SIZE 30000

int run(const char *code);
void error(const char *message) {
    fputs(message, stderr);
}
const char *skip_loop(const char *code_ptr);
const char *restart_loop(const char *code_ptr, const char *start_ptr);


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
                }
                else {
                    error("Pointer reached maximum\n");
                    return -1;
                }
                break;
            case '<':
                if (0 < pointer) {
                    pointer--;
                }
                else {
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
                    const char *loop_end = skip_loop(code);
                    if (loop_end == NULL) {
                        error("Syntax error: missing closing bracket\n");
                        return -1;
                    }
                code = loop_end;
                }
                break;
            case ']':
                // If value is not 0, go back to the beginning of the loop
                if (memory[pointer] > 0) {
                    const char *loop_start = restart_loop(code, start_ptr);
                    if (loop_start == NULL) {
                        error("Syntax error: missing opening bracket\n");
                        return -1;
                    }
                    code = loop_start;
                }
                break;
            default:
                break;
        }
        code++;
    }
    return 0;
}


const char *skip_loop(const char *code_ptr) {
    // Skip the loop and ignore the loops within the loop
    int brackets = 0;
    while (1) {
        code_ptr++;
        // Reached the end without an end bracket -> error
        if (*code_ptr == '\0') {
            return NULL;
        }
        // Add to brackets to ignore
        else if (*code_ptr == '[') {
            brackets++;
        }
        else if (*code_ptr == ']') {
            // Ignore the closing brackets and break if there are no brackets to ignore
            if (brackets > 0) {
                brackets--;
            }
            else {
                break;
            }
        }
    }
    return code_ptr;
}


const char *restart_loop(const char *code_ptr, const char *start_ptr) {
    // Go back to corresponding opening bracket and ignore the loops within the loop
    int brackets = 0;
    while (1) {
        code_ptr--;
        // Reached the beginning without an opening bracket -> error
        if (code_ptr == start_ptr && *code_ptr != ']') {
            return NULL;
        }
        else if (*code_ptr == ']') {
            brackets++;
        }
        else if (*code_ptr == '[') {
            if (brackets > 0) {
                brackets--;
            } else {
                break;
            }
        }
    }
    return code_ptr;
}
