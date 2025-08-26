# ✨ 3000. Maximum Area of Longest Diagonal Rectangle

<div align="center">
<a href="https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/description/" target="_blank">
    <img src="https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge&logo=leetcode" alt="Difficulty: Easy" />
</a>
<img src="https://img.shields.io/badge/Array-blue?style=for-the-badge&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSIyNCIgaGVpZ2h0PSIyNCIgdmlld0JveD0iMCAwIDI0IDI0Ij48cGF0aCBkPSJNMjIgNGgtMnYtMmgtMnYyaC02di0yaC0ydiJoNnY0aDJ2LTJoMnYtMmgtMnptLTYgMTJ2LTJoLTJ2Mmg0em0tNCAwdi0yaC0ydiJoNHptOC00aC0ydi0yaC0ydiJoNnYtMmgtMnptLTYgMGgtMnYtMmgtMnYyaDZ6bS00IDBoLTJ2LTJoLTJ2Mmg2em0tNCAwaC0ydi0yaC0ydiJoNnptLTYgNmgydjJoMnYtMmgtMnYtMmgtMnY0em00IDBoMnYyaDJ2LTJoMnYtMmgtNnYyem02IDBoMnYyaDJ2LTJoMnYtMmgtNnYyem0wIDRoMnYyaDJ2LTJoMnYtMmgtNnYyem0tNiAwaDJ2Mmgydi0yaDJ2LTJoLTZ2MnptLTYgMGgydjJoMnYtMmgtMnYtMmgtMnY0eiIvPjwvc3ZnPg==" alt="Category: Array" />
<img src="https://img.shields.io/badge/Math-orange?style=for-the-badge&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSIyNCIgaGVpZ2h0PSIyNCIgdmlld0JveD0iMCAwIDI0IDI0Ij48cGF0aCBkPSJNMTIgMmwtMTAtMTAgMTAgMTB6bTAgMGwxMCAxMGwtMTAtMTB6bS01IDVoLTd2LTdoN3Y3em0xMiAwdi03aDd2N2gtN3ptLTcgN2gtN3YtN2g3djd6bTcgN3YtN2g3djd2LTd6Ii8+PC9zdmc+" alt="Category: Math" />
</div>

---

## 📝 Problem Statement

You are given a 2D `0-indexed` integer array `dimensions`. For each index `i`, `dimensions[i][0]` represents the length and `dimensions[i][1]` represents the width of rectangle `i`.

Your task is to return the **area** of the rectangle that has the **longest diagonal**. If there are multiple rectangles with the same longest diagonal, you should return the area of the one with the **maximum area**.

---

## 🛑 Constraints

- `1 <= dimensions.length <= 100`
- `dimensions[i].length == 2`
- `1 <= dimensions[i][0], dimensions[i][1] <= 100`

---

## 📋 Examples

<div align="center">

| Input | Output | Explanation |
| :--- | :--- | :--- |
| `dimensions = [[9,3],[8,6]]` | `48` | Diagonal of `[9,3]` is `sqrt(90)`. Diagonal of `[8,6]` is `sqrt(100)`. The second rectangle has the longer diagonal. Its area is `8 * 6 = 48`. |
| `dimensions = [[3,4],[4,3]]` | `12` | Both rectangles have a diagonal of `5`. Since their areas are both `12`, the maximum area is `12`. |

</div>

---

## 💡 Approach

The problem asks us to find the area of a rectangle based on two conditions: it must have the longest possible diagonal, and if there's a tie in diagonal length, it must have the largest area among those with the longest diagonal.

A straightforward approach is to iterate through each rectangle, calculate its diagonal and area, and keep track of the best rectangle found so far.

The diagonal of a rectangle with length `l` and width `w` is calculated using the Pythagorean theorem: $d = \sqrt{l^2 + w^2}$. However, to compare two diagonals, we don't need to compute the actual square root. We can simply compare their squared values ($d^2 = l^2 + w^2$). This avoids floating-point arithmetic and is more efficient.

We can maintain two variables: `max_diagonal_sq` to store the maximum squared diagonal found so far, and `max_area` to store the area of the best rectangle.

<details>
<summary>📋 Step-by-Step Walkthrough</summary>

1.  Initialize `max_diagonal_sq = 0` and `max_area = 0`. These will track the longest diagonal (squared) and the corresponding maximum area.
2.  Iterate through each `dimension` pair `[l, w]` in the input array.
3.  For each rectangle, calculate its squared diagonal: `current_diagonal_sq = l * l + w * w`.
4.  Calculate its area: `current_area = l * w`.
5.  Compare `current_diagonal_sq` with `max_diagonal_sq`:
    * If `current_diagonal_sq > max_diagonal_sq`, we've found a new longest diagonal. We update `max_diagonal_sq` to `current_diagonal_sq` and `max_area` to `current_area`.
    * If `current_diagonal_sq == max_diagonal_sq`, we have a tie in diagonal length. The problem states we should then choose the one with the maximum area. So, we update `max_area = max(max_area, current_area)`.
6.  After iterating through all the rectangles, `max_area` will hold the area of the rectangle that satisfies the conditions. Return `max_area`.

</details>

This approach ensures we process each rectangle once, making it efficient and easy to implement.

---

## 💻 Solution Code

### C++

```cpp
// Intuition: The problem requires us to find the area of the rectangle with the longest diagonal. If multiple rectangles share the same longest diagonal, we should choose the one with the largest area. We can iterate through all rectangles, keeping track of the one that best fits these criteria.

// Approach: We will iterate through the `dimensions` array. For each rectangle, we calculate the square of its diagonal length (l*l + w*w) to avoid using `sqrt` for comparison. We maintain two variables: `maxDiag` for the maximum squared diagonal found so far, and `maxArea` for the corresponding area.
// 1. Initialize `maxDiag` and `maxArea` to 0.
// 2. Loop through each rectangle's dimensions `[l, w]`.
// 3. Calculate the squared diagonal (`diag = l*l + w*w`) and area (`area = l*w`).
// 4. If `diag` is greater than `maxDiag`, it means we've found a new longest diagonal. We update `maxDiag` to `diag` and `maxArea` to `area`.
// 5. If `diag` is equal to `maxDiag`, we have a tie. We then update `maxArea` to the maximum of its current value and the new `area`.
// 6. After the loop, `maxArea` will hold the final result.

// Time Complexity: O(N), where N is the number of rectangles in the `dimensions` array. We perform a single pass through the array.
// Space Complexity: O(1), as we only use a few constant extra variables (`maxDiag`, `maxArea`, `l`, `w`, `diag`, `area`).

class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        // Get the total number of rectangles.
        int n = dimensions.size();

        // Initialize max diagonal squared and max area to zero.
        int maxDiag = 0;
        int maxArea = 0;

        // Iterate through each rectangle's dimensions.
        for(int i = 0; i < n; i++) {
            // Extract length and width.
            int l = dimensions[i][0];
            int w = dimensions[i][1];

            // Calculate the square of the diagonal length.
            // Using squared value avoids sqrt and floating point issues.
            int diag = l * l + w * w;
            // Calculate the area.
            int area = l * w;

            // Check if the current diagonal is the new longest.
            if(diag > maxDiag) {
                maxDiag = diag; // Update the max diagonal squared.
                maxArea = area; // Update the max area.
            } else if(diag == maxDiag) {
                // If diagonals are equal, update area to the larger one.
                maxArea = max(maxArea, area);
            }
        }
        // Return the final maximum area found.
        return maxArea;
    }
};

/*
*
* Dry Run
*
* Input: dimensions = [[9,3],[8,6]]
*
* Initial state:
* n = 2
* maxDiag = 0
* maxArea = 0
*
* --- Loop Start ---
*
* i = 0:
* l = 9, w = 3
* diag = 9*9 + 3*3 = 81 + 9 = 90
* area = 9 * 3 = 27
* Check condition: if(diag > maxDiag) -> if(90 > 0) -> true
* Update: maxDiag = 90, maxArea = 27
*
* i = 1:
* l = 8, w = 6
* diag = 8*8 + 6*6 = 64 + 36 = 100
* area = 8 * 6 = 48
* Check condition: if(diag > maxDiag) -> if(100 > 90) -> true
* Update: maxDiag = 100, maxArea = 48
*
* --- Loop End ---
*
* Final Result: return maxArea -> 48
*
*/
```

---

## 🧠 Key Insights

-   **Comparing Diagonals:** The key optimization is to compare the squares of the diagonal lengths ($l^2 + w^2$) instead of the actual lengths ($\sqrt{l^2 + w^2}$). This avoids computationally intensive square root operations and potential floating-point precision issues, making the code cleaner and faster.
-   **Tie-Breaking Logic:** The problem has a clear two-level priority system:
    1.  Primary Criterion: Longest diagonal.
    2.  Secondary Criterion (Tie-breaker): Maximum area.
    The `if-else if` structure perfectly handles this logic by first checking for a new longest diagonal and then, only if there's a tie, checking for a larger area.

---

## 🧭 Further Exploration

-   What if the tie-breaking rule was to choose the rectangle with the smallest perimeter? How would the code change?
-   Consider a 3D version of this problem with cuboids `[length, width, height]`. How would you find the volume of the cuboid with the longest space diagonal?
-   Could this problem be solved using a custom sorting function and a lambda expression in C++ or a similar feature in other languages? What would be the trade-offs?

---

## 📚 References

-   [Pythagorean Theorem](https://en.wikipedia.org/wiki/Pythagorean_theorem)

---

## 🏷️ Tags

`Array` `Math` `Iteration` `Sorting`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)