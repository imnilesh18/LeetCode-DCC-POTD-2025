<div align="center">

# ✨ 326. Power of Three ✨

| Category | Difficulty |
| :------: | :--------: |
|   Math   |    Easy    |

<a href="https://leetcode.com/problems/power-of-three/">
    <img src="https://img.shields.io/badge/LeetCode-Link-blue?style=for-the-badge&logo=leetcode" alt="Leetcode Link">
</a>
<a href="https://github.com/imnilesh18/leetcode-dcc-potd-2025/blob/main/solutions/Power%20of%20Three/README.md">
    <img src="https://img.shields.io/badge/GitHub-Solution-darkgreen?style=for-the-badge&logo=github" alt="GitHub Solution">
</a>

</div>

---

### 📝 Problem Statement

Given an integer `n`, return `true` if it is a power of three. Otherwise, return `false`.

An integer `n` is a power of three if there exists an integer `x` such that `n == 3^x`.

---

### ⛓️ Constraints

- `-2^31 <= n <= 2^31 - 1`

---

### Examples🧪

Here are some examples to illustrate the problem:

| Input    | Output  | Explanation           |
| :------- | :------ | :-------------------- |
| `n = 27` | `true`  | `27 = 3^3`            |
| `n = 0`  | `false` | `No x where 3^x = 0`  |
| `n = -1` | `false` | `No x where 3^x = -1` |
| `n = 9`  | `true`  | `9 = 3^2`             |
| `n = 45` | `false` | Not a power of three  |

---

### 🤔 Approach

The problem asks us to determine if a given integer `n` can be expressed as `3^x` for some integer `x`. We can solve this using several approaches, ranging from simple iteration to mathematical tricks.

1.  **Iterative Division**: The most straightforward method is to repeatedly divide `n` by 3. If `n` is a power of three, this process will eventually result in 1. If at any point `n` is not divisible by 3 (and is not 1), it's not a power of three. We must handle edge cases like `n <= 0`.

2.  **Recursive Division**: This is a recursive variant of the first approach. The base cases handle `n=1` (true), `n<=0` or `n%3 != 0` (false). Otherwise, we recurse with `n/3`.

3.  **Logarithms**: Mathematically, if `n = 3^x`, then `log(n) = x * log(3)`. This means `x = log(n) / log(3)`. We can calculate this value and check if it's an integer. A common way to check for an integer is to see if a floating-point number is equal to its floor or ceiling.

4.  **Integer Limitations (Constant Time Trick)**: Given the constraint that `n` is a 32-bit signed integer, we can find the largest power of 3 that fits within this range. The largest such value is `3^19 = 1162261467`. Any other power of three (e.g., `3^0`, `3^1`, `3^2`) must be a divisor of this largest power. Therefore, we only need to check if `n` is positive and if `1162261467 % n == 0`. This solves the problem without loops or recursion.

---

### 💻 Solution Code

Here are the solutions implementing the described approaches.

Approach 1: Iterative Division

```cpp
// Intuition:
// A number is a power of three if it can be reduced to 1 by repeatedly dividing by 3.
// For example, 27 -> 9 -> 3 -> 1. If the number is not a power of three, like 45, the chain breaks: 45 -> 15 -> 5. Since 5 is not divisible by 3, 45 is not a power of three.

// Approach:
// 1. Handle the edge case where n is less than or equal to 0, as powers of three are positive.
// 2. Use a while loop to continuously divide n by 3 as long as it's perfectly divisible.
// 3. After the loop, if n has been reduced to 1, it was a power of three. Otherwise, it was not.

// Time Complexity:
// O(log3(n)), because we are dividing n by 3 in each step.

// Space Complexity:
// O(1), as we are not using any extra space.

class Solution {
public:
    bool isPowerOfThree(int n) {
        // Powers of three must be positive.
        if(n <= 0) {
            return false;
        }
        // Keep dividing n by 3 as long as it's divisible.
        while(n % 3 == 0) {
            n /= 3; // Reduce n.
        }
        // If n becomes 1, it's a power of three.
        return n == 1;
    }
};

/*
*
* Dry Run
*
* Input: n = 27
* 1. n (27) > 0. Condition met.
* 2. while(27 % 3 == 0) -> true. n becomes 27 / 3 = 9.
* 3. while(9 % 3 == 0) -> true. n becomes 9 / 3 = 3.
* 4. while(3 % 3 == 0) -> true. n becomes 3 / 3 = 1.
* 5. while(1 % 3 == 0) -> false. Loop terminates.
* 6. return n == 1 -> return 1 == 1 -> true.
*
* Input: n = 45
* 1. n (45) > 0. Condition met.
* 2. while(45 % 3 == 0) -> true. n becomes 45 / 3 = 15.
* 3. while(15 % 3 == 0) -> true. n becomes 15 / 3 = 5.
* 4. while(5 % 3 == 0) -> false. Loop terminates.
* 5. return n == 1 -> return 5 == 1 -> false.
*
*/
```

Approach 2: Recursive Division

```cpp
// Intuition:
// This approach applies the same logic as iteration but uses the call stack to manage the state. A number `n` is a power of three if it's divisible by 3 AND `n/3` is also a power of three.

// Approach:
// 1. Base Case 1: If n is 0 or negative, it can't be a power of three. Return false.
// 2. Base Case 2: If n is 1, it is 3^0, which is a power of three. Return true.
// 3. Recursive Step: If n is divisible by 3, recursively call the function with n/3. If not, it fails the test. The `&&` operator elegantly combines these checks.

// Time Complexity:
// O(log3(n)), due to the recursive calls dividing n by 3 each time.

// Space Complexity:
// O(log3(n)) for the recursion stack depth.

class Solution {
public:
    bool isPowerOfThree(int n) {
        // Negative numbers and zero are not powers of three.
        if(n <= 0) {
            return false;
        }
        // Base case: 1 is 3^0.
        else if(n == 1) {
            return true;
        }
        // If n is divisible by 3, check if n/3 is a power of three.
        return n % 3 == 0 && isPowerOfThree(n/3);
    }
};

/*
*
* Dry Run
*
* Input: n = 27
* 1. isPowerOfThree(27) -> 27%3==0 is true. Calls isPowerOfThree(9).
* 2. isPowerOfThree(9) -> 9%3==0 is true. Calls isPowerOfThree(3).
* 3. isPowerOfThree(3) -> 3%3==0 is true. Calls isPowerOfThree(1).
* 4. isPowerOfThree(1) -> returns true.
* 5. The true value propagates up the call stack. Final result: true.
*
* Input: n = 15
* 1. isPowerOfThree(15) -> 15%3==0 is true. Calls isPowerOfThree(5).
* 2. isPowerOfThree(5) -> 5%3==0 is false. The `&&` expression short-circuits to false.
* 3. The false value propagates up. Final result: false.
*
*/
```

Approach 3: Using Logarithms

```cpp
// Intuition:
// If n = 3^x, then log_b(n) = x * log_b(3) for any base b.
// We can find x by calculating x = log_b(n) / log_b(3).
// If n is a power of three, x must be a perfect integer.

// Approach:
// 1. Handle the n <= 0 edge case.
// 2. Calculate log10(n) / log10(3). The base 10 is arbitrary; any base works.
// 3. This gives a double value. Check if this value is an integer.
// 4. A simple check is to cast the double to an int and see if it equals the original double. Due to floating-point inaccuracies, this might sometimes fail, but it's generally acceptable for this problem's constraints.

// Time Complexity:
// O(1). The `log10` function is typically implemented in constant time on most hardware.

// Space Complexity:
// O(1).

class Solution {
public:
    bool isPowerOfThree(int n) {
        // Logarithm is undefined for non-positive numbers.
        if (n <= 0) {
            return false;
        }
        // Calculate log base 3 of n using change of base formula.
        double logValue = log10(n) / log10(3);
        // Check if logValue is an integer by comparing it to its truncated version.
        return logValue == (int)logValue;
    }
};

/*
*
* Dry Run
*
* Input: n = 27
* 1. n (27) > 0.
* 2. logValue = log10(27) / log10(3) = 1.43136... / 0.47712... = 3.0
* 3. return logValue (3.0) == (int)logValue (3) -> true.
*
* Input: n = 28
* 1. n (28) > 0.
* 2. logValue = log10(28) / log10(3) = 1.44715... / 0.47712... = 3.033...
* 3. return logValue (3.033) == (int)logValue (3) -> false.
*
*/
```

Approach 4: Integer Limitation Trick

```cpp
// Intuition:
// The problem uses a standard 32-bit integer. The range is from -2^31 to 2^31 - 1.
// We can find the largest power of 3 that fits within this integer range.
// 3^19 = 1162261467, but 3^20 is too large.
// If a number `n` is a power of 3 (e.g., 3^2, 3^5), it must be a divisor of the largest power of 3 (3^19).

// Approach:
// 1. First, check if n is positive, since powers of three cannot be zero or negative.
// 2. Then, check if the largest power of 3 (1162261467) is perfectly divisible by n.
// 3. If both conditions are true, n must be a power of three.

// Time Complexity:
// O(1), as it only involves a single comparison and a single modulo operation.

// Space Complexity:
// O(1).

class Solution {
public:
    bool isPowerOfThree(int n) {
        // n must be positive and must divide the largest power of 3 that fits in a 32-bit signed int.
        return n > 0 && 1162261467 % n == 0;
        // NOTE :  3^19 = 1162261467
    }
};

/*
*
* Dry Run
*
* Input: n = 81
* 1. n (81) > 0 -> true.
* 2. 1162261467 % 81 == 0 -> true (since 81 = 3^4 and 3^19 is divisible by 3^4).
* 3. true && true -> true.
*
* Input: n = 82
* 1. n (82) > 0 -> true.
* 2. 1162261467 % 82 == 0 -> false.
* 3. true && false -> false.
*
*/
```

---

### 💡 Key Insights

- The problem has a "Follow up" asking to solve it without loops/recursion. This is a strong hint towards a mathematical or constant-time trick.
- The integer limitation approach (Approach 4) is the most efficient and clever solution. It leverages the constraints of the problem to turn a logarithmic problem into a constant-time one.
- Understanding the properties of logarithms (Approach 3) and prime factorization (underlying Approach 4) provides elegant alternatives to brute-force iteration.

---

### 🚀 Further Exploration

- Could you solve this for `long long` integers? The constant in Approach 4 would need to be recalculated. `3^39` is the largest power of 3 that fits in a 64-bit signed integer.
- Consider how you would solve "Power of Two" or "Power of Four". The same approaches apply, but the details change. For "Power of Four", an interesting bit manipulation trick exists: `n > 0 && (n & (n - 1)) == 0 && (n & 0xaaaaaaaa) == 0`.

---

### 📚 References

- [LeetCode Problem: Power of Three](https://leetcode.com/problems/power-of-three/)

---

### 🏷️ Tags

`Math` `Recursion` `Logarithms` `Integer Constraints`

---

## 📄 License

This repository is released under the [MIT License](https://www.google.com/search?q=./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/power-of-three/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
