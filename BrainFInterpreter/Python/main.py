import sys


MEMORY_SIZE = 30000


def error(message: str):
    sys.stderr.write(message + "\n")


def skip_loop(code, index):
    # Skip the loop and ignore the loops within the loop
    brackets = 0
    while True:
        index += 1;
        # Reached the end without an end bracket -> error
        if index >= len(code):
            return -1

        # Add to brackets to ignore
        elif code[index] == '[':
            brackets += 1

        elif code[index] == ']':
            # Ignore the closing brackets and break if there are no brackets to ignore
            if (brackets > 0):
                brackets -= 1
            else:
                break
    return index


def restart_loop(code, index):
    # Go back to corresponding opening bracket and ignore the loops within the loop
    brackets = 0
    while True:
        index -= 1
        # Reached the beginning without an opening bracket -> error
        if index < 0:
            return -1

        elif code[index] == ']':
            brackets += 1

        elif code[index] == '[':
            if brackets > 0:
                brackets -= 1
            else:
                break
    return index


def run(code: str):
    # Declare necessary variables
    memory = [0] * MEMORY_SIZE
    pointer = 0
    index = 0

    # Go through each character until it reaches the end
    while index < len(code):
        if code[index] == '+':
            memory[pointer] += 1
        elif code[index] == '-':
            if 0 < memory[pointer]:
                memory[pointer] -= 1
            else:
                error("Value below 0 is not allowed")
                return -1
        elif code[index] == '>':
            if (pointer < MEMORY_SIZE - 1):
                pointer += 1
            else:
                error("Pointer reached maximum")
                return -1
        elif code[index] == '<':
            if (0 < pointer):
                pointer -= 1
            else:
                error("Pointer reached minimum")
                return -1
        elif code[index] == ',':
            in_ = input()
            memory[pointer] = in_ if len(in_) <= 1 else in_[0]
        elif code[index] == '.':
            print(chr(memory[pointer]), end='')
        elif code[index] == '[':
            # If value is 0, skip the loop
            if memory[pointer] == 0:
                loop_start = skip_loop(code, index)
                if loop_start == -1:
                    error("Syntax error: missing closing bracket")
                    return -1
                index = loop_start

        elif code[index] == ']':
            # If value is not 0, go back to the beginning of the loop
            if memory[pointer] > 0:
                loop_end = restart_loop(code, index)
                if loop_end == -1:
                    error("Syntax error: missing opening bracket")
                    return -1
                index = loop_end
        index += 1
    return 0


def main():
    # File argument is the target .bf file
    if len(sys.argv) < 2:
        error("Missing argument: target file")
        return -1
    elif not sys.argv[1].endswith(".bf"):
        error("Incorrect file type: file type has to be .bf")
        return -1

    # Open file and read content
    with open(sys.argv[1], "r") as f:
        code = f.read()
        
    # Run the file
    return run(code)


if __name__ == '__main__':
    exit(main())
