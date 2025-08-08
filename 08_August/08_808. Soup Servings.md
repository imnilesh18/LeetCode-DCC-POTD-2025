# 🥣 808. Soup Servings

![LeetCode](https://img.shields.io/badge/LeetCode-000000?style=for-the-badge&logo=LeetCode&logoColor=yellow)
![Difficulty](https://img.shields.io/badge/Medium-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

> ⚡️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [LeetCode problem](https://leetcode.com/problems/soup-servings/).

---

## 📝 Problem Statement

You have two soups, A and B, each starting with **n** mL. On every turn, one of the following four serving operations is chosen at random, each with probability **0.25** independent of all previous turns:

1.  pour 100 mL from type A and 0 mL from type B
2.  pour 75 mL from type A and 25 mL from type B
3.  pour 50 mL from type A and 50 mL from type B
4.  pour 25 mL from type A and 75 mL from type B

**Notes:**

- There is no operation that pours 0 mL from A and 100 mL from B.
- The amounts from A and B are poured simultaneously during the turn.
- If an operation asks you to pour more than you have left of a soup, pour all that remains of that soup.
- The process stops immediately after any turn in which one of the soups is used up.

Return the probability that **A is used up before B**, plus **half the probability that both soups are used up in the same turn**. Answers within `10^-5` of the actual answer will be accepted.

---

## 🧪 Examples

| Input     | Output    |
| :-------- | :-------- |
| `n = 50`  | `0.62500` |
| `n = 100` | `0.71875` |

<details>
<summary><strong>Example 1 Walkthrough (n=50)</strong></summary>

- **Initial State:** A = 50, B = 50. Each operation has a 0.25 probability.

1.  **Operation 1 (Serve 100 A, 0 B):** We only have 50 A. We serve all 50 A. A becomes 0. A finishes first. Probability contribution: **1.0**.
2.  **Operation 2 (Serve 75 A, 25 B):** We only have 50 A. We serve all 50 A. A becomes 0. A finishes first. Probability contribution: **1.0**.
3.  **Operation 3 (Serve 50 A, 50 B):** We serve 50 A and 50 B. Both become 0. They finish at the same time. Probability contribution: **0.5**.
4.  **Operation 4 (Serve 25 A, 75 B):** We serve 25 A (A becomes 25). We only have 50 B, so we serve all 50 B (B becomes 0). B finishes first. Probability contribution: **0.0**.

- **Total Probability:** `0.25 * (1.0 + 1.0 + 0.5 + 0.0) = 0.25 * 2.5 = 0.625`

</details>

---

## 🚨 Constraints

- `0 <= n <= 10^9`

---

## 🛠️ Approach

The problem can be modeled as a dynamic programming problem or a recursive problem with memoization. We need to find the probability of certain outcomes, which suggests a recursive structure where each state is defined by the remaining amounts of soup A and soup B.

Let `solve(A, B)` be the function that returns the desired probability given `A` mL of soup A and `B` mL of soup B.

1.  **Base Cases:**

    - If `A <= 0` and `B <= 0`: Both are empty. Return `0.5`.
    - If `A <= 0`: A is empty first. Return `1.0`.
    - If `B <= 0`: B is empty first. This is not a desired outcome. Return `0.0`.

2.  **Recursive Step:** From state `(A, B)`, we can transition to four new states based on the four operations. Since each operation has a `0.25` probability, the total probability is the sum of the probabilities from each path, weighted by `0.25`.
    `P(A, B) = 0.25 * [solve(A-100, B-0) + solve(A-75, B-25) + solve(A-50, B-50) + solve(A-25, B-75)]`

3.  **Memoization:** The state is defined by `(A, B)`. We can use a 2D array `memo[A][B]` to store the results of subproblems to avoid re-computation, which is key to passing the time limits.

4.  **Large `n` Optimization:** The constraint `n <= 10^9` makes a direct DP table impossible. However, we can observe that as `n` gets large, the amount served from soup A is generally more than from soup B (average serve A = (100+75+50+25)/4 = 62.5; average serve B = (0+25+50+75)/4 = 37.5). This means soup A is almost certain to finish first for very large `n`. The probability quickly converges to 1. By testing, a threshold like `n >= 5000` is sufficient to return `1.0` directly, which handles the large constraints.

---

## 💻 Solution Code

### C++

```cpp
// Intuition:
// The problem asks for the probability of soup A finishing before soup B, plus half the probability of them finishing at the same time. This can be modeled using recursion, where each state is defined by the remaining amounts of soup A and B. There are four possible serving operations, each with an equal probability of 0.25. We can explore these four operations recursively from the current state (A, B) to calculate the total probability. Memoization is used to store the results for previously computed states (A, B) to avoid redundant calculations. A key observation is that for large 'n', the probability of soup A finishing first approaches 1 because the serving amounts for A are generally larger than for B. This allows us to use a threshold for 'n' to return 1.0 directly, preventing deep recursion and memory issues.

// Approach:
// 1. Define a recursive function, say `solve(A, B)`, which computes the probability for the given amounts of soup A and B.
// 2. Base Cases:
//    - If both A and B are less than or equal to 0, it means they finished at the same time. Return 0.5 as per the problem statement.
//    - If only A is less than or equal to 0, it means A finished first. Return 1.0.
//    - If only B is less than or equal to 0, it means B finished first. Return 0.0, as we are not interested in this outcome.
// 3. Memoization: Use a 2D array `t[A][B]` to store the result of `solve(A, B)`. If the value is already computed, return it directly.
// 4. Recursive Step:
//    - For the current state (A, B), recursively call `solve` for each of the four serving operations:
//      - `solve(A-100, B-0)`
//      - `solve(A-75, B-25)`
//      - `solve(A-50, B-50)`
//      - `solve(A-25, B-75)`
//    - Since each operation has a 0.25 probability, sum their results and multiply by 0.25.
//      `probability = 0.25 * (solve(...) + solve(...) + solve(...) + solve(...))`
// 5. Main Function (`soupServings`):
//    - Handle the large 'n' case: If `n` is large (e.g., >= 5000), the probability gets very close to 1. Return 1.0 directly to pass constraints.
//    - Initialize the memoization table `t`.
//    - Start the recursion with `solve(n, n)`.

// Time Complexity: O(N*N), where N is the threshold (e.g., 5000). We are calculating the results for approximately N*N states, and each calculation is O(1) because we make four fixed recursive calls.
// Space Complexity: O(N*N), for the memoization table `t` of size N x N.

class Solution {
public:
    // Stores the four possible serving operations: {serve_A, serve_B}
    vector<pair<int, int>> serves{{100, 0}, {75, 25}, {50, 50}, {25, 75}};

    // Memoization table to store results of subproblems to avoid re-computation.
    vector<vector<double>> t;

    // Recursive function to calculate the probability.
    double solve(double A, double B) {
        // Base case: If both soups run out at the same time.
        if(A <= 0 && B <= 0)
            return 0.5; // Return half the probability as per the problem.

        // Base case: If soup A runs out first.
        if(A <= 0)
            return 1.0; // This is a successful outcome.

        // Base case: If soup B runs out first.
        if(B <= 0)
            return 0.0; // This is an unsuccessful outcome.

        // If the result for this state (A, B) is already computed, return it.
        if(t[A][B] != -1.0)
            return t[A][B];

        // Variable to accumulate probability from the four possible recursive paths.
        double probability = 0.0;

        // Iterate through each of the four serving operations.
        for(auto &p : serves) {

            // Get the amount of soup A and B to be served in this operation.
            double A_serve  = p.first;
            double B_serve  = p.second;

            // Recursively call for the next state and add its contribution to the total probability.
            // Each path has a 0.25 probability.
            probability += 0.25 * solve(A - A_serve, B - B_serve);
        }

        // Store the computed probability in the memoization table and return it.
        return t[A][B] = probability;
    }

    double soupServings(int n) {

        // For large n, the probability of A finishing first approaches 1.
        // This is because we serve more from A on average.
        // This check avoids TLE and Memory Limit Exceeded for large n.
        if(n >= 5000)
            return 1.0;

        // Initialize the memoization table with -1.0 to indicate states are not yet computed.
        t.resize(n + 1, vector<double>(n + 1, -1.0));

        // Start the recursion with initial amounts n for both soups.
        return solve(n, n);
    }
};

/*
*
* Dry Run (Example: n = 50)
*
* 1. `soupServings(50)` is called. `n < 5000`, so we proceed.
* 2. The memoization table `t` of size 51x51 is created.
* 3. `solve(50, 50)` is called. This state is not in `t`.
* 4. The function explores four recursive paths, each weighted by 0.25:
*
* a. `solve(50 - 100, 50 - 0)` -> `solve(-50, 50)`
* - In `solve(-50, 50)`, `A <= 0`. It hits a base case and returns 1.0.
*
* b. `solve(50 - 75, 50 - 25)` -> `solve(-25, 25)`
* - In `solve(-25, 25)`, `A <= 0`. It hits a base case and returns 1.0.
*
* c. `solve(50 - 50, 50 - 50)` -> `solve(0, 0)`
* - In `solve(0, 0)`, `A <= 0` and `B <= 0`. It hits a base case and returns 0.5.
*
* d. `solve(50 - 25, 50 - 75)` -> `solve(25, -25)`
* - In `solve(25, -25)`, `B <= 0`. It hits a base case and returns 0.0.
*
* 5. The total probability for `solve(50, 50)` is calculated:
* `probability = 0.25 * (1.0 (from a) + 1.0 (from b) + 0.5 (from c) + 0.0 (from d))`
* `probability = 0.25 * (2.5)`
* `probability = 0.625`
*
* 6. The result 0.625 is stored in `t[50][50]` and returned.
* 7. `soupServings(50)` returns 0.625, which matches the example output.
*
*/
```

---

## 💡 Key Insights

- **Probability as Recursion:** Problems asking for probability can often be broken down into smaller subproblems. The total probability is the sum of probabilities of different outcomes, each weighted by its chance of occurring.
- **The `n >= 5000` Trick:** This is a crucial observation. Without it, the `O(N^2)` space and time complexity would be too high for `n = 10^9`. Because soup A is served more aggressively on average, its probability of finishing first approaches 1 very quickly. The threshold `~5000` is found experimentally to be a point where the result is so close to 1 that it's within the acceptable error margin `10^-5`.
- **State Reduction:** A further optimization (not implemented here but common) is to notice all serving sizes are multiples of 25. One could divide `n` by 25 and work with smaller state values, reducing the size of the memoization table (e.g., `n=4800` becomes `192`).

---

## 🚀 Further Exploration

If you enjoyed this problem, consider exploring other probability-based Dynamic Programming questions on LeetCode:

- [688. Knight Probability in Chessboard](https://leetcode.com/problems/knight-probability-in-chessboard/)
- [576. Out of Boundary Paths](https://leetcode.com/problems/out-of-boundary-paths/)
- [New 21 Game](https://leetcode.com/problems/new-21-game/)

---

## 📚 References

- [Original LeetCode Problem](https://leetcode.com/problems/soup-servings/)
- [Discussion on Large `n` Optimization](https://leetcode.com/problems/soup-servings/solutions/121711/c-java-python-easy-and-concise-solution/)

---

## 👨‍💻 Author

- Connect with me on GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Tag](https://img.shields.io/badge/Dynamic%20Programming-4a90e2?style=for-the-badge)
![Tag](https://img.shields.io/badge/Math-b854d4?style=for-the-badge)
![Tag](https://img.shields.io/badge/Probability%20and%20Statistics-f5a623?style=for-the-badge)
![Tag](https://img.shields.io/badge/Memoization-c51162?style=for-the-badge)

---

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

**A gentle reminder that this is for educational purposes. Always try to solve problems on your own first!**
