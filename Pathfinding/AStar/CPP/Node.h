#pragma once

#include "Vector.h"

class Node {
    int f;  // Total cost
    int g;  // Distance from start to current
    int h;  // Distance from current to destination

    Vector parent_;
public:
    Vector pos;

    Node();
    Node(int x, int y);
    Node(Vector &pos);
    Node(int x, int y, Vector &parent);
    Node(Vector &pos, Vector &parent);

    int getStartDistance() const;
    int getEndDistance() const;
    int getTotalCost() const;
    Vector getParentVector() const;

    void setStartDistance(int dist);
    void setEndDistance(int dist);
    void setTotalCost(int cost);
    void setParentVector(Vector &parent);

    bool operator==(const Node &node);
};
