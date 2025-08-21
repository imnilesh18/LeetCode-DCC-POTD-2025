# 🔳 1504. Count Submatrices With All Ones

| Difficulty | Tags         |
| :--------- | :----------- |
| `Medium`   | `Array`, `Dynamic Programming`, `Matrix`, `Stack`, `Monotonic Stack` |

[![](https://img.shields.io/badge/Link%20to%20Problem-blue?style=for-the-badge&logo=leetcode)](https://leetcode.com/problems/count-submatrices-with-all-ones/description/)

---

## 📝 Problem Statement

Given an `m x n` binary matrix `mat`, return *the number of submatrices that have all ones*.

---

## ⚙️ Constraints

-   `1 <= m, n <= 150`
-   `mat[i][j]` is either `0` or `1`.

---

## 📌 Examples

<details>
<summary><strong>Example 1</strong></summary>

| Input                                     | Output |
| :---------------------------------------- | :----- |
| `mat = [[1,0,1],[1,1,0],[1,1,0]]`           | `13`   |

**Explanation:**
-   There are `6` submatrices of size `1x1`.
-   There are `2` submatrices of size `1x2`.
-   There are `3` submatrices of size `2x1`.
-   There is `1` submatrix of size `2x2`.
-   There is `1` submatrix of size `3x1`.
-   Total: `6 + 2 + 3 + 1 + 1 = 13`.
</details>

<details>
<summary><strong>Example 2</strong></summary>

| Input                                        | Output |
| :------------------------------------------- | :----- |
| `mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]`        | `24`   |

**Explanation:**
-   There are `8` submatrices of size `1x1`.
-   There are `5` submatrices of size `1x2`.
-   There are `2` submatrices of size `1x3`.
-   There are `4` submatrices of size `2x1`.
-   There are `2` submatrices of size `2x2`.
-   There are `2` submatrices of size `3x1`.
-   There is `1` submatrix of size `3x2`.
-   Total: `8 + 5 + 2 + 4 + 2 + 2 + 1 = 24`.
</details>

---

## 💡 Approach

The core idea is to simplify the 2D problem into a 1D problem. We can iterate through every possible pair of a `startRow` and an `endRow` which defines the upper and lower boundaries of potential submatrices.

For each `[startRow, endRow]` pair, we can "compress" the rows between them into a single 1D array (let's call it `vec`). This `vec` will have a length equal to the number of columns `n`. The value at `vec[col]` will be `1` if and only if **all** the elements in the original matrix `mat` from `startRow` to `endRow` in that specific `col` are `1`. If even one element is `0`, `vec[col]` becomes `0`. This compression is efficiently done using a bitwise `AND` operation.

Once we have this 1D array `vec`, the problem is reduced to a simpler one: **"Count the number of subarrays with all ones."** This is a standard problem that can be solved in linear time. We iterate through the 1D array, keeping a count of consecutive ones. For every `1` we encounter, we add the current count of consecutive ones to our total result. If we see a `0`, we reset the consecutive count.

By doing this for every possible submatrix height (defined by `startRow` and `endRow`) and summing up the results, we can find the total count of submatrices with all ones in the original 2D matrix.

<details>
<summary><strong>Step-by-step Walkthrough</strong></summary>

1.  Initialize a `result` counter to `0`.
2.  Iterate through each possible `startRow` from `0` to `m-1`.
3.  Inside this loop, start a second loop for the `endRow`, from `startRow` to `m-1`. This pair `(startRow, endRow)` defines a horizontal slice of the matrix.
4.  For each `(startRow, endRow)` pair, we create a temporary 1D array `vec` of size `n`, initially filled with `1`s. This `vec` will represent the compressed view of the matrix slice.
5.  Iterate through each `col` from `0` to `n-1`. Update `vec[col]` by performing a bitwise `AND` with the value `mat[endRow][col]`. This ensures that `vec[col]` remains `1` only if all cells in that column from `startRow` to `endRow` are `1`.
6.  After processing the entire row `endRow` and updating `vec`, we now have a 1D array problem.
7.  Call a helper function `OnedArrayCount(vec)` to count the subarrays of all ones in `vec`.
    -   Inside this helper, initialize a `consecutive_ones` counter and a `sub_count` to `0`.
    -   Iterate through `vec`. If the current element is `1`, increment `consecutive_ones`. If it's `0`, reset `consecutive_ones` to `0`.
    -   In each step, add the current `consecutive_ones` value to `sub_count`.
    -   Return `sub_count`.
8.  Add the result from the helper function to our main `result`.
9.  After all loops complete, `result` will hold the total number of submatrices with all ones.

This approach effectively covers all possible submatrices by iterating through all possible top and bottom boundaries (`startRow`, `endRow`) and then calculating the valid submatrices within that horizontal slice.

</details>

---

## 💻 Solution Code

```cpp
// Intuition: The problem of counting all-one submatrices in a 2D grid can be simplified by reducing it to a 1D problem. For every possible submatrix height (defined by a start and end row), we can compress the 2D slice into a 1D array. Then, we can count the number of all-one subarrays in this 1D array, which is a much simpler task.

// Approach: We iterate through all possible pairs of start and end rows. For each pair, we create a 1D vector `vec` where `vec[j]` is 1 if and only if all elements in column `j` from the start row to the end row are 1. This is achieved by using a bitwise AND operation. Once we have this 1D vector, we use a helper function to count the number of subarrays containing only ones. The helper function iterates through the 1D vector, maintaining a count of consecutive ones and adding this count to the total for each element. The final result is the sum of counts from all possible row pairs.

// Time Complexity: O(m * m * n), where 'm' is the number of rows and 'n' is the number of columns. We have nested loops for startRow (m), endRow (m), and column (n).

// Space Complexity: O(n), for the auxiliary vector `vec` used to store the compressed 1D representation of the matrix slice.

class Solution {
public:

    // Helper function to count subarrays with all ones in a 1D array.
    int OnedArrayCount(vector<int>& vec) {
        int cons = 0;       // Counter for consecutive ones.
        int subCount = 0;   // Total count of subarrays.

        // Iterate through each value in the 1D vector.
        for(int &val : vec) {
            if(val == 0) {
                // If we encounter a 0, reset the consecutive count.
                cons = 0;
            } else {
                // If it's a 1, increment the consecutive count.
                cons++;
            }
            // Add the current consecutive count to the total subarray count.
            // e.g., for [1,1,1], cons becomes 1, then 2, then 3. subCount = 1 + 2 + 3 = 6.
            subCount += cons;
        }

        return subCount;
    }

    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();      // Number of rows.
        int n = mat[0].size();   // Number of columns.

        int result = 0; // Initialize total count of submatrices.

        // Iterate through all possible starting rows.
        for(int startRow = 0; startRow < m; startRow++) {
            
            // Create a 1D vector to represent the compressed matrix slice.
            // Initialize with all ones, as we start with a single row.
            vector<int> vec(n, 1);
            
            // Iterate through all possible ending rows, starting from the current startRow.
            for(int endRow = startRow; endRow < m; endRow++) {
                
                // Update the 1D vector by performing a bitwise AND with the current row.
                // This ensures vec[col] is 1 only if all elements in that column from startRow to endRow are 1.
                for(int col = 0; col < n; col++) {
                    vec[col] = vec[col] & mat[endRow][col];
                }

                // Count the all-one subarrays in the compressed 1D vector and add to the result.
                result += OnedArrayCount(vec);
            }
        }

        return result;
    }
};

/*
*
* Dry Run
*
mat = [[1,0,1],
       [1,1,0],
       [1,1,0]]

1. startRow = 0:
   - endRow = 0:
     - vec becomes [1, 0, 1] (mat[0])
     - OnedArrayCount([1, 0, 1]) -> cons goes 1, 0, 1. subCount = 1 + 0 + 1 = 2.
     - result = 2.
   - endRow = 1:
     - vec was [1, 0, 1], now AND with mat[1] ([1, 1, 0]) -> vec becomes [1, 0, 0].
     - OnedArrayCount([1, 0, 0]) -> cons goes 1, 0, 0. subCount = 1 + 0 + 0 = 1.
     - result = 2 + 1 = 3.
   - endRow = 2:
     - vec was [1, 0, 0], now AND with mat[2] ([1, 1, 0]) -> vec becomes [1, 0, 0].
     - OnedArrayCount([1, 0, 0]) -> cons goes 1, 0, 0. subCount = 1 + 0 + 0 = 1.
     - result = 3 + 1 = 4.

2. startRow = 1:
   - vec is reset.
   - endRow = 1:
     - vec becomes [1, 1, 0] (mat[1])
     - OnedArrayCount([1, 1, 0]) -> cons goes 1, 2, 0. subCount = 1 + 2 + 0 = 3.
     - result = 4 + 3 = 7.
   - endRow = 2:
     - vec was [1, 1, 0], now AND with mat[2] ([1, 1, 0]) -> vec becomes [1, 1, 0].
     - OnedArrayCount([1, 1, 0]) -> cons goes 1, 2, 0. subCount = 1 + 2 + 0 = 3.
     - result = 7 + 3 = 10.

3. startRow = 2:
   - vec is reset.
   - endRow = 2:
     - vec becomes [1, 1, 0] (mat[2])
     - OnedArrayCount([1, 1, 0]) -> cons goes 1, 2, 0. subCount = 1 + 2 + 0 = 3.
     - result = 10 + 3 = 13.

Final result: 13.

*/
```

---

## 🔑 Key Insights

-   **Problem Reduction**: The main takeaway is transforming a complex 2D problem into a series of simpler 1D problems. By fixing the top and bottom rows, we can focus on counting valid "columns" which then becomes equivalent to counting contiguous subarrays of ones.
-   **Bitwise AND for Compression**: Using the bitwise `AND` operation is a clever and efficient way to "compress" multiple rows into one. `vec[j] = vec[j] & mat[i][j]` ensures that `vec[j]` stays `1` only if it was already `1` and the new element `mat[i][j]` is also `1`.
-   **1D Subarray Counting**: The logic for counting subarrays with all ones in a 1D array is fundamental. If you have `k` consecutive ones, they form `k * (k + 1) / 2` subarrays. Our code does this incrementally: for a sequence of `k` ones, it adds `1 + 2 + ... + k` to the count.

---

## 🚀 Further Exploration

-   **Monotonic Stack Approach**: This problem has a more optimal solution using a monotonic stack, similar to the "Largest Rectangle in Histogram" problem. You can process the matrix row by row, treating each row as the base of a histogram where the height of each bar is the number of consecutive ones above it. This improves the time complexity to `O(m * n)`.

---

## 🔗 References

-   [LeetCode Problem: Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
-   [Similar Problem: Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)

---

## 🏷️ Tags

`Array` `Dynamic Programming` `Matrix` `Stack` `Monotonic Stack`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/count-submatrices-with-all-ones/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)