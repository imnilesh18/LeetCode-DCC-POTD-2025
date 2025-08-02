# 🍋 2561. Rearranging Fruits

[![LeetCode](https://img.shields.io/badge/LeetCode-2561-FFA116?style=for-the-badge&logo=leetcode)](https://leetcode.com/problems/rearranging-fruits)
[![Difficulty](https://img.shields.io/badge/Difficulty-Hard-FF5733?style=for-the-badge)](https://leetcode.com/problems/rearranging-fruits)
[![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> ⚡️ **Educational Use Only:** > This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> The problem statement and test cases are based on the [LeetCode problem](https://leetcode.com/problems/rearranging-fruits).

---

## 📝 Problem Statement

You have two fruit baskets containing **n** fruits each. You are given two **0-indexed** integer arrays `basket1` and `basket2` representing the cost of fruit in each basket. You want to make both baskets **equal**. To do so, you can use the following operation as many times as you want:

- Choose two indices `i` and `j`, and swap the `i`-th fruit of `basket1` with the `j`-th fruit of `basket2`.
- The cost of the swap is `min(basket1[i], basket2[j])`.

Two baskets are considered **equal** if sorting them according to the fruit cost makes them exactly the same baskets.

Return _the minimum cost to make both the baskets equal or -1 if impossible._

---

## 🎨 Examples

### Example 1:

| Input                                        | Output |
| :------------------------------------------- | :----- |
| `basket1 = [4,2,2,2]`, `basket2 = [1,4,1,2]` | `1`    |

<details>
<summary><strong>Example Walkthrough</strong></summary>
Swap index 1 of `basket1` (value 2) with index 0 of `basket2` (value 1). The cost is `min(2, 1) = 1`.

After the swap:

- `basket1` becomes `[4,1,2,2]`
- `basket2` becomes `[2,4,1,2]`

If we sort both baskets, they become `[1,2,2,4]`, which are equal. The total cost is 1.

</details>

### Example 2:

| Input                                        | Output |
| :------------------------------------------- | :----- |
| `basket1 = [2,3,4,1]`, `basket2 = [3,2,5,1]` | `-1`   |

<details>
<summary><strong>Example Walkthrough</strong></summary>
Let's count the total fruits of each type across both baskets:
- Fruit `1`: Two
- Fruit `2`: Two
- Fruit `3`: Two
- Fruit `4`: One
- Fruit `5`: One

Since fruits `4` and `5` have an odd total count (1), it's impossible to distribute them equally between the two baskets. Therefore, we return -1.

</details>

---

## ⛓️ Constraints

- `basket1.length == basket2.length`
- $1 \le basket1.length \le 10^5$
- $1 \le basket1[i], basket2[i] \le 10^9$

---

## 🛠️ Approach

The core idea is to find the "imbalance" of fruits between the two baskets and then resolve it with the minimum cost.

1.  **Count Imbalance**: Use a map to count the net frequency of each fruit. Iterate through `basket1` and increment the count for each fruit, then iterate through `basket2` and decrement the count.
2.  **Check Possibility**: If any fruit's final count in the map is **odd**, it's impossible to make the baskets equal (an odd count means the total number of that fruit across both baskets is odd, so it can't be split evenly). In this case, return `-1`. Also, find the globally minimum fruit cost (`minEl`) across both baskets.
3.  **Identify Fruits to Swap**: For every fruit with a non-zero net count, the value `abs(count) / 2` tells us how many of that fruit need to be moved from one basket to the other to achieve balance. Collect these fruits into a list, let's call it `finalList`.
4.  **Greedy Swapping Strategy**: To minimize the total swap cost, we should focus on swapping the cheapest misplaced fruits. The `finalList` contains all fruits that need to be moved. Half of them are from `basket1` (surplus) and half are from `basket2` (surplus). To make the baskets equal, we need to swap the surplus from `basket1` with the surplus from `basket2`. The cheapest way to do this is to swap the smallest surplus fruits.
5.  **Calculate Minimum Cost**:
    - We isolate the smaller half of the fruits in `finalList`. These are the fruits we want to "give away" in swaps.
    - For each such fruit `x`, we have two options to swap it:
      - **Direct Swap**: Swap it with a more expensive fruit from the other side. The cost will be `x`.
      - **Indirect Swap**: Swap `x` with the globally minimum fruit `minEl`, and then swap that `minEl` into the other basket. The total cost for this two-step process is `2 * minEl`.
    - We greedily choose the cheaper of the two options for each fruit in the smaller half: `min(x, 2 * minEl)`.
    - The total minimum cost is the sum of these individual minimum swap costs.

---

## 💻 Solution Code (C++)

```cpp
// Intuition: The goal is to make two baskets identical by swapping fruits with minimum cost. This means we first need to identify which fruits are "in surplus" in one basket and "in deficit" in the other. Then, we need to perform swaps to balance these counts. The minimum cost is achieved by a greedy strategy.

// Approach:
// 1. Count Frequencies: Use an unordered_map to calculate the net frequency of each fruit across both baskets. Increment for basket1, decrement for basket2.
// 2. Find Global Minimum: While iterating, find the minimum fruit cost (`minEl`) across both baskets. This will be useful for an alternative swapping strategy.
// 3. Check Feasibility: Iterate through the map. If any fruit's net count is odd, it's impossible to make the baskets equal (since the total count of that fruit is odd). Return -1.
// 4. Identify Swaps: For any fruit with a non-zero even count `c`, it means `abs(c)/2` of that fruit needs to be moved from one basket to another. Collect these fruits into a `finalList`.
// 5. Isolate Fruits to Move: We have a list of fruits that are on the wrong side. To balance, we need to swap the `finalList.size()/2` smallest fruits from this list with the `finalList.size()/2` largest fruits. We only need to consider the cost of moving the smaller half.
// 6. Greedy Cost Calculation: For each fruit `x` in the smaller half of `finalList`, we have two swap options:
//    a. Direct Swap: Swap `x` with a larger fruit `y`. The cost is `min(x, y) = x`.
//    b. Indirect Swap: Use the globally cheapest fruit `minEl` as an intermediary. The cost is `2 * minEl`.
// 7. The minimum cost for swapping `x` is `min(x, 2 * minEl)`.
// 8. Sum up these minimum costs for all fruits in the smaller half of `finalList`. Using `nth_element` is an optimization over full sorting to find this smaller half in linear average time.

// Time Complexity: O(N), where N is the number of fruits in a basket. Building the map takes O(N). Iterating the map takes O(U) where U is the number of unique fruits. `nth_element` is O(U) on average.
// Space Complexity: O(U), for the map and the `finalList`. In the worst case, U can be up to 2N, so O(N).

class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        // Map to store frequency difference of fruits
        unordered_map<int, int> mp;
        int minEl = INT_MAX; // To store the global minimum fruit cost

        // Step 1: Count fruits in basket1 and find the global minimum
        for(int &x : basket1) {
            mp[x]++;
            minEl = min(minEl, x);
        }

        // Step 2: Decrement counts for basket2 and update the global minimum
        for(int &x : basket2) {
            mp[x]--;
            minEl = min(minEl, x);
        }

        vector<int> finalList; // List of fruits that need to be swapped
        // Step 3 & 4: Check for impossibility and create the list of fruits to be swapped
        for(auto &it : mp) {
            int cost = it.first;
            int count = it.second;

            if(count == 0) continue; // Fruit counts are already balanced
            // If count is odd, it's impossible to balance
            if(count % 2 != 0) return -1;
            // For a net count of 'count', we need to move abs(count)/2 fruits
            for(int c = 1; c <= abs(count)/2; c++) {
                finalList.push_back(cost);
            }
        }

        // Step 5: Partition the list to get the smaller half of fruits that need swapping.
        // nth_element is an optimization over a full sort. It places the element that would
        // be at the n-th position in a sorted array at that position. All elements before it
        // are less than or equal to it.
        nth_element(finalList.begin(), finalList.begin() + finalList.size()/2, finalList.end());

        long long result = 0;
        // Step 6 & 7: Calculate the minimum cost by swapping the smaller half of the fruits.
        for(int i = 0; i < finalList.size()/2; i++) {
            // For each fruit, choose the cheaper swap: direct (cost = fruit value) or
            // indirect via the global minimum element (cost = 2 * minEl).
            result += min((long long)finalList[i], (long long)minEl*2);
        }

        return result;
    }
};

/*
 *
 * Dry Run
 * basket1 = [4, 2, 2, 2], basket2 = [1, 4, 1, 2]
 *
 * 1. Build map from basket1: mp = {4:1, 2:3}. minEl = 2.
 * 2. Update map from basket2:
 * - x=1: mp[1]-- -> mp={4:1, 2:3, 1:-1}. minEl=min(2,1)=1.
 * - x=4: mp[4]-- -> mp={4:0, 2:3, 1:-1}. minEl=1.
 * - x=1: mp[1]-- -> mp={4:0, 2:3, 1:-2}. minEl=1.
 * - x=2: mp[2]-- -> mp={4:0, 2:2, 1:-2}. minEl=1.
 * Final map: mp = {4:0, 2:2, 1:-2}. Final minEl = 1.
 *
 * 3. Create finalList:
 * - it = {4:0}: skip.
 * - it = {2:2}: count is 2. abs(2)/2 = 1. finalList.push_back(2). finalList becomes [2].
 * - it = {1:-2}: count is -2. abs(-2)/2 = 1. finalList.push_back(1). finalList becomes [2, 1].
 *
 * 4. Partition finalList:
 * - finalList = [2, 1]. size = 2. size/2 = 1.
 * - nth_element(begin, begin+1, end).
    * This will rearrange finalList to something like [1, 2].
 *
 * 5. Calculate result:
 * - Loop from i = 0 to (2/2) - 1 = 0. So, just the i=0 case.
 * - i = 0: result += min((long long)finalList[0], (long long)minEl*2)
 * result += min((long long)1, (long long)1*2)
 * result += min(1, 2)
 * result += 1.
 *
 * 6. Return result: 1.
 *
 */
```

---

## 💡 Key Insights

- **Impossibility Condition**: The total count of each fruit across _both_ baskets must be even. If any fruit type has an odd total count, it's impossible to distribute them equally.
- **Swaps are Paired**: If there's an imbalance of `2k` total fruits (e.g., `k` extra 'apples' in one basket and `k` extra 'oranges' in the other), only `k` swaps are needed to resolve the imbalance.
- **Two-Way Swap Trick**: The minimum cost to swap out a fruit `A` is not just its own value. We can use the globally minimum fruit (`minEl`) as an intermediary. The cost is the minimum of a direct swap (`cost(A)`) versus an indirect swap (`2 * cost(minEl)`). This greedy choice minimizes the cost for each necessary swap.

---

## 🧭 Further Exploration

- [LeetCode 1247. Minimum Swaps to Make Strings Equal](https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/)
- [LeetCode 2121. Intervals Between Identical Elements](https://leetcode.com/problems/intervals-between-identical-elements/)

---

## 📚 References

- [Original LeetCode Problem](https://leetcode.com/problems/rearranging-fruits)
- [C++ nth_element](https://en.cppreference.com/w/cpp/algorithm/nth_element)

---

## 👨‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Greedy` `Hash Map` `Sorting` `Math`

---

## 📜 License

This project is licensed under the MIT License. See the `LICENSE` file for details.

> **Reminder:** The solutions and explanations are for educational purposes only and are designed to help you learn and practice problem-solving techniques.
