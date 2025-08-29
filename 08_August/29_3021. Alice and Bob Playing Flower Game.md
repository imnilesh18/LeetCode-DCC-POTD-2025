<div align="center">

# 🌹 Alice and Bob Playing Flower Game 🌹

### ✨ `Medium` | `LeetCode #3021` | `Math` `Game Theory`

</div>

---

<div align="center">

[![C++](https://img.shields.io/badge/C%2B%2B-Solution-blue?style=for-the-badge&logo=cplusplus)](./solution.cpp)
[![Problem Link](https://img.shields.io/badge/LeetCode-Problem-orange?style=for-the-badge&logo=leetcode)](https://leetcode.com/problems/alice-and-bob-playing-flower-game/description/)

</div>

---

## 📝 Problem Statement

Alice and Bob are playing a turn-based game on a field with two lanes of flowers. There are `x` flowers in the first lane and `y` flowers in the second.

**Game Rules:**
1.  Alice takes the first turn.
2.  In each turn, a player must choose one lane and pick one flower from it.
3.  If, at the end of a player's turn, no flowers are left, that player wins the game.

Given two integers, `n` and `m`, find the number of possible pairs `(x, y)` such that:
- Alice wins the game.
- `1 <= x <= n`
- `1 <= y <= m`

---

## 🎲 Examples

Here are a couple of examples to illustrate the game:

| `n` | `m` | `(x, y)` Pairs where Alice Wins | Output |
| :-- | :-: | :------------------------------ | :----: |
| 3 | 2 | `(1,2)`, `(3,2)`, `(2,1)` | `3` |
| 1 | 1 | None | `0` |

---

## 🤔 Approach & Intuition

The core of this problem is to determine the condition under which Alice wins. Let's analyze the game mechanics.

The game ends when the total number of flowers (`x + y`) has been picked. Since players pick one flower per turn, the total number of turns in the game is exactly `x + y`.

- Alice starts first, so she takes turns 1, 3, 5, ... (odd-numbered turns).
- Bob takes turns 2, 4, 6, ... (even-numbered turns).

The player who takes the **last turn** wins. For Alice to win, the last turn must be an odd number. This means the total number of turns, `x + y`, must be **odd**.

A sum of two integers `x + y` is odd if and only if one of them is odd and the other is even. This gives us two winning scenarios for Alice:

1.  **`x` is odd AND `y` is even.**
2.  **`x` is even AND `y` is odd.**

Our task is to count how many pairs `(x, y)` satisfy these conditions within the given ranges `1 <= x <= n` and `1 <= y <= m`.

<details>
<summary><b>Counting Odd and Even Numbers</b></summary>
<br>
To find the solution, we need to count the number of odd and even integers in the ranges `[1, n]` and `[1, m]`.

For any range `[1, k]`:
- The number of **even** numbers is `k / 2` (integer division).
- The number of **odd** numbers is `(k + 1) / 2`.

Let's define:
- `odd_n`: Number of odd integers in `[1, n]` = `(n + 1) / 2`
- `even_n`: Number of even integers in `[1, n]` = `n / 2`
- `odd_m`: Number of odd integers in `[1, m]` = `(m + 1) / 2`
- `even_m`: Number of even integers in `[1, m]` = `m / 2`

The total number of winning pairs is the sum of the counts from our two scenarios:
- **Scenario 1 (x is odd, y is even):** `odd_n * even_m`
- **Scenario 2 (x is even, y is odd):** `even_n * odd_m`

Total Winning Pairs = `(odd_n * even_m) + (even_n * odd_m)`

This simple mathematical formula allows us to solve the problem in constant time, without simulating the game for every pair.

</details>

---

## 💻 Solution Code

Here is the C++ implementation based on the mathematical approach.

```cpp
// Intuition:
// The player who takes the last turn wins. Alice starts, so she takes all odd-numbered turns (1, 3, 5, ...).
// For Alice to win, the total number of turns must be odd. The total number of turns equals the total number of flowers (x + y).
// Therefore, Alice wins if and only if (x + y) is an odd number.

// Approach:
// A sum (x + y) is odd if one number is odd and the other is even.
// We count the number of ways to form such pairs within the given ranges [1, n] and [1, m].
// Case 1: x is odd, y is even.
// Case 2: x is even, y is odd.
// The total number of winning pairs is the sum of possibilities from these two cases.
// - Number of odd numbers in [1, k] = (k + 1) / 2
// - Number of even numbers in [1, k] = k / 2

// Time Complexity: O(1)
// The solution involves a fixed number of arithmetic operations, independent of the input size.

// Space Complexity: O(1)
// No extra space is used that scales with the input size.

class Solution {
public:
    long long flowerGame(int n, int m) {
        // Calculate the number of odd and even numbers in the range [1, n]
        long long odd_n = (n + 1) / 2;
        long long even_n = n / 2;

        // Calculate the number of odd and even numbers in the range [1, m]
        long long odd_m = (m + 1) / 2;
        long long even_m = m / 2;

        // Case 1: x is odd and y is even
        long long case1 = odd_n * even_m;
        
        // Case 2: x is even and y is odd
        long long case2 = even_n * odd_m;

        // Total winning pairs is the sum of both cases
        return case1 + case2;
    }
};

/*
*
* Dry Run
* Example: n = 3, m = 2
*
* 1. Count odd/even numbers for n = 3:
* - Numbers in [1, 3]: {1, 2, 3}
* - odd_n = (3 + 1) / 2 = 2  (Numbers are 1, 3)
* - even_n = 3 / 2 = 1        (Number is 2)
*
* 2. Count odd/even numbers for m = 2:
* - Numbers in [1, 2]: {1, 2}
* - odd_m = (2 + 1) / 2 = 1  (Number is 1)
* - even_m = 2 / 2 = 1        (Number is 2)
*
* 3. Calculate winning combinations:
* - Case 1 (x is odd, y is even):
* - Ways = odd_n * even_m = 2 * 1 = 2
* - Pairs: (1, 2), (3, 2)
*
* - Case 2 (x is even, y is odd):
* - Ways = even_n * odd_m = 1 * 1 = 1
* - Pair: (2, 1)
*
* 4. Total Result:
* - Total = Case 1 + Case 2 = 2 + 1 = 3
*
* The final answer is 3.
*
*/
```

---

## 💡 Key Insights

- The problem, which appears to be about game theory, simplifies to a basic number theory question about parity (odd/even).
- Recognizing that the winner is determined by the parity of the total number of turns is the crucial observation.
- The constraints on `n` and `m` (up to 10^5) make a brute-force approach (checking every `(x, y)` pair) too slow, reinforcing that a mathematical shortcut is needed.

## 🚀 Further Exploration

- What if Bob starts the game first? How does the winning condition change?
- What if players could pick more than one flower in a turn? For example, 1, 2, or 3 flowers. This transforms the problem into a variant of the Game of Nim.

---

## 🔗 References

- [Parity in Game Theory](https://en.wikipedia.org/wiki/Parity_of_a_permutation)
- [Combinatorics and Counting](https://en.wikipedia.org/wiki/Combinatorics)

---

## 🏷️ Tags

`Math` `Game Theory` `Brain Teaser` `Combinatorics`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/alice-and-bob-playing-flower-game/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)