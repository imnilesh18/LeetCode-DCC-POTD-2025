# ✨ 2221. Find Triangular Sum of an Array

<div align="center">
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow" alt="Difficulty: Medium" />
    <a href="https://leetcode.com/problems/find-triangular-sum-of-an-array/">
        <img src="https://img.shields.io/badge/Link%20to%20Problem-blue" alt="Link to Problem" />
    </a>
</div>

<br>

<div align="center">
    <img src="https://assets.leetcode.com/uploads/2022/02/22/ex1drawio.png" alt="Problem visualization" width="400px" style="border-radius:10px;">
</div>

---

## 📝 Problem Statement

You are given a **0-indexed** integer array `nums`, where `nums[i]` is a digit between `0` and `9` (inclusive).

The **triangular sum** of `nums` is the value of the only element present in `nums` after the following process terminates:

1.  Let `nums` comprise `n` elements. If `n == 1`, **end** the process. Otherwise, **create** a new **0-indexed** integer array `newNums` of length `n - 1`.
2.  For each index `i`, where `0 <= i < n - 1`, **assign** the value of `newNums[i]` as `(nums[i] + nums[i+1]) % 10`.
3.  **Replace** the array `nums` with `newNums`.
4.  **Repeat** the entire process starting from step 1.

Return the triangular sum of `nums`.

---

## ⚙️ Constraints

- `1 <= nums.length <= 1000`
- `0 <= nums[i] <= 9`

---

## 📊 Examples

<details>
<summary>View Examples</summary>
<br>

| Input                | Output | Explanation                                                                                                      |
| -------------------- | ------ | ---------------------------------------------------------------------------------------------------------------- |
| `nums = [1,2,3,4,5]` | `8`    | The process is depicted in the image above. The final single element is 8.                                       |
| `nums = [5]`         | `5`    | The array already has only one element, so the process terminates, and the triangular sum is the element itself. |

</details>

---

## 🧠 Approach

The problem asks us to repeatedly transform an array until only one element remains. This process involves creating a new array where each element is the sum (modulo 10) of two adjacent elements from the previous array. This suggests a simulation-based approach.

We can visualize this as layers of a triangle, where each layer is smaller than the one above it. The most direct method is to simulate this process step-by-step:

1.  Start with the initial array.
2.  As long as the array has more than one element, create a new temporary array.
3.  Populate the temporary array by calculating `(nums[i] + nums[i+1]) % 10` for each `i`.
4.  Replace the original array with this new, smaller array.
5.  Repeat until the array size becomes 1.

A more space-efficient approach avoids creating a new array in each step. We can perform the updates **in-place**. Since the new value at `nums[i]` depends only on the original `nums[i]` and `nums[i+1]`, we can overwrite `nums[i]` with its new value. In each pass, we effectively reduce the "active" size of the array by one, until only the first element contains the final result.

---

## 💻 Solution Code

### ▶️ Brute-force Solution (Extra Space)

This solution follows the problem description exactly by creating a new temporary vector in each iteration.

```cpp
// Intuition:
// The problem can be solved by directly simulating the process described. We can repeatedly generate
// a new, smaller array from the current one until only a single element remains. This new array's
// elements are the sum modulo 10 of adjacent elements from the previous array.

// Approach:
// 1. Use a `while` loop that continues as long as the array size is greater than 1.
// 2. Inside the loop, create a temporary vector `temp` to store the results of the current step.
// 3. Iterate through the `nums` array from the first element to the second-to-last element.
// 4. For each pair of adjacent elements `nums[i]` and `nums[i+1]`, calculate their sum modulo 10 and push it into `temp`.
// 5. After the loop, the `temp` vector will be one element shorter than `nums`.
// 6. Replace `nums` with `temp` for the next iteration. `std::move` is used for an efficient transfer, avoiding a full copy.
// 7. When the loop terminates (`nums.size()` is 1), the only element `nums[0]` is the triangular sum.

// Time Complexity: O(n^2)
// The outer while loop runs `n-1` times. The inner for loop runs `n-1`, `n-2`, ..., `1` times.
// The total number of operations is proportional to the sum of an arithmetic series, which is O(n^2).

// Space Complexity: O(n)
// In each iteration, a new temporary vector is created. The largest temporary vector has a size of `n-1`.
// Thus, the auxiliary space complexity is linear with respect to the input size.

class Solution {
public:
    int triangularSum(vector<int>& nums) {
        // Continue the process until only one element remains in the array.
        while(nums.size() > 1) {
            // Create a temporary vector to store the new row of the triangle.
            vector<int> temp;

            // Iterate through adjacent elements of the current array.
            for(int i = 0; i < nums.size() - 1; i++) {
                // Calculate the sum modulo 10 and add it to the new vector.
                temp.push_back((nums[i] + nums[i + 1]) % 10);
            }

            // Replace the original array with the new one using std::move for efficiency.
            nums = move(temp);
        }
        // The final remaining element is the triangular sum.
        return nums[0];
    }
};

/*
*
* Dry Run
*
* Input: nums = [1, 2, 3, 4, 5]
*
* Iteration 1 (nums.size() = 5 > 1):
* temp = []
* i = 0: temp.push_back((1 + 2) % 10) -> temp = [3]
* i = 1: temp.push_back((2 + 3) % 10) -> temp = [3, 5]
* i = 2: temp.push_back((3 + 4) % 10) -> temp = [3, 5, 7]
* i = 3: temp.push_back((4 + 5) % 10) -> temp = [3, 5, 7, 9]
* nums becomes [3, 5, 7, 9]
*
* Iteration 2 (nums.size() = 4 > 1):
* temp = []
* i = 0: temp.push_back((3 + 5) % 10) -> temp = [8]
* i = 1: temp.push_back((5 + 7) % 10) -> temp = [8, 2]
* i = 2: temp.push_back((7 + 9) % 10) -> temp = [8, 2, 6]
* nums becomes [8, 2, 6]
*
* Iteration 3 (nums.size() = 3 > 1):
* temp = []
* i = 0: temp.push_back((8 + 2) % 10) -> temp = [0]
* i = 1: temp.push_back((2 + 6) % 10) -> temp = [0, 8]
* nums becomes [0, 8]
*
* Iteration 4 (nums.size() = 2 > 1):
* temp = []
* i = 0: temp.push_back((0 + 8) % 10) -> temp = [8]
* nums becomes [8]
*
* Loop terminates as nums.size() is now 1.
* Return nums[0], which is 8.
*
*/
```

### ▶️ Optimized Solution (In-place)

This solution modifies the input array directly, achieving $O(1)$ space complexity.

```cpp
// Intuition:
// Instead of creating a new array at each step, we can perform the updates in-place. The value at
// `nums[i]` for the next iteration depends only on `nums[i]` and `nums[i+1]` from the current
// iteration. We can overwrite `nums[i]` with the new value, effectively shrinking the conceptual
// size of the array by one in each pass.

// Approach:
// 1. Get the initial size `n` of the array.
// 2. Use an outer loop that simulates the shrinking size of the array. It runs from `size = n-1` down to `1`.
//    This `size` variable represents the number of elements in the current conceptual array.
// 3. The inner loop iterates from `i = 0` to `size - 1` (or `i < size`).
// 4. In the inner loop, update `nums[i]` directly with the new value: `(nums[i] + nums[i+1]) % 10`.
// 5. After each pass of the outer loop, the first `size` elements of `nums` are updated, and the array
//    is conceptually one element shorter.
// 6. When the loops complete, `nums[0]` will hold the final triangular sum.

// Time Complexity: O(n^2)
// The nested loop structure leads to a quadratic time complexity, similar to the brute-force approach.
// The outer loop runs `n-1` times, and the inner loop's iterations decrease from `n-1` to `1`.

// Space Complexity: O(1)
// The array is modified in-place. No extra space proportional to the input size is used.

class Solution {
public:
    int triangularSum(vector<int>& nums) {
        int n = nums.size();
        // The outer loop reduces the effective size of the array in each iteration.
        for(int size = n - 1; size >= 1; size--) {
            // The inner loop computes the new values for the current row.
            for(int i = 0; i < size; i++) {
                // Update the current element with the sum of itself and the next element, modulo 10.
                nums[i] = (nums[i] + nums[i + 1]) % 10;
            }
        }
        // The final result is stored in the first element of the array.
        return nums[0];
    }
};

/*
*
* Dry Run
*
* Input: nums = [1, 2, 3, 4, 5], n = 5
*
* Outer loop (size = 4):
* i = 0: nums[0] = (nums[0] + nums[1]) % 10 = (1 + 2) % 10 = 3.  nums is now [3, 2, 3, 4, 5]
* i = 1: nums[1] = (nums[1] + nums[2]) % 10 = (2 + 3) % 10 = 5.  nums is now [3, 5, 3, 4, 5]
* i = 2: nums[2] = (nums[2] + nums[3]) % 10 = (3 + 4) % 10 = 7.  nums is now [3, 5, 7, 4, 5]
* i = 3: nums[3] = (nums[3] + nums[4]) % 10 = (4 + 5) % 10 = 9.  nums is now [3, 5, 7, 9, 5]
*
* Outer loop (size = 3):
* i = 0: nums[0] = (nums[0] + nums[1]) % 10 = (3 + 5) % 10 = 8.  nums is now [8, 5, 7, 9, 5]
* i = 1: nums[1] = (nums[1] + nums[2]) % 10 = (5 + 7) % 10 = 2.  nums is now [8, 2, 7, 9, 5]
* i = 2: nums[2] = (nums[2] + nums[3]) % 10 = (7 + 9) % 10 = 6.  nums is now [8, 2, 6, 9, 5]
*
* Outer loop (size = 2):
* i = 0: nums[0] = (nums[0] + nums[1]) % 10 = (8 + 2) % 10 = 0.  nums is now [0, 2, 6, 9, 5]
* i = 1: nums[1] = (nums[1] + nums[2]) % 10 = (2 + 6) % 10 = 8.  nums is now [0, 8, 6, 9, 5]
*
* Outer loop (size = 1):
* i = 0: nums[0] = (nums[0] + nums[1]) % 10 = (0 + 8) % 10 = 8.  nums is now [8, 8, 6, 9, 5]
*
* Outer loop finishes.
* Return nums[0], which is 8.
*
*/
```

---

## 🔑 Key Insights

The process described is related to **Pascal's Triangle**. The final sum is a linear combination of the initial array elements, where the coefficients are binomial coefficients modulo 10. Specifically, the triangular sum is:

$$ \text{sum} = \sum\_{i=0}^{n-1} \left( \binom{n-1}{i} \times \text{nums}[i] \right) \pmod{10} $$

where `n` is the length of the initial array. While the simulation approach ($O(N^2)$) is sufficient given the constraints, this combinatorial approach could solve the problem in $O(N)$ if we could compute the binomial coefficients efficiently. However, calculating these for each term can be complex, making the simulation approach more practical for typical contest scenarios.

## 🚀 Further Exploration

- Implement the solution using the combinatorial formula with binomial coefficients. This requires pre-computing factorials and their modular inverses or using properties of Pascal's triangle.
- Consider the problem constraints. What if `nums.length` was much larger, e.g., $10^5$? The $O(N^2)$ solution would be too slow, and the $O(N)$ combinatorial approach would be necessary.

---

## 📚 References

- [Pascal's Triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle)
- [Binomial Coefficient](https://en.wikipedia.org/wiki/Binomial_coefficient)
- [Modular Arithmetic](https://en.wikipedia.org/wiki/Modular_arithmetic)

---

## 🏷️ Tags

`Array` `Simulation` `Math` `Combinatorics`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/find-triangular-sum-of-an-array/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
