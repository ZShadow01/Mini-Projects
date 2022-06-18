#include <iostream>

#include "Grid.h"


Grid::Grid(int width, int height) {
    this->width_ = width;
    this->height_ = height;
    this->nodes_ = std::vector<Node>(width * height, Node());
    for (int i = 0; i < this->nodes_.size(); i++) {
        this->nodes_.at(i).setTotalCost(INT32_MAX);
        this->nodes_.at(i).pos.x = (i % width);
        this->nodes_.at(i).pos.y = (i - (i % width)) / width;
    }
}


Node Grid::get(int x, int y) {
    return this->nodes_.at(x + this->width_ * y);
}


Node Grid::get(const Vector &pos) {
    return this->nodes_.at(pos.x + this->width_ * pos.y);
}


void Grid::set(int x, int y, Node node) {
    this->nodes_.at(x + this->width_ * y) = node;
}


void Grid::set(const Vector &pos, Node node) {
    this->nodes_.at(pos.x + this->width_ * pos.y) = node;
}


bool Grid::in(const Vector &pos) {
    return 0 <= pos.x && 0 <= pos.y && pos.x < this->width_ && pos.y < this->height_; 
}


int Grid::getWidth() const {
    return this->width_;
}


int Grid::getHeight() const {
    return this->height_;
}


int Grid::getSize() const {
    return this->width_ * this->height_;
}
