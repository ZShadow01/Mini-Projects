#include <iostream>

#include "Vector.h"


int count(const std::string &str, char target) {
    int n = 0;
    for (auto & ch : str) {
        if (ch == target) {
            n++;
        }
    }
    return n;
}


Vector::Vector() {
    this->x = 0;
    this->y = 0;
}


Vector::Vector(int x, int y) {
    this->x = x;
    this->y = y;
}


bool Vector::fromStr(const std::string &str) {
    /*
     * Extract vector from string "x,y" (no spaces)
     */
    if (count(str, ',') != 1) {
        return false;
    }

    try {
        int sepIndex = str.find(',');
        this->x = std::stoi(str.substr(0, sepIndex));
        this->y = std::stoi(str.substr(sepIndex + 1, str.size()));
    
    } catch (std::invalid_argument) {
        return false;
    }
    return true;
}


bool Vector::operator==(const Vector &vec) {
    return this->x == vec.x && this->y == vec.y;
}
