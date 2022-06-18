/*
1. No dynamic memory allocation
2. 
*/


#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>

#include "Grid.h"


std::deque<Vector> aStarPathfinding(Grid grid, const Vector &start, const Vector &end);


int main() {
    Grid grid(10, 10);
    std::deque<Vector> path = aStarPathfinding(grid, {0, 0}, {9, 9});
    if (path.empty()) {
        std::cout << "No path found\n";
    }
    else {
        std::cout << "Path found\n";
    }
    return 0;
}


std::deque<Vector> aStarPathfinding(Grid grid, const Vector &start, const Vector &end) {
    std::deque<Vector> path;
    std::deque<Node> openList;
    std::deque<Node> closedList;

    openList.emplace_back(start.x, start.y);

    while (!openList.empty()) {
        std::sort(openList.begin(), openList.end(), [grid] (const Node &v1, const Node &v2) {
            return v1.getTotalCost() < v2.getTotalCost();
        });

        Node currentNode = openList.front();
        openList.pop_front();
        closedList.push_back(currentNode);

        if (currentNode.pos == end) {
            Vector current = currentNode.pos;
            while (grid.in(current)) {
                path.push_front(current);
                current = grid.get(current).getParentVector();
            }
            return path;
        }

        std::array<Vector, 8> neighbours{{
            {currentNode.pos.x + 1, currentNode.pos.y}, {currentNode.pos.x - 1, currentNode.pos.y},
            {currentNode.pos.x, currentNode.pos.y + 1}, {currentNode.pos.x, currentNode.pos.y - 1},
            {currentNode.pos.x + 1, currentNode.pos.y + 1}, {currentNode.pos.x + 1, currentNode.pos.y - 1},
            {currentNode.pos.x - 1, currentNode.pos.y + 1}, {currentNode.pos.x - 1, currentNode.pos.y - 1}
        }};
        for (auto & pos : neighbours) {
            if (pos.y < 0 || pos.y >= grid.getHeight() || pos.x < 0 || pos.x >= grid.getWidth()) {
                continue;
            }

            Node newNode(pos, currentNode.pos);
            
            if (std::find(closedList.begin(), closedList.end(), newNode) != closedList.end()) {
                continue;
            }

            // Heuristics
            newNode.setStartDistance(currentNode.getStartDistance() + 1);
            newNode.setEndDistance(pow(end.x - newNode.pos.x, 2) + pow(end.y - newNode.pos.y, 2));
            newNode.setTotalCost(newNode.getStartDistance() + newNode.getEndDistance());

            if (grid.get(pos).getTotalCost() > newNode.getTotalCost()) {
                grid.set(pos, newNode);
                openList.emplace_back(newNode);
            }
        }
    }

    return path;
}
