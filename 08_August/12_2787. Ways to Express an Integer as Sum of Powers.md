<h1 align="center">
  <strong>✨ 2787. Ways to Express an Integer as Sum of Powers ✨</strong>
</h1>

<p align="center">
  A stylish, educational, and in-depth guide to solving LeetCode's "Ways to Express an Integer as Sum of Powers" problem.
</p>

<p align="center">
  <a href="https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/description/" target="_blank">
    <img src="https://img.shields.io/badge/Problem%20Link-LeetCode-blue?style=for-the-badge&logo=leetcode" alt="Problem Link"/>
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Language-C%2B%2B-purple?style=for-the-badge&logo=cplusplus" alt="Language: C++" />
  <img src="https://img.shields.io/badge/Pattern-0/1%20Knapsack-orange?style=for-the-badge" alt="Pattern: 0/1 Knapsack" />
</p>

---

## 🎯 **Problem Statement**

Given two **positive** integers, `n` and `x`, your task is to determine the number of distinct ways `n` can be expressed as the sum of the `x`-th power of **unique** positive integers.

In other words, you need to find the number of unique sets of integers `[n₁, n₂, ..., nₖ]` such that:
`n = n₁ˣ + n₂ˣ + ... + nₖˣ`

Since the result can be very large, it must be returned modulo `10⁹ + 7`.

---

### 📋 **Constraints**

- `1 <= n <= 300`
- `1 <= x <= 5`

---

### 💡 **Examples**

Here are a couple of examples to clarify the goal:

| Input           | Output | Explanation                                        |
| :-------------- | :----- | :------------------------------------------------- |
| `n = 10, x = 2` | `1`    | The only way is `10 = 3² + 1²` (since 9 + 1 = 10). |
| `n = 4, x = 1`  | `2`    | Two ways exist: `4 = 4¹` and `4 = 3¹ + 1¹`.        |

---

## 🧠 **Approach & Logic: Top-Down DP (Memoization)**

This problem can be elegantly solved using recursion with memoization, a classic dynamic programming technique. The core idea is to model it as a **0/1 Knapsack** problem. For each integer starting from 1, we have two choices: either include its `x`-th power in our sum or skip it.

<details>
<summary><strong>🔍 Click to see the Step-by-Step Walkthrough</strong></summary>

1.  **Recursive State**: We define a function, `solve(target, num)`, which represents the number of ways to achieve the `target` sum using powers of unique integers starting from `num`.

2.  **The "Take" or "Skip" Decision**: For the current number `num`, we face a choice:

    - **Take**: Include `numˣ` in the sum. The new target becomes `target - numˣ`, and we proceed to the next unique integer, `num + 1`.
    - **Skip**: Exclude `numˣ`. The target remains unchanged, and we move on to `num + 1`.

3.  **Base Cases (Termination Conditions)**:

    - If `target == 0`, we have successfully formed the sum. This path is a valid solution, so we return `1`.
    - If `target < 0` or `numˣ > target`, the current path is invalid because we've either overshot the target or the current number's power is too large. We backtrack by returning `0`.

4.  **Combining Results**: The total number of ways is the sum of possibilities from both choices: `ways = (ways_from_take) + (ways_from_skip)`.

5.  **Memoization**: A pure recursive solution would be too slow due to re-computing the same subproblems. We optimize this by using a 2D DP table, `dp[target][num]`, to cache the results. Before any computation, we check if `dp[target][num]` has been solved. If yes, we return the cached value; otherwise, we compute, store, and then return the result.

This DP approach reduces the time complexity from exponential to polynomial, making it efficient enough to pass all test cases.

</details>

---

## 🔐 **Solution Code**

### **Method 1: Brute-Force Recursion**

This initial approach directly translates the "take/skip" logic into a recursive function. While conceptually simple, its exponential nature makes it too slow for the given constraints.

```cpp
// Intuition:
// The problem structure naturally lends itself to a decision tree. For each number, we decide to either use its power or not, leading to a recursive solution.
// Approach:
// A function `solve(n, num)` explores the choices. It returns 1 for a valid path (n=0), 0 for an invalid one (n<0 or num^x > n). It recursively sums the results of taking `num^x` and skipping it.
// Time Complexity: O(2^n) - Exponential, as each call can lead to two more.
// Space Complexity: O(n) - Due to the depth of the recursion stack.
class Solution {
public:
    int M = 1e9 + 7;

    int solve(int n, int num, int x) {
        if (n == 0) return 1;
        if (n < 0) return 0;

        long long currPowerValue = pow(num, x);
        if (currPowerValue > n) {
            return 0;
        }

        long long take = solve(n - currPowerValue, num + 1, x);
        long long skip = solve(n, num + 1, x);

        return (take + skip) % M;
    }

    int numberOfWays(int n, int x) {
        return solve(n, 1, x);
    }
};

/*
*
* Dry Run (n=10, x=2):
* solve(10, 1) explores two main branches:
* 1. Take 1^2 -> solve(9, 2)
* - Take 2^2 -> solve(5, 3) -> invalid (3^2 > 5), returns 0.
* - Skip 2^2 -> solve(9, 3)
* - Take 3^2 -> solve(0, 4) -> valid, returns 1.
* - Skip 3^2 -> solve(9, 4) -> invalid (4^2 > 9), returns 0.
* -> Total from solve(9, 3) is 1.
* -> Total from solve(9, 2) is 1.
* 2. Skip 1^2 -> solve(10, 2) -> eventually leads to 0.
* Total = 1 + 0 = 1.
*/
```

### **Method 2: Optimized with Memoization (Top-Down DP)**

The efficient solution uses a 2D array to cache results, avoiding redundant calculations and drastically improving performance.

```cpp
// Intuition:
// The brute-force recursion is slow because it re-solves identical subproblems. Caching these results (memoization) will make it much faster.
// Approach:
// A 2D array `t[n][num]` stores the result for `solve(n, num)`. Before computing, check if `t[n][num]` exists. If so, return it. Otherwise, compute using the take/skip logic, store the result in the table, and then return.
// Time Complexity: O(n * n) - Each state (n, num) is computed only once.
// Space Complexity: O(n * n) - For the memoization table.
class Solution {
public:
    // Modulo constant for large results
    int M = 1e9+7;
    // Memoization table: t[n][num]
    int t[301][301];

    int solve(int n, int num, int x) {
        // Base case: A valid combination is found
        if(n == 0)
            return 1;

        // Base case: Invalid path (sum exceeded or no more numbers to try)
        if(n < 0)
            return 0;

        // Calculate the power of the current number
        int currPowerValue = pow(num, x);
        // Pruning: If power is greater than remaining n, this path is invalid
        if(currPowerValue > n) {
            return 0;
        }

        // If this subproblem is already solved, return the cached result
        if(t[n][num] != -1) {
            return t[n][num];
        }

        // Recursive "take" choice: use current power, move to next number
        int take = solve(n-currPowerValue, num+1, x);
        // Recursive "skip" choice: ignore current power, move to next number
        int skip = solve(n, num+1, x);

        // Cache and return the total ways from both choices (modulo M)
        return t[n][num] = (take+skip)%M;
    }

    int numberOfWays(int n, int x) {
        // Initialize memoization table with -1 (uncomputed)
        memset(t, -1, sizeof(t));
        // Start the process from the initial state
        return solve(n, 1, x);
    }
};

/*
*
* Dry Run (n=10, x=2) with Memoization
*
* solve(10, 1): t[10][1] = -1. Compute...
* take -> solve(9, 2)
* solve(9, 2): t[9][2] = -1. Compute...
* take -> solve(5, 3) -> returns 0.
* skip -> solve(9, 3)
* solve(9, 3): t[9][3] = -1. Compute...
* take -> solve(0, 4) -> returns 1.
* skip -> solve(9, 4) -> returns 0.
* t[9][3] = 1. Return 1.
* t[9][2] = 0 + 1 = 1. Return 1.
* skip -> solve(10, 2)
* solve(10, 2): computes and stores t[10][2] = 0.
* t[10][1] = 1 + 0 = 1. Return 1.
* Later calls to solve(9, 2) or solve(10, 2) would instantly return from the cache.
*
*/
```

---

## ✨ **Key Insights & Further Learning**

- **DP Pattern Recognition**: Identifying this as a **0/1 Knapsack** variant is key. The items are the powers, the weights are their values, and the capacity is `n`. The goal is to find combinations that perfectly fill the knapsack.
- **State Definition**: The DP state `(target, num)` is crucial. It fully captures the subproblem, allowing for independent computation.
- **Optimization Path**: Consider how you might implement this iteratively (**Bottom-Up DP**) to remove recursion overhead. Could the space complexity be further optimized to `O(n)`?

---

## 📄 **License**

This repository is released under the [MIT License](./LICENSE).

> **Disclaimer:** This content is for educational purposes. The original problem statement and copyright belong to LeetCode. Please refer to the [official problem page](https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/description/) for more details.

---

## 👨‍💻 **Author**

- [imnilesh18](https://github.com/imnilesh18)

---
