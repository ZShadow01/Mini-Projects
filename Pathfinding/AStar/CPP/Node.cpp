#include "Node.h"


Node::Node() {
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->parent_ = {-1, -1};
}


Node::Node(int x, int y) {
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->pos = {x, y};
    this->parent_ = {-1, -1};
}


Node::Node(Vector &pos) {
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->pos = pos;
    this->parent_ = {-1, -1};
}


Node::Node(int x, int y, Vector &parent) {
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->pos = {x, y};
    this->parent_ = parent;
}


Node::Node(Vector &pos, Vector &parent) {
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->pos = pos;
    this->parent_ = parent;
}


int Node::getStartDistance() const {
    return this->g;
}


int Node::getEndDistance() const {
    return this->h;
}


int Node::getTotalCost() const {
    return this->f;
}


Vector Node::getParentVector() const {
    return this->parent_;
}


void Node::setStartDistance(int dist) {
    this->g = dist;
}


void Node::setEndDistance(int dist) {
    this->h = dist;
}


void Node::setTotalCost(int cost) {
    this->f = cost;
}


void Node::setParentVector(Vector &parent) {
    this->parent_ = pos;
}


bool Node::operator==(const Node &node) {
    return this->pos == node.pos;
}
