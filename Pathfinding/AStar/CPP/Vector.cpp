#include "Vector.h"


Vector::Vector() {
    this->x = 0;
    this->y = 0;
}


Vector::Vector(int x, int y) {
    this->x = x;
    this->y = y;
}


bool Vector::operator==(const Vector &vec) {
    return this->x == vec.x && this->y == vec.y;
}
