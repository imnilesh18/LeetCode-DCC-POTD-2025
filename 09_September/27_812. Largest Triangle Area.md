<div align="center">
  <h1>📐 812. Largest Triangle Area</h1>
  <a href="https://leetcode.com/problems/largest-triangle-area/description/">
    <img src="https://img.shields.io/badge/LeetCode-812-yellow?style=for-the-badge&logo=leetcode" alt="LeetCode Problem">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge" alt="Difficulty: Easy">
</div>

<br>

<p align="center">
  <img src="https://s3-lc-upload.s3.amazonaws.com/uploads/2018/04/04/1027.png" alt="Problem Visualization" width="400"/>
</p>

---

## 📝 Problem Statement

Given an array of points on the X-Y plane `points` where `points[i] = [xi, yi]`, return the area of the **largest triangle** that can be formed by any three different points. Answers within `10^-5` of the actual answer will be accepted.

---

## ⚙️ Constraints

- `3 <= points.length <= 50`
- `-50 <= xi, yi <= 50`
- All the given points are **unique**.

---

## 💡 Examples

| Input                                      | Output    | Explanation                                                               |
| :----------------------------------------- | :-------- | :------------------------------------------------------------------------ |
| `points = [[0,0],[0,1],[1,0],[0,2],[2,0]]` | `2.00000` | The five points are shown in the figure. The red triangle is the largest. |
| `points = [[1,0],[0,0],[0,1]]`             | `0.50000` | This triangle has vertices at (1,0), (0,0), and (0,1).                    |

---

## 🧠 Approach

Since the number of points is small (up to 50), we can afford to check every possible combination of three points. The most straightforward approach is to use a brute-force method.

1.  **Iterate Through All Combinations**: Use three nested loops to select every unique triplet of points `(i, j, k)` from the `points` array. These three points will form the vertices of a triangle.

2.  **Calculate Triangle Area**: For each triplet of points `(x1, y1)`, `(x2, y2)`, and `(x3, y3)`, we need to calculate the area of the triangle they form. There are two primary formulas for this:

    a. **Shoelace Formula**: This is a direct and computationally efficient method to find the area of a polygon given the coordinates of its vertices. The formula for a triangle is:
    $$ \text{Area} = \frac{1}{2} |x_1(y_2 - y_3) + x_2(y_3 - y_1) + x_3(y_1 - y_2)| $$
    This formula avoids complex calculations like square roots, making it ideal for this problem.

    b. **Heron's Formula**: This formula calculates the area from the lengths of the three sides (`a`, `b`, `c`).

    - First, calculate the side lengths using the distance formula: $a = \sqrt{(x_2-x_1)^2 + (y_2-y_1)^2}$. A useful C++ function `hypot(dx, dy)` can compute this directly.
    - Next, calculate the semi-perimeter: $s = (a + b + c) / 2$.
    - Finally, apply Heron's formula: $\text{Area} = \sqrt{s(s-a)(s-b)(s-c)}$.
      While accurate, this method involves multiple square root calculations, which can be slower and introduce precision issues.

3.  **Track Maximum Area**: Maintain a variable, `maxArea`, initialized to 0. After calculating the area of each triangle, update `maxArea` if the current triangle's area is larger.

4.  **Return Result**: After checking all combinations, `maxArea` will hold the area of the largest possible triangle.

The overall time complexity will be $O(n^3)$ due to the three nested loops, which is perfectly acceptable for $n \le 50$.

---

## 💻 Solution Code (Brute Force)

Here is the implementation using both the Shoelace and Heron's formulas for completeness.

```cpp
// Intuition:
// To find the largest triangle area, we must consider every possible triangle that can be formed by the given points.
// Since the number of points is small (n <= 50), a brute-force approach of checking every combination of three points is feasible.
// For each triplet of points, we can calculate the area using a standard geometric formula and keep track of the maximum area found.

// Approach:
// 1. Initialize a variable `maxArea` to 0.0 to store the maximum area found so far.
// 2. Use three nested loops to iterate through all unique combinations of three points (i, j, k).
// 3. For each combination, extract the coordinates (x1, y1), (x2, y2), and (x3, y3).
// 4. Calculate the area of the triangle formed by these three points. We can use two methods:
//    a. Heron's Formula: Calculate the lengths of the three sides (a, b, c) using the `hypot` function, find the semi-perimeter `s`, and then compute the area.
//    b. Shoelace Formula: A more direct and computationally cheaper method using the coordinates directly. Area = 0.5 * |x1(y2-y3) + x2(y3-y1) + x3(y1-y2)|.
// 5. Update `maxArea` with the maximum of its current value and the areas calculated from both formulas.
// 6. After iterating through all combinations, return `maxArea`.

// Time Complexity: O(n^3) - The three nested loops dominate the complexity, where n is the number of points.
// Space Complexity: O(1) - We only use a constant amount of extra space for variables regardless of the input size.

class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        int n = points.size(); // Get the total number of points.
        double maxArea = 0.0; // Initialize maxArea to store the result.

        // First loop to pick the first point of the triangle.
        for(int i = 0; i < n; i++) {
            // Second loop to pick the second point, starting from i+1 to avoid duplicate triplets.
            for(int j = i+1; j < n; j++) {
                // Third loop to pick the third point, starting from j+1.
                for(int k = j+1; k < n; k++) {
                    // Extract coordinates for the three points.
                    double x1 = points[i][0];
                    double y1 = points[i][1];

                    double x2 = points[j][0];
                    double y2 = points[j][1];

                    double x3 = points[k][0];
                    double y3 = points[k][1];

                    // --- Heron's Formula Calculation ---
                    // Calculate side lengths using the distance formula (hypot(dx, dy) = sqrt(dx^2 + dy^2)).
                    double a = hypot(x2-x1, y2-y1); // Side between point i and j.
                    double b = hypot(x3-x2, y3-y2); // Side between point j and k.
                    double c = hypot(x1-x3, y1-y3); // Side between point k and i.

                    // Calculate the semi-perimeter.
                    double s = (a + b + c) * 0.5;

                    // Calculate area using Heron's formula. Handle cases where points are collinear (area is 0).
                    double heron_area = (s > 0 && s > a && s > b && s > c) ? sqrt(s * (s-a) * (s-b) * (s-c)) : 0.0;

                    // --- Shoelace Formula Calculation ---
                    // A more direct and stable way to calculate area from coordinates.
                    double shoelace_area = 0.5 * abs(x1 * (y2-y3) + x2 * (y3-y1) + x3 * (y1 - y2));

                    // Update the maxArea with the largest area found so far.
                    maxArea = max({maxArea, heron_area, shoelace_area});
                }
            }
        }

        // Return the final maximum area.
        return maxArea;
    }
};

/*
*
* Dry Run
*
* Input: points = [[1,0], [0,0], [0,1]]
* n = 3
* maxArea = 0.0
*
* Loops will run for i=0, j=1, k=2 (the only combination).
*
* i = 0, j = 1, k = 2:
* - Point 1 (i): (x1, y1) = (1, 0)
* - Point 2 (j): (x2, y2) = (0, 0)
* - Point 3 (k): (x3, y3) = (0, 1)
*
* Heron's Formula:
* - a (dist(p1,p2)) = hypot(0-1, 0-0) = hypot(-1, 0) = 1.0
* - b (dist(p2,p3)) = hypot(0-0, 1-0) = hypot(0, 1) = 1.0
* - c (dist(p3,p1)) = hypot(1-0, 0-1) = hypot(1, -1) = sqrt(2) approx 1.414
* - s = (1.0 + 1.0 + 1.414) * 0.5 = 1.707
* - heron_area = sqrt(1.707 * (0.707) * (0.707) * (0.293)) approx sqrt(0.25) = 0.5
*
* Shoelace Formula:
* - shoelace_area = 0.5 * abs(1 * (0-1) + 0 * (1-0) + 0 * (0-0))
* - shoelace_area = 0.5 * abs(-1 + 0 + 0)
* - shoelace_area = 0.5 * 1 = 0.5
*
* Update maxArea:
* - maxArea = max({0.0, 0.5, 0.5}) = 0.5
*
* Final loop finishes.
* Return maxArea = 0.5
*
*/
```

---

## 🔑 Key Insights

- **Brute Force is Viable**: The problem constraints ($N \le 50$) are a strong hint that a polynomial-time solution like $O(N^3)$ is acceptable. Don't overthink looking for a more complex geometric algorithm.
- **Choice of Area Formula**: The Shoelace formula is generally superior to Heron's formula in a computational context. It is less prone to floating-point precision errors and avoids costly `sqrt` operations, making the code cleaner and faster.
- **C++ `hypot` function**: The `hypot(dx, dy)` function is a convenient and numerically stable way to compute $\sqrt{dx^2 + dy^2}$, which is useful for implementing Heron's formula.

---

## 🔗 References

- [Heron's Formula - Wikipedia](https://en.wikipedia.org/wiki/Heron%27s_formula)
- [Shoelace Formula - Wikipedia](https://en.wikipedia.org/wiki/Shoelace_formula)
- [std::hypot - C++ Reference](https://en.cppreference.com/w/cpp/numeric/math/hypot)

---

## 🏷️ Tags

<div align="center">
  <a href="https://leetcode.com/tag/math/"><img src="https://img.shields.io/badge/Topic-Math-blue?style=for-the-badge&logo=react" alt="Math"></a>
  <a href="https://leetcode.com/tag/geometry/"><img src="https://img.shields.io/badge/Topic-Geometry-yellow?style=for-the-badge&logo=react" alt="Geometry"></a>
  <a href="https://leetcode.com/tag/brute-force/"><img src="https://img.shields.io/badge/Topic-Brute%20Force-red?style=for-the-badge&logo=react" alt="Brute Force"></a>
</div>

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/largest-triangle-area/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
