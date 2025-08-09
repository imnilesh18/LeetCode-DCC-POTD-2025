# 🟢 231. Power of Two

<p align="center">
  <a href="https://leetcode.com/problems/power-of-two/description/" target="_blank">
    <img src="https://img.shields.io/badge/LeetCode-Problem-orange?style=for-the-badge&logo=leetcode" alt="LeetCode Problem">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge" alt="Difficulty: Easy">
  <a href="https://github.com/imnilesh18/leetcode-dcc-potd-2025/blob/main/LICENSE" target="_blank">
    <img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge" alt="License: MIT">
  </a>
</p>

> ⚡️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [LeetCode problem](https://leetcode.com/problems/power-of-two/description/).

---

## 📜 Problem Statement

Given an integer `n`, return `true` if it is a power of two. Otherwise, return `false`.

An integer `n` is a power of two, if there exists an integer `x` such that $n = 2^x$.

---

## 📋 Examples

| Input    | Output | Explanation |
| :------- | :----- | :---------- |
| `n = 1`  | `true` | $2^0 = 1$     |
| `n = 16` | `true` | $2^4 = 16$    |
| `n = 3`  | `false`|             |
| `n = 0`  | `false`|             |
| `n = -8` | `false`|             |

<details>
<summary><strong>Example Walkthrough (n = 8)</strong></summary>

- **Is 8 a power of two?**
- We need to check if there is an integer `x` such that $2^x = 8$.
- We know $2^3 = 2 * 2 * 2 = 8$.
- Since such an `x` (which is 3) exists, the answer is `true`.
</details>

---

## 🛑 Constraints

- $-2^{31} \le n \le 2^{31} - 1$

---

## 🛠️ Approach

The problem asks us to determine if a given integer `n` can be expressed as 2 raised to some integer power `x`.

There are several ways to solve this, but the most elegant and efficient solution uses a bitwise trick.

1.  **Positive Check**: A power of two must be a positive number. So, any `n <= 0` cannot be a power of two.
2.  **Bitwise Insight**: A number that is a power of two (e.g., 1, 2, 4, 8, 16, ...) has a unique property in its binary representation: it consists of exactly **one '1' bit** followed by all '0's.
    - `8` in binary is `1000`
    - `16` in binary is `10000`
3.  **The `n & (n - 1)` Trick**: If we take a power-of-two number `n` and subtract 1 from it, the result `(n - 1)` will have all the bits flipped from the right up to that single '1' bit.
    - `n = 8` (binary `1000`)
    - `n - 1 = 7` (binary `0111`)
    - When we perform a bitwise AND (`&`) between `n` and `n-1`, the result is always `0`.
    - `1000 & 0111 = 0000`
4.  **Conclusion**: A number `n` is a power of two if and only if `n > 0` and `(n & (n - 1)) == 0`. This avoids loops and recursion, satisfying the follow-up question.

Other approaches include recursively dividing by 2 or using built-in functions to count set bits, but the bitwise AND trick is the most optimal.

---

## 💻 Solution Code

### Optimized Solution (Bit Manipulation)

#### C++
```cpp
// Intuition: A positive integer is a power of two if and only if it has exactly one '1' bit in its binary representation.
//            Subtracting 1 from a power of two flips the single '1' bit to '0' and all following '0's to '1's.
//            This means that the bitwise AND of a power of two and its predecessor is always zero.
// Approach: First, handle the edge case where n is not positive, as powers of two must be greater than 0.
//           Then, apply the bitwise trick: return true if (n & (n - 1)) == 0, otherwise false.
// Time Complexity: O(1), as it involves a few constant-time arithmetic and bitwise operations.
// Space Complexity: O(1), as no extra space is used.
class Solution {
public:
    bool isPowerOfTwo(int n) {
        // A power of two must be a positive number.
        // The bitwise AND of a power of two (e.g., 8 -> 1000) and its predecessor (7 -> 0111) is always 0.
        return (n > 0) && ((n & (n - 1)) == 0);
    }
};

/*
*
* Dry Run
*
* Example 1: n = 16
* 1. (n > 0) is (16 > 0) -> true.
* 2. n in binary is 10000.
* 3. n - 1 is 15, which is 01111 in binary.
* 4. (n & (n - 1)) -> (10000 & 01111) -> 00000.
* 5. (0 == 0) is true.
* 6. Final result: true && true -> true.
*
* Example 2: n = 12
* 1. (n > 0) is (12 > 0) -> true.
* 2. n in binary is 1100.
* 3. n - 1 is 11, which is 1011 in binary.
* 4. (n & (n - 1)) -> (1100 & 1011) -> 1000 (which is 8).
* 5. (8 == 0) is false.
* 6. Final result: true && false -> false.
*/
```

#### Java
```java
// Intuition: A positive integer is a power of two if and only if it has exactly one '1' bit in its binary representation.
//            Subtracting 1 from a power of two flips the single '1' bit to '0' and all following '0's to '1's.
//            This means that the bitwise AND of a power of two and its predecessor is always zero.
// Approach: First, handle the edge case where n is not positive, as powers of two must be greater than 0.
//           Then, apply the bitwise trick: return true if (n & (n - 1)) == 0, otherwise false.
// Time Complexity: O(1), as it involves a few constant-time arithmetic and bitwise operations.
// Space Complexity: O(1), as no extra space is used.
class Solution {
    public boolean isPowerOfTwo(int n) {
        // A power of two must be a positive number.
        // The bitwise AND of a power of two (e.g., 8 -> 1000) and its predecessor (7 -> 0111) is always 0.
        return (n > 0) && ((n & (n - 1)) == 0);
    }
}

/*
*
* Dry Run
*
* Example 1: n = 1
* 1. (n > 0) is (1 > 0) -> true.
* 2. n in binary is 0001.
* 3. n - 1 is 0, which is 0000 in binary.
* 4. (n & (n - 1)) -> (0001 & 0000) -> 0000.
* 5. (0 == 0) is true.
* 6. Final result: true && true -> true.
*
* Example 2: n = 6
* 1. (n > 0) is (6 > 0) -> true.
* 2. n in binary is 0110.
* 3. n - 1 is 5, which is 0101 in binary.
* 4. (n & (n - 1)) -> (0110 & 0101) -> 0100 (which is 4).
* 5. (4 == 0) is false.
* 6. Final result: true && false -> false.
*/
```

---

### Alternative Solutions

#### Recursive Solution
```cpp
// Intuition: A number is a power of two if it can be recursively divided by 2 until it becomes 1.
// Approach: Define base cases. If n is 0 or not positive, it's false. If n is 1, it's the base power of two (2^0), so it's true.
//           For other positive numbers, the number must be even (n % 2 == 0) and its half (n / 2) must also be a power of two.
// Time Complexity: O(log n), because with each recursive call, n is halved. The number of divisions is logarithmic.
// Space Complexity: O(log n), due to the recursion stack depth.
class Solution {
public:
    bool isPowerOfTwo(int n) {
        // Base case: Powers of two must be positive.
        if(n <= 0)
            return false;
        // Base case: 2^0 = 1, the smallest power of two.
        if(n == 1)
            return true;
        
        // A power of two must be even, and its half must also be a power of two.
        return n % 2 == 0 && isPowerOfTwo(n/2);
    }
};
/*
*
* Dry Run
*
* Example: n = 8
* 1. isPowerOfTwo(8): 8 > 1, 8 % 2 == 0. Returns isPowerOfTwo(4).
* 2. isPowerOfTwo(4): 4 > 1, 4 % 2 == 0. Returns isPowerOfTwo(2).
* 3. isPowerOfTwo(2): 2 > 1, 2 % 2 == 0. Returns isPowerOfTwo(1).
* 4. isPowerOfTwo(1): n == 1, returns true.
* The true value propagates back up the call stack, so the final result is true.
*
* Example: n = 6
* 1. isPowerOfTwo(6): 6 > 1, 6 % 2 == 0. Returns isPowerOfTwo(3).
* 2. isPowerOfTwo(3): 3 > 1, but 3 % 2 != 0. Returns false.
* The false value propagates back, and the final result is false.
*/
```

#### Built-in Popcount Solution
```cpp
// Intuition: As established, a power of two has exactly one bit set to '1' in its binary representation.
// Approach: Use the GCC built-in function `__builtin_popcount(n)` which efficiently counts the number of set bits (1s) in an integer.
//           First, check if n is positive. If so, return true if the popcount is exactly 1.
// Time Complexity: O(1) on most modern architectures due to hardware support, or O(log n) as it needs to check all bits.
// Space Complexity: O(1), no extra space required.
class Solution {
public:
    bool isPowerOfTwo(int n) {
        // A power of two must be a positive number.
        if(n <= 0)
            return false;
        
        // Use the built-in function to count set bits. For a power of two, it must be 1.
        return __builtin_popcount(n) == 1;
    }
};
/*
*
* Dry Run
*
* Example 1: n = 32
* 1. (n <= 0) is false.
* 2. Binary of 32 is 100000.
* 3. __builtin_popcount(32) returns 1.
* 4. (1 == 1) is true. Final result: true.
*
* Example 2: n = 24
* 1. (n <= 0) is false.
* 2. Binary of 24 is 11000.
* 3. __builtin_popcount(24) returns 2.
* 4. (2 == 1) is false. Final result: false.
*/
```

---

## 🧠 Key Insights

The core idea for the most optimal solution revolves around the binary structure of numbers.

- **Uniqueness of Powers of Two**: Numbers that are powers of two are unique in that they have only a single set bit. This is the fundamental property we exploit.
- **`n & (n - 1)` trick**: This is a powerful and widely applicable bit manipulation trick. It's not just for this problem; it's also commonly used to count set bits or to isolate the rightmost set bit. Subtracting one from a number flips its rightmost '1' bit to a '0' and all subsequent '0's to '1's. ANDing this with the original number effectively cancels out the rightmost '1' bit. For a power of two, since there's only one '1', the result is zero.

---

## 🚀 Further Exploration

- **[191. Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)**: The direct problem of counting set bits, which can be solved using the `n & (n-1)` trick repeatedly.
- **[342. Power of Four](https://leetcode.com/problems/power-of-four/)**: A harder version of this problem that requires additional checks on the position of the single set bit.
- **[326. Power of Three](https://leetcode.com/problems/power-of-three/)**: This variant cannot be solved with simple bitwise tricks, requiring mathematical or looping approaches.

---

## 📚 References

- **[LeetCode Problem: 231. Power of Two](https://leetcode.com/problems/power-of-two/description/)**
- **[GeeksForGeeks Article on Bitwise Tricks](https://www.geeksforgeeks.org/check-if-a-number-is-power-of-another-number/)**

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<p>
  <img src="https://img.shields.io/badge/Topic-Math-blue?style=for-the-badge" alt="Math">
  <img src="https://img.shields.io/badge/Topic-Bit%20Manipulation-yellow?style=for-the-badge" alt="Bit Manipulation">
  <img src="https://img.shields.io/badge/Topic-Recursion-green?style=for-the-badge" alt="Recursion">
</p>

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/imnilesh18/leetcode-dcc-potd-2025/blob/main/LICENSE) file for details.

> **Disclaimer:** This is for educational purposes only. All problem statements and examples are from LeetCode.