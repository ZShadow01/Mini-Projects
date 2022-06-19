#pragma once

#include <string>

class Vector {
public:
    int x, y;

    Vector();
    Vector(int x, int y);

    bool fromStr(const std::string &str);

    bool operator==(const Vector &vec);
};
