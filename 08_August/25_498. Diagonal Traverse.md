<div align="center">
  <img src="https://assets.leetcode.com/uploads/2021/04/10/diag1-grid.jpg" alt="Diagonal Traverse" width="150"/>
  <h1>498. Diagonal Traverse</h1>
  <p><strong>Difficulty: Medium</strong></p>
  <p>
    <a href="https://github.com/imnilesh18/LeetCode-DCC-POTD-2025" target="_blank">
      <img src="https://img.shields.io/badge/Repo-LeetCode%20Solutions-blue?style=for-the-badge&logo=github" alt="GitHub Repo">
    </a>
    <a href="https://leetcode.com/problems/diagonal-traverse/description/" target="_blank">
      <img src="https://img.shields.io/badge/Problem-Link-yellow?style=for-the-badge&logo=leetcode" alt="LeetCode Problem Link">
    </a>
  </p>
</div>

---

## 📝 Problem Statement

Given an `m x n` matrix `mat`, return an array of all the elements of the array in a diagonal order.

---

## constraining a bit

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n <= 10^4`
- `1 <= m * n <= 10^4`
- `-10^5 <= mat[i][j] <= 10^5`

---

## 🖼️ Examples

<details>
<summary><strong>Example 1</strong></summary>

| Input                             | Output                |
| --------------------------------- | --------------------- |
| `mat = [[1,2,3],[4,5,6],[7,8,9]]` | `[1,2,4,7,5,3,6,8,9]` |

**Visualization:**
<img src="https://assets.leetcode.com/uploads/2021/04/10/diag1-grid.jpg" alt="Example 1 Visualization" width="300"/>

</details>

<details>
<summary><strong>Example 2</strong></summary>

| Input                 | Output      |
| --------------------- | ----------- |
| `mat = [[1,2],[3,4]]` | `[1,2,3,4]` |

</details>

---

## 💡 Approach

The key observation is that elements on the same diagonal share a common property: the sum of their row and column indices (`i + j`) is constant. We can leverage this to group all elements of a diagonal together.

1.  **Group Diagonals:** We can use a hash map (or a map in C++) where the key is the sum of indices (`i + j`) and the value is a list of all elements `mat[i][j]` that have this sum.
2.  **Populate the Map:** Iterate through the entire `m x n` matrix. For each element `mat[i][j]`, calculate the key `i + j` and push the element into the corresponding list in the map.
3.  **Alternate Directions:** The problem requires the traversal direction to flip for each diagonal. Diagonals with an even sum of indices (`i + j`) are traversed upwards (bottom-left to top-right), while those with an odd sum are traversed downwards (top-right to bottom-left).
4.  **Reverse Diagonals:** The natural order of insertion into our map's lists (by iterating `i` then `j`) matches the downwards traversal. For the upwards diagonals (even-sum keys), we simply need to **reverse** the list of elements we collected.
5.  **Construct Result:** Iterate through the map from the smallest key to the largest. For each key, if it's even, reverse the corresponding list. Then, append all elements from the list to our final result array.

This method systematically collects, reorders, and combines the diagonals to produce the final desired output.

---

## 💻 Solution Code

Here are the solutions in C++.

### C++ (Optimized Map-Based Approach)

```cpp
// Intuition:
// The core idea is that all elements on the same diagonal (from top-right to bottom-left)
// share the same sum of their indices (i + j). We can use this property to group elements
// by their diagonal. The traversal order alternates for each diagonal, which can be handled
// by reversing the lists of elements for alternating diagonals.

// Approach:
// 1. Use a map where the key is the diagonal index (i + j) and the value is a vector of numbers on that diagonal.
// 2. Iterate through the input matrix `mat` from top to bottom, left to right.
// 3. For each element `mat[i][j]`, add it to the vector associated with the key `i + j` in the map.
// 4. After populating the map, iterate through its key-value pairs.
// 5. A `flip` boolean is used to keep track of the direction. For every other diagonal, reverse the vector of elements.
// 6. Append the elements of each vector (now in the correct order) to the final `result` vector.
// 7. Return the `result`.

// Time Complexity: O(m * n * log(m + n))
// - We iterate through all m*n elements of the matrix.
// - For each element, inserting it into the map takes O(log K) time, where K is the number of diagonals (m + n - 1).
// - Reversing and appending elements takes a total of O(m * n) time across all diagonals.
// - The dominant factor is populating the map.

// Space Complexity: O(m * n)
// - The map stores all m*n elements of the matrix.

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int m = mat.size(); // Get the number of rows
        int n = mat[0].size(); // Get the number of columns

        // Use a map to store elements based on the sum of their indices (i + j)
        map<int, vector<int>> mp;

        vector<int> result; // This vector will store the final diagonally traversed elements

        // Populate the map by iterating through the matrix
        // fill the map using [i + j]
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                mp[i + j].push_back(mat[i][j]); // Group elements by the sum of their indices
            }
        }

        bool flip = true; // A flag to alternate the direction of traversal
        // Iterate through the map, which is sorted by key (diagonal index)
        for(auto &it: mp) {
            // For upward diagonals (even sum of indices), we need to reverse the order
            if(flip) {
                //it.second reverse
                reverse(it.second.begin(), it.second.end());
            }

            // Append the elements of the current diagonal to the result vector
            for(int &num: it.second) {
                result.push_back(num);
            }

            // Flip the flag for the next diagonal to change direction
            flip = !flip;
        }
        return result; // Return the final ordered vector
    }
};

/*
*
* Dry Run
*
* Input: mat = [[1,2,3],
* [4,5,6],
* [7,8,9]]
*
* 1. Initialize m = 3, n = 3, map<int, vector<int>> mp, vector<int> result.
*
* 2. Populate map:
* - i=0, j=0: mp[0].push_back(1) -> mp = {0: [1]}
* - i=0, j=1: mp[1].push_back(2) -> mp = {0: [1], 1: [2]}
* - i=0, j=2: mp[2].push_back(3) -> mp = {0: [1], 1: [2], 2: [3]}
* - i=1, j=0: mp[1].push_back(4) -> mp = {0: [1], 1: [2, 4]}
* - i=1, j=1: mp[2].push_back(5) -> mp = {0: [1], 1: [2, 4], 2: [3, 5]}
* - i=1, j=2: mp[3].push_back(6) -> mp = {0: [1], 1: [2, 4], 2: [3, 5], 3: [6]}
* - i=2, j=0: mp[2].push_back(7) -> mp = {0: [1], 1: [2, 4], 2: [3, 5, 7]}
* - i=2, j=1: mp[3].push_back(8) -> mp = {0: [1], 1: [2, 4], 2: [3, 5, 7], 3: [6, 8]}
* - i=2, j=2: mp[4].push_back(9) -> mp = {0: [1], 1: [2, 4], 2: [3, 5, 7], 3: [6, 8], 4: [9]}
*
* Final Map:
* - 0: [1]
* - 1: [2, 4]
* - 2: [3, 5, 7]
* - 3: [6, 8]
* - 4: [9]
*
* 3. Process map and build result:
* - flip = true
* - it -> key=0, value=[1]: flip is true, reverse [1] -> [1]. result.push_back(1). result = [1]. flip = false.
* - it -> key=1, value=[2, 4]: flip is false. result.push_back(2), result.push_back(4). result = [1, 2, 4]. flip = true.
* - it -> key=2, value=[3, 5, 7]: flip is true, reverse [3, 5, 7] -> [7, 5, 3]. result.push_back(7, 5, 3). result = [1, 2, 4, 7, 5, 3]. flip = false.
* - it -> key=3, value=[6, 8]: flip is false. result.push_back(6, 8). result = [1, 2, 4, 7, 5, 3, 6, 8]. flip = true.
* - it -> key=4, value=[9]: flip is true, reverse [9] -> [9]. result.push_back(9). result = [1, 2, 4, 7, 5, 3, 6, 8, 9]. flip = false.
*
* 4. Return result: [1, 2, 4, 7, 5, 3, 6, 8, 9]
*
*/
```

---

## 🔑 Key Insights

- The sum of indices `i + j` is a powerful invariant for identifying diagonals in a matrix.
- A map provides a convenient way to group elements by this diagonal index, automatically handling the sorting of diagonals by their key.
- The alternating traversal pattern can be implemented with a simple boolean flag that toggles for each diagonal, triggering a reversal of the collected elements.

---

## 🚀 Further Exploration

- **Simulation Approach:** Can you solve this problem without using a map? Consider a direct simulation where you manually control the `(row, col)` indices and the direction of movement. You would need logic to handle boundary conditions (hitting the top, bottom, left, or right edges) and to switch the direction of traversal. This approach would have an O(1) space complexity (excluding the result array).
- **Different Diagonal Directions:** How would you adapt the `i + j` logic to traverse diagonals from top-left to bottom-right? (Hint: Consider using `i - j`).

---

## 📚 References

- [LeetCode Problem: Diagonal Traverse](https://leetcode.com/problems/diagonal-traverse/)

---

## 🏷️ Tags

`Array` `Matrix` `Simulation`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/diagonal-traverse/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
