# 1304. Find N Unique Integers Sum up to Zero

<div align="center">
    <a href="https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/description/">
        <img src="https://img.shields.io/badge/Problem%20Link-0077B5?style=for-the-badge&logo=leetcode&logoColor=white" alt="Problem Link">
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy">
    <img src="https://img.shields.io/badge/Topic-Array-blue?style=for-the-badge&logo=cplusplus" alt="Topic: Array">
    <img src="https://img.shields.io/badge/Topic-Math-blueviolet?style=for-the-badge&logo=cplusplus" alt="Topic: Math">
</div>

---

## 📝 Problem Statement

Given an integer `n`, return **any** array containing `n` **unique** integers such that they add up to 0.

---

## 📊 Examples

Here are the examples provided:

| Input | Output | Explanation |
| :--- | :--- | :--- |
| `n = 5` | `[-7,-1,1,3,4]` | These arrays are also accepted: `[-5,-1,1,2,3]`, `[-3,-1,2,-2,4]`. |
| `n = 3` | `[-1,0,1]` | A simple balanced array. |
| `n = 1` | `[0]` | The only single integer that sums to zero is 0. |

---

## 🧠 Constraints

- $1 \le n \le 1000$

---

## 💡 Approach Explanation

The core requirement of this problem is to generate `n` **unique** integers that sum to **zero**. Since the problem asks for *any* valid array, we can choose the simplest possible mathematical pattern.

The easiest way to guarantee a sum of zero is by using **additive inverses**. For any non-zero integer $x$, its inverse $-x$ will cancel it out, (i.e., $x + (-x) = 0$).

Our strategy will be to fill the array with as many unique pairs of $(x, -x)$ as possible.

This leaves one special case: what happens if `n` is an **odd** number?

If `n` is odd (e.g., $n=5$), we can't perfectly pair all elements. However, we can create pairs for $n-1$ elements (which is an even number) and fill the last remaining slot with the integer **0**. The number 0 does not change the sum and will be unique (since we start our pairs from 1).

**Example for n = 5:**
We can use the pairs $(1, -1)$ and $(2, -2)$. This gives us 4 unique elements: `[1, -1, 2, -2]`. We have one slot left, which we fill with `0`. The final array `[1, -1, 2, -2, 0]` contains 5 unique integers and sums to 0.

We can implement this logic using two primary (and equally efficient) methods:

<details>
<summary><b>Approach 1: Linear Pair Fill (Iterating i += 2)</b></summary>
<br>
We can iterate through the array from the beginning, filling pairs as we go.

1.  Initialize the result array of size `n` (which defaults to all zeros in C++/Java).
2.  Start an index `i = 0` and a number `start = 1`.
3.  Loop while `i + 1 < n`. This condition cleverly ensures we only operate if we have space for a full pair (`i` and `i+1`).
4.  Inside the loop, set `result[i] = start` and `result[i+1] = -start`.
5.  Increment `start` (for the next unique pair) and increment the index by two (`i += 2`).
6.  **Odd Case (n=5):**
    - `i=0`: Fills `[1, -1, 0, 0, 0]`. Loop continues.
    - `i=2`: Fills `[1, -1, 2, -2, 0]`. Loop continues.
    - `i=4`: The loop check `(4 + 1 < 5)` fails. The loop terminates.
7.  The last element (at index 4) retains its default initialized value of `0`.
</details>

<details>
<summary><b>Approach 2: Two Pointers (Symmetric Fill)</b></summary>
<br>
We can fill the array symmetrically from both ends simultaneously.

1.  Initialize the result array of size `n` (defaulting to all zeros).
2.  Set two pointers: a `left` pointer `i = 0` and a `right` pointer `j = n - 1`.
3.  Start a number `start = 1`.
4.  Loop while `i < j`.
5.  Set `result[i] = start` and `result[j] = -start`.
6.  Increment `start`, and move both pointers inward (`i++`, `j--`).
7.  **Odd Case (n=5):**
    - `i=0, j=4`: Fills `[1, 0, 0, 0, -1]`. Pointers move to `i=1, j=3`.
    - `i=1, j=3`: Fills `[1, 2, 0, -2, -1]`. Pointers move to `i=2, j=2`.
    - `i=2, j=2`: The loop check `(i < j)` (i.e., `2 < 2`) fails. The loop terminates.
8.  The middle element (at index 2) was never touched and retains its default initialized value of `0`.
</details>

---

## 💻 Solution Code (Approach 1: Linear Fill)

```cpp
// Intuition: To make n unique integers sum to zero, we can use the property of additive inverses. Any number 'x' and its negative '-x' sum to 0. We can create pairs (1, -1), (2, -2), etc.
// Approach:
// 1. Create a result vector of size 'n', which defaults to all zeros.
// 2. Initialize a counter 'start = 1'.
// 3. Iterate through the array with an index 'i', jumping two steps at a time (i += 2).
// 4. The loop condition 'while(i + 1 < n)' ensures we only process full pairs.
// 5. For each valid 'i', set result[i] = start and result[i+1] = -start.
// 6. Increment 'start' to ensure the next pair is unique (e.g., 2 and -2).
// 7. If 'n' is odd (e.g., n=5), the loop will stop when 'i' points to the last element (i=4). Since (4+1 < 5) is false, the loop terminates.
// 8. The last element retains its default initialized value of 0.
// 9. The final array (e.g., [1, -1, 2, -2, 0]) sums to zero and contains unique integers.
// Time Complexity: O(n) - We iterate roughly n/2 times (visiting each element once) to fill the array.
// Space Complexity: O(1) - Auxiliary space. The O(n) space for the result vector is not counted as extra space.

//Approach-1 (iterate linear)
//T.C : O(n) 
//S.C : O(1)
class Solution {
public:
    vector<int> sumZero(int n) {
        // Create the result vector of size n, initialized with all zeros.
        vector<int> result(n);

        int start = 1; // Start our unique pairs from 1
        int i = 0;     // Initialize the index
        
        // Loop while there is space for a pair (at index i and i+1)
        while(i+1 < n) { 
            result[i] = start;    // Set the positive part of the pair
            result[i+1] = -start; // Set the negative part (additive inverse)

            i+= 2;      // Jump forward two positions to the next empty slot for a pair
            start++;     // Increment start for the next unique pair (e.g., 2, then 3, ...)
        }

        // If n is odd, the loop terminates leaving the last element as 0 (from initialization).
        // Example n=5:
        // i=0: result=[1, -1, 0, 0, 0], i=2, start=2
        // i=2: result=[1, -1, 2, -2, 0], i=4, start=3
        // i=4: Loop check (4+1 < 5) fails. Loop terminates.
        // Final result: [1, -1, 2, -2, 0]

        return result; // Return the constructed array
    }
};

/*
*
* Dry Run
* Input: n = 5
* 1. vector<int> result(5); // result = [0, 0, 0, 0, 0]
* 2. start = 1, i = 0
* 3. Loop 1 (while i+1 < n):
* - Check: (0+1 < 5) -> true.
* - result[0] = 1
* - result[1] = -1
* - // result is now [1, -1, 0, 0, 0]
* - i += 2; // i becomes 2
* - start++; // start becomes 2
* 4. Loop 2 (while i+1 < n):
* - Check: (2+1 < 5) -> true.
* - result[2] = 2
* - result[3] = -2
* - // result is now [1, -1, 2, -2, 0]
* - i += 2; // i becomes 4
* - start++; // start becomes 3
* 5. Loop 3 (while i+1 < n):
* - Check: (4+1 < 5) -> (5 < 5) is false.
* - Loop terminates.
* 6. Return result: [1, -1, 2, -2, 0]
*
* Input: n = 4
* 1. result = [0, 0, 0, 0], start = 1, i = 0
* 2. Loop 1 (0+1 < 4) -> true.
* - result = [1, -1, 0, 0]
* - i = 2, start = 2
* 3. Loop 2 (2+1 < 4) -> true.
* - result = [1, -1, 2, -2]
* - i = 4, start = 3
* 4. Loop 3 (4+1 < 4) -> false.
* 5. Return result: [1, -1, 2, -2]
*
*/
```

---

## 💻 Solution Code (Approach 2: Two Pointers)

```cpp
// Intuition: Similar to the first approach, we need to create (x, -x) pairs. We can fill these pairs symmetrically from both ends of the array inward.
// Approach:
// 1. Create the result vector of size 'n' (defaulting to all zeros).
// 2. Initialize two pointers: 'i' at the start (0) and 'j' at the end (n-1).
// 3. Initialize a counter 'start = 1'.
// 4. Loop as long as the start pointer is less than the end pointer (while i < j).
// 5. In each iteration, set the start position: result[i] = start.
// 6. Set the end position: result[j] = -start (the additive inverse).
// 7. Increment 'start' for the next unique pair.
// 8. Move the pointers inward: i++ and j--.
// 9. If 'n' is odd (e.g., n=5), the pointers will eventually meet (i=2, j=2). The loop (i < j) terminates.
// 10. The center element (where i == j) is never touched by the loop and retains its default value of 0.
// Time Complexity: O(n) - We iterate n/2 times, performing O(1) work.
// Space Complexity: O(1) - Auxiliary space. (O(n) if counting the output array).

//Approach-2 (two pointer)
//T.C : O(n) 
//S.C : O(1)
class Solution {
public:
    vector<int> sumZero(int n) {
        // Create result vector of size n, initialized to all zeros
        vector<int> result(n);

        int i = 0;       // Left pointer (starts at the beginning)
        int j = n-1;     // Right pointer (starts at the end)
        int start = 1;   // The value to insert (starting with 1)

        // Loop while the left pointer is strictly less than the right pointer
        while(i < j) {
            result[i] = start;   // Place the positive value at the left
            result[j] = -start;  // Place the negative (inverse) value at the right
            
            start++; // Increment the value for the next pair (2, 3, ...)

            i++; // Move left pointer right
            j--; // Move right pointer left
        }

        // If n is odd (e.g., n=5):
        // 1. i=0, j=4. result=[1, 0, 0, 0, -1]. start=2, i=1, j=3.
        // 2. i=1, j=3. result=[1, 2, 0, -2, -1]. start=3, i=2, j=2.
        // 3. Loop check (i < j) -> (2 < 2) is false. Loop terminates.
        // The middle element (result[2]) remains 0.
        
        // If n is even (e.g., n=4):
        // 1. i=0, j=3. result=[1, 0, 0, -1]. start=2, i=1, j=2.
        // 2. i=1, j=2. result=[1, 2, -2, -1]. start=3, i=2, j=1.
        // 3. Loop check (i < j) -> (2 < 1) is false. Loop terminates.

        return result; // Return the completed array
    }
};

/*
*
* Dry Run
* Input: n = 5
* 1. result = [0, 0, 0, 0, 0]
* 2. i = 0, j = 4, start = 1
* 3. Loop 1 (while i < j):
* - Check: (0 < 4) -> true.
* - result[0] = 1
* - result[4] = -1
* - // result is [1, 0, 0, 0, -1]
* - start = 2, i = 1, j = 3
* 4. Loop 2 (while i < j):
* - Check: (1 < 3) -> true.
* - result[1] = 2
* - result[3] = -2
* - // result is [1, 2, 0, -2, -1]
* - start = 3, i = 2, j = 2
* 5. Loop 3 (while i < j):
* - Check: (2 < 2) -> false.
* - Loop terminates.
* 6. Return result: [1, 2, 0, -2, -1] (This is a valid answer)
*
*/
```

---

## 🔑 Key Insights

* **Additive Inverse:** The core idea hinges on the mathematical property that $x + (-x) = 0$.
* **Handling the Odd Case:** Both approaches automatically handle an odd `n` by relying on the default 0-initialization of the array/vector. The loop terminates just before processing the final (or middle) element, leaving it as 0. This completes the array correctly as 0 is unique (we start pairs from 1) and does not affect the sum.
* **"Any" Solution:** The problem's prompt specifies returning *any* valid array, which signals that we should find the simplest, most straightforward pattern rather than a complex algorithm.

---

## 🔗 References

* **LeetCode Problem:** [https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/](https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/)
* **Concept:** Additive Inverse in Mathematics

---

## 🏷️ Tags

- Array
- Math
- Two Pointers

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)