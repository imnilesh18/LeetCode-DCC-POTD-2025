<div align="center">

# **<ins>3459. Length of Longest V-Shaped Diagonal Segment</ins>**

</div>

<p align="center">
  <a href="https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/description/">
    <img src="https://img.shields.io/badge/LeetCode-Problem-orange?style=for-the-badge&logo=leetcode" alt="LeetCode Problem">
  </a>
  <a href="https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/solutions/">
    <img src="https://img.shields.io/badge/LeetCode-Solutions-brightgreen?style=for-the-badge&logo=leetcode" alt="LeetCode Solutions">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty: Hard">
</p>

<p align="center">
    <img src="https://assets.leetcode.com/uploads/2025/01/11/length_of_longest3.jpg" alt="Problem Illustration" width="80%">
</p>

---

## 📜 Problem Statement

You are given a 2D integer matrix `grid` of size `n x m`, where each element is either `0`, `1`, or `2`.

A **V-shaped diagonal segment** is defined as:
1.  The segment starts with `1`.
2.  The subsequent elements follow this infinite sequence: `2, 0, 2, 0, ...`.
3.  The segment:
    * Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
    * Continues the sequence in the same diagonal direction.
    * Makes **at most one** clockwise 90-degree turn to another diagonal direction while maintaining the sequence.

Return the *length* of the *longest* V-shaped diagonal segment. If no valid segment exists, return 0.

---

## 📋 Constraints

-   `n == grid.length`
-   `m == grid[i].length`
-   `1 <= n, m <= 500`
-   `grid[i][j]` is either `0`, `1` or `2`.

---

## ✨ Examples

### Example 1:

|               |                                                                                                                                                                                                                                                                     |
| :------------ | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Input:** | `grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]`                                                                                                                                                                                                 |
| **Output:** | `5`                                                                                                                                                                                                                                                                 |
| **Explain:** | The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: `(0,2) → (1,3) → (2,4)`, takes a 90-degree clockwise turn at `(2,4)`, and continues as `(3,3) → (4,2)`. <br/> <div align="center"><img src="https://assets.leetcode.com/uploads/2024/12/09/matrix_1-2.jpg" width="300"></div> |

### Example 2:

|               |                                                                                                                                                                                                                                                                     |
| :------------ | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Input:** | `grid = [[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]`                                                                                                                                                                                                 |
| **Output:** | `4`                                                                                                                                                                                                                                                                 |
| **Explain:** | The longest V-shaped diagonal segment has a length of 4 and follows these coordinates: `(2,3) → (3,2)`, takes a 90-degree clockwise turn at `(3,2)`, and continues as `(2,1) → (1,0)`. <br/> <div align="center"><img src="https://assets.leetcode.com/uploads/2024/12/09/matrix_2.jpg" width="300"></div> |

### Example 3:

|               |                                                                                                                                                                                                                                                                     |
| :------------ | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Input:** | `grid = [[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]`                                                                                                                                                                                                 |
| **Output:** | `5`                                                                                                                                                                                                                                                                 |
| **Explain:** | The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: `(0,0) → (1,1) → (2,2) → (3,3) → (4,4)`. This is a straight diagonal path, which is a valid V-shape with zero turns. <br/> <div align="center"><img src="https://assets.leetcode.com/uploads/2024/12/09/matrix_3.jpg" width="300"></div> |

---

## 💡 Approach & Explanation

The problem asks for the longest "V-shaped" path starting from a `1`, following a `2, 0, 2, 0, ...` sequence, and allowing at most one 90-degree clockwise turn. This problem can be effectively solved using **Depth-First Search (DFS)** combined with **memoization** to avoid recomputing results for the same state.

<details>
<summary><strong>Detailed Walkthrough</strong></summary>

1.  **Search Initiation**: We must check every cell in the grid. If a cell `(i, j)` contains a `1`, it is a potential starting point for a V-shaped segment.

2.  **State Representation**: To uniquely identify the state of our traversal at any point, we need to keep track of:
    * `i, j`: The current coordinates.
    * `d`: The current diagonal direction. We can represent the four diagonal directions using integer indices from 0 to 3, corresponding to coordinate changes:
        * `0`: `(1, 1)` (Bottom-Right)
        * `1`: `(1, -1)` (Bottom-Left)
        * `2`: `(-1, -1)` (Top-Left)
        * `3`: `(-1, 1)` (Top-Right)
        These are ordered to facilitate 90-degree clockwise turns. A turn from direction `d` leads to `(d + 1) % 4`.
    * `canTurn`: A boolean flag that is initially `true` and becomes `false` after the first turn is made.
    * `val`: The next value (`2` or `0`) expected in the sequence.

3.  **Recursive Logic (`solve` function)**:
    * For each starting `1`, we initiate a DFS in all four possible diagonal directions.
    * The `solve(i, j, d, canTurn, val, grid)` function computes the length of the longest valid path *from the next cell* after `(i, j)`.
    * **Base Case**: The recursion terminates if the next cell is out-of-bounds or if its value does not match the expected `val`. In this case, the path ends, and we return a length of `0`.
    * **Recursive Step**: If the next cell is valid, we explore two options:
        1.  **Continue Straight**: Proceed in the same direction `d`. The path length is `1 + solve(next_i, next_j, d, canTurn, next_val, grid)`.
        2.  **Make a Turn**: If `canTurn` is `true`, we can make a 90-degree clockwise turn to `(d + 1) % 4`. The path length is `1 + solve(next_i, next_j, (d+1)%4, false, next_val, grid)`.
    * The function then returns the maximum length obtained from these valid moves.

4.  **Memoization**: Since the same state `(i, j, d, canTurn)` can be visited multiple times, we use a 4D memoization table `t[i][j][d][canTurn]` to cache the results. This avoids redundant computations and significantly improves efficiency.

5.  **Final Result**: The main loop iterates through all cells. When a `1` is found, it calls the `solve` function for all four initial directions, adds `1` (for the starting cell), and updates a global maximum. The final value of this maximum is the answer.

</details>

---

## 🖥️ C++ Solution Code

```cpp
// Intuition:
// The problem asks for the longest path in a grid under specific movement and value constraints.
// This path-finding structure suggests a recursive Depth-First Search (DFS). Since a path
// from a cell can be determined by its position, direction, and whether a turn has been made,
// we can memoize the results for each state (cell, direction, turn_status) to optimize the search
// and avoid re-calculating overlapping subproblems.

// Approach:
// 1. Iterate through every cell (i, j) of the grid. If grid[i][j] is 1, it's a valid starting point.
// 2. From each starting '1', launch a recursive search (`solve`) for all four initial diagonal directions.
// 3. The `solve` function represents the DFS traversal. Its state is defined by (i, j, direction, canTurn).
// 4. In each recursive call, calculate the coordinates of the next cell based on the current direction.
// 5. Check for base cases: if the next cell is out-of-bounds or its value doesn't match the expected
//    sequence value (alternating 2s and 0s), the path terminates, returning a length of 0.
// 6. If the move is valid, explore two recursive paths:
//    a. `keepMoving`: Continue in the same direction.
//    b. `turnAndMove`: If `canTurn` is true, make a 90-degree clockwise turn.
// 7. Use a 4D memoization table `t[i][j][d][canTurn]` to store and retrieve the results for each state,
//    ensuring that each state is computed only once.
// 8. The final answer is the maximum length found across all starting points and initial directions.

// Time Complexity: O(m * n)
// With memoization, each state (i, j, d, canTurn) is computed at most once. The total number of states
// is m * n * 4 * 2. Thus, the time complexity is proportional to the number of states, O(m * n).

// Space Complexity: O(m * n)
// The space complexity is dominated by the memoization table `t` of size m * n * 4 * 2.

class Solution {
public:
    // Directions: 0:BR, 1:BL, 2:TL, 3:TR (in clockwise order)
    vector<vector<int>> directions = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    int m, n;
    int t[501][501][4][2]; // Memoization table: t[row][col][direction][canTurn]

    // Recursive DFS function with memoization
    int solve(int i, int j, int d, bool canTurn, int val, vector<vector<int>>& grid) {
        // Calculate coordinates of the next cell
        int i_ = i + directions[d][0];
        int j_ = j + directions[d][1];

        // Base Case: If next cell is invalid (out of bounds or wrong value), path ends.
        if (i_ < 0 || i_ >= m || j_ < 0 || j_ >= n || grid[i_][j_] != val) {
            return 0;
        }

        // Return cached result if this state has been computed before
        if (t[i_][j_][d][canTurn] != -1) {
            return t[i_][j_][d][canTurn];
        }

        int result = 0;
        
        // Option 1: Continue straight
        // Length is 1 (for the current step) + length of the rest of the path.
        // The next expected value alternates between 2 and 0.
        int keepMoving = 1 + solve(i_, j_, d, canTurn, val == 2 ? 0 : 2, grid);
        result = max(result, keepMoving);

        // Option 2: Turn 90-degrees clockwise, if a turn is available
        if (canTurn) {
            // New direction is (d+1)%4. `canTurn` becomes false after this.
            int turnAndMove = 1 + solve(i_, j_, (d + 1) % 4, false, val == 2 ? 0 : 2, grid);
            result = max(result, turnAndMove);
        }
        
        // Cache and return the maximum length found from this state
        return t[i_][j_][d][canTurn] = result;
    }

    int lenOfVDiagonal(vector<vector<int>>& grid) {
        // Initialize grid dimensions
        m = grid.size();
        n = grid[0].size();
        
        // Initialize memoization table with -1 (uncomputed)
        memset(t, -1, sizeof(t));

        int result = 0;

        // Iterate through the grid to find every '1' as a potential start
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    // A single '1' itself is a valid segment of length 1.
                    result = max(result, 1);
                    
                    // From this '1', explore paths starting in all 4 diagonal directions
                    for (int d = 0; d <= 3; d++) {
                        // Total length = 1 (for the start cell) + path length from the next cell.
                        // The next value required after a '1' is always '2'.
                        result = max(result, 1 + solve(i, j, d, true, 2, grid));
                    }
                }
            }
        }
        return result;
    }
};

/*
*
* Dry Run
*
* Grid: [[2,2,1,2,2], [2,0,2,2,0], ...]
* Start Point: (0, 2), where grid[0][2] = 1.
* Initial `result` = 1.
*
* Trace for initial direction `d=0` (Bottom-Right, {1,1}):
*
* Call `solve(i=0, j=2, d=0, canTurn=true, val=2)`
* - Next cell: (1, 3). `grid[1][3]` is 2. Valid move.
* - Now at (1,3), explore from here:
* - `keepMoving`: `1 + solve(1, 3, d=0, canTurn=true, val=0)`
* - Next cell: (2, 4). `grid[2][4]` is 0. Valid.
* - Now at (2,4), explore:
* - `keepMoving`: `1 + solve(2, 4, d=0, true, 2)`. Next (3,5) is out of bounds. Returns 0. Path: (0,2)->(1,3)->(2,4). Length = 3.
* - `turnAndMove`: `1 + solve(2, 4, d=1, false, 2)` (Turn to Bottom-Left)
* - Next cell: (3, 3). `grid[3][3]` is 2. Valid.
* - Now at (3,3), explore (canTurn is now false):
* - `keepMoving`: `1 + solve(3, 3, d=1, false, 0)`. Next (4,2). `grid[4][2]` is 0. Valid.
* - Now at (4,2), explore: `solve(4, 2, ...)` -> next (5,1) is out of bounds, returns 0.
* - This path segment has length 1 + 1 + 1 + 1 + 1 = 5.
* - Path: (0,2) -> (1,3) -> (2,4) -> (turn) -> (3,3) -> (4,2).
*
* The recursion unwinds, returning the maximum length of 5. This value updates the global `result`.
* The algorithm continues checking all other starting points and directions, but 5 remains the maximum.
*
*/
```

---

## 🔑 Key Insights

-   **State is Key**: The problem's complexity is managed by correctly defining the state for the recursion: `(position, direction, turn_availability)`. This allows for effective memoization.
-   **Systematic Exploration**: By starting a new DFS from every `1` and for each of the four initial directions, we ensure all possible valid paths are explored.
-   **Clockwise Turns**: The directional vectors `{{1, 1}, {1, -1}, {-1, -1}, {-1, 1}}` are ordered to make clockwise turns simple. A turn is just `(d + 1) % 4`.

---

## 🔗 Tags

<p align="left">
  <img src="https://img.shields.io/badge/Topic-Matrix-blue?style=for-the-badge" alt="Matrix">
  <img src="https://img.shields.io/badge/Topic-DFS-green?style=for-the-badge" alt="Depth-First Search">
  <img src="https://img.shields.io/badge/Topic-Memoization-purple?style=for-the-badge" alt="Memoization">
  <img src="https://img.shields.io/badge/Topic-Dynamic%20Programming-yellow?style=for-the-badge" alt="Dynamic Programming">
</p>

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **Note**: This solution is provided for educational purposes. The original problem description and rights belong to LeetCode. Please refer to the [official problem statement](https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/description/) on LeetCode.

---

## 👨‍💻 Author

<p align="left">
  <a href="https://github.com/imnilesh18">
    <img src="https://img.shields.io/badge/Author-imnilesh18-blue?style=for-the-badge&logo=github" alt="Author: imnilesh18">
  </a>
</p>