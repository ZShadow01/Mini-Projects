#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <algorithm>
#include <array>
#include <cmath>

#include "Grid.h"


Grid::Grid() {
    this->width_ = 0;
    this->height_ = 0;
}


bool Grid::readFromFile(const std::string &fileName) {
    /*
     * Create nodes list with their positions and characters
     * Map has to be correctly formatted
     * On error return false
     */
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        return false;
    }

    this->width_ = 0;
    this->height_ = 0;
    this->nodes_.clear();
    
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.size() == 0) {
            continue;
        }

        std::istringstream stream(line);
        char ch;
        int index = 0;

        // Only accept '#' or '.', if any other character appears, return empty node list
        while (stream >> ch) {
            if (ch == Grid::BLOCK || ch == Grid::SPACE) {
                this->nodes_.emplace_back(ch, Vector(index++, this->height_));
            } else {
                file.close();
                return false;
            }
        }
        this->height_++;
        
        // Set official map width
        if (this->width_ == 0) {
            this->width_ = index;
        } 
        // If map width has already been set, check current width
        else if (index != this->width_) {
            // Return if inconsistent map width
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}


void Grid::resetNodes() {
    for (auto & node : this->nodes_) {
        node.setTotalCost(Node::DEFAULT_TOTAL_COST);
        node.setEndDistance(0);
        node.setStartDistance(0);
        node.setParentNode({0, 0});
    }
}


std::deque<Vector> Grid::findPath(const Vector &start, const Vector &end) {
    /*
     * A* algorithm
     * Move node with the least cost from openList to closedList and check for each neighbouring nodes
     * Set the heuristics accordingly and add to openList, skip if the neighbouring node is in closedList (already visited)
     */
    std::deque<Vector> openList;
    std::deque<Vector> closedList;

    std::deque<Vector> path;

    // Start from starting pos
    openList.push_back(start);

    while (!openList.empty()) {
        // Sort by total cost (ascending)
        std::sort(openList.begin(), openList.end(), [this](Vector v1, Vector v2) {
            return this->nodes_.at(v1.x + this->width_ * v1.y).getTotalCost() < this->nodes_.at(v2.x + this->width_ * v2.y).getTotalCost();
        });

        // Get current node and close node to prevent revisits
        Vector currentPos = openList.front();
        openList.pop_front();
        closedList.push_back(currentPos);

        // If the end is reached, trace back through parent nodes
        if (currentPos == end) {
            Vector &pos = currentPos;
            while (!(pos == start)) {
                path.push_front(pos);
                pos = this->nodes_.at(pos.x + pos.y * this->width_).getParentNode();
            }
            return path;
        }

        // 8 neighbouring positions surrounding the current node
        std::array<Vector, 8> neighbours {{
            {currentPos.x + 1, currentPos.y}, {currentPos.x - 1, currentPos.y},
            {currentPos.x, currentPos.y + 1}, {currentPos.x, currentPos.y - 1},
            {currentPos.x + 1, currentPos.y + 1}, {currentPos.x + 1, currentPos.y - 1},
            {currentPos.x - 1, currentPos.y + 1}, {currentPos.x - 1, currentPos.y - 1}
        }};
        for (auto & pos : neighbours) {
            // Skip if node is not within the map
            if (pos.x < 0 || pos.y < 0 || pos.x >= this->width_ || pos.y >= this->height_) {
                continue;
            }

            Node &node = this->nodes_.at(pos.x + pos.y * this->width_);

            // Skip if node is blocked
            if (node.getRepr() == Grid::BLOCK) {
                continue;
            }

            // Skip if node is closed
            if (std::find(closedList.begin(), closedList.end(), pos) != closedList.end()) {
                continue;
            }

            // Heuristics - pythagorean theorem (a^2 + b^2 = c^2)
            int startDist = node.getStartDistance() + 1;
            int endDist = pow(end.x - pos.x, 2) + pow(end.y - pos.y, 2);  // sqrt not necessary
            int totalCost = startDist + endDist;

            // Check if cost is less than previously recorded
            if (node.getTotalCost() > totalCost) {
                node.setStartDistance(startDist);
                node.setEndDistance(endDist);
                node.setTotalCost(totalCost);
                node.setParentNode(currentPos);  // Important to trace back the path

                openList.push_back(node.pos);
            }
        }
    }
    return path;
}


void Grid::findAndSavePath(const std::string &fileName, const Vector &start, const Vector &end) {    
    // Create copy from node list and change the node representative characters
    std::deque<Node> nodes(this->nodes_);
    std::deque<Vector> path = this->findPath(start, end);
    for (auto & n : path) {
        nodes.at(n.x + n.y * this->width_).setRepr(Grid::PATH);
    }
    nodes.at(start.x + start.y * this->width_).setRepr(Grid::START);
    nodes.at(end.x + end.y * this->width_).setRepr(Grid::END);

    // Open file stream
    std::ofstream file(fileName);

    if (!file.is_open()) {
        return;
    }

    // Write to file
    for (int y = 0; y < this->height_; y++) {
        for (int x = 0; x < this->width_; x++) {
            file << nodes.at(x + y * this->width_).getRepr() << ' ';
        }
        file << '\n';
    }

    file.close();
}
