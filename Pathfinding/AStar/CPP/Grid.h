#pragma once

#include <string>
#include <deque>
#include "Node.h"


class Grid {
    std::deque<Node> nodes_;
    int width_;
    int height_;
public:
    static constexpr char BLOCK = '#';
    static constexpr char SPACE = '.';
    static constexpr char PATH = '+';
    static constexpr char START = '@';
    static constexpr char END = '$';

    Grid();

    bool readFromFile(const std::string &fileName);
    void resetNodes();
    std::deque<Vector> findPath(const Vector &start, const Vector &end);
    void findAndSavePath(const std::string &fileName, const Vector &start, const Vector &end);
};
