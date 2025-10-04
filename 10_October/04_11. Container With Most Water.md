# 🌊 11. Container With Most Water

## `Medium`

<div align="center">
  <img src="https://img.shields.io/badge/Array-2D3748?style=for-the-badge&logo=Array&logoColor=white" alt="Array Badge"/>
  <img src="https://img.shields.io/badge/Two_Pointers-4285F4?style=for-the-badge&logo=TwoPointers&logoColor=white" alt="Two Pointers Badge"/>
  <img src="https://img.shields.io/badge/Greedy-34A853?style=for-the-badge&logo=Greedy&logoColor=white" alt="Greedy Badge"/>
</div>

<br>

<div align="center">
  <a href="https://leetcode.com/problems/container-with-most-water/description/">
    <img src="https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/17/question_11.jpg" alt="Problem Illustration" width="600px" style="border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.1);">
  </a>
</div>

---

## 📝 Problem Statement

You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i-th` line are `(i, 0)` and `(i, height[i])`.

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return _the maximum amount of water a container can store_.

**Notice** that you may not slant the container.

---

## ⚙️ Constraints

- `n == height.length`
- `2 <= n <= 10^5`
- `0 <= height[i] <= 10^4`

---

## 📋 Examples

| Input                          | Output | Explanation                                                                                                                                    |
| :----------------------------- | :----- | :--------------------------------------------------------------------------------------------------------------------------------------------- |
| `height = [1,8,6,2,5,4,8,3,7]` | `49`   | The max area of water is formed by the lines at index 1 (height 8) and index 8 (height 7). Width = 8-1=7, Height = min(8,7)=7. Area = 7\*7=49. |
| `height = [1,1]`               | `1`    | Width = 1-0=1, Height = min(1,1)=1. Area = 1\*1=1.                                                                                             |

---

## 🧠 Approach

The problem asks us to find the two lines that can hold the most water between them. The amount of water is determined by the area of the container, which is calculated as `width * height`.

- **Width**: The distance between the two lines, i.e., `j - i`.
- **Height**: The height of the shorter of the two lines, i.e., `min(height[i], height[j])`, because water would spill over the shorter side.

<details>
<summary><strong>Brute-Force Intuition</strong></summary>

The most straightforward way is to consider every possible pair of lines and calculate the area for each pair. We can use two nested loops to iterate through all pairs `(i, j)` and compute the area. We keep track of the maximum area found so far and return it at the end. This guarantees we check every possibility but is inefficient, with a time complexity of $O(n^2)$.

</details>

<details>
<summary><strong>Optimized Two-Pointer Approach</strong></summary>

A more efficient method is the **two-pointer approach**. We can start with the widest possible container and iteratively try to find a better one.

1.  **Initialization**:

    - Initialize a `left` pointer `i` at the beginning of the array (`0`).
    - Initialize a `right` pointer `j` at the end of the array (`n-1`).
    - Initialize a variable `maxWater` to `0`.

2.  **Iteration**:

    - Loop as long as `i` is less than `j`.
    - Calculate the current area:
      - `width = j - i`
      - `height = min(height[i], height[j])`
      - `currentArea = width * height`
    - Update `maxWater = max(maxWater, currentArea)`.

3.  **Pointer Movement (The Greedy Choice)**:

    - The key to this approach is deciding which pointer to move. Our goal is to maximize the area. Since we are decreasing the `width` in each step, the only way to potentially get a larger area is by increasing the `height`.
    - The current `height` is limited by the shorter of the two lines (`height[i]` or `height[j]`).
    - If we move the pointer of the taller line, the new height will either be the same or smaller, and since the width is also smaller, the new area cannot be larger.
    - Therefore, we should move the pointer of the **shorter** line inwards. This gives us a chance to find a taller line that might compensate for the reduced width.
      - If `height[i] < height[j]`, we move the left pointer: `i++`.
      - Otherwise, we move the right pointer: `j--`.

4.  **Termination**:
    - The loop continues until the pointers cross (`i >= j`). The value stored in `maxWater` will be the maximum possible area.

This greedy approach works because we start with the maximum possible width and systematically eliminate containers that cannot possibly be the largest, ensuring we check all promising candidates in linear time.

</details>

---

## 💻 Solution Code

### Brute-Force Solution (C++)

```cpp
// Intuition:
// To find the maximum possible area, we can systematically check every single pair of vertical lines.
// For each pair, we calculate the area they can contain and keep track of the largest one seen.

// Approach:
// 1. Initialize a variable `maxWater` to 0.
// 2. Use a nested loop to iterate through all possible pairs of indices (i, j) where i < j.
// 3. For each pair, calculate the width as `w = j - i`.
// 4. Determine the height as the minimum of the two lines: `h = min(height[i], height[j])`.
// 5. Calculate the area: `area = w * h`.
// 6. Update `maxWater = max(maxWater, area)`.
// 7. After checking all pairs, return `maxWater`.

// Time Complexity: O(n^2), as we are checking every possible pair of lines using nested loops.
// Space Complexity: O(1), as we only use a few variables for storage, regardless of input size.
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size(); // Get the total number of lines.
        int maxWater = 0;      // Initialize the maximum water capacity to zero.

        // Iterate through each possible pair of lines.
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Calculate the width between the two lines.
                int w = j - i;
                // The height of the container is limited by the shorter line.
                int h = min(height[i], height[j]);
                // Calculate the area for the current pair of lines.
                int area = w * h;
                // Update the maximum water capacity if the current area is larger.
                maxWater = max(maxWater, area);
            }
        }

        return maxWater; // Return the maximum area found.
    }
};

/*
*
* Dry Run
* Input: height = [1, 8, 6]
*
* Initial state:
* maxWater = 0
* n = 3
*
* i = 0:
* j = 1:
* w = 1 - 0 = 1
* h = min(height[0], height[1]) = min(1, 8) = 1
* area = 1 * 1 = 1
* maxWater = max(0, 1) = 1
* j = 2:
* w = 2 - 0 = 2
* h = min(height[0], height[2]) = min(1, 6) = 1
* area = 2 * 1 = 2
* maxWater = max(1, 2) = 2
*
* i = 1:
* j = 2:
* w = 2 - 1 = 1
* h = min(height[1], height[2]) = min(8, 6) = 6
* area = 1 * 6 = 6
* maxWater = max(2, 6) = 6
*
* Loops end.
* Return maxWater = 6
*/
```

### Optimized Two-Pointer Solution (C++)

```cpp
// Intuition:
// The maximum area is a balance between width and height. Starting with the maximum possible width
// (the two ends of the array) allows us to systematically narrow down the search. To have a chance of
// finding a larger area with a smaller width, we must find a greater height. The current height is
// limited by the shorter of the two lines. Thus, it's always optimal to move the pointer of the
// shorter line inward, as this is the only way to potentially increase the height of the container.

// Approach:
// 1. Initialize two pointers, `i` at the start (index 0) and `j` at the end (index n-1).
// 2. Initialize `maxWater` to 0.
// 3. Loop while `i` is less than `j`.
// 4. Calculate the width `w = j - i`.
// 5. Calculate the height `h = min(height[i], height[j])`.
// 6. Calculate the current area `area = w * h`.
// 7. Update `maxWater = max(maxWater, area)`.
// 8. Move the pointer that points to the shorter line inward.
//    - If `height[i] < height[j]`, increment `i`.
//    - Otherwise, decrement `j`.
// 9. When the loop finishes (i >= j), return `maxWater`.

// Time Complexity: O(n), because each pointer (i and j) traverses the array at most once.
// Space Complexity: O(1), because we only use a constant amount of extra space for pointers and variables.
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size(); // Get the number of vertical lines.

        int i = 0;       // Left pointer, starting at the beginning.
        int j = n - 1;   // Right pointer, starting at the end.

        int maxWater = 0; // Variable to store the maximum water found so far.

        // Loop until the two pointers meet.
        while(i < j) {
            int w = j - i; // Calculate the width between the pointers.
            int h = min(height[i], height[j]); // Height is limited by the shorter line.
            int area = w * h; // Calculate the current area.
            maxWater = max(maxWater, area); // Update maxWater if current area is greater.

            // Greedily move the pointer of the shorter line inward
            // to have a chance of finding a taller line.
            if(height[i] > height[j]) {
                j--;
            } else {
                i++;
            }
        }

        return maxWater; // Return the maximum water capacity found.
    }
};

/*
*
* Dry Run
* Input: height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
*
* Initial state:
* i = 0, j = 8
* maxWater = 0
*
* Loop 1:
* i = 0, j = 8 -> height[i]=1, height[j]=7
* w = 8 - 0 = 8
* h = min(1, 7) = 1
* area = 8 * 1 = 8
* maxWater = 8
* height[i] < height[j] (1 < 7) -> i++
*
* Loop 2:
* i = 1, j = 8 -> height[i]=8, height[j]=7
* w = 8 - 1 = 7
* h = min(8, 7) = 7
* area = 7 * 7 = 49
* maxWater = 49
* height[i] > height[j] (8 > 7) -> j--
*
* Loop 3:
* i = 1, j = 7 -> height[i]=8, height[j]=3
* w = 7 - 1 = 6
* h = min(8, 3) = 3
* area = 6 * 3 = 18
* maxWater remains 49
* height[i] > height[j] (8 > 3) -> j--
*
* Loop 4:
* i = 1, j = 6 -> height[i]=8, height[j]=8
* w = 6 - 1 = 5
* h = min(8, 8) = 8
* area = 5 * 8 = 40
* maxWater remains 49
* height[i] == height[j], so else block executes -> i++
*
* ... The process continues until i >= j ...
*
* Final Result:
* Return maxWater = 49
*
*/
```

---

## ✨ Key Insights

- The limiting factor for the water capacity is always the **shorter of the two vertical lines**.
- The greedy strategy of moving the shorter line's pointer is optimal. By moving the shorter line, we trade a decrease in width for a potential increase in height. Moving the taller line's pointer would decrease the width without any chance of increasing the height, thus guaranteeing a smaller area.
- This problem beautifully demonstrates how a greedy two-pointer approach can reduce a quadratic complexity problem ($O(n^2)$) to a linear one ($O(n)$) by making an informed, optimal choice at each step.

---

## 🚀 Further Exploration

- What if you were allowed to use one additional vertical line from a different array of heights? How would you find the optimal placement?
- Consider a 3D version of this problem where you are given a grid of heights. How would you find the container with the most water volume?
- Can you prove mathematically why the two-pointer greedy approach is guaranteed to find the optimal solution?

---

## 🔗 References

- [LeetCode Problem Page](https://leetcode.com/problems/container-with-most-water/)
- [Two Pointers Technique - GeeksforGeeks](https://www.geeksforgeeks.org/two-pointers-technique/)

---

## 🏷️ Tags

`Array`, `Two Pointers`, `Greedy`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/container-with-most-water/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
