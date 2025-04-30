#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <fstream> // Added for file operations

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
    // Simple setter to mark a cell as alive
    void setAlive(int64_t x, int64_t y) {
        alive.insert({x, y});
    }

    // Run a single generation
    void tick() {
        // Can't modify as we iterate, so need a new set
        std::unordered_set<Cell, CellHash> next_gen;

        // get cells we need to evalate
        auto candidates = getCellsToEvaluate();

        // Apply Conway's rules
        for (const auto& cell : candidates) {
            int neighbors = neighborCount(cell);
            bool is_alive = alive.count(cell) > 0;

            // Rule 1: Living cell survives with 2-3 neighbors
            if (is_alive && (neighbors == 2 || neighbors == 3)) {
                next_gen.insert(cell);
            }
            // Rule 2: Dead cell with exactly 3 neighbors comes to life
            else if (!is_alive && neighbors == 3) {
                next_gen.insert(cell);
            }
            // Otherwise: cell is dead in next generation (no need to add it)
        }

        // update for next generaton
        alive = std::move(next_gen);
    }

    // Get all living cells (for output)
    const std::unordered_set<Cell, CellHash>& getAliveCells() const {
        return alive;
    }
};

int main() {
    std::string line;
    ConwaysGame game;

    // Open the input file from the same directory
    std::ifstream inputFile("sample_input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open sample_input.txt" << std::endl;
        return 1;
    }

    // Read Life 1.06 format
    std::getline(inputFile, line); // Skip header line

    // parse initial state
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        int64_t x, y;

        if (iss >> x >> y) {
            game.setAlive(x, y);
        }
    }

    // Close the input file
    inputFile.close();

    // Simulate 10 generations
    for (int gen = 0; gen < 10; ++gen) {
        game.tick();
    }

    // output in Life 1.06 format
    std::cout << "#Life 1.06\n";

    // Print all living cells
    for (const auto& cell : game.getAliveCells()) {
        std::cout << cell.x << " " << cell.y << "\n";
    }

    return 0;
}