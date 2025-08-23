# 🔱 3197. Find the Minimum Area to Cover All Ones II

<p align="center">
  <strong>Difficulty: Hard</strong>
</p>

<p align="center">
  <a href="https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/description" target="_blank">
    <img src="https://img.shields.io/badge/Problem%20Link-LeetCode-blue?style=for-the-badge&logo=leetcode" alt="LeetCode Problem Link">
  </a>
</p>

---

## 📝 Problem Statement

You are given a 2D **binary** array `grid`. You need to find 3 **non-overlapping** rectangles having **non-zero** areas with horizontal and vertical sides such that all the 1's in `grid` lie inside these rectangles.

Return the _minimum_ possible sum of the area of these rectangles.

**Note** that the rectangles are allowed to touch.

---

## ⚙️ Constraints

- `1 <= grid.length, grid[i].length <= 30`
- `grid[i][j]` is either `0` or `1`.
- The input is generated such that there are at least three `1`'s in `grid`.

---

## 🎨 Examples

### Example 1:

| Input                      | Output |
| :------------------------- | :----- |
| `grid = [[1,0,1],[1,1,1]]` | `5`    |

**Explanation:**
The 1's can be covered by three rectangles as shown below, with a total area of 2 + 2 + 1 = 5.

<p align="center">
  <img src="https://assets.leetcode.com/uploads/2024/05/14/example0rect21.png" alt="Example 1" width="400"/>
</p>

### Example 2:

| Input                          | Output |
| :----------------------------- | :----- |
| `grid = [[1,0,1,0],[0,1,0,1]]` | `5`    |

**Explanation:**
The 1's can be covered by three rectangles with areas 3, 1, and 1, for a total area of 5.

<p align="center">
  <img src="https://assets.leetcode.com/uploads/2024/05/14/example1rect2.png" alt="Example 2" width="400"/>
</p>

---

## 💡 Approach

The core idea is to find the minimum area required to cover all `1`s using three non-overlapping rectangles. Since the optimal solution is unknown, we must explore all possible ways to partition the grid into three rectangular sections.

Any division of the grid into three rectangles can be achieved by making two straight-line cuts. The key insight is that there are only a few fundamental ways to make these two cuts:

1.  **Two Horizontal Cuts:** Two parallel horizontal lines divide the grid into three horizontal rectangular strips (top, middle, bottom).
2.  **Two Vertical Cuts:** Two parallel vertical lines divide the grid into three vertical rectangular strips (left, middle, right).
3.  **One Horizontal & One Vertical Cut:** This creates a 'T' shape. This configuration has four variations:
    - Top rectangle + Bottom-Left + Bottom-Right
    - Bottom rectangle + Top-Left + Top-Right
    - Left rectangle + Top-Right + Bottom-Right
    - Right rectangle + Top-Left + Bottom-Left

Instead of coding all these variations separately, we can simplify. The cases with vertical cuts are just 90-degree rotations of the cases with horizontal cuts. This leads to a powerful simplification:

1.  **Enumerate** all partitions for the original grid based on:
    - Two horizontal cuts.
    - One horizontal and one vertical cut (two sub-cases: a full top rectangle or a full bottom rectangle).
2.  **Rotate** the entire grid by 90 degrees.
3.  **Repeat** the same enumeration process on the rotated grid. This will implicitly cover all the vertical cut configurations from the original grid.

For each of the three sub-rectangles created by a partition, we calculate the minimum bounding box required to cover all the `1`s within that specific sub-rectangle. This is the same logic as the "Find the Minimum Area to Cover All Ones I" problem. The sum of these three minimum areas gives the total area for that specific partition. We keep track of the minimum total area found across all possible partitions and their rotations.

The algorithm is as follows:

1.  Create a `utility` function that calculates the minimum area by trying all partitions for a given grid.
    - It iterates through all possible pairs of horizontal splits.
    - It iterates through all possible single horizontal and single vertical splits.
    - For each partition, it calls a `minimumArea` helper to find the tightest bounding box for the `1`s in each of the three sub-grids.
    - It returns the minimum total area found.
2.  Call the `utility` function on the original `grid`.
3.  Create a new grid by rotating the original `grid` 90 degrees clockwise.
4.  Call the `utility` function on the `rotatedGrid`.
5.  The final answer is the minimum of the results from the two calls.

---

## 💻 Solution Code

### Optimized Solution (C++)

```cpp
// Intuition: The problem requires partitioning a 2D grid into three non-overlapping rectangles to cover all '1's with minimum total area.
// This can be achieved by making two straight cuts. We can exhaustively check all possible cutting configurations.
// The key configurations are: two parallel horizontal cuts, two parallel vertical cuts, and one horizontal plus one vertical cut.
// A crucial simplification is that vertical cut configurations are equivalent to horizontal cut configurations on a rotated grid.
// Thus, we only need to implement the logic for horizontal and 'T' shaped cuts and apply it to both the original and a 90-degree rotated version of the grid.

// Approach:
// 1. Create a helper function `minimumArea` that takes the coordinates of a sub-grid and calculates the smallest bounding box area required to cover all '1's within it.
// 2. Create a `utility` function that tries all possible ways to split a given grid into three rectangles:
//    a. (Two horizontal splits): Iterate through all pairs of horizontal lines (split1, split2) to form top, middle, and bottom rectangles.
//    b. (One horizontal, one vertical split): Iterate through all combinations of one horizontal line (rowSplit) and one vertical line (colSplit). This covers two cases:
//       i.  A single top rectangle, with the bottom part split into left and right.
//       ii. A single bottom rectangle, with the top part split into left and right.
//    c. For each split configuration, calculate the sum of the areas of the three sub-rectangles using the `minimumArea` helper and update the minimum result.
// 3. Create a helper function `rotateClockWise` to rotate the grid by 90 degrees.
// 4. In the main function `minimumSum`:
//    a. Call the `utility` function on the original grid to find the minimum area for all horizontal-based partitions.
//    b. Rotate the grid.
//    c. Call the `utility` function on the rotated grid to cover all vertical-based partitions.
//    d. Return the minimum of the two results.

// Time Complexity: O(m^2 * n^2) - The utility function has nested loops up to O(m*n) for splits. Inside, it calls minimumArea which is O(m*n).
// The dominant part is the double loop for 'T' splits (O(m*n)) calling minimumArea three times (O(m*n)), resulting in O(m^2 * n^2). Constraints are small (30x30), so this is acceptable.
// Space Complexity: O(m*n) - Primarily for storing the rotated grid.

class Solution {
public:

    // Rotates the grid 90 degrees clockwise.
    vector<vector<int>> rotateClockWise(vector<vector<int>>& grid) {
        int m = grid.size(); // Original rows
        int n = grid[0].size(); // Original columns

        // The new grid will have dimensions n x m.
        vector<vector<int>> rotatedGrid(n, vector<int>(m));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                // Map original (i, j) to new (j, m-i-1).
                rotatedGrid[j][m-i-1] = grid[i][j];
            }
        }
        return rotatedGrid;
    }

    // Calculates the minimum bounding box area for '1's in a specified sub-grid.
    int minimumArea(int startRow, int endRow, int startCol, int endCol, vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Initialize boundaries to find the min/max row/col containing a '1'.
        int minRow = m;
        int maxRow = -1;
        int minCol = n;
        int maxCol = -1;
        bool foundOne = false; // Track if any '1' is found.

        for(int i = startRow; i < endRow; i++) {
            for(int j = startCol; j < endCol; j++) {
                if(grid[i][j] == 1) {
                    foundOne = true;
                    minRow = min(minRow, i);
                    maxRow = max(maxRow, i);
                    minCol = min(minCol, j);
                    maxCol = max(maxCol, j);
                }
            }
        }
        // If no '1's are in the sub-grid, the area is 0.
        if (!foundOne) return 0;
        return (maxRow - minRow + 1) * (maxCol - minCol + 1);
    }

    // Main logic to test all partition types on a given grid.
    int utility(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int result = INT_MAX;

        // Case 1: One horizontal split and one vertical split.
        for(int rowSplit = 1; rowSplit < m; rowSplit++) {
            for(int colSplit = 1; colSplit < n; colSplit++) {

                // Configuration A: Full top, bottom split into left/right.
                int top = minimumArea(0, rowSplit, 0, n, grid);
                int bottomLeft = minimumArea(rowSplit, m, 0, colSplit, grid);
                int bottomRight = minimumArea(rowSplit, m, colSplit, n, grid);
                if (top > 0 && bottomLeft > 0 && bottomRight > 0)
                    result = min(result, top + bottomLeft + bottomRight);

                // Configuration B: Full bottom, top split into left/right.
                int topLeft = minimumArea(0, rowSplit, 0, colSplit, grid);
                int topRight = minimumArea(0, rowSplit, colSplit, n, grid);
                int bottom = minimumArea(rowSplit, m, 0, n, grid);
                if (topLeft > 0 && topRight > 0 && bottom > 0)
                    result = min(result, topLeft + topRight + bottom);
            }
        }

        // Case 2: Two parallel horizontal splits.
        for(int split1 = 1; split1 < m; split1++) {
            for(int split2 = split1 + 1; split2 < m; split2++) {
                int top = minimumArea(0, split1, 0, n, grid);
                int middle = minimumArea(split1, split2, 0, n, grid);
                int bottom = minimumArea(split2, m, 0, n, grid);
                if (top > 0 && middle > 0 && bottom > 0)
                    result = min(result, top + middle + bottom);
            }
        }
        return result;
    }

    // Main function to orchestrate the process.
    int minimumSum(vector<vector<int>>& grid) {
        // Calculate min area for horizontal-based splits.
        int result = utility(grid);

        // Rotate grid to handle vertical-based splits.
        vector<vector<int>> rotatedGrid = rotateClockWise(grid);

        // The result is the minimum of original and rotated configurations.
        result = min(result, utility(rotatedGrid));

        return result;
    }
};

/*
*
* Dry Run
*
* Input: grid = [[1,0,1],[1,1,1]]
* m = 2, n = 3
*
* 1. Call minimumSum(grid):
* - Call utility(grid):
* - It will check various splits. Let's trace one plausible split from the example.
* - Consider `rowSplit = 1` and `colSplit = 1`:
* - top: minimumArea(0, 1, 0, 3, grid) -> covers row 0 -> area is (0-0+1)*(2-0+1) = 3
* - bottomLeft: minimumArea(1, 2, 0, 1, grid) -> covers (1,0) -> area is 1
* - bottomRight: minimumArea(1, 2, 1, 3, grid) -> covers (1,1) and (1,2) -> area is (1-1+1)*(2-1+1) = 2
* - Total Area = 3 + 1 + 2 = 6. result = 6.
* - Consider `rowSplit = 1` and `colSplit = 2`:
* - topLeft: minimumArea(0,1,0,2,grid) -> covers (0,0) -> area is 1
* - topRight: minimumArea(0,1,2,3,grid) -> covers (0,2) -> area is 1
* - bottom: minimumArea(1,2,0,3,grid) -> covers row 1 -> area is (1-1+1)*(2-0+1) = 3
* - Total Area = 1 + 1 + 3 = 5. result = min(6, 5) = 5.
* - After checking all splits, utility(grid) will likely return 5.
* - result = 5.
*
* 2. Rotate the grid:
* rotatedGrid = [[1,1],[1,0],[1,1]]
* m = 3, n = 2
*
* 3. Call utility(rotatedGrid):
* - It will check splits on the rotated grid.
* - Consider `split1 = 1`, `split2 = 2` (two horizontal splits):
* - top: minimumArea(0,1,0,2, rotated) -> covers (0,0),(0,1) -> area is 2
* - middle: minimumArea(1,2,0,2, rotated) -> covers (1,0) -> area is 1
* - bottom: minimumArea(2,3,0,2, rotated) -> covers (2,0),(2,1) -> area is 2
* - Total Area = 2 + 1 + 2 = 5.
* - The minimum found here will also be 5.
*
* 4. Final result = min(5, 5) = 5.
*
*/
```

---

## 🧠 Key Insights

- **Partitioning Strategy:** The problem boils down to finding the optimal way to partition a grid into three rectangles. This can always be achieved with two straight-line cuts.
- **Rotational Symmetry:** A critical optimization is recognizing that vertical partitions are simply horizontal partitions on a rotated grid. This allows us to reuse the same logic, halving the number of distinct cases to code.
- **Exhaustive Search:** Given the small constraints (`N, M <= 30`), an exhaustive search (brute-force) of all possible split points is feasible. The complexity, while polynomial (`O(m^2 * n^2)`), passes within the time limits.
- **Subproblem Decomposition:** The main problem is broken down into a subproblem: finding the minimum area for a single rectangle. This subproblem is straightforward—find the min/max row/col of all `1`s and calculate the bounding box area.

---

## 🚀 Further Exploration

- Can you generalize this approach to find the minimum area for **N** non-overlapping rectangles? How would the partitioning strategy change?
- What if the rectangles could be rotated (i.e., not axis-aligned)? How would that change the complexity of the problem?
- Consider if the grid contained values other than 0 and 1, where the goal is to cover cells with values greater than some threshold `k`.

---

## 📚 References

- [LeetCode Problem: Find the Minimum Area to Cover All Ones I](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/) (Pre-requisite logic)
- [Matrix Rotation Techniques](https://www.geeksforgeeks.org/rotate-a-matrix-by-90-degree-in-clockwise-direction-without-using-any-extra-space/)

---

## 🏷️ Tags

- `Array`
- `Matrix`
- `Brute Force`
- `Enumeration`
- `Geometry`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/description) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
