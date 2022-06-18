#pragma once


class Vector {
public:
    int x, y;
    Vector();
    Vector(int x, int y);

    bool operator==(const Vector &vec);
};
