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
private:
    // just store living cells - much more efficient for sparse board
    std::unordered_set<Cell, CellHash> alive;

    int neighborCount(const Cell& cell) const {
        int neighbors = 0;

        // CHECK THE 8 SURROUNDING CELLS
        for (int x_offset = -1; x_offset <= 1; ++x_offset) {
            for (int y_offset = -1; y_offset <= 1; ++y_offset) {
                // Skip the cell itself
                if (x_offset == 0 && y_offset == 0)
                    continue;

                // create neighbor cell and check if it's alive
                Cell neighbor = {cell.x + x_offset, cell.y + y_offset};
                if (alive.count(neighbor) > 0) {
                    neighbors++;
                }
            }
        }

        return neighbors;
    }

    // this is a key optimzation - only check cells that might change
    std::unordered_set<Cell, CellHash> getCellsToEvaluate() const {
        std::unordered_set<Cell, CellHash> candidates;

        // need to check all living cells and their neighbors
        for (const auto& cell : alive) {
            // The cell itself might die
            candidates.insert(cell);

            // Its neighbors might come to life
            for (int x_offset = -1; x_offset <= 1; ++x_offset) {
                for (int y_offset = -1; y_offset <= 1; ++y_offset) {
                    Cell neighbor = {cell.x + x_offset, cell.y + y_offset};
                    candidates.insert(neighbor);
                }
            }
        }

        return candidates;
    }

public:

};

int main() {


    return 0;
}