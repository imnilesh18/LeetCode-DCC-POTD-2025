# 1317. Convert Integer to the Sum of Two No-Zero Integers

<p align="center">
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Topic-Math-blue" alt="Topic: Math" />
  <img src="https://img.shields.io/badge/Topic-Greedy-blue" alt="Topic: Greedy" />
  <img src="https://img.shields.io/badge/Topic-Brute%20Force-blue" alt="Topic: Brute Force" />
</p>

<p align="center">
  <a href="https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/description/"><strong>Problem Link</strong></a>
</p>

---

## 📝 Problem Statement

A **No-Zero integer** is a positive integer that does not contain any `0` in its decimal representation.

Given an integer `n`, return a list of two integers `[a, b]` where:
* `a` and `b` are **No-Zero integers**.
* `a + b = n`

The test cases are generated so that there is at least one valid solution. If there are many valid solutions, you can return any of them.

---

## ⛓️ Constraints

* `2 <= n <= 10^4`

---

## 🎯 Examples

<details>
<summary><strong>Example 1</strong></summary>

<div style="background-color: #f7f7f7; border-left: 5px solid #2196F3; padding: 10px; margin-left: 20px;">
  <strong>Input:</strong> n = 2<br>
  <strong>Output:</strong> [1,1]<br>
  <strong>Explanation:</strong> Let a = 1 and b = 1.
  Both a and b are no-zero integers, and a + b = 2 = n.
</div>

</details>

<details>
<summary><strong>Example 2</strong></summary>

<div style="background-color: #f7f7f7; border-left: 5px solid #2196F3; padding: 10px; margin-left: 20px;">
  <strong>Input:</strong> n = 11<br>
  <strong>Output:</strong> [2,9]<br>
  <strong>Explanation:</strong> Let a = 2 and b = 9.
  Both a and b are no-zero integers, and a + b = 11 = n.
  Note that there are other valid answers as [8, 3] that can be accepted.
</div>

</details>

---

## 💡 Approach & Walkthrough

### Approach 1: Brute Force Iteration

The most straightforward approach is to test every possible pair that sums to `n`. We are looking for two numbers, `A` and `B`, such that `A + B = n`.

1.  We can simply iterate with a loop, letting `A` take on every value from `1` up to `n - 1`.
2.  For each value of `A`, the corresponding value for `B` is uniquely determined: `B = n - A`.
3.  All we need is a helper function, let's call it `containsZero(num)`, which checks if a given number contains any zero digits. This can be done by repeatedly taking `num % 10` (to get the last digit) and checking if it's 0, then dividing the number by 10 (`num /= 10`) to move to the next digit, until the number becomes 0.
4.  In our main loop, we check: `if (!containsZero(A) && !containsZero(B))`.
5.  The moment this condition is true, we have found a valid pair, and we can immediately return `{A, B}`. The problem guarantees a solution always exists.

**Complexity Analysis:**
* **Time Complexity:** O(N * log N). The loop runs O(N) times. Inside the loop, checking the digits of both `A` and `B` takes O(log N) time (since the number of digits in `n` is proportional to log₁₀(n)).
* **Space Complexity:** O(1).

---

### Approach 2: Digit-by-Digit Greedy Construction

We can improve the time complexity significantly by building `A` and `B` constructively, ensuring no zero is created at any step.

The core idea is to start with `A = n` and `B = 0`. We know `A + B` equals the original `n`. We will iteratively "transfer" value from `A` to `B` at each place value (ones, tens, hundreds...), making sure that the resulting digits in both `A` and `B` are never zero.

1.  Initialize `A = n`, `B = 0`, and `placeValue = 1`.
2.  We iterate through the digits of `n` from right to left using a `while` loop that runs as long as the remaining part of `n` (let's call it `current_n`) is greater than 1.
3.  At each step, we look at the last digit of `current_n`: `digit = current_n % 10`.
4.  **The Key Problem:** If `digit` is `0` or `1`, we cannot simply split it. We can't use 0. If we split 1 into 1 and 0, that's invalid. If we subtract 1 from a number ending in 1 (like 31), we get 30, which is also invalid.
5.  **The Greedy Solution:**
    * **Case 1: `digit == 0` or `digit == 1`:** If we just "take 1" (i.e., subtract `1 * placeValue` from A), we will create a zero digit in A (e.g., 31 - 1 = 30) or leave a zero behind after borrowing (e.g., 30 - 1 = 29, but the 3 became a 2, and the 0 became 10). To avoid this, we must "take 2".
        * We subtract `2 * placeValue` from `A`.
        * We add `2 * placeValue` to `B`.
        * This forces a borrow. For example, if the digit is 1, `1 - 2` borrows, becoming `11 - 2 = 9`. If the digit is 0, `0 - 2` borrows, becoming `10 - 2 = 8`. In both cases, the resulting digit in `A` is non-zero, and the digit we add to `B` (2) is also non-zero.
    * **Case 2: `digit >= 2`:** We are safe. We can simply "take 1".
        * We subtract `1 * placeValue` from `A`.
        * We add `1 * placeValue` to `B`.
        * The digit in `A` becomes `digit - 1` (which is >= 1), and the digit in `B` becomes 1. Both are non-zero.
6.  The provided code simplifies this slightly: it only checks `if (n % 10 == 1)` as the special case to take 2. If the digit is 0, it takes 1 (e.g., `30 - 1*1 = 29`), which also works because this forces a borrow, turning the 0 into 9 and reducing the next digit.
7.  After transferring the `take` amount, we update `current_n = (current_n - take) / 10` to process the remaining digits, and update `placeValue *= 10` to move to the next decimal place.
8.  The loop stops when `current_n <= 1` because the most significant digit can just remain in `A` (since it's `1` or more, it's already non-zero) and does not need to be split.

**Complexity Analysis:**
* **Time Complexity:** O(log N). We perform one operation for each decimal digit of `n`.
* **Space Complexity:** O(1).

---

## Solution Code

### Approach 1: Brute Force

```cpp
// Intuition: We need two numbers, a and b, that sum to n, and neither can contain a '0' digit. The simplest way is to try every possible 'a' from 1 up to n-1.
// Approach:
// 1. Loop 'a' from 1 to n-1.
// 2. For each 'a', calculate its counterpart 'b' as (n - a).
// 3. Create a helper function `check(num)` that iterates through every digit of a number. If any digit is 0, it returns false. Otherwise, it returns true.
// 4. In the loop, if `check(a)` is true AND `check(b)` is true, we found a valid pair.
// 5. Return the pair {a, b} immediately. Since a solution is guaranteed, we will always find one.
// Time Complexity: O(n * log10(n))
//   - The outer loop runs O(n) times.
//   - Inside the loop, `check(a)` and `check(b)` are called. The `check` function's while loop runs based on the number of digits in 'a' and 'b', which is O(log10(n)).
//   - Therefore, the total complexity is O(n * logn).
// Space Complexity: O(1)
//   - We only use a few variables (a, b) and no extra data structures.
//Approach-1 (Brute Force - Try all possible numbers fro 1 to n-1 for a and thne b = n-a)
//T.C : O(n*logn)
//S.C : O(1)
class Solution {
public:

    // Helper function to check if a number contains any zero digits
    bool check(int num) {
        while(num > 0) { // Iterate while there are digits left to check
            if(num % 10 == 0) { // Check the last digit (unit's place)
                return false; // Found a zero, this number is invalid
            }
            num /= 10; // Remove the last digit to check the next one
        }   
        return true; // No zeros were found after checking all digits
    }

    vector<int> getNoZeroIntegers(int n) {
        // Iterate through all possible values for 'a'
        for(int a = 1; a <= n - 1; a++) {
            int b = n - a; // Calculate the corresponding 'b'

            // Check if both 'a' and 'b' are "No-Zero" integers
            if(check(a) && check(b)) {
                return {a, b}; // Found a valid pair, return it
            }
        }

        return {}; // Should not be reached as per problem constraints (solution always exists)
    }
};

/*
*
* Dry Run
*
* Input: n = 11
*
* 1. a = 1:
* b = 11 - 1 = 10
* check(1) -> true
* check(10) -> false (contains 0)
* Continue.
*
* 2. a = 2:
* b = 11 - 2 = 9
* check(2) -> true
* check(9) -> true
* Both are true. Return {2, 9}.
*
*/
```

---

### Approach 2: Optimized Greedy (Digit Construction)

```cpp
// Intuition: We can build 'a' and 'b' digit by digit by transferring value from 'a' to 'b' while ensuring no zero digit is created in either number at any position.
// Approach:
// 1. Initialize `a = n`, `b = 0`, and `placeValue = 1` (for the ones place). The invariant `a + b == n` is true.
// 2. We will process the digits of `n` from right to left using a loop `while (n > 1)`.
// 3. At each step, we look at the current last digit of `n` (which is `n % 10`).
// 4. We want to subtract some amount (`take`) from this digit for 'a' and add it to 'b'.
// 5. If the last digit `n % 10` is 1, subtracting 1 would create a 0 (e.g., 31 - 1 = 30).
//    - So, if `n % 10 == 1`, set `take = 2`. This requires borrowing (11-2=9), ensuring a non-zero digit.
// 6. If the last digit `n % 10` is 0, or 2-9, we can safely "take" 1.
//    - If 0, taking 1 (0-1) borrows, becoming 9.
//    - If >= 2, taking 1 (e.g., 2-1) becomes 1. All results are non-zero.
// 7. Update 'a' and 'b':
//    - `a = a - (take * placeValue)`
//    - `b = b + (take * placeValue)`
//    - This maintains the invariant `a + b == n`.
// 8. Update `n` for the next iteration: we processed the current digit by subtracting `take`, so we do `n = (n - take) / 10` to move to the next digit.
// 9. Update `placeValue`: multiply by 10 (moving from ones to tens, tens to hundreds, etc.).
// 10. The loop stops when `n <= 1` because the last remaining digit doesn't need splitting and is guaranteed to be non-zero (part of 'a').
// 11. Return {a, b}. Both 'a' and 'b' are guaranteed to be No-Zero integers by this construction.
// Time Complexity: O(log10(n))
//   - The while loop iterates once for each decimal digit of n. The number of digits is log base 10 of n.
// Space Complexity: O(1)
//   - We only use a few integer variables (a, b, placeValue, n, take).

//Approach-2 (Fixing each digit and forming a and b digit by digit)
//T.C : O(logn)
//S.C : O(1)
class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        int a = n; // Start with 'a' as the full number
        int b = 0; // Start with 'b' as zero
        int placeValue = 1; // Start at the ones place (10^0)

        // We always maintain the invariant: a + b == n (original n)
        while(n > 1) { // Loop until we've processed all digits except the most significant one
            int take = 1; // Default amount to transfer from 'a' to 'b' for this place value

            // Get the last digit of the remaining n
            if(n % 10 == 1) { // Special case: if digit is 1
                // Taking 1 would result in 1-1=0.
                // So, we must take 2. This ensures the digit in 'a' becomes (11-2=9).
                take = 2;
            }
            // Note: If n % 10 == 0, we still take 1, which borrows (10-1=9), also avoiding a zero.

            // Transfer the 'take' amount, scaled by its place value, from a to b
            a = a - take * placeValue;
            b = b + take * placeValue;

            // Update n for the next digit
            n = (n - take) / 10; // Remove the processed value and shift right (integer division)

            placeValue *= 10; // Move to the next place value (tens, hundreds, etc.)
        }

        return {a, b}; // Both a and b are guaranteed to be No-Zero integers
    }
};

/*
*
* Dry Run (Following Code Exactly)
*
* Input: n = 2031
* Initial: a = 2031, b = 0, placeValue = 1, n_loop = 2031
*
* Loop 1 (Ones place):
* n_loop (2031) % 10 = 1. Condition met.
* take = 2
* a = 2031 - 2*1 = 2029
* b = 0 + 2*1 = 2
* n_loop = (2031 - 2) / 10 = 2029 / 10 = 202
* placeValue = 10
*
* Loop 2 (Tens place):
* n_loop (202) % 10 = 2. Condition NOT met.
* take = 1
* a = 2029 - 1*10 = 2019
* b = 2 + 1*10 = 12
* n_loop = (202 - 1) / 10 = 201 / 10 = 20
* placeValue = 100
*
* Loop 3 (Hundreds place):
* n_loop (20) % 10 = 0. Condition NOT met. (Code only checks for == 1)
* take = 1
* a = 2019 - 1*100 = 1919
* b = 12 + 1*100 = 112
* n_loop = (20 - 1) / 10 = 19 / 10 = 1
* placeValue = 1000
*
* Loop 4:
* n_loop = 1. Condition (n > 1) is false. Loop terminates.
*
* Final: Return {1919, 112}.
* Check: 1919 + 112 = 2031. Neither 1919 nor 112 contains a zero. Valid.
*/
```

---

## 🔑 Key Insights

* **Brute Force is Viable:** Given the small constraint (`n <= 10000`), an O(N * log N) solution passes easily and is simple to implement.
* **Motivation for Optimization:** The brute force works, but the O(log N) solution shows a clever way to think about the problem by constructing the answer digit-by-digit, which is a common pattern in math and number theory problems.
* **The "Zero" Problem:** The core difficulty lies in digits 0 and 1. Any digit 2 or greater can be easily split into two non-zero parts (e.g., `5 = 1 + 4`). A digit of `1` *cannot* be split into two positive non-zero integers. A digit of `0` also cannot be split.
* **Borrowing is the Key:** The greedy algorithm works by using the concept of borrowing. When it encounters a problematic digit (like 0 or 1), it "takes" a larger value (like 2, or 1 which forces a borrow), which automatically borrows from the next highest place value, resolving the problem by changing both the current digit and the next digit.

---

## 🚀 Further Exploration

* What if the problem asked for three No-Zero integers? How would the greedy approach change?
* What if the constraint was much larger (e.g., `n <= 10^18`)? We would need to process `n` as a string, but the same digit-by-digit greedy logic would apply.

---

## 📚 References

* [Basic Math: Iterating through digits](https://www.geeksforgeeks.org/program-count-digits-integer-3-different-methods/)
* [Greedy Algorithms](https://en.wikipedia.org/wiki/Greedy_algorithm)

---

## 🏷️ Tags

`Math` `Greedy` `Brute Force`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/description/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)