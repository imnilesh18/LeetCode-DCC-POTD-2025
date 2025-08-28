<div align="center">

# 🚀 3446. Sort Matrix by Diagonals 🚀

<a href="https://leetcode.com/problems/sort-matrix-by-diagonals/description/">
  <img src="https://img.shields.io/badge/Problem%20Link-0077B5?style=for-the-badge&logo=leetcode&logoColor=white" alt="LeetCode Problem Link">
</a>
<img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
<img src="https://img.shields.io/badge/Tags-Array-blue?style=for-the-badge" alt="Tag: Array">
<img src="https://img.shields.io/badge/Tags-Matrix-green?style=for-the-badge" alt="Tag: Matrix">
<img src="https://img.shields.io/badge/Tags-Sorting-orange?style=for-the-badge" alt="Tag: Sorting">

</div>

---

## 📝 Problem Statement

You are given an `n x n` square matrix of integers `grid`. Return the matrix such that:

-   The diagonals in the **bottom-left triangle** (including the middle diagonal) are sorted in **non-increasing** order.
-   The diagonals in the **top-right triangle** are sorted in **non-decreasing** order.

---

## 📋 Constraints

-   `grid.length == grid[i].length == n`
-   `1 <= n <= 10`
-   `-10^5 <= grid[i][j] <= 10^5`

---

## 🖼️ Examples

### Example 1:

**Input:** `grid = [[1,7,3],[9,8,2],[4,5,6]]`
**Output:** `[[8,2,3],[9,6,7],[4,5,1]]`

<p align="center">
  <img src="https://assets.leetcode.com/uploads/2024/12/29/4052example1drawio.png" alt="Example 1 visualization" style="width: 70%; border-radius: 10px; box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);">
</p>

**Explanation:**
- The bottom-left diagonals `[1, 8, 6]` are sorted non-increasingly to `[8, 6, 1]`.
- The top-right diagonal `[7, 2]` is sorted non-decreasingly to `[2, 7]`.

### Example 2:

**Input:** `grid = [[0,1],[1,2]]`
**Output:** `[[2,1],[1,0]]`

<p align="center">
  <img src="https://assets.leetcode.com/uploads/2024/12/29/4052example2adrawio.png" alt="Example 2 visualization" style="width: 50%; border-radius: 10px; box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);">
</p>

**Explanation:**
- The bottom-left diagonal `[0, 2]` is sorted non-increasingly to `[2, 0]`.

---

## 🤔 Approach

There are two main approaches to solve this problem effectively:

<details>
  <summary><strong>🧠 Approach 1: Direct Simulation</strong></summary>
  
  This approach directly implements the logic described in the problem statement. We can break it down into these steps:

1.  **Identify Diagonals**: We iterate through all possible starting points of the diagonals.
    -   The diagonals in the **bottom-left** part (including the main diagonal) all start at column `0`. We iterate from `row = 0` to `n-1` with `col = 0`.
    -   The diagonals in the **top-right** part all start at row `0` (excluding the main diagonal's start at `[0][0]`). We iterate from `col = 1` to `n-1` with `row = 0`.

2.  **Extract and Sort**: For each starting point `(r, c)`:
    -   Create a temporary vector to store all elements of that diagonal. You can traverse the diagonal by repeatedly incrementing both the row and column index (`i++`, `j++`).
    -   Sort this vector based on the rules:
        -   **Non-increasing** (descending) if it's a bottom-left diagonal.
        -   **Non-decreasing** (ascending) if it's a top-right diagonal.

3.  **Place Back**:
    -   Traverse the same diagonal again from its starting point `(r, c)`.
    -   Populate the grid cells with the sorted values from the temporary vector.

This method is straightforward and follows the problem's logic step-by-step.
</details>

<details>
  <summary><strong>🗺️ Approach 2: Using a Map (Group by `i - j`)</strong></summary>
  
  This approach uses a clever mathematical property of diagonals.

1.  **Diagonal Property**: All elements `grid[i][j]` on the same diagonal share a constant value for the difference `i - j`.
    -   For the main diagonal, `i - j` is always `0`.
    -   For diagonals in the bottom-left triangle, `i - j` is `> 0`.
    -   For diagonals in the top-right triangle, `i - j` is `< 0`.

2.  **Group and Sort**:
    -   Create a map where the key is the diagonal identifier (`i - j`) and the value is a list (or vector) of elements on that diagonal.
    -   Iterate through the entire `grid`. For each element `grid[i][j]`, calculate `diag = i - j` and push the element into `map[diag]`.
    -   Iterate through the map. For each key-value pair:
        -   If `key >= 0` (bottom-left), sort the vector in **ascending** order.
        -   If `key < 0` (top-right), sort the vector in **descending** order.
        *Note: We sort in the reverse order of what's required because we will be picking elements from the back of the vector, which is an efficient O(1) operation.*

3.  **Place Back**:
    -   Iterate through the `grid` again from `(0, 0)` to `(n-1, n-1)`.
    -   For each cell `grid[i][j]`, calculate `diag = i - j`.
    -   Take the last element from `map[diag]`, place it in `grid[i][j]`, and then pop it from the vector.

This method elegantly groups the diagonals and simplifies the sorting logic.
</details>

---

## 💻 Solution Code

### Approach 1: Direct Simulation

```cpp
// Intuition: The most straightforward way is to simulate the process directly. We can iterate through each diagonal, extract its elements, sort them according to the specified order, and then place them back into the matrix.
// Approach:
// 1. Identify all diagonal starting points. Diagonals in the bottom-left triangle start at `(row, 0)`, and those in the top-right triangle start at `(0, col)`.
// 2. Create a helper function `sortDiagonal` that takes a starting row `r`, column `c`, the grid, and a boolean `asc` for sort order.
// 3. Inside the helper function:
//    a. Traverse the diagonal starting from `(r, c)` and store all its elements in a temporary vector.
//    b. Sort the vector: ascending if `asc` is true, descending otherwise.
//    c. Traverse the diagonal again and update the grid with the sorted elements.
// 4. Call this helper function for all bottom-left diagonals (`row` from 0 to n-1, `col` = 0) with `asc = false`.
// 5. Call it again for all top-right diagonals (`col` from 1 to n-1, `row` = 0) with `asc = true`.
// 6. Return the modified grid.
// Time Complexity: O(n^2 * logn). For each of the 2n-1 diagonals, we might traverse up to n elements and sort them, leading to roughly O(n * n log n).
// Space Complexity: O(n). At any time, we only store elements of the longest diagonal, which has n elements.
class Solution {
public:
    int n; // Size of the grid

    // Helper function to sort a single diagonal
    void sortDiagonal(int r, int c, vector<vector<int>>& grid, bool asc) {
        vector<int> vec; // Stores diagonal elements

        // Pointers to traverse the diagonal
        int i = r;
        int j = c;

        // Extract elements from the diagonal
        while(i < n && j < n) {
            vec.push_back(grid[i][j]);
            i++;
            j++;
        }

        // Sort based on the required order
        if(asc) { // Non-decreasing for top-right
            sort(begin(vec), end(vec));
        } else { // Non-increasing for bottom-left
            sort(rbegin(vec), rend(vec));
        }

        // Reset pointers to the start of the diagonal
        i = r;
        j = c;

        // Place sorted elements back into the grid
        for(int &val : vec) {
            grid[i][j] = val;
            i++;
            j++;
        }
    }

    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        n = grid.size();

        // Sort Bottom-Left diagonals (non-increasing order)
        for(int row = 0; row < n; row++) {
            sortDiagonal(row, 0, grid, false);
        }

        // Sort Top-Right diagonals (non-decreasing order)
        for(int col = 1; col < n; col++) {
            sortDiagonal(0, col, grid, true);
        }

        return grid;
    }
};

/*
*
* Dry Run
* grid = [[1,7,3],[9,8,2],[4,5,6]], n = 3
*
* --- Bottom-Left Diagonals (asc=false) ---
* 1. row = 0: sortDiagonal(0, 0, ...)
* - vec = [1, 8, 6] -> sort descending -> [8, 6, 1]
* - grid becomes [[8,7,3],[9,6,2],[4,5,1]]
* 2. row = 1: sortDiagonal(1, 0, ...)
* - vec = [9, 5] -> sort descending -> [9, 5]
* - grid remains [[8,7,3],[9,6,2],[4,5,1]]
* 3. row = 2: sortDiagonal(2, 0, ...)
* - vec = [4] -> sort descending -> [4]
* - grid remains unchanged.
*
* --- Top-Right Diagonals (asc=true) ---
* 1. col = 1: sortDiagonal(0, 1, ...)
* - vec = [7, 2] -> sort ascending -> [2, 7]
* - grid becomes [[8,2,3],[9,6,7],[4,5,1]]
* 2. col = 2: sortDiagonal(0, 2, ...)
* - vec = [3] -> sort ascending -> [3]
* - grid remains unchanged.
*
* Final Result: [[8,2,3],[9,6,7],[4,5,1]]
*
*/
```

### Approach 2: Using a Map

```cpp
// Intuition: A key property of diagonals is that for any element `grid[i][j]`, the value `i - j` is constant along its diagonal. This allows us to group elements by their diagonal using a hash map.
// Approach:
// 1. Create an unordered_map where the key is an integer representing the diagonal (`i - j`) and the value is a vector of integers on that diagonal.
// 2. Iterate through the entire grid and populate the map. For each `grid[i][j]`, push it to `mp[i-j]`.
// 3. Iterate through the map's key-value pairs.
//    a. If the key `i-j >= 0` (bottom-left), sort the vector in ascending order.
//    b. If the key `i-j < 0` (top-right), sort the vector in descending order.
//    (Note: We sort in the reverse of the final required order because we'll be efficiently popping from the back).
// 4. Iterate through the grid again. For each cell `(i, j)`:
//    a. Find its diagonal key: `diag = i-j`.
//    b. Get the last element from `mp[diag]` and place it in `grid[i][j]`.
//    c. Pop the last element from `mp[diag]`.
// 5. Return the modified grid.
// Time Complexity: O(n^2 * logn). Populating the map is O(n^2). Sorting each diagonal in the map takes O(k log k), where k is the length. In the worst case, this sums up to O(n^2 * logn). Refilling the grid is O(n^2).
// Space Complexity: O(n^2). The map stores all n*n elements of the grid.
class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();

        // Map to group elements by diagonal ID (i-j)
        unordered_map<int, vector<int>> mp; 

        // Populate the map with diagonal elements
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int diag = i-j;
                mp[diag].push_back(grid[i][j]);       
            }
        }

        // Sort each diagonal's vector
        for(auto &it : mp) {
            if(it.first >= 0) { // Bottom-left diagonals
                // Sort ascending to pick from back for non-increasing order
                sort(begin(it.second), end(it.second));
            } else { // Top-right diagonals
                // Sort descending to pick from back for non-decreasing order
                sort(rbegin(it.second), rend(it.second));
            }
        }

        // Refill the grid with sorted elements
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int diag = i-j;
                // Get the last element (correctly sorted)
                grid[i][j] = mp[diag].back();
                // Remove the used element
                mp[diag].pop_back();        
            }
        }

        return grid;
    }
};
/*
*
* Dry Run
* grid = [[1,7,3],[9,8,2],[4,5,6]]
*
* 1. Populate Map:
* mp[0] = [1, 8, 6]
* mp[-1] = [7, 2]
* mp[-2] = [3]
* mp[1] = [9, 5]
* mp[2] = [4]
*
* 2. Sort Map Values (in reverse order for pop_back):
* mp[0] (key>=0): sort ascending -> [1, 6, 8]
* mp[-1] (key<0): sort descending -> [7, 2]
* mp[-2] (key<0): sort descending -> [3]
* mp[1] (key>=0): sort ascending -> [5, 9]
* mp[2] (key>=0): sort ascending -> [4]
*
* 3. Refill Grid:
* grid[0][0]: diag=0, pop 8 from mp[0] -> grid[0][0]=8
* grid[0][1]: diag=-1, pop 2 from mp[-1] -> grid[0][1]=2
* grid[0][2]: diag=-2, pop 3 from mp[-2] -> grid[0][2]=3
* grid[1][0]: diag=1, pop 9 from mp[1] -> grid[1][0]=9
* grid[1][1]: diag=0, pop 6 from mp[0] -> grid[1][1]=6
* grid[1][2]: diag=-1, pop 7 from mp[-1] -> grid[1][2]=7
* ...and so on.
*
* Final Result: [[8,2,3],[9,6,7],[4,5,1]]
*
*/
```

---

## 💡 Key Insights

-   **Diagonal Traversal**: A key trick for traversing a diagonal starting at `(r, c)` in a matrix is to repeatedly increment both row and column indices (`i++`, `j++`) until one goes out of bounds.
-   **Diagonal Property `(i - j)`**: The property that `i - j` is constant for all elements on a diagonal is a very powerful tool for solving many matrix diagonal problems. It provides an elegant way to group, process, and identify diagonals without complex traversal logic.

---

## 🚀 Further Exploration

-   [1329. Sort the Matrix Diagonally](https://leetcode.com/problems/sort-the-matrix-diagonally/): A similar problem where all diagonals need to be sorted in ascending order.
-   [498. Diagonal Traverse](https://leetcode.com/problems/diagonal-traverse/): A problem that requires traversing the matrix in a zig-zag diagonal pattern.
-   Consider how the solution would change if the matrix was not square (`m x n`). The `i-j` approach would still work perfectly, while the simulation approach would need slight adjustments to loop boundaries.

---

## 📚 References

-   [Problem on LeetCode](https://leetcode.com/problems/sort-matrix-by-diagonals/description/)
-   [Discussion Forum](https://leetcode.com/problems/sort-matrix-by-diagonals/discuss/)

---

## 🏷️ Tags

`Array` `Matrix` `Sorting` `Hash Table`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/sort-matrix-by-diagonals/description/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)