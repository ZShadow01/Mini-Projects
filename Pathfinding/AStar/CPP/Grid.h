#pragma once

#include <vector>
#include "Node.h"

class Grid {
    int width_;
    int height_;

    std::vector<Node> nodes_;
public:
    Grid(int width, int height);

    Node get(int x, int y);
    Node get(const Vector &pos);

    void set(int x, int y, Node node);
    void set(const Vector &pos, Node node);

    bool in(const Vector &pos);

    int getWidth() const;
    int getHeight() const;
    int getSize() const;
};
