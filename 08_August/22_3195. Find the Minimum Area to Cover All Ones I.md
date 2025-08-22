# 🚀 LeetCode: 3195. Find the Minimum Area to Cover All Ones I

<div align="center">
  <a href="https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/description/">
    <img src="https://img.shields.io/badge/Problem%20Link-LeetCode-blue?style=for-the-badge&logo=leetcode" alt="LeetCode Problem Link">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blueviolet?style=for-the-badge&logo=c%2B%2B" alt="Language: C++">
</div>

---

### 🖼️ Visuals

<div align="center">
  <table>
    <tr>
      <td align="center"><strong>Example 1</strong></td>
      <td align="center"><strong>Example 2</strong></td>
    </tr>
    <tr>
      <td align="center"><img src="https://assets.leetcode.com/uploads/2024/05/08/examplerect0.png" alt="Example 1 Visualization" width="250"/></td>
      <td align="center"><img src="https://assets.leetcode.com/uploads/2024/05/08/examplerect1.png" alt="Example 2 Visualization" width="250"/></td>
    </tr>
  </table>
</div>

---

## 📝 Problem Statement

You are given a 2D binary array `grid`. Your task is to find the smallest rectangle (with horizontal and vertical sides) that encloses all the `1`s present in the grid.

Return the **minimum possible area** of this rectangle.

---

## ⚙️ Constraints

- `1 <= grid.length, grid[i].length <= 1000`
- `grid[i][j]` is either `0` or `1`.
- The input is generated such that there is at least one `1` in the `grid`.

---

## examples: 
<details>
<summary><strong>Example Walkthroughs</strong></summary>

| Input Grid             | Output | Explanation                                                                                             |
| ---------------------- | ------ | ------------------------------------------------------------------------------------------------------- |
| `[[0,1,0],[1,0,1]]`    | `6`    | The smallest rectangle to cover all ones has a height of 2 and a width of 3. The area is `2 * 3 = 6`. |
| `[[1,0],[0,0]]`        | `1`    | The smallest rectangle has both a height and width of 1. The area is `1 * 1 = 1`.                       |

</details>

---

## 🧠 Approach

The core idea is to find the **bounding box** that perfectly encloses all the `1`s in the grid. The area of the smallest rectangle is determined by the positions of the outermost `1`s.

To define this bounding box, we need to find four values:
1.  **`minRow`**: The topmost row index containing a `1`.
2.  **`maxRow`**: The bottommost row index containing a `1`.
3.  **`minCol`**: The leftmost column index containing a `1`.
4.  **`maxCol`**: The rightmost column index containing a `1`.

We can find these four boundary values by iterating through the entire grid. We initialize `minRow` and `minCol` to very large values and `maxRow` and `maxCol` to very small values. Whenever we encounter a `1` at `grid[i][j]`, we update our boundaries:
- `minRow = min(minRow, i)`
- `maxRow = max(maxRow, i)`
- `minCol = min(minCol, j)`
- `maxCol = max(maxCol, j)`

After checking all the cells, the width of the rectangle will be `(maxCol - minCol + 1)` and the height will be `(maxRow - minRow + 1)`. The minimum area is simply the product of this width and height.

---

## 💻 Solution Code

### Optimized Solution (C++)

```cpp
// Intuition: The problem asks for the smallest rectangular area that covers all '1's.
// This is equivalent to finding the bounding box of all the '1's. The area of this
// bounding box can be calculated if we know its top, bottom, left, and right boundaries.

// Approach: We can find these four boundaries by iterating through the grid once.
// 1. Initialize four variables: minRow, maxRow, minCol, maxCol to track the extremities.
//    - minRow/minCol can be initialized to a value larger than any possible index (e.g., grid size).
//    - maxRow/maxCol can be initialized to a value smaller than any possible index (e.g., -1).
// 2. Traverse every cell (i, j) of the grid.
// 3. If a '1' is found at grid[i][j], update the four boundary variables:
//    - minRow = min(minRow, i)
//    - maxRow = max(maxRow, i)
//    - minCol = min(minCol, j)
//    - maxCol = max(maxCol, j)
// 4. After the traversal, the height of the bounding box is (maxRow - minRow + 1).
// 5. The width of the bounding box is (maxCol - minCol + 1).
// 6. The minimum area is the product of the height and width.

// Time Complexity: O(m * n), where m is the number of rows and n is the number of columns.
// We need to visit every cell in the grid once.

// Space Complexity: O(1), as we only use a few variables to store the boundaries,
// regardless of the input grid size.

class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int m = grid.size();      // Get number of rows.
        int n = grid[0].size();   // Get number of columns.

        int minRow = m;           // Initialize minRow to a value beyond the max possible row index.
        int maxRow = -1;          // Initialize maxRow to a value before the min possible row index.
        int minCol = n;           // Initialize minCol to a value beyond the max possible col index.
        int maxCol = -1;          // Initialize maxCol to a value before the min possible col index.

        // Iterate through each cell of the grid.
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                // If a '1' is found, update the boundaries.
                if(grid[i][j] == 1) {
                    minRow = min(minRow, i); // Update the topmost row.
                    maxRow = max(maxRow, i); // Update the bottommost row.

                    minCol = min(minCol, j); // Update the leftmost column.
                    maxCol = max(maxCol, j); // Update the rightmost column.
                }           
            }
        }
        
        // Calculate the height and width of the bounding box.
        int height = maxRow - minRow + 1;
        int width = maxCol - minCol + 1;
        
        // Return the area.
        return height * width;
    }
};

/*
*
* Dry Run
*
* Input: grid = [[0,1,0],[1,0,1]]
* m = 2, n = 3
*
* Initial values:
* minRow = 2
* maxRow = -1
* minCol = 3
* maxCol = -1
*
* Traversal:
* i=0, j=0 (grid[0][0] = 0): No change.
* i=0, j=1 (grid[0][1] = 1):
* minRow = min(2, 0) -> 0
* maxRow = max(-1, 0) -> 0
* minCol = min(3, 1) -> 1
* maxCol = max(-1, 1) -> 1
* i=0, j=2 (grid[0][2] = 0): No change.
*
* i=1, j=0 (grid[1][0] = 1):
* minRow = min(0, 1) -> 0
* maxRow = max(0, 1) -> 1
* minCol = min(1, 0) -> 0
* maxCol = max(1, 0) -> 1
* i=1, j=1 (grid[1][1] = 0): No change.
* i=1, j=2 (grid[1][2] = 1):
* minRow = min(0, 1) -> 0
* maxRow = max(1, 1) -> 1
* minCol = min(0, 2) -> 0
* maxCol = max(1, 2) -> 2
*
* End of traversal. Final boundary values:
* minRow = 0
* maxRow = 1
* minCol = 0
* maxCol = 2
*
* Calculation:
* Height = maxRow - minRow + 1 = 1 - 0 + 1 = 2
* Width  = maxCol - minCol + 1 = 2 - 0 + 1 = 3
* Area   = Height * Width = 2 * 3 = 6
*
* Return: 6
*/
```

---

## 💡 Key Insights

- The problem simplifies to finding the extreme coordinates (min/max row and column) of all the `1`s.
- A single pass through the grid is sufficient to gather all the information needed.
- The area calculation `(max - min + 1)` is a standard way to find the inclusive range between two indices.

---

## 🚀 Further Exploration

- **Follow-up Problem**: Consider the next problem in the series, [Find the Minimum Area to Cover All Ones II](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/), which involves multiple rectangles.
- **Dimensionality**: How would this approach change if the grid were 3-dimensional? You would need to find `minZ` and `maxZ` as well, and the volume would be the product of height, width, and depth.

---

## 📚 References

- **Concepts**: Bounding Box, 2D Array Traversal
- **Similar Problems**:
  - [850. Rectangle Area II](https://leetcode.com/problems/rectangle-area-ii/)
  - [221. Maximal Square](https://leetcode.com/problems/maximal-square/)

---

## 🏷️ Tags

`Array` `Matrix` `Geometry` `Brainteaser`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)