<div align="center">
  <h1>2348. Number of Zero-Filled Subarrays 🎲</h1>
  <a href="https://leetcode.com/problems/number-of-zero-filled-subarrays/">
    <img src="https://img.shields.io/badge/LeetCode-Link-blue?style=for-the-badge&logo=leetcode" alt="LeetCode Link">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blueviolet?style=for-the-badge&logo=c%2B%2B" alt="Language: C++">
</div>

---

## 📝 Problem Statement

Given an integer array `nums`, return the number of subarrays filled with `0`. A subarray is a contiguous non-empty sequence of elements within an array.

---

## ⚙️ Constraints

- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

---

## Egs. Examples

<details>
<summary><b>Example 1</b></summary>
<br>

| Input                      | Output | Explanation                                                                                                                                                     |
| :------------------------- | :----: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `nums = [1,3,0,0,2,0,0,4]` |   6    | There are 4 occurrences of `[0]` as a subarray. There are 2 occurrences of `[0,0]` as a subarray. No subarray with a size > 2 filled with 0. Total = 4 + 2 = 6. |

</details>

<details>
<summary><b>Example 2</b></summary>
<br>

| Input                  | Output | Explanation                                                           |
| :--------------------- | :----: | :-------------------------------------------------------------------- |
| `nums = [0,0,0,2,0,0]` |   9    | There are 5 `[0]`, 3 `[0,0]`, and 1 `[0,0,0]`. Total = 5 + 3 + 1 = 9. |

</details>

<details>
<summary><b>Example 3</b></summary>
<br>

| Input                | Output | Explanation                |
| :------------------- | :----: | :------------------------- |
| `nums = [2,10,2019]` |   0    | No subarray filled with 0. |

</details>

---

## 🧠 Approach

The core idea is to find contiguous blocks of zeros. For any block of `k` consecutive zeros, the number of zero-filled subarrays it can form is the sum of integers from 1 to `k`, which is calculated by the formula `k * (k + 1) / 2`.

We can solve this in two main ways:

1.  **Mathematical Approach**: Iterate through the array. Whenever we find a `0`, we start an inner loop to count how many consecutive zeros (`k`) there are. Once the sequence of zeros ends, we calculate the number of subarrays using the formula `k * (k + 1) / 2` and add it to our total result. We then continue our outer loop from where the zero sequence ended.

2.  **Iterative Counting Approach**: A more streamlined approach is to iterate through the array once. We maintain a counter for the current number of consecutive zeros. If the current element is `0`, we increment this counter. If it's a non-zero number, we reset the counter to `0`. At each step, we add the current value of the consecutive zero counter to our total result. This works because a new zero adds itself as a subarray and also forms new subarrays with all the preceding consecutive zeros.

For example, with `[0, 0, 0]`:

- First `0`: `count = 1`. `total = 1`. (Subarray: `[0]`)
- Second `0`: `count = 2`. `total = 1 + 2 = 3`. (New subarrays: `[0,0]` and the second `[0]`)
- Third `0`: `count = 3`. `total = 3 + 3 = 6`. (New subarrays: `[0,0,0]`, `[0,0]` starting at index 1, and the third `[0]`)

Both approaches are efficient with a time complexity of O(n) and use constant extra space.

---

## 💻 Solution Code

### Brute Force Solution (Mathematical Approach)

```cpp
// Intuition: The problem asks for the total number of subarrays that are filled only with zeros.
// A contiguous block of 'k' zeros can form k*(k+1)/2 such subarrays.
// We can iterate through the array, find each block of consecutive zeros, calculate the number of subarrays for that block, and sum them up.
// Approach:
// 1. Initialize a 'result' counter to 0.
// 2. Iterate through the input array 'nums' with an index 'i'.
// 3. If nums[i] is 0, start an inner loop to count the length of the contiguous block of zeros.
// 4. Let the length be 'zeros'.
// 5. Calculate the number of subarrays for this block using the formula: (zeros * (zeros + 1)) / 2.
// 6. Add this count to the 'result'.
// 7. Advance the main loop index 'i' to the end of the current zero block.
// 8. If nums[i] is not 0, simply increment 'i'.
// 9. Return the final 'result'.
// Time Complexity: O(n), as each element is visited at most once by the combined loops.
// Space Complexity: O(1), as we only use a few variables for counting.
//Approach-1 (Using simple math to calculate count of subarrays)
//T.C : O(n)
//S.C : O(1)
class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long result = 0; // Stores the total count of zero-filled subarrays

        int n = nums.size(); // Get the size of the array

        int i = 0; // Initialize the loop counter
        while(i < n) {

            long long zeros = 0; // Counter for consecutive zeros in the current block

            // Check if the current element is a zero to start counting
            if(nums[i] == 0) {

                // Inner loop to count all consecutive zeros from the current position
                while(i < n && nums[i] == 0) {
                    i++; // Move to the next element
                    zeros++; // Increment the zero counter
                }

            } else {
                // If the element is not zero, just move to the next one
                i++;
            }
            // A block of 'zeros' count can form (zeros * (zeros + 1)) / 2 subarrays
            result += (zeros)*(zeros+1)/2;
        }

        return result; // Return the total count

    }
};

/*
*
* Dry Run
*
* Input: nums = [1, 3, 0, 0, 2, 0, 0, 4]
*
* Initial State:
* result = 0
* i = 0
*
* Loop 1 (i=0): nums[0] is 1. 'else' block runs. i becomes 1. zeros = 0. result = 0 + 0 = 0.
* Loop 2 (i=1): nums[1] is 3. 'else' block runs. i becomes 2. zeros = 0. result = 0 + 0 = 0.
* Loop 3 (i=2): nums[2] is 0. 'if' block runs.
* Inner while loop starts:
* - i=2, nums[2]==0: i becomes 3, zeros becomes 1.
* - i=3, nums[3]==0: i becomes 4, zeros becomes 2.
* - i=4, nums[4]==2: Inner loop terminates.
* Calculate subarrays: (2 * (2 + 1)) / 2 = 3.
* result = 0 + 3 = 3.
* Loop 4 (i=4): nums[4] is 2. 'else' block runs. i becomes 5. zeros = 0. result = 3 + 0 = 3.
* Loop 5 (i=5): nums[5] is 0. 'if' block runs.
* Inner while loop starts:
* - i=5, nums[5]==0: i becomes 6, zeros becomes 1.
* - i=6, nums[6]==0: i becomes 7, zeros becomes 2.
* - i=7, nums[7]==4: Inner loop terminates.
* Calculate subarrays: (2 * (2 + 1)) / 2 = 3.
* result = 3 + 3 = 6.
* Loop 6 (i=7): nums[7] is 4. 'else' block runs. i becomes 8. zeros = 0. result = 6 + 0 = 6.
*
* Main loop ends as i (8) is not less than n (8).
* Final Result: 6
*
*/
```

### Optimized Solution (Iterative Counting)

```cpp
// Intuition: We can count the subarrays by observing a pattern. When we encounter a sequence of zeros,
// each new zero adds a number of subarrays equal to its position in the sequence.
// For example, the first zero adds 1 subarray ([0]), the second adds 2 ([0,0] and the new [0]), the third adds 3, and so on.
// This simplifies the logic to a single pass.
// Approach:
// 1. Initialize 'result' (total count) and 'countSubArray' (current consecutive zeros) to 0.
// 2. Iterate through the array.
// 3. If the current element is 0, increment 'countSubArray'.
// 4. If the current element is not 0, it breaks the sequence, so reset 'countSubArray' to 0.
// 5. In each iteration, add the current value of 'countSubArray' to 'result'.
// 6. After the loop, return 'result'.
// Time Complexity: O(n), as we iterate through the array only once.
// Space Complexity: O(1), using only a couple of variables.
//Approach-2 (Better and clean approach using observation)
//T.C : O(n)
//S.C : O(1)
class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long result = 0; // To store the final count of zero-filled subarrays

        int n = nums.size(); // Size of the input array

        int countSubArray = 0; // To count consecutive zeros

        // Iterate through each element of the array
        for(int i = 0; i<n; i++) {

            // If the current element is 0, we extend the current subarray of zeros
            if(nums[i] == 0)
                countSubArray += 1; // Increment the consecutive zero counter
            else
                // If the element is non-zero, the sequence is broken
                countSubArray = 0; // Reset the counter

            // Add the count of new subarrays formed by the current zero to the result
            result += countSubArray;

        }

        return result; // Return the total count

    }
};

/*
*
* Dry Run
*
* Input: nums = [1, 3, 0, 0, 2, 0, 0, 4]
*
* Initial State:
* result = 0
* countSubArray = 0
*
* i = 0, nums[0] = 1: countSubArray = 0. result = 0 + 0 = 0.
* i = 1, nums[1] = 3: countSubArray = 0. result = 0 + 0 = 0.
* i = 2, nums[2] = 0: countSubArray = 1. result = 0 + 1 = 1.
* i = 3, nums[3] = 0: countSubArray = 2. result = 1 + 2 = 3.
* i = 4, nums[4] = 2: countSubArray = 0. result = 3 + 0 = 3.
* i = 5, nums[5] = 0: countSubArray = 1. result = 3 + 1 = 4.
* i = 6, nums[6] = 0: countSubArray = 2. result = 4 + 2 = 6.
* i = 7, nums[7] = 4: countSubArray = 0. result = 6 + 0 = 6.
*
* Loop finishes.
* Final Result: 6
*
*/
```

---

## 💡 Key Insights

- The problem can be broken down into finding contiguous blocks of zeros.
- The number of subarrays in a contiguous block of `k` identical elements is `1 + 2 + ... + k`, which simplifies to the formula `k * (k + 1) / 2`.
- An even more direct observation leads to an O(n) single-pass solution where you accumulate the length of the current zero-streak at each step.

---

## 🚀 Further Exploration

- Try solving similar problems like "Maximum Subarray" (LeetCode 53) or "Number of Substrings with Only 1s".
- Consider how the problem would change if you were looking for subarrays filled with any given number `x`, not just `0`.
- Think about a variation where you can change at most `m` non-zero elements to zero to maximize the number of zero-filled subarrays.

---

## 📚 References

- [LeetCode Problem: Number of Zero-Filled Subarrays](https://leetcode.com/problems/number-of-zero-filled-subarrays/)
- [Arithmetic Progression Sum Formula](https://en.wikipedia.org/wiki/Arithmetic_progression)

---

## #️⃣ Tags

`Array` `Math` `Subarray` `Counting`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/number-of-zero-filled-subarrays/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
