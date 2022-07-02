import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;


public class Interpreter {
    public static final int MEMORYSIZE = 30000;

    private char memory[];
    private int pointer;
    private String code;

    public Interpreter(String fileName) {
        this.memory = new char[MEMORYSIZE];
        this.pointer = 0;
        this.readfile(fileName);
    }

    private void readfile(String fileName) {
        File file = new File(fileName);
        try {
            BufferedReader reader = new BufferedReader(new FileReader(file));
            StringBuilder builder = new StringBuilder();
            String line;
            
            while ((line = reader.readLine()) != null) {
                builder.append(line);
            }

            reader.close();
            this.code = builder.toString();
        } catch (IOException err) {
            err.printStackTrace(System.err);
        }
    }

    public int run() {
        InputStreamReader streamReader = new InputStreamReader(System.in);

        for (int i = 0; i < this.code.length(); i++) {
            char ch = this.code.charAt(i);
            // Check character
            switch (ch) {
                case '+':
                    memory[pointer]++;
                    break;
                case '-':
                    if (0 < memory[pointer]) {
                        memory[pointer]--;
                    } else {
                        System.err.println("Value below 0 is not allowed");
                        return -1;
                    }
                    break;
                case '>':
                    if (pointer < MEMORYSIZE - 1) {
                        pointer++;
                    }
                    else {
                        System.err.println("Pointer reached maximum");
                        return -1;
                    }
                    break;
                case '<':
                    if (0 < pointer) {
                        pointer--;
                    }
                    else {
                        System.err.println("Pointer reached minimum");
                        return -1;
                    }
                    break;
                case ',':
                    try {
                        memory[pointer] = (char) streamReader.read();
                    } catch (IOException e) {
                        System.err.println("Error reading input character");
                        return -1;
                    }
                    break;
                case '.':
                    System.out.print(memory[pointer]);
                    break;
                case '[':
                    // If value is 0, skip the loop
                    if (memory[pointer] == 0) {
                        int loopEnd = this.skipLoop(i);
                        if (loopEnd == -1) {
                            System.err.println("Syntax error: missing closing bracket");
                            return -1;
                        }
                        i = loopEnd;
                    }
                    break;
                case ']':
                    // If value is not 0, go back to the beginning of the loop
                    if (memory[pointer] > 0) {
                        int loopStart = this.restartLoop(i);
                        if (loopStart == -1) {
                            System.err.println("Syntax error: missing opening bracket");
                            return -1;
                        }
                        i = loopStart;
                    }
                    break;
                default:
                    break;
            }
        }
        return 0;
    }

    private int skipLoop(int index) {
            // Skip the loop and ignore the loops within the loop
        int brackets = 0;
        while (true) {
            index++;
            // Reached the end without an end bracket -> error
            if (index >= this.code.length()) {
                return -1;
            }
            // Add to brackets to ignore
            else if (this.code.charAt(index) == '[') {
                brackets++;
            }
            else if (this.code.charAt(index) == ']') {
                // Ignore the closing brackets and break if there are no brackets to ignore
                if (brackets > 0) {
                    brackets--;
                }
                else {
                    break;
                }
            }
        }
        return index;
    }

    private int restartLoop(int index) {
            // Go back to corresponding opening bracket and ignore the loops within the loop
        int brackets = 0;
        while (true) {
            index--;
            // Reached the beginning without an opening bracket -> error
            if (index < 0) {
                return -1;
            }
            else if (this.code.charAt(index) == ']') {
                brackets++;
            }
            else if (this.code.charAt(index) == '[') {
                if (brackets > 0) {
                    brackets--;
                } else {
                    break;
                }
            }
        }
        return index;
    }
}
