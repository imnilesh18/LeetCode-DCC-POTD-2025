# 💧 3100. Water Bottles II

<p align="center">
  <img src="https://img.shields.io/badge/LeetCode-3100-yellow?style=for-the-badge" alt="LeetCode Problem 3100">
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Medium Difficulty">
  <img src="https://img.shields.io/badge/Language-C++-blue?style=for-the-badge" alt="C++ Language">
</p>

<p align="center">
  <img src="https://assets.leetcode.com/uploads/2024/01/28/exampleone1.png" alt="Problem Illustration" width="600">
</p>

---

## 📝 Problem Statement

You are given two integers `numBottles` and `numExchange`.

`numBottles` represents the number of full water bottles that you initially have. In one operation, you can perform one of the following operations:

1. Drink any number of full water bottles turning them into empty bottles.
2. Exchange `numExchange` empty bottles with one full water bottle. Then, increase `numExchange` by one.

**Note:** You cannot exchange multiple batches of empty bottles for the same value of `numExchange`. For example, if you have 13 empty bottles and `numExchange` is 6, you can exchange 6 empty bottles for 1 full bottle, but you cannot immediately exchange another 6 empty bottles. The value of `numExchange` will increase to 7 for the next exchange.

Return the **maximum** number of water bottles you can drink.

---

## ⛓️ Constraints

- `1 <= numBottles <= 100`
- `1 <= numExchange <= 100`

---

## 📋 Examples

### Example 1:

| Full Bottles | Empty Bottles | `numExchange` | Drunk | Action                                     |
| :----------: | :-----------: | :-----------: | :---: | :----------------------------------------- |
|      13      |       0       |       6       |   0   | **Initial State**                          |
|      0       |      13       |       6       |  13   | Drink 13 bottles                           |
|      1       |       7       |       7       |  14   | Exchange 6 empty for 1 full, then drink it |
|      1       |       1       |       8       |  15   | Exchange 7 empty for 1 full, then drink it |
|      0       |       2       |       8       |  15   | Stop (2 empty < 8 required)                |

**Input:** `numBottles = 13`, `numExchange = 6`
**Output:** `15`

### Example 2:

| Full Bottles | Empty Bottles | `numExchange` | Drunk | Action                                     |
| :----------: | :-----------: | :-----------: | :---: | :----------------------------------------- |
|      10      |       0       |       3       |   0   | **Initial State**                          |
|      0       |      10       |       3       |  10   | Drink 10 bottles                           |
|      1       |       7       |       4       |  11   | Exchange 3 empty for 1 full, then drink it |
|      1       |       4       |       5       |  12   | Exchange 4 empty for 1 full, then drink it |
|      1       |       0       |       6       |  13   | Exchange 5 empty for 1 full, then drink it |
|      0       |       1       |       6       |  13   | Stop (1 empty < 6 required)                |

**Input:** `numBottles = 10`, `numExchange = 3`
**Output:** `13`

---

## 🤔 Approach

The problem asks for the maximum number of bottles we can drink. We start with a certain number of full bottles, which we can drink immediately. This gives us empty bottles, which can then be exchanged for new full bottles. The catch is that the cost of exchange (`numExchange`) increases by one after each exchange.

### 🧠 Simulation Approach

This is the most intuitive way to solve the problem. We can directly simulate the process described:

1.  **Drink Initial Bottles:** We start by drinking all the `numBottles` we have. The total number of drunk bottles becomes `numBottles`, and we now have `numBottles` empty bottles.
2.  **Loop for Exchanges:** We enter a loop that continues as long as we have enough empty bottles to make an exchange (i.e., `emptyBottles >= numExchange`).
3.  **Perform Exchange:** Inside the loop, we:
    - Subtract `numExchange` from our `emptyBottles` count.
    - Increment `numExchange` for the next potential exchange.
    - We receive one new full bottle. We immediately drink it, so we increment our total `drunk` count.
    - Since we drank the new bottle, it becomes empty. We increment our `emptyBottles` count by one.
4.  **Termination:** The loop stops when we can no longer afford an exchange. The final `drunk` count is our answer.

### 📐 Mathematical Approach (O(1) Solution)

Instead of simulating, we can derive a mathematical formula. The core idea is to determine the maximum number of exchanges, let's call it `x`, that we can perform.

- The initial `numBottles` can all be drunk.
- The number of extra bottles we can drink is equal to the number of successful exchanges (`x`).
- The cost of the exchanges forms an arithmetic progression: `numExchange`, `numExchange + 1`, `numExchange + 2`, ..., `numExchange + x - 1`.
- The total number of empty bottles required for `x` exchanges is the sum of this series.
- The total empty bottles available to us comes from the initial `numBottles` plus the `x` bottles we get from the exchanges.

By setting up an inequality where `(available empty bottles) >= (required empty bottles)`, we get a quadratic inequality in terms of `x`. Solving this using the quadratic formula (Sridharacharya formula) gives us the value of `x` directly. The final answer is `numBottles + x`.

---

## 💻 Solution Code

### Solution 1: Simulation

```cpp
// Intuition:
// The problem can be solved by directly simulating the process of drinking and exchanging bottles
// step-by-step until no more exchanges are possible.

// Approach:
// 1. Initialize 'drink' with the initial 'numBottles', as we can drink all of them.
// 2. Initialize 'emptyBottle' to 'numBottles'.
// 3. Use a while loop that continues as long as we have enough empty bottles for an exchange (`emptyBottle >= numExchange`).
// 4. In each iteration:
//    a. Decrease 'emptyBottle' by 'numExchange' to pay for the new bottle.
//    b. Increment 'numExchange' for the next round.
//    c. Increment 'drink' because we get a new bottle to drink.
//    d. Increment 'emptyBottle' because the newly drunk bottle becomes empty.
// 5. The total bottles drunk is the initial `numBottles` plus the `drink` count from exchanges.

// Time Complexity: O(sqrt(numBottles))
// The number of exchanges 'k' is limited. The total bottles required for 'k' exchanges grows quadratically (sum of an arithmetic series).
// So, k^2 is roughly proportional to numBottles, making the number of loop iterations k proportional to sqrt(numBottles).

// Space Complexity: O(1)
// We only use a few variables to store counts, regardless of the input size.
class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int emptyBottle = numBottles; // Start with empty bottles from initial drinking
        int drink = 0; // Counter for bottles drunk via exchange

        // Loop as long as we can afford an exchange
        while(emptyBottle >= numExchange) {
            // Pay for the exchange
            emptyBottle -= numExchange;
            // The cost for the next exchange increases
            numExchange++;
            // We get one new bottle and drink it
            drink++;
            // The new bottle is now empty, adding to our pool
            emptyBottle++;
        }
        // Total is initial bottles + bottles from exchanges
        return numBottles + drink;
    }
};

/*
*
* Dry Run
* Input: numBottles = 13, numExchange = 6
*
* Initial State:
* numBottles = 13
* numExchange = 6
* drink = 0
* emptyBottle = 13 (from drinking the initial 13 bottles)
* * Iteration 1:
* Condition: emptyBottle (13) >= numExchange (6) -> true
* emptyBottle = 13 - 6 = 7
* numExchange = 6 + 1 = 7
* drink = 0 + 1 = 1
* emptyBottle = 7 + 1 = 8
*
* Iteration 2:
* Condition: emptyBottle (8) >= numExchange (7) -> true
* emptyBottle = 8 - 7 = 1
* numExchange = 7 + 1 = 8
* drink = 1 + 1 = 2
* emptyBottle = 1 + 1 = 2
*
* Iteration 3:
* Condition: emptyBottle (2) >= numExchange (8) -> false
* Loop terminates.
*
* Final Result:
* return numBottles + drink = 13 + 2 = 15
*
*/
```

### Solution 2: Mathematical O(1) Approach

```cpp
// Intuition:
// Instead of simulating, we can derive a direct mathematical formula to find the maximum
// number of exchanges possible. This transforms the iterative problem into a constant-time calculation.

// Approach:
// The problem of finding the maximum number of exchanges ('x') can be modeled as a quadratic inequality.
// Total empty bottles available = numBottles + x
// Total empty bottles required for 'x' exchanges = sum of an arithmetic series from numExchange to numExchange + x - 1
// The inequality is solved using the Sridharacharya formula (quadratic formula) for 'x'.
// The final answer is numBottles (initial) + x (from exchanges). This code directly implements the solved formula.

// Time Complexity: O(1)
// The solution involves a fixed number of arithmetic operations and a square root, which are considered constant time.

// Space Complexity: O(1)
// No extra space is used that scales with the input.

//Approach-2 (Maths derivation - Using Sridharacharya formula)
//T.C : O(1)
//S.C : O(1)
class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        // The formula calculates the number of successful exchanges ('x') and adds it to the initial bottles.
        // This is derived from solving the quadratic inequality representing the exchange process.
        return numBottles + ((-2 * numExchange + 3 + sqrt(4 * numExchange * numExchange + 8 * numBottles - 12 * numExchange + 1)) / 2);
    }
};

/*
*
* Dry Run
* Input: numBottles = 13, numExchange = 6
*
* The formula calculates 'x' (number of exchanges):
* x = ((-2*6 + 3 + sqrt(4*6*6 + 8*13 - 12*6 + 1)) / 2)
* x = ((-12 + 3 + sqrt(144 + 104 - 72 + 1)) / 2)
* x = ((-9 + sqrt(177)) / 2)
* x = ((-9 + 13.304) / 2)
* x = (4.304 / 2)
* x = 2.152
* Taking the integer part, max exchanges possible is 2.
*
* Final Result:
* return numBottles + x = 13 + 2 = 15
*
*/
```

---

## 💡 Key Insights

- **Simulation vs. Formula:** While the simulation approach is intuitive and easy to code, the mathematical approach offers a highly efficient O(1) solution. Understanding how to model iterative problems mathematically can lead to significant performance improvements.
- **Greedy Choice:** At each step, it is always optimal to perform an exchange if possible. There is no benefit in holding onto empty bottles, as the exchange cost only increases. This justifies the greedy approach used in the simulation.

## 🚀 Further Exploration

- Can you solve this problem recursively? What would be the state variables for the recursion?
- Consider how the problem changes if `numExchange` could decrease or stay the same under certain conditions.
- Explore other problems where a simulation can be optimized into a mathematical formula (e.g., problems involving arithmetic or geometric series).

---

## 📚 References

- [LeetCode Problem Link](https://leetcode.com/problems/water-bottles-ii/description/)
- [Quadratic Formula](https://en.wikipedia.org/wiki/Quadratic_formula)

---

## 🏷️ Tags

`Simulation`, `Math`, `Greedy`, `Medium`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/water-bottles-ii/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
