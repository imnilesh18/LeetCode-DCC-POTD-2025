<div align="center">

# **💧 1518. Water Bottles**

<a href="https://leetcode.com/problems/water-bottles/description/"><img src="https://img.shields.io/badge/LeetCode-Problem-blue?style=for-the-badge&logo=leetcode" alt="LeetCode Problem"></a>
<img src="https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge" alt="Difficulty: Easy">
<img src="https://img.shields.io/badge/Language-C++-orange?style=for-the-badge&logo=c%2b%2b" alt="Language: C++">

</div>

---

## 📝 Problem Statement

There are `numBottles` water bottles that are initially full of water. You can exchange `numExchange` empty water bottles from the market with one full water bottle.

The operation of drinking a full water bottle turns it into an empty bottle.

Given the two integers `numBottles` and `numExchange`, return the **maximum** number of water bottles you can drink.

---

## Constraints

- `1 <= numBottles <= 100`
- `2 <= numExchange <= 100`

---

## Examples

<details>
<summary><strong>Example 1</strong></summary>

| Input                               | Output | Explanation                                                                                                                                                                                                                                                                               |
| ----------------------------------- | ------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `numBottles = 9`, `numExchange = 3` | `13`   | You can exchange 3 empty bottles to get 1 full water bottle. <br> **Total bottles drank:** <br> - Drink the initial 9 bottles. (9 empty) <br> - Exchange 9 empty for 3 full. Drink them. (3 empty) <br> - Exchange 3 empty for 1 full. Drink it. (1 empty) <br> **Total: 9 + 3 + 1 = 13** |

</details>

<details>
<summary><strong>Example 2</strong></summary>

| Input                                | Output | Explanation                                                                                                                                                                                                                                                                                                                                 |
| ------------------------------------ | ------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `numBottles = 15`, `numExchange = 4` | `19`   | You can exchange 4 empty bottles to get 1 full water bottle. <br> **Total bottles drank:** <br> - Drink the initial 15 bottles. (15 empty) <br> - Exchange 12 empty for 3 full. Drink them. (3 empty + 3 leftover = 6 empty) <br> - Exchange 4 empty for 1 full. Drink it. (1 empty + 2 leftover = 3 empty) <br> **Total: 15 + 3 + 1 = 19** |

</details>

---

## 🧠 Approach

The problem asks for the maximum number of water bottles we can drink, given an initial number of full bottles and an exchange rate for empty bottles. We can approach this through simulation, optimization, or a direct mathematical formula.

1.  **Simulation (Brute-Force):**
    This approach mimics the process step-by-step. We start by drinking the initial bottles. Then, as long as we have enough empty bottles to make an exchange, we trade them for a new full bottle, drink it, and repeat the process. We keep a running total of all bottles consumed.

2.  **Optimized Simulation:**
    Instead of simulating one exchange at a time, we can process them in batches. After drinking the initial bottles, we have a certain number of empty ones. We can calculate how many new full bottles (`extraFullBottles`) we can get by integer division (`emptyBottles / numExchange`) and how many empty bottles will be left over (`emptyBottles % numExchange`). We add the `extraFullBottles` to our total consumed count. The new number of empty bottles for the next iteration is the sum of these newly acquired bottles (which become empty after drinking) and the leftover ones. This is much faster as it reduces the number of loop iterations significantly.

3.  **Mathematical Approach (O(1)):**
    This is the most efficient method. We start with the `numBottles` we can initially drink. The key insight is to figure out how many _extra_ bottles we can get through exchanges. When you exchange `numExchange` bottles and get 1 back, you are effectively using up `numExchange - 1` empty bottles from your supply to gain 1 drink.
    So, the question becomes: how many times can you perform this `(numExchange - 1)` trade?
    With `numBottles`, you have `numBottles` potential empty bottles to start with. However, the very last bottle cannot be exchanged, so we have `numBottles - 1` bottles that can participate in the exchange cycle.
    The number of extra bottles we can drink is `(numBottles - 1) / (numExchange - 1)`.
    The total is the initial bottles plus the extra ones: `numBottles + (numBottles - 1) / (numExchange - 1)`.

---

## 💻 Solution Code

<details>
<summary><strong>Approach 1: Simple Simulation</strong></summary>

```cpp
// Intuition: Simulate the process of drinking and exchanging one by one.
// Approach:
// 1. Initialize `consumed` bottles to 0.
// 2. Use a while loop that continues as long as `numBottles` is greater than or equal to `numExchange`.
// 3. Inside the loop, "consume" `numExchange` bottles by adding them to `consumed` and subtracting from `numBottles`.
// 4. For each exchange, you get one new full bottle, so increment `numBottles` by 1.
// 5. After the loop, any remaining `numBottles` can also be consumed, so add them to the final result.
// Time Complexity: O(numBottles / numExchange), as we group exchanges.
// Space Complexity: O(1), as we only use a few variables.

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int consumed = 0; // Total bottles consumed so far

        // Loop as long as we can make an exchange
        while(numBottles >= numExchange) {

            // Drink `numExchange` bottles
            consumed   += numExchange;
            // `numExchange` bottles are now empty
            numBottles -= numExchange;

            // Exchange the empty bottles for one full bottle
            numBottles += 1;
        }

        // Return total consumed plus any remaining full bottles
        return consumed + numBottles;
    }
};

/*
*
* Dry Run
* Input: numBottles = 9, numExchange = 3
*
* Initial State:
* consumed = 0
* numBottles = 9
*
* Iteration 1: (9 >= 3 is true)
* consumed = 0 + 3 = 3
* numBottles = 9 - 3 = 6
* numBottles = 6 + 1 = 7
*
* Iteration 2: (7 >= 3 is true)
* consumed = 3 + 3 = 6
* numBottles = 7 - 3 = 4
* numBottles = 4 + 1 = 5
*
* Iteration 3: (5 >= 3 is true)
* consumed = 6 + 3 = 9
* numBottles = 5 - 3 = 2
* numBottles = 2 + 1 = 3
*
* Iteration 4: (3 >= 3 is true)
* consumed = 9 + 3 = 12
* numBottles = 3 - 3 = 0
* numBottles = 0 + 1 = 1
*
* Loop End: (1 >= 3 is false)
*
* Final Return:
* return consumed + numBottles
* return 12 + 1 = 13
*
*/
```

</details>

<details>
<summary><strong>Approach 2: Optimized Simulation</strong></summary>

```cpp
// Intuition: Instead of exchanging one by one, calculate exchanges in batches for better performance.
// Approach:
// 1. Initialize `consumed` to `numBottles`, as we drink all initial bottles.
// 2. Initialize `emptyBottles` to `numBottles`.
// 3. Loop while `emptyBottles` are enough for an exchange.
// 4. Calculate `extraFullBottles` received from the exchange (`emptyBottles / numExchange`).
// 5. Calculate `remain`ing empty bottles (`emptyBottles % numExchange`).
// 6. Add `extraFullBottles` to `consumed`.
// 7. Update `emptyBottles` for the next iteration: they are the sum of the newly drunk bottles (`extraFullBottles`) and the `remain`der.
// Time Complexity: O(log_numExchange(numBottles)), because the number of empty bottles decreases by a factor of roughly `numExchange` in each step.
// Space Complexity: O(1), constant extra space.

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int consumed = numBottles; // Initially, drink all available bottles
        int emptyBottles = numBottles; // These become empty bottles

        // Loop while we have enough empty bottles to exchange
        while(emptyBottles >= numExchange) {
            // Calculate how many new full bottles we can get
            int extraFullBottles = emptyBottles / numExchange;

            // Calculate leftover empty bottles that can't be exchanged yet
            int remain = emptyBottles % numExchange;

            // Add the newly acquired bottles to our consumed count
            consumed += extraFullBottles;

            // For the next round, our empty bottles are the ones we just drank plus leftovers
            emptyBottles = remain + extraFullBottles;
        }

        return consumed; // Return the total
    }
};

/*
*
* Dry Run
* Input: numBottles = 9, numExchange = 3
*
* Initial State:
* consumed = 9
* emptyBottles = 9
*
* Iteration 1: (9 >= 3 is true)
* extraFullBottles = 9 / 3 = 3
* remain = 9 % 3 = 0
* consumed = 9 + 3 = 12
* emptyBottles = 0 + 3 = 3
*
* Iteration 2: (3 >= 3 is true)
* extraFullBottles = 3 / 3 = 1
* remain = 3 % 3 = 0
* consumed = 12 + 1 = 13
* emptyBottles = 0 + 1 = 1
*
* Loop End: (1 >= 3 is false)
*
* Final Return:
* return 13
*
*/
```

</details>

<details>
<summary><strong>Approach 3: Mathematical O(1) Solution</strong></summary>

```cpp
// Intuition: A direct mathematical formula can solve this without looping.
// Approach:
// 1. You start with `numBottles`.
// 2. To get 1 new bottle, you must give `numExchange` empty bottles. This means you have a net loss of `numExchange - 1` empty bottles for each new bottle you drink.
// 3. The maximum number of "exchanges" you can make is limited by this net loss.
// 4. With `numBottles - 1` bottles available for the exchange cycle (the last bottle can't be part of a new exchange), the number of extra bottles is `(numBottles - 1) / (numExchange - 1)`.
// 5. The total is the initial bottles plus these extra bottles.
// Time Complexity: O(1), as it's a direct calculation.
// Space Complexity: O(1), no extra space needed.

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        // Initial bottles + extra bottles from exchanges
        return numBottles + (numBottles - 1) / (numExchange - 1);
    }
};

/*
*
* Dry Run
* Input: numBottles = 9, numExchange = 3
*
* Calculation:
* return 9 + (9 - 1) / (3 - 1)
* = 9 + 8 / 2
* = 9 + 4
* = 13
*
* Final Return:
* return 13
*
*/
```

</details>

---

## 💡 Key Insights

- The problem can be solved by simulating the process directly, but this can be inefficient.
- Optimizing the simulation by handling exchanges in batches (using division and modulo) leads to a logarithmic time complexity, which is a significant improvement.
- The most optimal solution is a mathematical one with O(1) complexity, derived by observing that each extra drink costs `numExchange - 1` empty bottles.

## 🚀 Further Exploration

- What if the exchange rate was not constant? For example, the first 10 exchanges cost 3 bottles each, and subsequent exchanges cost 4 bottles each.
- Consider a variation where you can also sell empty bottles for money and buy full bottles for a different price.

## 🔗 References

- [LeetCode Problem: 1518. Water Bottles](https://leetcode.com/problems/water-bottles/description/)
- [Discussion on Mathematical O(1) Solution](<https://leetcode.com/problems/water-bottles/discuss/743126/JavaC%2B%2BPython-O(1)>)

## 🏷️ Tags

`Math` `Simulation` `Greedy`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/water-bottles/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
