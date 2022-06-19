#include "Node.h"


Node::Node() {
    this->f = Node::DEFAULT_TOTAL_COST;
    this->g = 0;
    this->h = 0;
    this->repr_ = '\0';
}


Node::Node(Vector position) {
    this->f = Node::DEFAULT_TOTAL_COST;
    this->g = 0;
    this->h = 0;
    this->repr_ = '\0';
    this->pos = position;
}


Node::Node(char repr, Vector position) {
    this->f = Node::DEFAULT_TOTAL_COST;
    this->g = 0;
    this->h = 0;
    this->repr_ = repr;
    this->pos = position;
}

Vector Node::getParentNode() const {
    return this->parent_;
}


int Node::getTotalCost() const {
    return this->f;
}


int Node::getStartDistance() const {
    return this->g;
}


int Node::getEndDistance() const {
    return this->h;
}


char Node::getRepr() const {
    return this->repr_;
}


void Node::setParentNode(Vector parent) {
    this->parent_ = parent;
}


void Node::setTotalCost(int cost) {
    this->f = cost;
}


void Node::setStartDistance(int dist) {
    this->g = dist;
}


void Node::setEndDistance(int dist) {
    this->h = dist;
}


void Node::setRepr(char ch) {
    this->repr_ = ch;
}
