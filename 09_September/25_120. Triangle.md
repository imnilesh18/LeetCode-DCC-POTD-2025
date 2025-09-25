# 🔺 120. Triangle

| **Difficulty** |            **Tags**            |
| :------------: | :----------------------------: |
|    `Medium`    | `Array`, `Dynamic Programming` |

**[Problem Link](https://leetcode.com/problems/triangle/description/)**

---

## 📝 Problem Statement

Given a `triangle` array, return the _minimum path sum from top to bottom_.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index `i` on the current row, you may move to either index `i` or index `i + 1` on the next row.

---

## ⚙️ Constraints

- `1 <= triangle.length <= 200`
- `triangle[0].length == 1`
- `triangle[i].length == triangle[i - 1].length + 1`
- `-10^4 <= triangle[i][j] <= 10^4`

---

## 🎬 Examples

| Input                                      | Output |
| :----------------------------------------- | :----- |
| `triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]` | `11`   |
| `triangle = [[-10]]`                       | `-10`  |

<details>
<summary><strong>Explanation for Example 1</strong></summary>

The triangle looks like:
**`2`**
**`3`** `4`
`6` **`5`** `7`
`4` **`1`** `8` `3`

The minimum path sum from top to bottom is **2 + 3 + 5 + 1 = 11**.

</details>

---

## 🧠 Approach

The problem asks for the minimum path sum from the top of a triangle to the bottom. At each step, we can move from a number at `(row, col)` to either `(row + 1, col)` or `(row + 1, col + 1)`.

A greedy approach of always choosing the smaller of the two children at each step fails. A locally optimal choice does not guarantee a globally optimal solution. For instance, a path with a larger number might lead to much smaller numbers later on, resulting in a smaller overall sum.

This problem has optimal substructure and overlapping subproblems, making it a perfect candidate for **Dynamic Programming**.

1.  **Top-Down (Recursion + Memoization)**:

    - Define a function `solve(row, col)` that returns the minimum path sum from `(row, col)` to the bottom.
    - **Base Case**: If `row` is the last row, the path sum is just the value of the element itself, so we return `triangle[row][col]`.
    - **Recursive Step**: From `(row, col)`, we can go to `(row + 1, col)` or `(row + 1, col + 1)`. The minimum path from the current cell is its own value plus the minimum of the paths from its two children.
      `min_path = triangle[row][col] + min(solve(row + 1, col), solve(row + 1, col + 1))`
    - **Memoization**: We use a 2D DP table, `t[row][col]`, to store the results of `solve(row, col)` to avoid re-computing for the same subproblems.

2.  **Bottom-Up (Tabulation)**:

    - We can convert the recursive solution into an iterative one. The state `dp[row][col]` will represent the minimum path sum starting from `(row, col)` down to the bottom.
    - We initialize a 2D DP table, `dp`, of the same size as the triangle, often just by copying the triangle.
    - The last row of our `dp` table is the base case, which is the same as the last row of the triangle.
    - We iterate from the second-to-last row upwards to the top (`row = n-2` down to `0`).
    - For each cell `(row, col)`, we calculate its minimum path sum using the already computed values from the row below:
      `dp[row][col] = triangle[row][col] + min(dp[row + 1][col], dp[row + 1][col + 1])`
    - The final answer is at `dp[0][0]`.

3.  **Space-Optimized Bottom-Up**:

    - Notice that for calculating the values for a `row`, we only need the values from the `row + 1`. We don't need the entire 2D table.
    - We can optimize the space to `O(n)` by using a 1D array, `dp`, of size `n` (where `n` is the number of rows).
    - Initialize `dp` with the values of the last row of the triangle.
    - Iterate from the second-to-last row upwards. For each row, update the `dp` array:
      `dp[col] = triangle[row][col] + min(dp[col], dp[col + 1])`
    - After the loops complete, `dp[0]` will hold the final answer.

4.  **In-Place Modification (Top-Down)**:
    - Another approach is to modify the input triangle itself, saving space to `O(1)`. This approach works top-to-bottom.
    - Iterate from the second row (`row = 1` to `n-1`).
    - For each cell `(row, col)`, update its value to be the minimum path sum from the top to that cell.
      `triangle[row][col] += min(parent1, parent2)`
    - Care must be taken for edge cases (the first and last elements of each row), as they only have one parent.
    - After the loops, the minimum value in the last row of the modified triangle will be the answer.

---

## 💻 Solution Code

<details>
<summary><strong>Solution 1: Recursion with Memoization</strong></summary>

```cpp
// Intuition:
// The problem asks for the minimum path sum from top to bottom. This can be solved by exploring all possible paths. A recursive approach naturally fits this exploration. To avoid re-computing paths for the same cell, we can store the results in a memoization table.

// Approach:
// 1. Define a recursive function `solve(row, col)` that calculates the minimum path sum from the cell `(row, col)` to the last row.
// 2. The base case for the recursion is when we reach the last row (`row == n-1`). In this case, the path sum is just the value of the cell itself.
// 3. In the recursive step, the minimum path sum from `(row, col)` is its own value plus the minimum of the path sums from its two possible next steps: `(row + 1, col)` and `(row + 1, col + 1)`.
// 4. Use a 2D array `t[201][201]` initialized to -1 to store the results of subproblems. Before computing, check if `t[row][col]` is not -1. If so, return the stored value.
// 5. After computing the `minPath`, store it in `t[row][col]` before returning.
// 6. The initial call will be `solve(triangle, 0, 0)`.

// Time Complexity: O(n*n), where n is the number of rows. Each state (row, col) is computed only once.
// Space Complexity: O(n*n) for the memoization table `t` and O(n) for the recursion stack depth.

class Solution {
public:
    int t[201][201]; // Memoization table
    int n;

    int solve(vector<vector<int>>& triangle, int row, int col) {
        // Base case: if we are at the last row, return the element's value
        if (row == n-1)
            return triangle[row][col];

        // If the result for this state is already computed, return it
        if(t[row][col] != -1)
            return t[row][col];

        // Calculate the minimum path by adding the current element's value
        // to the minimum of the paths from the two adjacent cells in the row below
        int minPath = triangle[row][col] +
                      min(solve(triangle, row + 1, col),
                          solve(triangle, row + 1, col + 1));

        // Store and return the result
        return t[row][col] = minPath;
    }

    int minimumTotal(vector<vector<int>>& triangle) {
        n = triangle.size(); // Get the total number of rows
        memset(t, -1, sizeof(t)); // Initialize memoization table with -1
        return solve(triangle, 0, 0); // Start the recursion from the top of the triangle
    }
};

/*
*
* Dry Run
*
* triangle = [[2], [3,4], [6,5,7], [4,1,8,3]]
* n = 4
*
* solve(0, 0):
* triangle[0][0] + min(solve(1,0), solve(1,1))
*
* solve(1, 0) -> triangle[1][0] + min(solve(2,0), solve(2,1))
* solve(2, 0) -> triangle[2][0] + min(solve(3,0), solve(3,1)) -> 6 + min(4, 1) = 7. Store t[2][0]=7
* solve(2, 1) -> triangle[2][1] + min(solve(3,1), solve(3,2)) -> 5 + min(1, 8) = 6. Store t[2][1]=6
* Returns 3 + min(7, 6) = 9. Store t[1][0]=9
*
* solve(1, 1) -> triangle[1][1] + min(solve(2,1), solve(2,2))
* solve(2, 1) -> returns 6 (from memoization)
* solve(2, 2) -> triangle[2][2] + min(solve(3,2), solve(3,3)) -> 7 + min(8, 3) = 10. Store t[2][2]=10
* Returns 4 + min(6, 10) = 10. Store t[1][1]=10
*
* Returns 2 + min(9, 10) = 11.
*
*  11
*
*/
```

</details>

<details><summary><strong>Solution 2: Bottom-Up DP (Tabulation)</strong></summary>

```cpp
// Intuition:
// Instead of a top-down recursive approach, we can solve this iteratively from the bottom up. The minimum path sum from any cell in the last row to the bottom is just the cell's value itself. We can use this information to calculate the minimum path sums for cells in the row above, and so on, until we reach the top.

// Approach:
// 1. Create a 2D DP table `t` of the same size as the triangle and initialize it with the triangle's values.
// 2. The last row of `t` already contains the correct minimum path sums (the base cases).
// 3. Iterate from the second-to-last row (`n-2`) up to the top row (`0`).
// 4. For each row, iterate through its columns (`col` from `0` to `row`).
// 5. Update the value at `t[row][col]` by adding the minimum of its two children in the row below: `min(t[row+1][col], t[row+1][col+1])`.
// 6. After the loops, `t[row][col]` will store the minimum path sum from that cell to the bottom.
// 7. The final answer will be at `t[0][0]`, which represents the minimum path sum from the top of the triangle.

// Time Complexity: O(n*n) due to the nested loops iterating through each element of the triangle once.
// Space Complexity: O(n*n) to store the DP table `t`.

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> t = triangle; // copy triangle for DP table

        // Start from the second last row and move upwards
        for (int row = n - 2; row >= 0; row--) {
            // Iterate through each column in the current row
            for (int col = 0; col <= row; col++) { // 1st row has 1 col, 2nd has 2, hence col <= row
                // Update current cell with its value + the minimum of its two children
                t[row][col] += min(t[row + 1][col], t[row + 1][col + 1]);
            }
        }

        return t[0][0]; // The top element now holds the minimum path sum
    }
};

/*
*
* Dry Run
*
* triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
* t is initialized as a copy of triangle.
* n = 4
*
* Loop row = 2 (n-2):
* col = 0: t[2][0] = 6 + min(t[3][0], t[3][1]) = 6 + min(4, 1) = 7
* col = 1: t[2][1] = 5 + min(t[3][1], t[3][2]) = 5 + min(1, 8) = 6
* col = 2: t[2][2] = 7 + min(t[3][2], t[3][3]) = 7 + min(8, 3) = 10
* Now t's 3rd row is [7, 6, 10]
*
* Loop row = 1:
* col = 0: t[1][0] = 3 + min(t[2][0], t[2][1]) = 3 + min(7, 6) = 9
* col = 1: t[1][1] = 4 + min(t[2][1], t[2][2]) = 4 + min(6, 10) = 10
* Now t's 2nd row is [9, 10]
*
* Loop row = 0:
* col = 0: t[0][0] = 2 + min(t[1][0], t[1][1]) = 2 + min(9, 10) = 11
* Now t's 1st row is [11]
*
* Return t[0][0] which is 11.
*
*/
```

</details>

<details>
<summary><strong>Solution 3: Bottom-Up DP with Space Optimization</strong></summary>

```cpp
// Intuition:
// In the bottom-up DP approach, to compute the values for the current row, we only need the values from the immediate next row. We don't need the entire 2D DP table. This suggests that we can optimize the space complexity.

// Approach:
// 1. Create a 1D DP array `t` and initialize it with the values of the last row of the triangle.
// 2. Iterate from the second-to-last row (`n-2`) up to the top row (`0`).
// 3. For each row, iterate through its columns (`col` from `0` to `row`).
// 4. Update the `t[col]` value. The new value represents the minimum path from `triangle[row][col]`. It's calculated using the original `triangle` value and the minimum of the two corresponding paths from the row below, which are currently stored in `t[col]` and `t[col+1]`.
//    `t[col] = triangle[row][col] + min(t[col], t[col + 1])`.
// 5. After the loops complete, the 1D array `t` effectively holds the minimum path sums for the top row, and the final answer is at `t[0]`.

// Time Complexity: O(n*n) due to the nested loops.
// Space Complexity: O(n) for the 1D DP vector `t`, where n is the number of rows.

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> t = triangle.back(); // Initialize with the last row

        // Iterate from the second last row upwards
        for (int row = n - 2; row >= 0; row--) {
            // Update the dp array for the current row
            for (int col = 0; col <= row; col++) {
                // `t[col]` and `t[col+1]` hold the min paths from the row below
                t[col] = triangle[row][col] + min(t[col], t[col + 1]);
            }
        }

        return t[0]; // The result is stored at the first element
    }
};

/*
*
* Dry Run
*
* triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
* n = 4
* t is initialized with the last row: t = [4, 1, 8, 3]
*
* Loop row = 2 (n-2):
* col = 0: t[0] = triangle[2][0] + min(t[0], t[1]) = 6 + min(4, 1) = 7
* col = 1: t[1] = triangle[2][1] + min(t[1], t[2]) = 5 + min(1, 8) = 6
* col = 2: t[2] = triangle[2][2] + min(t[2], t[3]) = 7 + min(8, 3) = 10
* Now t = [7, 6, 10, 3]
*
* Loop row = 1:
* col = 0: t[0] = triangle[1][0] + min(t[0], t[1]) = 3 + min(7, 6) = 9
* col = 1: t[1] = triangle[1][1] + min(t[1], t[2]) = 4 + min(6, 10) = 10
* Now t = [9, 10, 10, 3]
*
* Loop row = 0:
* col = 0: t[0] = triangle[0][0] + min(t[0], t[1]) = 2 + min(9, 10) = 11
* Now t = [11, 10, 10, 3]
*
* Return t[0], which is 11.
*
*/
```

</details>

<details>
<summary><strong>Solution 4: Top-to-Bottom DP with O(n) space</strong></summary>

```cpp
// Intuition:
// We can also build the solution from top to bottom. Let `t[col]` store the minimum path sum to reach column `col` in the *previous* row. When processing the current row, we can calculate the minimum path sum to each cell by considering the minimum sums from its parent(s) in the previous row.

// Approach:
// 1. Create a 1D DP array `t` of size `n` initialized to 0.
// 2. Set `t[0]` to the value of the triangle's top element, `triangle[0][0]`.
// 3. Iterate from the second row (`row = 1`) to the last row (`n-1`).
// 4. For each row, iterate through its columns from right to left (`col = row` down to `0`). This is crucial to prevent using already updated values of `t` from the current row's iteration.
// 5. Handle the three cases for each cell `(row, col)`:
//    - Rightmost element (`col == row`): It can only be reached from `t[col-1]`.
//    - Leftmost element (`col == 0`): It can only be reached from `t[col]`.
//    - Middle elements: Can be reached from `t[col]` or `t[col-1]`. Take the minimum.
// 6. After iterating through all rows, the `t` array will contain the minimum path sums to each cell in the last row.
// 7. The final answer is the minimum element in the `t` array.

// Time Complexity: O(n*n) due to nested loops.
// Space Complexity: O(n) for the 1D DP vector `t`.

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> t(n, 0); // DP array to store min path sums for a row

        t[0] = triangle[0][0]; // Initialize with the top element

        // Iterate from the second row
        for (int row = 1; row < n; row++) {
            // Go from right to left to avoid overwriting values needed in the same row's calculation
            for (int col = row; col >= 0; col--) {
                if (col == 0) {
                    // Leftmost element can only come from the element directly above
                    t[col] = t[col] + triangle[row][col];
                } else if (col == row) {
                    // Rightmost element can only come from the upper-left element
                    t[col] = t[col - 1] + triangle[row][col];
                } else {
                    // Middle elements can come from either above or upper-left
                    t[col] = min(t[col], t[col - 1]) + triangle[row][col];
                }
            }
        }

        // The answer is the minimum path sum in the last row
        return *min_element(t.begin(), t.end());
    }
};

/*
*
* Dry Run
*
* triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
* n = 4, t = [0,0,0,0]
*
* Initial: t[0] = 2. Now t = [2, 0, 0, 0]
*
* Loop row = 1:
* col = 1: t[1] = t[0] + triangle[1][1] = 2 + 4 = 6.  t = [2, 6, 0, 0]
* col = 0: t[0] = t[0] + triangle[1][0] = 2 + 3 = 5.  t = [5, 6, 0, 0]
*
* Loop row = 2:
* col = 2: t[2] = t[1] + triangle[2][2] = 6 + 7 = 13. t = [5, 6, 13, 0]
* col = 1: t[1] = min(t[1], t[0]) + triangle[2][1] = min(6, 5) + 5 = 10. t = [5, 10, 13, 0]
* col = 0: t[0] = t[0] + triangle[2][0] = 5 + 6 = 11. t = [11, 10, 13, 0]
*
* Loop row = 3:
* col = 3: t[3] = t[2] + triangle[3][3] = 13 + 3 = 16. t = [11, 10, 13, 16]
* col = 2: t[2] = min(t[2], t[1]) + triangle[3][2] = min(13, 10) + 8 = 18. t = [11, 10, 18, 16]
* col = 1: t[1] = min(t[1], t[0]) + triangle[3][1] = min(10, 11) + 1 = 11. t = [11, 11, 18, 16]
* col = 0: t[0] = t[0] + triangle[3][0] = 11 + 4 = 15. t = [15, 11, 18, 16]
*
* Final t = [15, 11, 18, 16]
* Return min_element(t) which is 11.
*
*/
```

</details>

<details>
<summary><strong>Solution 5: In-place Manipulation (Top-to-Bottom)</strong></summary>

```cpp
// Intuition:
// We can achieve O(1) extra space by modifying the input `triangle` array itself to serve as our DP table. This approach builds the solution top-down, where `triangle[row][col]` is updated to store the minimum path sum from the top `(0,0)` to the current cell `(row,col)`.

// Approach:
// 1. Start iterating from the second row (`row = 1`) to the end.
// 2. For each cell `(row, col)`, determine its parent(s) in the previous row (`row-1`).
// 3. A cell `(row, col)` can be reached from `(row-1, col-1)` and `(row-1, col)`.
// 4. We must handle boundary conditions to avoid accessing out-of-bounds indices.
//    - The `prev_up_val` corresponds to the parent at `(row-1, col)`. If `col` is out of bounds for the previous row, we use the last valid column.
//    - The `prev_up_left` corresponds to the parent at `(row-1, col-1)`. If `col-1` is negative, we use column `0`.
// 5. Update the current cell's value by adding the minimum of its valid parents' values:
//    `triangle[row][col] += min(prev_up_val, prev_up_left);`
// 6. After the loops, the last row of the triangle will contain the total minimum path sums to each of its cells.
// 7. The final answer is the minimum element in the last row of the modified triangle.

// Time Complexity: O(n*n) due to nested loops.
// Space Complexity: O(1) as we modify the input array in place.

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();

        // Start from the second row
        for(int row = 1; row < n; row++) {
            for(int col = 0; col < triangle[row].size(); col++) {
                // Get value from parent directly above, handling right boundary
                int prev_up_val  = triangle[row-1][min(col, (int)triangle[row-1].size()-1)];
                // Get value from upper-left parent, handling left boundary
                int prev_up_left = triangle[row-1][max(col-1, 0)];

                // Add the minimum of the two possible parents to the current cell
                triangle[row][col] += min(prev_up_val, prev_up_left);
            }
        }

        // The minimum path sum will be the minimum value in the last row
        return *min_element(triangle[n-1].begin(), triangle[n-1].end());
    }
};

/*
*
* Dry Run
*
* triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
*
* Loop row = 1:
* col = 0: prev_up_val=2, prev_up_left=2. min=2. triangle[1][0] = 3+2=5
* col = 1: prev_up_val=2, prev_up_left=2. min=2. triangle[1][1] = 4+2=6
* Now triangle[1] is [5, 6]
*
* Loop row = 2:
* col = 0: prev_up_val=5, prev_up_left=5. min=5. triangle[2][0] = 6+5=11
* col = 1: prev_up_val=6, prev_up_left=5. min=5. triangle[2][1] = 5+5=10
* col = 2: prev_up_val=6, prev_up_left=6. min=6. triangle[2][2] = 7+6=13
* Now triangle[2] is [11, 10, 13]
*
* Loop row = 3:
* col = 0: prev_up_val=11, prev_up_left=11. min=11. triangle[3][0] = 4+11=15
* col = 1: prev_up_val=10, prev_up_left=11. min=10. triangle[3][1] = 1+10=11
* col = 2: prev_up_val=13, prev_up_left=10. min=10. triangle[3][2] = 8+10=18
* col = 3: prev_up_val=13, prev_up_left=13. min=13. triangle[3][3] = 3+13=16
* Now triangle[3] is [15, 11, 18, 16]
*
* Return min_element of [15, 11, 18, 16] which is 11.
*
*/
```

</details>

---

## 🔑 Key Insights

- **Greedy Fails**: Always choosing the locally optimal path (the smaller number) doesn't lead to a globally optimal solution.
- **DP is Key**: The problem's structure with optimal substructure (the min path to the end from a point depends on the min paths from its children) and overlapping subproblems (the same sub-path can be reached from multiple parents) makes it ideal for Dynamic Programming.
- **State Representation**: The core of the DP solution is defining the state. We can define `dp[i][j]` as either "min path from top to `(i,j)`" or "min path from `(i,j)` to bottom". Both lead to correct solutions, just with different iteration directions (top-down vs. bottom-up).
- **Space Optimization**: Recognizing that a row's calculation only depends on the adjacent row allows for a significant reduction in space complexity from `O(n^2)` to `O(n)`.

## 🚀 Further Exploration

- **Minimum Falling Path Sum**: This problem is very similar but on a rectangular grid instead of a triangle.
- **Maximum Path Sum**: Consider how the logic would change if you needed to find the _maximum_ path sum instead of the minimum.
- **Counting Paths**: How would you count the number of minimum paths, or all possible paths?

## 🔗 References

- [Dynamic Programming on Grids](https://www.google.com/search?q=https://www.youtube.com/watch%3Fv%3DN_aJ5qAFw70)
- [LeetCode Discussion on Space Optimization](https://www.google.com/search?q=https://leetcode.com/problems/triangle/solutions/38730/dp-solution-for-triangle)

## 🏷️ Tags

`Array`, `Dynamic Programming`

---

## 📄 License

This repository is released under the [MIT License](https://www.google.com/search?q=./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/triangle/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
