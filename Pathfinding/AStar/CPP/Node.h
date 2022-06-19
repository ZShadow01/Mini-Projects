#pragma once

#include "Vector.h"

class Node {
    int f;
    int g;
    int h;
    Vector parent_;
    char repr_;
public:
    static constexpr int DEFAULT_TOTAL_COST = INT32_MAX;
    Vector pos;

    Node();
    Node(Vector position);
    Node(char repr, Vector position);
    
    Vector getParentNode() const;
    int getTotalCost() const;
    int getStartDistance() const;
    int getEndDistance() const;
    char getRepr() const;

    void setParentNode(Vector parent);
    void setTotalCost(int cost);
    void setStartDistance(int dist);
    void setEndDistance(int dist);
    void setRepr(char ch);
};
