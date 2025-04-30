# Conway's Game of Life Implementation

This is my implementation of Conway's Game of Life in 64-bit signed integer space as specified in the challenge.

## Challenge

Implement Conway's Game of Life in 64-bit signed integer space.

Imagine a 2D grid - each cell (coordinate) can be either "alive" or "dead". Every generation of the simulation, the system ticks forward. Each cell's value changes according to the following:

- If an "alive" cell had less than 2 or more than 3 alive neighbors (in any of the 8 surrounding cells), it becomes dead.
- If a "dead" cell had *exactly* 3 alive neighbors, it becomes alive.

The input is a list of integer coordinates for live cells in the Life 1.06 format. They could be anywhere in the signed 64-bit range, making the board potentially very large.

## Implementation Approach

The key challenge in this problem is handling the potentially enormous grid space (with 64-bit coordinates). Using a traditional 2D array would be impossible, so I implemented a sparse representation that only stores the living cells using an unordered_set with a custom hash function.

## Key Design Decisions:

1. **Sparse Representation**: Only living cells are stored, which is memory-efficient for the vast 64-bit coordinate space.

2. **Cell Checking Optimization**: Rather than checking every possible cell in the infinite grid, the implementation only evaluates living cells and their immediate neighbors, as these are the only cells that could potentially change state.

3. **Hash Function**: A custom hash function for the Cell coordinates ensures efficient lookups in the unordered_set.

4. **Direct Output**: The implementation prints the cells directly from the unordered_set without sorting, matching the requirements in the prompt.

5. **File Input**: The program reads initial cell positions from a file named "sample_input.txt" located in the same directory as the executable.


## Time and Space Complexity
[<img src="https://img.youtube.com/vi/g2o22C3CRfU/maxresdefault.jpg" width="600" height="auto" alt="Big-O explainer video">](https://www.youtube.com/watch?v=g2o22C3CRfU "Big-O explainer video")

**Time Complexity**: O(n) where n is the number of living cells, since we only need to evaluate living cells and their immediate neighbors.
- **Space Complexity**: O(n) as we only store the living cells.

## Trade-offs Considered

1. **Set vs. Map**: I chose an unordered_set over an unordered_map because we only need to track whether a cell is alive (not store additional data).
2. **Single File vs. Multi-File**: For this exercise, I kept everything in a single file for simplicity, but noted how it would be structured in a production environment.
    ### Project Structure

    For this coding challenge, I submitted a single file implementation for simplicity and ease of review. In a production environment, I would structure the project as follows:

    ```
    ├── include/
    │   ├── Cell.h         (Cell struct and CellHash)
    │   ├── ConwaysGame.h  (Game class declaration)
    ├── src/
    │   ├── ConwaysGame.cpp (Game class implementation)
    │   ├── main.cpp       (main function)
    └── CMakeLists.txt     (or Makefile)
    ```

    This structure would better separate concerns and improve maintainability for long-term development.

3. **Hash Function**: The hash function is designed to be simple but effective for this specific use case. In a production environment, I might use a more sophisticated hash function if collision patterns became an issue with very large datasets.
4. **Edge Cases**: The implementation correctly handles the entire 64-bit signed integer range without overflow issues.
5. **File Input**: Using a hardcoded file name means less flexibility but simpler usage. In a production environment, I would add command-line argument support to specify different input files.
## Dev Process

This implementation is my own. I didn't use AI to generate any code assets. 
- I used CLION IDE with normal intellisense. 
- I did use AI to do the initial format of this readme.
- I then filled in the readme myself for pertinent info.

In a normal environment I likely would use AI to perform first pass or mundane tasks like loop generations etc. In my experience
AI is inconsistent in evaluating large codebases and falls short of holistic architectural decisions. One day this will change, but today.
