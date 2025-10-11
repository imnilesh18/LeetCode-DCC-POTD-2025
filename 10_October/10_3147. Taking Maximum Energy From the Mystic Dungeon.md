# ✨ 3147. Taking Maximum Energy From the Mystic Dungeon

<div align="center">
  
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg)](https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description/)
[![Tags](https://img.shields.io/badge/Tags-Array-blue.svg)](https://leetcode.com/tag/array/)
[![Tags](https://img.shields.io/badge/Tags-Dynamic%20Programming-orange.svg)](https://leetcode.com/tag/dynamic-programming/)

</div>

---

## 📝 Problem Statement

In a mystic dungeon, `n` magicians are standing in a line. Each magician has an attribute that gives you energy. Some magicians can give you negative energy, which means taking energy from you.

You have been cursed in such a way that after absorbing energy from magician `i`, you will be instantly transported to magician `(i + k)`. This process will be repeated until you reach a magician where `(i + k)` does not exist.

In other words, you will choose a starting point and then teleport with `k` jumps until you reach the end of the magicians' sequence, absorbing all the energy during the journey.

You are given an array `energy` and an integer `k`. Return the **maximum** possible energy you can gain.

---

## 🛑 Constraints

- `1 <= energy.length <= 10^5`
- `-1000 <= energy[i] <= 1000`
- `1 <= k <= energy.length - 1`

---

## 🧪 Examples

<details>
<summary><strong>Example 1</strong></summary>

| Input | Output | Explanation |
|---|---|---|
| `energy = [5,2,-10,-5,1], k = 3` | `3` | We can gain a total energy of 3 by starting from magician 1, absorbing `2 + 1 = 3`. |

</details>

<details>
<summary><strong>Example 2</strong></summary>

| Input | Output | Explanation |
|---|---|---|
| `energy = [-2,-3,-1], k = 2` | `-1` | We can gain a total energy of -1 by starting from magician 2. |

</details>

---

## 💡 Approach

The problem asks for the maximum energy we can collect by starting at any magician and repeatedly jumping `k` steps forward. Since we can start from any index, we need to explore all possible starting points and find the one that yields the highest total energy.

### 🤔 Thought Process

1.  **Identify the Core Task**: For any given starting index `i`, the path is fixed: `i`, `i + k`, `i + 2k`, `i + 3k`, ... until the index goes out of bounds. The total energy for this path is the sum of `energy[j]` for all `j` in this sequence.

2.  **Brute-Force Idea (Recursion)**: We have the option to start from any index. This suggests trying all possibilities.
    -   We can write a function, say `solve(i)`, that calculates the total energy if we continue the journey *from* index `i`.
    -   `solve(i)` would be `energy[i] + solve(i + k)`. The base case is when `i` is out of bounds, where we return 0.
    -   To find the overall maximum, we can loop through all possible starting indices from `0` to `n-1`, call our `solve` function for each, and keep track of the maximum result.

3.  **Optimization (Memoization)**: In the recursive approach, we might recompute `solve(i)` multiple times. For example, if we start at `i` and later another path leads to `i`, we would recalculate the same path segment. We can cache the results in a memoization table (e.g., a 1D array `t`) to store the result of `solve(i)` once it's computed. This turns the brute-force recursion into a dynamic programming solution.

4.  **Bottom-Up Dynamic Programming**: The recursive solution can be converted to an iterative one. Let `t[i]` be the maximum energy we can gain if our journey *starts* at index `i`.
    -   The energy gained from starting at `i` is `energy[i]` plus the energy gained from the rest of the path, which starts at `i + k`. This gives us the recurrence relation: `t[i] = energy[i] + t[i + k]`.
    -   Notice that to calculate `t[i]`, we need a "future" value, `t[i + k]`. This suggests that if we compute the values of `t` from right to left (i.e., from `n-1` down to `0`), the required value `t[i + k]` will always be available before we need it.
    -   **Algorithm**:
        1.  Initialize a DP array `t` of the same size as `energy`.
        2.  Iterate from `i = n - 1` down to `0`.
        3.  For each `i`, calculate `t[i] = energy[i]`. If `i + k` is within the array bounds, add `t[i + k]` to `t[i]`.
        4.  After the loop, the `t` array contains the total energy for a journey starting at each index `i`.
        5.  The final answer is the maximum value in the `t` array.

This bottom-up approach is very efficient, requiring a single pass over the array and O(n) extra space.

---

## 💻 Solution Code

### Method 1: Recursion with Memoization (Top-Down)

```cpp
// Intuition:
// The problem asks for the maximum energy gained by starting at any magician and jumping `k` steps.
// This can be solved by exploring the path from every possible starting index.
// A recursive approach naturally models this, where `solve(i)` calculates the total energy from index `i` onwards.
// To avoid redundant calculations for the same subproblems (paths), we use memoization.

// Approach:
// 1. Iterate through each index `i` from `0` to `n-1` as a potential starting point.
// 2. For each `i`, call a recursive helper function `solve(i)` to compute the total energy for the path starting at `i`.
// 3. The `solve(i, t)` function works as follows:
//    - If `i` is out of bounds, return 0 (base case).
//    - If the result for `t[i]` is already computed, return it from the memoization table.
//    - Otherwise, calculate the result as `energy[i] + solve(i + K, t)`.
//    - Store this result in `t[i]` and return it.
// 4. Keep track of the maximum energy found across all starting points.

// Time Complexity: O(n)
// Each state `solve(i)` is computed only once due to memoization. The main loop runs `n` times, but each recursive call chain fills the memoization table.
// So, the total number of computations is proportional to `n`.

// Space Complexity: O(n)
// This is for the memoization table `t` of size `n` and the recursion stack depth, which can be up to O(n) in the worst case.

class Solution {
public:
    int n; // Size of the energy array
    int K; // Jump value

    // Recursive function with memoization to find energy from index i
    int solve(vector<int>& energy, int i, vector<int> &t) {

        // Base case: If index is out of bounds, no more energy can be gained
        if(i >= n) {
            return 0;
        }

        // If this subproblem is already solved, return the stored result
        if(t[i] != INT_MIN) {
            return t[i];
        }
        
        // Recursive step: current energy + energy from the next jump
        return t[i] = energy[i] + solve(energy, i + K, t);
    }

    int maximumEnergy(vector<int>& energy, int k) {
        n = energy.size(); // Initialize size
        K = k;             // Initialize jump value
        vector<int> t(n, INT_MIN); // Memoization table initialized to a sentinel value
        int maxEnergy = INT_MIN;   // Variable to store the maximum energy found

        // Iterate through all possible starting points
        for(int i = 0; i < n; i++) {
            // Update maxEnergy with the result from each starting path
            maxEnergy = max(maxEnergy, solve(energy, i, t));
        }   
           
        return maxEnergy; // Return the overall maximum
    }
};

/*
*
* Dry Run: energy = [5, 2, -10, -5, 1], k = 3
*
* Initial call: maximumEnergy([5, 2, -10, -5, 1], 3)
* n = 5, K = 3, maxEnergy = INT_MIN
* t = [INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN]
*
* Loop i = 0:
* call solve(0):
* t[0] is INT_MIN.
* t[0] = energy[0] + solve(3) = 5 + solve(3)
* call solve(3):
* t[3] is INT_MIN.
* t[3] = energy[3] + solve(6) = -5 + solve(6)
* call solve(6): returns 0 (i >= n)
* t[3] = -5 + 0 = -5. return -5.
* t[0] = 5 + (-5) = 0. return 0.
* maxEnergy = max(INT_MIN, 0) = 0.
*
* Loop i = 1:
* call solve(1):
* t[1] is INT_MIN.
* t[1] = energy[1] + solve(4) = 2 + solve(4)
* call solve(4):
* t[4] is INT_MIN.
* t[4] = energy[4] + solve(7) = 1 + solve(7)
* call solve(7): returns 0 (i >= n)
* t[4] = 1 + 0 = 1. return 1.
* t[1] = 2 + 1 = 3. return 3.
* maxEnergy = max(0, 3) = 3.
*
* Loop i = 2:
* call solve(2):
* t[2] is INT_MIN.
* t[2] = energy[2] + solve(5) = -10 + solve(5)
* call solve(5): returns 0 (i >= n)
* t[2] = -10 + 0 = -10. return -10.
* maxEnergy = max(3, -10) = 3.
*
* Loop i = 3:
* call solve(3):
* t[3] is not INT_MIN (it's -5). return -5.
* maxEnergy = max(3, -5) = 3.
*
* Loop i = 4:
* call solve(4):
* t[4] is not INT_MIN (it's 1). return 1.
* maxEnergy = max(3, 1) = 3.
*
* End of loop. Return maxEnergy = 3.
*
*/
```

### Method 2: Bottom-Up Dynamic Programming

```cpp
// Intuition:
// We can rephrase the problem: for each starting index `i`, what is the total energy?
// The total energy starting from `i` is `energy[i]` plus the total energy starting from `i + k`.
// This structure suggests a DP approach. Let `t[i]` be the total energy if we start at `i`.
// The relation is `t[i] = energy[i] + t[i + k]`.
// Since calculating `t[i]` depends on a future index `i+k`, we can build our solution backwards from `n-1` to `0`.
// This ensures that when we compute `t[i]`, `t[i+k]` has already been computed.

// Approach:
// 1. Create a DP array `t` of size `n` to store the results. `t[i]` will hold the total energy starting from index `i`.
// 2. Iterate backwards from `i = n - 1` down to `0`.
// 3. For each index `i`:
//    - Initialize `t[i]` with the energy at that position, `energy[i]`.
//    - If the next jump `i + k` is within the array bounds, it means the path continues. Add the already computed total from that next step, `t[i+k]`, to `t[i]`.
// 4. After the loop, `t[i]` holds the total energy for a path starting at `i`.
// 5. The final answer is the maximum value in the entire `t` array, as we can start from any index.

// Time Complexity: O(n)
// We iterate through the array once to fill the DP table. Then, we iterate through it again to find the maximum element.

// Space Complexity: O(n)
// We use an auxiliary DP array `t` of size `n`. (This can be optimized to O(1) by modifying the input `energy` array in-place, if allowed).

class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        int n = energy.size(); // Get the size of the energy array
        vector<int> t(n, 0);   // DP array to store the total energy starting from each index

        // Iterate backwards from the end of the array
        for(int i = n - 1; i >= 0; i--) {
            // The total energy from `i` is at least `energy[i]`
            // And if a next step exists, we add the total from that path
            if(i + k < n) {
                // If the next jump is valid, add the pre-calculated energy from that point
                t[i] = energy[i] + t[i + k];
            } else {
                // If there's no next jump, the total energy is just the current magician's energy
                t[i] = energy[i];
            }
        }

        // The answer is the maximum value in the DP table, as we can start from any index
        return *max_element(begin(t), end(t));
    }
};

/*
*
* Dry Run: energy = [5, 2, -10, -5, 1], k = 3
*
* Initial state:
* n = 5, k = 3
* t = [0, 0, 0, 0, 0]
*
* Loop i = 4 (n-1):
* i + k = 7 >= 5.
* t[4] = energy[4] = 1.
* t -> [0, 0, 0, 0, 1]
*
* Loop i = 3:
* i + k = 6 >= 5.
* t[3] = energy[3] = -5.
* t -> [0, 0, 0, -5, 1]
*
* Loop i = 2:
* i + k = 5 >= 5.
* t[2] = energy[2] = -10.
* t -> [0, 0, -10, -5, 1]
*
* Loop i = 1:
* i + k = 4 < 5.
* t[1] = energy[1] + t[4] = 2 + 1 = 3.
* t -> [0, 3, -10, -5, 1]
*
* Loop i = 0:
* i + k = 3 < 5.
* t[0] = energy[0] + t[3] = 5 + (-5) = 0.
* t -> [0, 3, -10, -5, 1]
*
* End of loop.
* Final DP array t = [0, 3, -10, -5, 1].
* Find max_element in t, which is 3.
* Return 3.
*
*/
```

---

## 🎯 Key Insights

-   **Independent Chains**: The problem can be viewed as `k` separate, independent problems. The sequence of indices `0, k, 2k, ...` is completely independent of `1, 1+k, 1+2k, ...`, and so on for starting points `0, 1, ..., k-1`.
-   **Suffix Sums**: For each of these `k` chains, the problem is equivalent to finding the maximum "suffix sum". The bottom-up DP approach cleverly calculates these suffix sums for all chains simultaneously by iterating from right to left. `t[i]` is essentially the suffix sum of its chain starting from `i`.
-   **Space Optimization**: The bottom-up DP approach can be optimized to use O(1) extra space. Since `t[i]` only depends on `energy[i]` and `t[i+k]`, we can perform the calculations in-place on the input `energy` array itself, thus eliminating the need for a separate `t` array.

---

## 🚀 Further Exploration

-   Try implementing the space-optimized O(1) solution where you modify the `energy` array in-place. Remember to ask an interviewer if modifying the input is acceptable.
-   Consider how the problem would change if you could make a limited number of jumps, say `m` jumps, instead of jumping until you go out of bounds.

---

## 📚 References

-   [LeetCode Problem: Taking Maximum Energy From the Mystic Dungeon](https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description/)
-   [Dynamic Programming Patterns](https://leetcode.com/discuss/general-discussion/458695/dynamic-programming-patterns)

---

## 🏷️ Tags

`Array` `Dynamic Programming` `Recursion` `Memoization`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)