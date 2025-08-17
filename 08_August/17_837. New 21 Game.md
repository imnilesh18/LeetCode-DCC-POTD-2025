<div align="center">
  <h1>837. New 21 Game</h1>
  <a href="https://leetcode.com/problems/new-21-game/description">
    <img src="https://img.shields.io/badge/LeetCode-Link-blue?style=for-the-badge&logo=leetcode" alt="LeetCode Link">
  </a>
</div>

<br>

---

## 📝 Problem Statement

Alice plays a game that starts with **0** points. She draws numbers while her score is less than `k`. In each draw, she gets a random integer from `[1, maxPts]`. When her score reaches `k` or more, she stops.

We need to return the probability that her final score is `n` or less.

---

## 📜 Constraints

- `0 <= k <= n <= 10^4`
- `1 <= maxPts <= 10^4`
- Answers within `10^-5` of the actual answer are accepted.

---

## 📊 Examples

| Input                         | Output    | Explanation                                                                                                                              |
| :---------------------------- | :-------- | :--------------------------------------------------------------------------------------------------------------------------------------- |
| `n = 10, k = 1, maxPts = 10`  | `1.00000` | Alice gets a single card, then stops. Her score will be between 1 and 10, all of which are <= 10.                                        |
| `n = 6, k = 1, maxPts = 10`   | `0.60000` | Alice gets one card and stops. There are 10 possibilities (1 to 10). 6 of these (1 to 6) are at or below 6. So, the probability is 6/10. |
| `n = 21, k = 17, maxPts = 10` | `0.73278` | A more complex scenario where multiple draws might be needed before the score reaches 17.                                                |

---

## 🧠 Approach

This problem can be solved using **Dynamic Programming**. Let `dp[i]` be the probability of getting a score of exactly `i`. Our goal is to find the sum of probabilities of all scores from `k` to `n`, i.e., `sum(dp[k]...dp[n])`.

The base case is `dp[0] = 1`, as Alice starts with a score of 0 with 100% certainty.

For any score `i > 0`, the probability `dp[i]` is the sum of probabilities of reaching `i` from all possible previous scores. A score `i` can be reached by drawing a card with value `j` (where `1 <= j <= maxPts`) from a previous score of `i-j`. The probability of drawing any specific card `j` is `1 / maxPts`.

So, the recurrence relation is:
`dp[i] = (dp[i-1] + dp[i-2] + ... + dp[i-maxPts]) / maxPts`

This holds as long as the previous score `i-j` is less than `k`, because Alice stops drawing once her score is `k` or more.

A naive implementation of this would involve a nested loop, leading to a time complexity of `O(n * maxPts)`, which is too slow and will result in a **Time Limit Exceeded (TLE)** error.

To optimize this, we can observe that the sum `(dp[i-1] + ... + dp[i-maxPts])` is a sliding window sum. As we calculate `dp[i]`, we can maintain this sum in `O(1)` time. Let `probSum` be the sum of probabilities in the current window of size `maxPts`.

- When calculating `dp[i]`, it is simply `probSum / maxPts`.
- To calculate `dp[i+1]`, we update the window: add `dp[i]` to `probSum` and subtract `dp[i-maxPts]` from `probSum`.

This sliding window optimization reduces the time complexity to `O(n)`, which is efficient enough to pass all test cases.

---

## 💻 Solution Code

### Brute Force (TLE)

```cpp
// Intuition:
// The problem asks for a probability, which suggests a dynamic programming approach. We can define dp[i] as the probability of reaching a score of exactly 'i'. The final answer would be the sum of probabilities of all valid final scores (from k to n).

// Approach:
// 1. Create a DP array `P` of size `n+1` to store the probabilities, P[i] being the probability of scoring 'i'.
// 2. Initialize P[0] = 1, as Alice starts at score 0 with 100% certainty. All other probabilities are 0.
// 3. Iterate from i = 1 to n to calculate P[i].
// 4. For each score `i`, iterate through all possible card values `j` from 1 to `maxPts`.
// 5. If the previous score `i-j` is valid (i.e., non-negative and less than `k`), it means we could have drawn card `j` to reach score `i`.
// 6. The probability of drawing card `j` is 1/maxPts. So, we add `P[i-j] / maxPts` to `P[i]`.
// 7. This accumulates the probabilities from all valid previous states.
// 8. Finally, sum up the probabilities from P[k] to P[n] to get the total probability that Alice's score is n or fewer.

// Time Complexity: O(n * maxPts), due to the nested loops iterating up to n and maxPts respectively. This will lead to TLE.
// Space Complexity: O(n), for the DP array used to store probabilities.
class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        vector<double> P(n + 1); // DP array to store probabilities

        // P[i] = probability of getting score = i
        P[0] = 1; // Initially, Alice has a score of 0, so the probability of scoring 0 is 1.

        // Iterate through each possible score from 1 to n
        for (int i = 1; i <= n; i++) {

            // Iterate through each possible card value
            for (int j = 1; j <= maxPts; j++) {

                // Check if the previous score (i-j) is valid to continue the game
                if (i - j >= 0 && i - j < k) {

                    // Probability of score j = 1/maxPts
                    // Remaining points = (i-j)
                    // P[i] is the sum of probabilities of reaching i from all valid previous scores
                    // P[i] += Probability of drawing j * Probability of having score (i-j)
                    // P[i] += (1/maxPts) * P[i-j]
                    P[i] += P[i - j] / maxPts;
                }
            }
        }

        // The final answer is the sum of probabilities of scores from k to n.
        return accumulate(P.begin() + k, P.end(), 0.0);
    }
};

/*
*
* Dry Run
* n = 6, k = 1, maxPts = 10
* P = [0.0] * 7
* P[0] = 1.0
*
* i = 1:
* j = 1: i-j=0 < k. P[1] += P[0]/10 = 0.1
* j = 2..10: i-j < 0. No change.
* P[1] = 0.1
*
* i = 2:
* j = 1: i-j=1 >= k. Stop.
* j = 2: i-j=0 < k. P[2] += P[0]/10 = 0.1
* ... all other j will be from P[0] as previous scores > 0 are invalid
* P[2] = 0.1
*
* Similarly, P[3]=0.1, P[4]=0.1, P[5]=0.1, P[6]=0.1
*
* Final Answer = sum from P[k] to P[n] -> sum(P[1]..P[6])
* = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 = 0.6
*/
```

### Optimized Solution

```cpp
// Intuition:
// The brute-force DP approach is slow because of the inner loop which re-calculates a sum of previous probabilities. This sum is essentially a sliding window over the DP array. We can optimize by maintaining this sum in O(1) time.

// Approach:
// 1. Create a DP array `P` of size `n+1` and initialize `P[0] = 1`.
// 2. Initialize a variable `currProbabSum` to represent the sum of probabilities in the sliding window. If k > 0, the initial window contains just P[0], so `currProbabSum = 1`. If k = 0, the game stops immediately, so the sum is 0.
// 3. Iterate from `i = 1` to `n`.
// 4. Calculate `P[i] = currProbabSum / maxPts`. This is the core DP transition using the optimized sum.
// 5. If `i < k`, the current probability `P[i]` is part of the next window's sum, so add it: `currProbabSum += P[i]`.
// 6. If `i - maxPts` is a valid score that is now falling out of the window (i.e., `i-maxPts >= 0` and `i-maxPts < k`), subtract its probability from the sum: `currProbabSum -= P[i-maxPts]`.
// 7. After filling the DP table, sum the probabilities from `P[k]` to `P[n]` for the final answer.

// Time Complexity: O(n), as we iterate through the scores from 1 to n only once.
// Space Complexity: O(n), for the DP array.
class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if (k == 0 || n >= k + maxPts) {
            return 1.0; // Edge cases: if k=0, score is 0, which is <= n. if n is large enough, prob is 1.
        }
        vector<double> P(n + 1, 0.0); // DP array for probabilities

        // P[i] = probability of getting score = i
        P[0] = 1; // Base case: starts with score 0, probability is 1

        // Sliding window sum of probabilities
        double currProbabSum = (k > 0) ? 1.0 : 0.0;

        // Iterate from score 1 to n
        for (int i = 1; i <= n; i++) {

            // P[i] is the sum of the last 'maxPts' probabilities, divided by maxPts
            P[i] = currProbabSum / maxPts;

            // If we are still drawing cards (score < k)
            if (i < k) {
                // Add the new probability to our sliding window sum
                currProbabSum += P[i];
            }

            // If the window has moved past a point, remove the leftmost element
            // We only subtract if P[i-maxPts] corresponded to a state where Alice was still playing (score < k)
            if (i - maxPts >= 0 && i - maxPts < k) {
                // Remove the probability that's now outside the window of size 'maxPts'
                currProbabSum -= P[i - maxPts];
            }
        }

        // Summing the probabilities for all outcomes where Alice stops with a score between k and n
        return accumulate(P.begin() + k, P.end(), 0.0);
    }
};

/*
*
* Dry Run
* n = 6, k = 1, maxPts = 10
* P = [0.0] * 7
* P[0] = 1.0
* currProbabSum = 1.0
*
* i = 1:
* P[1] = currProbabSum / 10 = 1.0 / 10 = 0.1
* i=1 is not < k=1. No change to currProbabSum.
* i-maxPts = 1-10 < 0. No change.
*
* i = 2:
* P[2] = currProbabSum / 10 = 1.0 / 10 = 0.1
* i=2 is not < k=1.
* i-maxPts = 2-10 < 0.
* ...
* i = 6:
* P[6] = currProbabSum / 10 = 1.0 / 10 = 0.1
* i=6 is not < k=1.
* i-maxPts = 6-10 < 0.
*
* Final P array will have P[1] through P[6] as 0.1 (and up to P[10]).
* Answer = accumulate(P.begin()+1, P.end(), 0.0) = P[1]+...+P[6] = 0.6
*/
```

---

## 💡 Key Insights

- **Dynamic Programming is Natural**: The problem builds upon previous states (scores), making DP a suitable approach. The probability of a state depends on the sum of probabilities of previous states.
- **Sliding Window Optimization**: The key to passing the time limit is recognizing that the recurrence `dp[i] = sum(dp[i-j] for j in 1..maxPts) / maxPts` involves a sliding window sum. Instead of re-calculating this sum every time, we can maintain it in `O(1)` by adding the new element and removing the oldest one.
- **State Transition Condition**: The crucial condition is that we only add probabilities from previous scores `s` where `s < k`. Once a score of `k` or more is reached, the game stops, and that path cannot be extended further.

---

## 🚀 Further Exploration

- Consider how the solution would change if the probabilities of drawing cards were not uniform.
- Explore variations where the stopping condition is different, e.g., stopping after a certain number of draws.
- This problem is similar to other DP problems involving paths on a 1D line, like the frog jump or climbing stairs problems, but with a probabilistic twist.

---

## 📚 References

- [LeetCode Problem Link](https://leetcode.com/problems/new-21-game/description)
- [Sliding Window Technique](https://www.geeksforgeeks.org/window-sliding-technique/)

---

## 🏷️ Tags

<div align="left">
  <a href="https://leetcode.com/tag/dynamic-programming/" target="_blank" rel="noopener noreferrer">
    <img src="https://img.shields.io/badge/Dynamic_Programming-4A90E2?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="Dynamic Programming">
  </a>
  <a href="https://leetcode.com/tag/sliding-window/" target="_blank" rel="noopener noreferrer">
    <img src="https://img.shields.io/badge/Sliding_Window-F5A623?style=for-the-badge" alt="Sliding Window">
  </a>
  <a href="https://leetcode.com/tag/math/" target="_blank" rel="noopener noreferrer">
    <img src="https://img.shields.io/badge/Math-D0021B?style=for-the-badge" alt="Math">
  </a>
  <a href="https://leetcode.com/tag/probability-and-statistics/" target="_blank" rel="noopener noreferrer">
    <img src="https://img.shields.io/badge/Probability-7ED321?style=for-the-badge" alt="Probability">
  </a>
</div>

---

## 📄 License

This repository is released under the [MIT License](https://www.google.com/search?q=./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/new-21-game/description) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
