#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Grid.h"

constexpr char BLOCK = '#';
constexpr char SPACE = '.';

int main(int argc, char *argv[]) {
    if (argc < 4) {
        return -1;
    }
    
    Vector start;
    start.fromStr(std::string(argv[1]));
    Vector end;
    end.fromStr(std::string(argv[2]));

    Grid grid;
    grid.readFromFile(std::string(argv[3]));
    grid.findAndSavePath("path-result.txt", start, end);
    return 0;
}
