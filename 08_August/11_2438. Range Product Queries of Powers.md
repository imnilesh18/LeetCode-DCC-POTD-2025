<div align="center">

# ✨ 2438. Range Product Queries of Powers ✨

</div>

<div align="center">

[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge&logo=leetcode)](https://leetcode.com/problems/range-product-queries-of-powers/)
[![Category](https://img.shields.io/badge/Category-Bit%20Manipulation-green?style=for-the-badge)](https://leetcode.com/tag/bit-manipulation/)
[![Category](https://img.shields.io/badge/Category-Array-blue?style=for-the-badge)](https://leetcode.com/tag/array/)
[![Category](https://img.shields.io/badge/Category-Prefix%20Sum-orange?style=for-the-badge)](https://leetcode.com/tag/prefix-sum/)

</div>

---

## 🎯 Problem Statement

> Given a positive integer `n`, there exists a 0-indexed array called `powers`, composed of the minimum number of powers of 2 that sum to `n`. The array is sorted in non-decreasing order, and there is only one way to form the array.
>
> You are also given a 0-indexed 2D integer array `queries`, where `queries[i] = [lefti, righti]`. Each `queries[i]` represents a query where you have to find the product of all `powers[j]` with `lefti <= j <= righti`.
>
> Return an array `answers`, equal in length to `queries`, where `answers[i]` is the answer to the i-th query. Since the answer may be large, each `answers[i]` should be returned **modulo** 10<sup>9</sup> + 7.

---

## ⚙️ Constraints

- `1 <= n <= 10^9`
- `1 <= queries.length <= 10^5`
- `0 <= lefti <= righti < powers.length`

---

## 📊 Examples

| Input                                   | Output     | Explanation                                                                                                               |
| --------------------------------------- | ---------- | ------------------------------------------------------------------------------------------------------------------------- |
| `n = 15, queries = [[0,1],[2,2],[0,3]]` | `[2,4,64]` | For n = 15, `powers` = [1,2,4,8]. <br> Query [0,1]: 1 _ 2 = 2. <br> Query [2,2]: 4. <br> Query [0,3]: 1 _ 2 _ 4 _ 8 = 64. |
| `n = 2, queries = [[0,0]]`              | `[2]`      | For n = 2, `powers` = [2]. <br> The answer to the only query is `powers[0]` = 2.                                          |

---

## 🧠 Approach & Intuition

The problem's description of the `powers` array as the "minimum number of powers of 2 that sum to n" is a classic pointer towards the **binary representation** of `n`. Every integer has a unique decomposition into a sum of powers of two, which corresponds to the '1's in its binary form.

For instance, `n = 15` is `1111` in binary. This translates to:
`15 = 8 + 4 + 2 + 1 = 2^3 + 2^2 + 2^1 + 2^0`

The elements `[1, 2, 4, 8]` are precisely the `powers` array we need.

<details>
<summary>Click for Step-by-Step Breakdown</summary>

1.  **Construct the `powers` Array**:

    - We iterate through the bits of `n` from `i = 0` to `31`. A 32-bit integer is sufficient since `n <= 10^9`.
    - For each bit `i`, we check if it is "set" (i.e., equals 1). The bitwise operation `(n & (1 << i)) != 0` does this perfectly. `(1 << i)` creates a mask for the i-th bit (e.g., `...00100`).
    - If the bit is set, `2^i` is a component of `n`, so we add `2^i` to our `powers` array.
    - Since we check bits from right to left (least significant to most significant), the resulting `powers` array is automatically sorted.

2.  **Process Queries**:
    - With the `powers` array built, the rest is straightforward. For each query `[left, right]`, we need to compute the product of `powers[left]` through `powers[right]`.
    - We initialize a `product` variable to 1 and loop from `left` to `right`.
    - In each iteration, we multiply the `product` by the current `powers` element and apply the modulo `10^9 + 7`. This prevents the number from becoming too large and causing an overflow.

</details>

This strategy is highly efficient because the `powers` array will have at most 32 elements, making the subsequent query processing very fast.

---

## 💻 Solution Code

C++ Code & Dry Run

```cpp
// Intuition: The core idea is that the `powers` array, described as the minimum number of powers of 2 that sum to `n`,
// is simply the set of powers of 2 corresponding to the set bits in `n`'s binary representation.
// For example, if `n=15` (binary `1111`), the `powers` array is `[2^0, 2^1, 2^2, 2^3]`, which is `[1, 2, 4, 8]`.

// Approach:
// 1. Initialize an empty `powers` array to store the powers of 2.
// 2. Iterate through the bits of `n` from 0 to 31.
// 3. For each bit `i`, check if it's set in `n` using the bitwise AND operation `(n & (1 << i))`.
// 4. If the `i`-th bit is set, it means `2^i` is part of the sum, so push `2^i` (which is `1 << i`) into the `powers` array.
// 5. The array will be inherently sorted as we iterate from the 0th bit upwards.
// 6. Iterate through each query `[start, end]`.
// 7. For each query, calculate the product of elements in `powers` from index `start` to `end`.
// 8. Apply the modulo operator (`% M`) at each multiplication step to prevent overflow.
// 9. Store the final product for the query in the `result` array.
// 10. Return the `result` array.

// Time Complexity: O(log(n) + Q * log(n)). Building the `powers` array takes O(log n) time.
// Each of the Q queries takes at most O(log n) time as the `powers` array size is at most ~32.
// This can be simplified to O(Q * log(n)) or just O(Q) since log(n) is a small constant.

// Space Complexity: O(log n) to store the `powers` array. The size depends on the number of set bits in n, which is at most ~32.
// This is often considered O(1) constant space.

class Solution {
public:
    int M = 1e9 + 7; // Define the modulo constant

    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> powers; // This will store the powers of 2 that sum to n
        vector<int> result; // This will store the answers to the queries

        // Step 1: Build the 'powers' array from the bits of n
        for (int i = 0; i < 32; i++) {
            // Check if the i-th bit of n is set using a bitwise AND
            if ((n & (1 << i)) != 0) { // The expression (1 << i) calculates 2^i
                // If the bit is set, add the corresponding power of 2 to our array
                powers.push_back(1 << i);
            }
        }

        // Step 2: Process each query
        for (auto& query : queries) {
            int start = query[0]; // Get the start index of the range
            int end = query[1];   // Get the end index of the range

            long long product = 1; // Use long long to prevent intermediate overflow before modulo
            // Iterate from the start to the end index of the 'powers' array
            for (int i = start; i <= end; i++) {
                // Multiply the current product by the power at index i
                product = (product * powers[i]) % M; // Apply modulo at each step
            }

            // Add the final computed product for the query to the result vector
            result.push_back(product);
        }

        // Return the final list of answers
        return result;
    }
};

/*
*
* -----------------
* |   Dry Run 🏃‍♂️  |
* -----------------
*
* Input: n = 15, queries = [[0,1], [2,2], [0,3]]
* M = 1e9 + 7
*
* 1. Build `powers` array for n = 15:
* - n = 15 in binary is `...0001111`.
* - i = 0: (15 & 1) -> true. powers.push_back(1). `powers` = [1]
* - i = 1: (15 & 2) -> true. powers.push_back(2). `powers` = [1, 2]
* - i = 2: (15 & 4) -> true. powers.push_back(4). `powers` = [1, 2, 4]
* - i = 3: (15 & 8) -> true. powers.push_back(8). `powers` = [1, 2, 4, 8]
* - Final `powers` array: [1, 2, 4, 8]
*
* 2. Process queries:
* - Query 1: [0, 1]
* - product = (1 * powers[0]) * powers[1] = 1 * 2 = 2.
* - result.push_back(2). `result` = [2]
*
* - Query 2: [2, 2]
* - product = powers[2] = 4.
* - result.push_back(4). `result` = [2, 4]
*
* - Query 3: [0, 3]
* - product = powers[0] * powers[1] * powers[2] * powers[3]
* - product = 1 * 2 * 4 * 8 = 64.
* - result.push_back(64). `result` = [2, 4, 64]
*
* 3. Final Return: [2, 4, 64]
*
*/
```

---

## 🚀 Key Insights & Further Exploration

### 💡 Key Insights:

- The "minimum number of powers of 2" is a direct hint for binary representation. Recognizing this simplifies the problem immensely.
- Bitwise operations (`&`, `<<`) are the most efficient way to work with the binary components of integers.

### 🔭 Further Exploration (Prefix Products Optimization):

For an even faster solution, especially with a massive number of queries, we can use a **Prefix Product** array.

1.  **Preprocessing**: After building the `powers` array, create a `prefix_products` array where `prefix_products[i]` holds the product of `powers[0]...powers[i]` (all modulo `M`).
2.  **Querying**: To find the product of a range `[left, right]`, you would normally compute `prefix_products[right] / prefix_products[left - 1]`. In modular arithmetic, division is done by multiplying with the **modular multiplicative inverse**.
3.  **O(1) Queries**: A query can be answered in `O(1)` time using the formula `(prefix_products[right] * modInverse(prefix_products[left - 1])) % M`.

This would reduce the total time complexity to `O(log(n) + Q)`, which is a substantial improvement.

---

## 🔗 References

- [LeetCode Problem](https://leetcode.com/problems/range-product-queries-of-powers/)
- [Bitwise Operations Explained](https://en.wikipedia.org/wiki/Bitwise_operation)
- [Modular Multiplicative Inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse)

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/range-product-queries-of-powers/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
