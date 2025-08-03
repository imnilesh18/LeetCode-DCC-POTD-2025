# 🍎 2106. Maximum Fruits Harvested After at Most K Steps

[![LeetCode](https://img.shields.io/badge/LeetCode-2106-blue?style=for-the-badge&logo=leetcode)](https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/description/)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

> ⚡️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [LeetCode problem](https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/description/).

---

## 📄 Problem Statement

Fruits are available at some positions on an infinite x-axis. You are given a 2D integer array `fruits` where `fruits[i] = [positioni, amounti]` depicts `amounti` fruits at the position `positioni`. `fruits` is already **sorted** by `positioni` in **ascending order**, and each `positioni` is **unique**.

You are also given an integer `startPos` and an integer `k`. Initially, you are at the position `startPos`. From any position, you can either walk to the **left or right**. It takes **one step** to move **one unit** on the x-axis, and you can walk **at most** `k` steps in total. For every position you reach, you harvest all the fruits at that position, and the fruits will disappear from that position.

Return _the **maximum total number** of fruits you can harvest_.

---

## Examples

### Example 1

| Input                                               | Output |
| --------------------------------------------------- | ------ |
| `fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4` | `9`    |

<p><img src="https://assets.leetcode.com/uploads/2021/11/21/1.png" alt="Example 1 Diagram" width="400"/> </p>

<details>

<summary><strong>Example Walkthrough</strong></summary>

**Explanation:**
The optimal way is to:

- Move right to position 6 and harvest 3 fruits (1 step).
- Move right to position 8 and harvest 6 fruits (2 more steps).
  You moved a total of `(8 - 5) = 3` steps and harvested `3 + 6 = 9` fruits.

</details>

### Example 2

| Input                                                                  | Output |
| ---------------------------------------------------------------------- | ------ |
| `fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4` | `14`   |

<p><img src="https://assets.leetcode.com/uploads/2021/11/21/2.png" alt="Example 2 Diagram" width="400"/> </p>

<details>
<summary><strong>Example Walkthrough</strong></summary>

**Explanation:**
You can move at most `k = 4` steps.
The optimal way is to:

- Harvest the 7 fruits at the starting position 5 (0 steps).
- Move left to position 4 and harvest 1 fruit (1 step).
- From `startPos`, move right to position 6 and harvest 2 fruits (1 step).
- From `startPos`, move right to position 7 and harvest 4 fruits (2 steps).

This path is complex. A better way to think is:

1.  Go left 1 step to pos 4. **Cost: 1**.
2.  Go back to start (pos 5) and then to pos 7. **Cost: 1 (back) + 2 (to 7) = 3**.
    Total steps: `1 + 3 = 4`.
    Total fruits: `7 (at pos 5) + 1 (at pos 4) + 2 (at pos 6) + 4 (at pos 7) = 14`. Note that you collect fruits at all positions visited within the path, including the start.

</details>

---

## ⛓️ Constraints

- `1 <= fruits.length <= 10^5`
- `fruits[i].length == 2`
- `0 <= startPos, positioni <= 2 * 10^5`
- `positioni-1 < positioni` for any `i > 0`
- `1 <= amounti <= 10^4`
- `0 <= k <= 2 * 10^5`

---

## 🛠️ Approach

The core insight is that any optimal path will involve at most one change of direction. Any path like "left, then right, then left again" is inefficient. Why? The steps taken on the final "left" leg could have been covered more cheaply during the initial "left" leg.

This simplifies the problem into two main scenarios:

1.  **Go Left, then Turn Right:** Move left by some distance `d`, collect fruits, then use the remaining steps `k - d` to go back to the starting point and then move right.
2.  **Go Right, then Turn Left:** Move right by some distance `d`, collect fruits, then use the remaining steps `k - d` to go back and move left.

The distance `d` we can travel in the first direction is limited. If we go `d` steps left, we must use another `d` steps to return to our starting point before we can go right. This means the total steps for the round trip is `2*d`. The remaining steps for the rightward journey are `k - 2*d`. This must be non-negative, so `k - 2*d >= 0`, which implies `d <= k / 2`.

**Algorithm:**

1.  **Prefix Sum:** Pre-calculate the prefix sums of the fruit amounts. This will allow us to find the sum of fruits in any range `[i, j]` in `O(1)` time.
2.  **Iterate on Distance `d`:** Loop through all possible initial distances `d` from `0` to `k / 2`.
3.  **Calculate for Both Scenarios:** For each `d`:
    - **Case 1 (Left First):**
      - The leftmost point reached is `startPos - d`.
      - The steps remaining to go right are `remain = k - 2*d`.
      - The rightmost point reached is `startPos + remain`.
      - We need to find the total fruits in the range `[startPos - d, startPos + remain]`.
    - **Case 2 (Right First):**
      - The rightmost point reached is `startPos + d`.
      - The steps remaining to go left are `remain = k - 2*d`.
      - The leftmost point reached is `startPos - remain`.
      - We need to find the total fruits in the range `[startPos - remain, startPos + d]`.
4.  **Find Fruit Sum:** The `fruits` array is sorted by position. To find which fruits fall into our calculated range `[i, j]`, we can use **binary search** (`lower_bound` for `i` and `upper_bound` for `j`) on the fruit positions. This gives us the start and end indices in our prefix sum array.
5.  **Maximize:** Keep track of the maximum fruits collected across all iterations and scenarios.

---

## 💻 Solution Code

### C++

```cpp
// Intuition:
// The problem asks for the maximum fruits collected within k steps. The key observation is that the optimal path will only have one turn.
// We either go left and then right, or right and then left. Any other path (e.g., L->R->L) is suboptimal.
//
// Approach:
// 1. Pre-calculate prefix sums of fruit amounts for O(1) range sum queries.
// 2. Create a separate array for fruit positions to perform binary search.
// 3. Iterate through all possible initial move distances `d` from 0 to k/2. A move of `d` and back costs `2*d`, so `d` can't exceed `k/2`.
// 4. For each `d`, consider two cases:
//    a) Move left `d` steps, then right with remaining steps (`k - 2*d`). Calculate the fruit total in this range.
//    b) Move right `d` steps, then left with remaining steps (`k - 2*d`). Calculate the fruit total in this range.
// 5. To find the fruits within a calculated position range [i, j], use binary search (`lower_bound` on i, `upper_bound` on j) on the positions array to find the corresponding indices.
// 6. Use the prefix sum array to get the total fruits for these indices.
// 7. Keep track of the maximum fruits found.
//
// Time Complexity: O(N + K * logN), where N is the number of fruits. O(N) for prefix sums, and the loop runs K/2 times with binary search (logN) inside.
// Space Complexity: O(N) for storing prefix sums and positions.

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        vector<int> prefixSum(n);
        vector<int> indices(n);

        // Build prefix sum and extract indices
        for (int i = 0; i < n; i++) {
            indices[i]   = fruits[i][0];
            prefixSum[i] = fruits[i][1] + (i > 0 ? prefixSum[i - 1] : 0);
        }

        int maxFrutis = 0;

        // Iterate through all possible distances 'd' for the first leg of the journey
        for (int d = 0; d <= k / 2; d++) {
            int remain = k - 2 * d;

            // Case 1: Move left 'd' steps, then right with 'remain' steps
            int i   = startPos - d;
            int j  = startPos + remain;

            // Find the indices in the fruits array corresponding to the calculated range [i, j]
            int left  = lower_bound(indices.begin(), indices.end(), i) - indices.begin();
            int right = upper_bound(indices.begin(), indices.end(), j) - indices.begin() - 1;

            if(left <= right) {
                int total = prefixSum[right] - (left > 0 ? prefixSum[left - 1] : 0);
                maxFrutis = max(maxFrutis, total);
            }

            // Case 2: Move right 'd' steps, then left with 'remain' steps
            i  = startPos - remain;
            j  = startPos + d;

            left  = lower_bound(indices.begin(), indices.end(), i) - indices.begin();
            right = upper_bound(indices.begin(), indices.end(), j) - indices.begin() - 1;

            if(left <= right) {
                int total = prefixSum[right] - (left > 0 ? prefixSum[left - 1] : 0);
                maxFrutis = max(maxFrutis, total);
            }
        }

        return maxFrutis;
    }
};

/*
 *
 * Dry Run (Example 1: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4)
 *
 * 1. Initialization:
 * - indices: [2, 6, 8]
 * - prefixSum: [8, 11, 17]
 * - maxFrutis: 0
 * - k/2 = 2
 *
 * 2. Loop for d from 0 to 2:
 *
 * - d = 0:
 * - remain = 4 - 2*0 = 4
 * - Case 1 (L:0, R:4): i=5-0=5, j=5+4=9. Range [5, 9].
 * - indices in range: 6, 8. Indices: 1, 2.
 * - total = prefixSum[2] - prefixSum[1-1] = 17 - 8 = 9.
 * - maxFrutis = max(0, 9) = 9.
 * - Case 2 (R:0, L:4): i=5-4=1, j=5+0=5. Range [1, 5].
 * - indices in range: 2. Index: 0.
 * - total = prefixSum[0] = 8.
 * - maxFrutis = max(9, 8) = 9.
 *
 * - d = 1:
 * - remain = 4 - 2*1 = 2
 * - Case 1 (L:1, R:2): i=5-1=4, j=5+2=7. Range [4, 7].
 * - indices in range: 6. Index: 1.
 * - total = prefixSum[1] - prefixSum[1-1] = 11 - 8 = 3.
 * - maxFrutis = max(9, 3) = 9.
 * - Case 2 (R:1, L:2): i=5-2=3, j=5+1=6. Range [3, 6].
 * - indices in range: 6. Index: 1.
 * - total = prefixSum[1] - prefixSum[1-1] = 11 - 8 = 3.
 * - maxFrutis = max(9, 3) = 9.
 *
 * - d = 2:
 * - remain = 4 - 2*2 = 0
 * - Case 1 (L:2, R:0): i=5-2=3, j=5+0=5. Range [3, 5].
 * - No indices in range.
 * - Case 2 (R:2, L:0): i=5-0=5, j=5+2=7. Range [5, 7].
 * - indices in range: 6. Index: 1.
 * - total = prefixSum[1] - prefixSum[1-1] = 11 - 8 = 3.
 * - maxFrutis = max(9, 3) = 9.
 *
 * 3. Final Result:
 * - Return maxFrutis = 9.
 *
 */
```

---

## 🧠 Key Insights

The crucial observation is that the optimal path is a simple one-turn trip. Any path that zig-zags (e.g., Left -\> Right -\> Left) is inefficient. The final "Left" segment could have been covered during the initial "Left" move, saving the steps used to travel back and forth. By limiting our search to the two one-turn scenarios (L-\>R and R-\>L), we cover all optimal possibilities.

The `d <= k/2` condition is a powerful optimization. It prunes the search space by acknowledging that traveling a distance `d` and returning to the start (`2*d` steps) must leave some steps (`k - 2*d >= 0`) for the second leg of the journey.

---

## 🚀 Further Exploration

- **Follow-up Question:** What if the cost of moving left and right is different?
- **Related Problems:**
  - [LeetCode 904. Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/): Another "fruit" problem, but focused on the sliding window technique to find the longest subarray with at most two distinct elements.
  - [LeetCode 304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/): A classic problem to practice prefix sums in two dimensions.

---

## 📚 References

- **Original Problem:** [LeetCode 2106](https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/)
- **Techniques:** [Prefix Sum](https://usaco.guide/silver/prefix-sums?lang=cpp), [Binary Search](https://en.wikipedia.org/wiki/Binary_search_algorithm)

---

## 👨‍💻 Author

- **Connect with me:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Prefix Sum` `Binary Search` `Array` `Greedy` `Range Query`

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

**A Strong Reminder:** All solutions and code are provided for educational purposes and personal practice. They are not intended for use in any academic or commercial settings without proper citation and adherence to the platform's terms of service.
