# 1039. Minimum Score Triangulation of Polygon

---

### <p align="center"> ✨ A detailed, stylish, and educational guide to solving problem #1039 ✨ </p>

---

## MEDIUM

- **Problem Link:** [1039. Minimum Score Triangulation of Polygon](https://leetcode.com/problems/minimum-score-triangulation-of-polygon/description/)
- **Tags:** `Dynamic Programming`, `Recursion`, `Memoization`, `Matrix Chain Multiplication`
- **Badges:**
    <p align="center">
        <img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg" alt="Difficulty: Medium">
        <img src="https://img.shields.io/badge/Topic-Dynamic%20Programming-blue.svg" alt="Topic: Dynamic Programming">
        <img src="https://img.shields.io/badge/Pattern-MCM-orange.svg" alt="Pattern: Matrix Chain Multiplication">
    </p>

---

## 📝 Problem Statement

You have a convex **n-sided polygon** where each vertex has an integer value. You are given an integer array `values` where `values[i]` is the value of the i-th vertex (in **clockwise** order).

You will **triangulate** the polygon into `n - 2` triangles. For each triangle, the value of that triangle is the **product** of the values of its vertices, and the total score of the triangulation is the **sum** of these values over all `n - 2` triangles.

Return _the minimum possible total score that you can achieve with some triangulation of the polygon_.

---

## ⛓️ Constraints

- `n == values.length`
- `3 <= n <= 50`
- `1 <= values[i] <= 100`

---

## 📊 Examples

| Input                    | Output | Explanation                                                                                                              |
| ------------------------ | ------ | ------------------------------------------------------------------------------------------------------------------------ |
| `values = [1,2,3]`       | `6`    | The polygon is already a triangle. The score is `1 * 2 * 3 = 6`.                                                         |
| `values = [3,7,4,5]`     | `144`  | Two triangulations exist: <br> 1. `3*7*5 + 4*5*7 = 105 + 140 = 245` <br> 2. `3*4*5 + 3*4*7 = 60 + 84 = 144`. Min is 144. |
| `values = [1,3,1,4,1,5]` | `13`   | The minimum score is `1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13`.                                                               |

---

## 🧠 Approach & Explanation

The problem asks for the minimum score of a polygon triangulation. This problem has optimal substructure and overlapping subproblems, which strongly hints at **Dynamic Programming**. It's a classic variation of the **Matrix Chain Multiplication (MCM)** pattern.

### Core Idea

1.  **Fix an Edge:** Consider an edge of the polygon connecting vertices `i` and `j`. To form a triangle with this edge, we must pick a third vertex `k` where `i < k < j`.

2.  **Form a Triangle:** Creating the triangle `(i, k, j)` adds `values[i] * values[k] * values[j]` to our total score.

3.  **Decompose into Subproblems:** This triangle splits the original polygon (defined by vertices `i` through `j`) into two smaller, independent sub-polygons:

    - One polygon with vertices from `i` to `k`.
    - Another polygon with vertices from `k` to `j`.

4.  **Recursive Formulation:** We can define a function, let's say `solve(i, j)`, that computes the minimum triangulation score for the sub-polygon from vertex `i` to `j`. The total score for a particular choice of `k` would be:
    `score = (values[i] * values[k] * values[j]) + solve(i, k) + solve(k, j)`

5.  **Find the Minimum:** We must try every possible intermediate vertex `k` between `i` and `j` and take the minimum score among all possibilities.

<details>
<summary><b>Recursive Walkthrough</b></summary>
<p>
Let's define our main recursive function `solve(i, j)`.

- **Base Case:** If we have fewer than 3 vertices (i.e., `j - i + 1 < 3`), we cannot form a triangle. The score for this non-existent triangulation is `0`. So, if `j` and `i` are adjacent, we return `0`.

- **Recursive Step:** We iterate through all possible vertices `k` from `i + 1` to `j - 1`. For each `k`, we calculate the cost:

  1.  The cost of the triangle `(i, k, j)`.
  2.  The cost of recursively solving the left sub-polygon `(i, ..., k)`.
  3.  The cost of recursively solving the right sub-polygon `(k, ..., j)`.

  We keep track of the minimum cost found across all possible `k`.

- **Memoization:** Many subproblems `(i, k)` and `(k, j)` will be calculated multiple times. To optimize this, we use a 2D array `t[i][j]` to store the result of `solve(i, j)`, avoiding redundant computations.
</p>
</details>

---

## 💻 Solution Code

### Optimized C++ Solution (Recursion + Memoization)

```cpp
// Intuition:
// The problem asks for the minimum score from triangulating a polygon. This can be broken down into smaller, overlapping subproblems.
// By fixing an edge (from vertex `i` to `j`), we can form a triangle with any other vertex `k`.
// This triangle splits the remaining polygon into two smaller subproblems. This structure suggests a dynamic programming approach,
// very similar to the Matrix Chain Multiplication (MCM) pattern.

// Approach:
// We use a recursive function `solve(i, j)` with memoization to find the minimum score for the polygon formed by vertices `i` to `j`.
// 1. Base Case: If there are fewer than 3 vertices (`j - i + 1 < 3`), no triangle can be formed, so the score is 0.
// 2. Memoization Check: If the result for `solve(i, j)` is already computed and stored in our memoization table `t`, return it.
// 3. Recursive Step: Iterate through all possible intermediate vertices `k` from `i + 1` to `j - 1`.
//    - For each `k`, calculate the cost of forming the triangle `(i, k, j)`.
//    - The total score for this choice is `(values[i] * values[k] * values[j]) + solve(i, k) + solve(k, j)`.
// 4. Find Minimum: Keep track of the minimum score among all choices of `k`.
// 5. Store and Return: Store the minimum result in `t[i][j]` and return it.

// Time Complexity: O(n^3) - There are O(n^2) states `(i, j)`, and for each state, we iterate `k` from `i` to `j`, taking O(n) time.
// Space Complexity: O(n^2) - For the 2D memoization table `t` of size approximately 51x51.

class Solution {
public:
    // Memoization table to store results of subproblems.
    int t[51][51];

    // Recursive function to solve for the sub-polygon from vertex i to j.
    int solve(vector<int>& values, int i, int j) {

        // Base case: A polygon must have at least 3 vertices to form a triangle.
        if(j - i + 1 < 3) {
            return 0; // No triangles can be formed, so score is 0.
        }

        // If this subproblem has already been solved, return the stored result.
        if(t[i][j] != -1) {
            return t[i][j];
        }

        // Initialize result for this subproblem to a very large value.
        int result = INT_MAX;

        // Iterate through all possible third vertices 'k' for the triangle (i, k, j).
        for(int k = i + 1; k < j; k++) {
            // Calculate the total weight for the current triangulation choice.
            int wt = (values[i] * values[k] * values[j]) // Score of the current triangle.
                   + solve(values, i, k)                // Minimum score for the left sub-polygon.
                   + solve(values, k, j);               // Minimum score for the right sub-polygon.

            // Update the result with the minimum weight found so far.
            result = min(result, wt);
        }

        // Store the result in the memoization table and return it.
        return t[i][j] = result;
    }

    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        // Initialize the memoization table with -1.
        memset(t, -1, sizeof(t));
        // Start the recursion for the entire polygon from vertex 0 to n-1.
        return solve(values, 0, n - 1);
    }
};

/*
*
* Dry Run
*
* Let's trace `minScoreTriangulation([3,7,4,5])`:
* n = 4
*
* Initial call: `solve(values, 0, 3)`
* i = 0, j = 3
* Loop for k from 1 to 2:
*
* 1. k = 1:
* wt = (values[0] * values[1] * values[3]) + solve(0, 1) + solve(1, 3)
* - solve(0, 1): Base case (2 vertices), returns 0.
* - solve(1, 3): i=1, j=3. k can only be 2.
* - wt_sub = (values[1] * values[2] * values[3]) + solve(1, 2) + solve(2, 3)
* - solve(1, 2) returns 0.
* - solve(2, 3) returns 0.
* - wt_sub = 7 * 4 * 5 + 0 + 0 = 140.
* - solve(1, 3) returns 140.
* wt = (3 * 7 * 5) + 0 + 140 = 105 + 140 = 245.
* result = min(INT_MAX, 245) = 245.
*
* 2. k = 2:
* wt = (values[0] * values[2] * values[3]) + solve(0, 2) + solve(2, 3)
* - solve(2, 3): Base case (2 vertices), returns 0.
* - solve(0, 2): i=0, j=2. k can only be 1.
* - wt_sub = (values[0] * values[1] * values[2]) + solve(0, 1) + solve(1, 2)
* - solve(0, 1) returns 0.
* - solve(1, 2) returns 0.
* - wt_sub = 3 * 7 * 4 + 0 + 0 = 84.
* - solve(0, 2) returns 84.
* wt = (3 * 4 * 5) + 84 + 0 = 60 + 84 = 144.
* result = min(245, 144) = 144.
*
* Loop ends. `t[0][3]` is set to 144.
* Final answer returned is 144.
*
*/
```

---

## 💡 Key Insights & Notes

- **MCM Pattern:** The key is recognizing the structure `solve(i, j) = min(solve(i, k) + solve(k, j) + cost)` for `k` between `i` and `j`. This is the hallmark of the Matrix Chain Multiplication pattern.
- **Polygon as an Array:** The clockwise ordering of vertices allows us to treat the polygon's edges as segments of an array, making it easier to define subproblems with indices `(i, j)`.
- **Base Case Importance:** The base case where `j - i + 1 < 3` is crucial. It signifies that a segment of the polygon is just a line or a point, which cannot be triangulated further, hence its contribution to the score is zero.

---

## 🚀 Further Exploration

- **Bottom-Up DP:** This problem can also be solved iteratively using a bottom-up dynamic programming approach. The state transitions would depend on the length of the polygon chain. This can sometimes be more efficient by avoiding recursion overhead.
- **Catalan Numbers:** The number of ways to triangulate a convex n-gon is related to the Catalan numbers, `C_(n-2)`. While not directly needed for this problem, it's an interesting related concept in combinatorics.

---

## 📚 References

- [Matrix Chain Multiplication (GeeksforGeeks)](https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/)
- [Polygon Triangulation (Wikipedia)](https://en.wikipedia.org/wiki/Polygon_triangulation)

---

## 🏷️ Tags

`LeetCode` `Medium` `Dynamic Programming` `Recursion` `Memoization` `C++` `MCM`

---

## 📄 License

This repository is released under the [MIT License](https://www.google.com/search?q=./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/minimum-score-triangulation-of-polygon/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

<!-- end list -->
