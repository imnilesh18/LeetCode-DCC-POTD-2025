# ✨ 342. Power of Four

[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-green.svg)](https://leetcode.com/problems/power-of-four/)
[![Tags](https://img.shields.io/badge/Tags-Math-blue.svg)](https://leetcode.com/tag/math/)
[![Tags](https://img.shields.io/badge/Tags-Bit_Manipulation-yellow.svg)](https://leetcode.com/tag/bit-manipulation/)
[![Tags](https://img.shields.io/badge/Tags-Recursion-red.svg)](https://leetcode.com/tag/recursion/)

---

## 📝 Problem Statement

Given an integer `n`, return `true` if it is a power of four. Otherwise, return `false`.

An integer `n` is a power of four if there exists an integer `x` such that `n == 4^x`.

---

## 📌 Constraints

-   `-2^31 <= n <= 2^31 - 1`

---

## 💡 Examples

| Input | Output | Explanation |
| :---- | :----- | :---------- |
| `n = 16`| `true` | `16 = 4^2` |
| `n = 5` | `false`| `5 is not a power of 4` |
| `n = 1` | `true` | `1 = 4^0` |

---

## 🤔 Approach & Explanation

This problem can be solved in several ways, ranging from a simple iterative approach to more optimized mathematical and bit manipulation techniques.

### Approach 1: Iterative Division

The most straightforward approach is to repeatedly divide the number `n` by 4. If `n` is a power of four, this process will eventually result in `1`. We must handle edge cases like `n <= 0`. For any positive `n`, we can enter a loop that continues as long as `n` is divisible by 4. Inside the loop, we update `n` to `n / 4`. After the loop, if `n` is `1`, it was a power of four.

<details>
<summary>Click for walkthrough</summary>

Let's take `n = 64`:
1.  **Initial Check:** `n` is positive.
2.  **Loop 1:** `64 % 4 == 0` is true. `n` becomes `64 / 4 = 16`.
3.  **Loop 2:** `16 % 4 == 0` is true. `n` becomes `16 / 4 = 4`.
4.  **Loop 3:** `4 % 4 == 0` is true. `n` becomes `4 / 4 = 1`.
5.  **Loop End:** `1 % 4 == 0` is false. The loop terminates.
6.  **Final Check:** The final value of `n` is `1`, so we return `true`.

</details>

### Approach 2: Mathematical (Logarithms)

A number `n` is a power of four if `n = 4^x` for some integer `x`. We can solve for `x` using logarithms: `x = log₄(n)`. Using the change of base formula, this is equivalent to `x = log(n) / log(4)`.

We can calculate this value of `x`. If `n` is truly a power of four, `x` must be an integer. We can then verify if `4^x` equals the original `n`.

<details>
<summary>Click for walkthrough</summary>

Let's take `n = 16`:
1. **Calculate `x`:** `x = log(16) / log(4)`. This gives `x = 2`.
2. **Verify:** Check if `pow(4, 2)` equals `16`. `16 == 16` is true.
3. **Return:** `true`.

Let's take `n = 12`:
1. **Calculate `x`:** `x = log(12) / log(4) ≈ 1.79`. When cast to an integer, `x` becomes `1`.
2. **Verify:** Check if `pow(4, 1)` equals `12`. `4 == 12` is false.
3. **Return:** `false`.
</details>

### Approach 3: Bit Manipulation & Mathematics

This is the most efficient, O(1) solution. It relies on two key properties of numbers that are a power of four:

1.  **They must be a power of two.** A power of two in binary has exactly one bit set to `1` (e.g., 4 is `100`, 16 is `10000`). This can be checked with the bitwise trick `n > 0 && (n & (n - 1)) == 0`.

2.  **The set bit must be in an odd position.** The positions of set bits for powers of four (`4^0`, `4^1`, `4^2`, ...) are `1`, `4`, `16`, `64`, which in binary are `1`, `100`, `10000`, `1000000`. The `1` is always at an odd position (1st, 3rd, 5th bit, etc., counting from the right starting at 1). An alternative mathematical property is that for any power of four `n`, `(n - 1)` is always divisible by 3.
    * `4^1 - 1 = 3` (divisible by 3)
    * `4^2 - 1 = 15` (divisible by 3)
    * `4^3 - 1 = 63` (divisible by 3)

By combining these two checks, we can determine if a number is a power of four in constant time.

---

## 💻 Solution Code

### Brute-force Solution (Iterative Division)

```cpp
// Intuition: A number is a power of four if it can be repeatedly divided by 4 until it becomes 1.
// Approach:
// 1. Handle the edge case where n is 0, which is not a power of four.
// 2. Use a while loop to check if n is divisible by 4.
// 3. In each iteration, divide n by 4.
// 4. After the loop, if the remaining n is 1, it's a power of four.
// Time Complexity: O(log₄(n)), as we divide n by 4 in each step.
// Space Complexity: O(1), as we only use a few variables.
class Solution {
public:
    bool isPowerOfFour(int n) {
        if(n==0){ // Powers of four must be positive.
            return false;
        }
        while(n%4 == 0){ // Keep dividing by 4 as long as it's possible.
            n /= 4;
        }
        return n==1; // If the final result is 1, it was a power of four.
    }
};

/*
*
* Dry Run
*
* Example: n = 64
* 1. n is not 0.
* 2. while(64 % 4 == 0) -> true. n becomes 16.
* 3. while(16 % 4 == 0) -> true. n becomes 4.
* 4. while(4 % 4 == 0)  -> true. n becomes 1.
* 5. while(1 % 4 == 0)  -> false. Loop terminates.
* 6. return n == 1 -> return 1 == 1 -> true.
*
* Example: n = 12
* 1. n is not 0.
* 2. while(12 % 4 == 0) -> true. n becomes 3.
* 3. while(3 % 4 == 0)  -> false. Loop terminates.
* 4. return n == 1 -> return 3 == 1 -> false.
*
*/
```

### Optimized Solution (Mathematical - Logarithms)

```cpp
// Intuition: If n = 4^x, we can find x using logarithms: x = log(n) / log(4).
// If x is an integer and 4^x equals n, then n is a power of four.
// Approach:
// 1. Handle non-positive numbers, which cannot be powers of four.
// 2. Calculate the potential exponent 'a' using the change of base formula for logarithms.
// 3. Since floating-point arithmetic can have precision issues, we cast the result to an integer.
// 4. Verify if raising 4 to the power of 'a' gives back the original number n.
// Time Complexity: O(log(a)), where 'a' is the exponent. The pow() function typically has a logarithmic time complexity.
// Space Complexity: O(1), no extra space is used that scales with input.
class Solution {
public:
    bool isPowerOfFour(int n) {
        if(n <= 0) return false; // Powers of four are positive.
        
        int a = (log(n)/log(4)); // Calculate the exponent 'a' if n = 4^a.
        /*
            4^a = n
            a = log(n) to base 4
            a = log(n) to base e / log(4) to base e
        */
        
        if(n == pow(4, a)) // Check if 4 raised to 'a' equals n.
            return true;
        
        return false;
    }
};

/*
*
* Dry Run
*
* Example: n = 16
* 1. n is > 0.
* 2. a = log(16) / log(4) = 2.0. Cast to int, a = 2.
* 3. if (16 == pow(4, 2)) -> if (16 == 16) -> true.
* 4. Return true.
*
* Example: n = 15
* 1. n is > 0.
* 2. a = log(15) / log(4) approx 1.95. Cast to int, a = 1.
* 3. if (15 == pow(4, 1)) -> if (15 == 4) -> false.
* 4. Return false.
*
*/
```

### Most Optimized Solution (Bit Manipulation)

```cpp
// Intuition: A number is a power of four if and only if it is a power of two,
// and the single set bit is in an odd-numbered position (1st, 3rd, 5th, etc.).
// The second condition is mathematically equivalent to (n-1) being divisible by 3.
// Approach:
// 1. Check if n is positive (n > 0).
// 2. Check if n is a power of two using (n & (n - 1)) == 0. This ensures there's only one set bit.
// 3. Check if (n - 1) is divisible by 3. This ensures the set bit is in an odd position.
// 4. If all three conditions are met, it's a power of four.
// Time Complexity: O(1), as all operations are constant time.
// Space Complexity: O(1), no extra space is used.
class Solution {
public:
    bool isPowerOfFour(int n) {

      /*
        n > 0                  : Ensures the number is positive.
        (n & (n - 1)) == 0     : This checks if the number is a power of 2 (has only one set bit).
        (n - 1) % 3 == 0       : All numbers that are powers of 4 have this property. 
                                 Example: 4^1-1=3, 4^2-1=15, 4^3-1=63. This property ensures
                                 the single set bit is at an odd position.
      */
        
        return n > 0 && (n & (n - 1)) == 0 && (n - 1) % 3 == 0;
    }
};
/*
*
* Dry Run
*
* Example: n = 16 (Binary: 10000)
* 1. n > 0 -> true.
* 2. (16 & 15) == 0 -> (10000 & 01111) == 0 -> 0 == 0 -> true. (It's a power of 2)
* 3. (16 - 1) % 3 == 0 -> 15 % 3 == 0 -> true.
* 4. Result: true && true && true -> true.
*
* Example: n = 8 (Binary: 1000)
* 1. n > 0 -> true.
* 2. (8 & 7) == 0 -> (1000 & 0111) == 0 -> 0 == 0 -> true. (It's a power of 2)
* 3. (8 - 1) % 3 == 0 -> 7 % 3 == 1 -> false.
* 4. Result: true && true && false -> false.
*
*/
```

---

## 🔑 Key Insights

-   A power of four is always a power of two, but the reverse is not true.
-   The binary representation of a power of four has a single `1` bit followed by an even number of `0`s.
-   The property `(n-1) % 3 == 0` is a clever mathematical trick to filter out powers of two that are not powers of four (like 2, 8, 32, etc.).

## 🚀 Further Exploration

-   Can you solve this problem without loops or recursion (as suggested by the follow-up)? The bit manipulation approach does exactly this.
-   Consider how you would solve for "Power of Eight" or "Power of Sixteen". What properties would change?
    -   For a power of eight (`8^x = 2^(3x)`), the number of trailing zeros after the single set bit must be a multiple of 3.
-   A bitmask `0x55555555` (binary `010101...`) can be used to check if the set bit is in an odd position. `(n & 0x55555555) != 0` would work.

---

## 📚 References

-   [LeetCode Problem Link](https://leetcode.com/problems/power-of-four/)
-   [Proof for (n-1)%3 property](https://math.stackexchange.com/questions/199343/prove-that-4n-1-is-a-multiple-of-3)

---

## ##️⃣ Tags

#Math #BitManipulation #Recursion #LeetCode #Easy

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/power-of-four/) for original content and copyright.**

---

## 👨‍💻 Author

-   [imnilesh18](https://github.com/imnilesh18)