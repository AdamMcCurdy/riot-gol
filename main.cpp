#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdint>

// represents a cell in our infinite grid
struct Cell {
    int64_t x;
    int64_t y;

    // need this for comparison in containers
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};

// Need a custom hash for our unordered_set
struct CellHash {
    std::size_t operator()(const Cell& cell) const {
        // This is a bit hacky but works well for distributing coordinates
        auto x_hash = std::hash<int64_t>{}(cell.x);
        auto y_hash = std::hash<int64_t>{}(cell.y);
        return x_hash ^ (y_hash + 0x9e3779b9 + (x_hash << 6) + (x_hash >> 2));
    }
};

class ConwaysGame {

};

int main() {


    return 0;
}