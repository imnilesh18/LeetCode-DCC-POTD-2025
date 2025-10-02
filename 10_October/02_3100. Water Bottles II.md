# ✨ 3100. Water Bottles II

<div align="center">
    <a href="https://leetcode.com/problems/water-bottles-ii/description/">
        <img src="https://img.shields.io/badge/LeetCode-Link-blue?style=for-the-badge&logo=leetcode" alt="LeetCode Link">
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
    <img src="https://img.shields.io/badge/Language-C%2B%2B-orange?style=for-the-badge&logo=c%2B%2B" alt="Language: C++">
</div>

<br>

<p align="center">
  <img src="https://assets.leetcode.com/uploads/2024/01/28/exampleone1.png" alt="Problem Illustration" width="600px">
</p>

---

## 📝 Problem Statement

You are given two integers `numBottles` and `numExchange`.

`numBottles` represents the number of full water bottles that you initially have. In one operation, you can perform one of the following operations:
- Drink any number of full water bottles turning them into empty bottles.
- Exchange `numExchange` empty bottles with one full water bottle. Then, increase `numExchange` by one.

Note that you cannot exchange multiple batches of empty bottles for the same value of `numExchange`. For example, if `numBottles == 3` and `numExchange == 1`, you cannot exchange `3` empty water bottles for `3` full bottles.

Return the **maximum** number of water bottles you can drink.

---

## ⚙️ Constraints

- `1 <= numBottles <= 100`
- `1 <= numExchange <= 100`

---

## 🧪 Examples

Here are a couple of examples to illustrate the process:

<center>

| Input                        | Output | Explanation                                                                                                                              |
| ---------------------------- | ------ | ---------------------------------------------------------------------------------------------------------------------------------------- |
| `numBottles = 13`, `numExchange = 6` | `15`   | You drink 13 bottles, have 13 empty. Exchange 6 for 1 new bottle (drink count: 14), now have 8 empty. Exchange 7 for 1 new bottle (drink count: 15). No more exchanges possible. |
| `numBottles = 10`, `numExchange = 3` | `13`   | You drink 10 bottles, have 10 empty. Exchange 3, 4, and 5 empty bottles in sequence for 3 new bottles. Total drunk: 10 + 3 = 13. |

</center>

---

## 🧠 Approach

The problem asks for the maximum number of bottles we can drink. This can be solved using a direct simulation. We start with a certain number of full bottles, drink them all, and then use the resulting empty bottles to get more full bottles through exchanges.

The key aspects of the simulation are:
1.  **Initial State**: We begin by drinking all `numBottles`. So, our initial count of drunk bottles is `numBottles`, and we have `numBottles` empty bottles.
2.  **Exchange Loop**: We can continue to exchange empty bottles for full ones as long as we have enough. The condition for an exchange is `emptyBottle >= numExchange`.
3.  **State Updates per Exchange**:
    - We use `numExchange` empty bottles.
    - We gain one new full bottle. We immediately drink it.
    - This means our total `drunk` count increases by 1.
    - The new bottle becomes an empty bottle.
    - So, the net change in empty bottles is `-numExchange` (from the exchange) `+ 1` (from drinking the new bottle).
    - Crucially, the cost of the next exchange increases: `numExchange` is incremented by 1.
4.  **Termination**: The process stops when we no longer have enough empty bottles to meet the current `numExchange` requirement.

The final answer is the total number of bottles drunk, which is the initial `numBottles` plus any additional bottles gained through exchanges.

---

## 💻 Solution Code

### Optimized Solution (Simulation)

```cpp
// Intuition:
// The problem can be solved by simulating the process step-by-step. We start by drinking all the initial bottles. Then, we repeatedly check if we have enough empty bottles to exchange for a new one. Each time we make an exchange, we drink the new bottle, update our counts of empty bottles and drunk bottles, and increase the exchange cost for the next round.

// Approach:
// 1. Initialize `emptyBottle` to `numBottles`, as we drink all initial bottles first.
// 2. Initialize `drink` to count the number of bottles drunk through exchanges.
// 3. Use a `while` loop that continues as long as we have enough empty bottles to make an exchange (`emptyBottle >= numExchange`).
// 4. Inside the loop:
//    a. Decrease `emptyBottle` by `numExchange` for the exchange.
//    b. Increment `numExchange` for the next transaction.
//    c. Increment `drink` because we got one new bottle to drink.
//    d. Increment `emptyBottle` by 1, as the newly acquired bottle is also drunk and becomes empty.
// 5. The total number of drunk bottles is the initial `numBottles` plus the extra bottles (`drink`) we obtained via exchanges. Return this sum.

// Time Complexity: O(sqrt(numBottles))
// The number of loop iterations depends on how quickly `numExchange` grows compared to how `emptyBottle` decreases. `numExchange` increases linearly (k, k+1, k+2, ...), which is an arithmetic progression. The number of iterations is relatively small and bounded, making this efficient for the given constraints.

// Space Complexity: O(1)
// We only use a few variables (`emptyBottle`, `drink`, `numExchange`) to keep track of the state, so the space used is constant.

class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        // Initially, all full bottles are drunk, becoming empty bottles.
        int emptyBottle = numBottles;
        // 'drink' will count bottles drunk from exchanges.
        int drink = 0;
        
        // Loop as long as we can exchange empty bottles for a full one.
        while(emptyBottle >= numExchange) {
            // Perform the exchange.
            emptyBottle -= numExchange;
            // The cost for the next exchange increases.
            numExchange++;
            // We gained one new bottle and drank it.
            drink++;
            // The newly drunk bottle becomes an empty one.
            emptyBottle++;
        }
        
        // Total drunk is initial bottles + exchanged bottles.
        return numBottles + drink;
    }
};

/*
*
* Dry Run
*
* Input: numBottles = 13, numExchange = 6
*
* Initial state:
* - numBottles = 13
* - numExchange = 6
* - emptyBottle = 13
* - drink = 0
*
* --> Start while loop (condition: emptyBottle >= numExchange)
*
* Iteration 1:
* - Condition: 13 >= 6 (True)
* - emptyBottle = 13 - 6 -> 7
* - numExchange = 6 + 1 -> 7
* - drink = 0 + 1 -> 1
* - emptyBottle = 7 + 1 -> 8
*
* Iteration 2:
* - Condition: 8 >= 7 (True)
* - emptyBottle = 8 - 7 -> 1
* - numExchange = 7 + 1 -> 8
* - drink = 1 + 1 -> 2
* - emptyBottle = 1 + 1 -> 2
*
* Iteration 3:
* - Condition: 2 >= 8 (False)
* - Loop terminates.
*
* Final Calculation:
* - Return numBottles + drink = 13 + 2 = 15
*
* Output: 15
*
*/
```

---

## 📌 Key Insights

- **Greedy Simulation**: The most straightforward approach is a greedy one. At each step, if we can make an exchange, we should do it. There's no benefit in holding onto empty bottles because the exchange cost only increases.
- **State Management**: The core of the problem is correctly updating the state variables (`emptyBottle` and `numExchange`) within the loop. The net change in empty bottles after one full cycle of exchanging and drinking is `+1 - numExchange`.

---

## 🚀 Further Exploration

- Can you devise a purely mathematical formula to solve this without a loop? This would involve solving for the number of successful exchanges given the arithmetic progression of `numExchange`.
- How would the solution change if `numExchange` decreased by one after each exchange instead of increasing?

---

## 📚 References

- [LeetCode Problem: Water Bottles II](https://leetcode.com/problems/water-bottles-ii/description/)

---

## 🏷️ Tags

<div align="center">
    <a href="https://leetcode.com/tag/simulation/"><img src="https://img.shields.io/badge/Simulation-lightgrey?style=for-the-badge" alt="Simulation"></a>
    <a href="https://leetcode.com/tag/math/"><img src="https://img.shields.io/badge/Math-grey?style=for-the-badge" alt="Math"></a>
    <a href="https://leetcode.com/tag/greedy/"><img src="https://img.shields.io/badge/Greedy-green?style=for-the-badge" alt="Greedy"></a>
</div>

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/water-bottles-ii/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)