# 2197. Replace Non-Coprime Numbers in Array

![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red.svg)
[![Tag: Array](https://img.shields.io/badge/Array-blue)](https://leetcode.com/tag/array/)
[![Tag: Math](https://img.shields.io/badge/Math-purple)](https://leetcode.com/tag/math/)
[![Tag: Stack](https://img.shields.io/badge/Stack-orange)](https://leetcode.com/tag/stack/)
[![Tag: Number Theory](https://img.shields.io/badge/Number%20Theory-green)](https://leetcode.com/tag/number-theory/)

---

### 🔗 Problem Link

[https://leetcode.com/problems/replace-non-coprime-numbers-in-array/](https://leetcode.com/problems/replace-non-coprime-numbers-in-array/)

---

### 📝 Problem Statement

You are given an array of integers `nums`. Perform the following steps:

1.  Find **any** two **adjacent** numbers in `nums` that are **non-coprime**.
2.  If no such numbers are found, **stop** the process.
3.  Otherwise, delete the two numbers and **replace** them with their **LCM (Least Common Multiple)**.
4.  **Repeat** this process as long as you keep finding two adjacent non-coprime numbers.

Return _the final modified array_. It can be shown that replacing adjacent non-coprime numbers in **any** arbitrary order will lead to the same result.

Two values `x` and `y` are **non-coprime** if `GCD(x, y) > 1` where `GCD(x, y)` is the **Greatest Common Divisor** of `x` and `y`.

---

### ⛓️ Constraints

- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^5`
- The test cases are generated such that the values in the final array are **less than or equal** to `10^8`.

---

### 📊 Examples

<div style="overflow-x:auto;">
<table style="width:100%; border-collapse: collapse; background-color: #282c34; border-radius: 8px; color: white; margin-bottom: 20px;">
  <thead style="background-color: #3e4451;">
    <tr>
      <th style="padding: 12px 15px; text-align: left; border-bottom: 2px solid #555;">Example</th>
      <th style="padding: 12px 15px; text-align: left; border-bottom: 2px solid #555;">Input</th>
      <th style="padding: 12px 15px; text-align: left; border-bottom: 2px solid #555;">Output</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="padding: 12px 15px; border-bottom: 1px solid #444;">1</td>
      <td style="padding: 12px 15px; border-bottom: 1px solid #444;"><code style="font-family: monospace; background-color: #444; padding: 2px 5px; border-radius: 4px;">nums = [6,4,3,2,7,6,2]</code></td>
      <td style="padding: 12px 15px; border-bottom: 1px solid #444;"><code style="font-family: monospace; background-color: #444; padding: 2px 5px; border-radius: 4px;">[12,7,6]</code></td>
    </tr>
    <tr>
      <td colspan="3" style="padding: 10px 15px; background-color: #333942; border-bottom: 1px solid #444;">
        <strong>Explanation:</strong><br>
        - (6, 4) are non-coprime with LCM(6, 4) = 12. Now, nums = [<strong>12</strong>,3,2,7,6,2].<br>
        - (12, 3) are non-coprime with LCM(12, 3) = 12. Now, nums = [<strong>12</strong>,2,7,6,2].<br>
        - (12, 2) are non-coprime with LCM(12, 2) = 12. Now, nums = [<strong>12</strong>,7,6,2].<br>
        - (6, 2) are non-coprime with LCM(6, 2) = 6. Now, nums = [12,7,<strong>6</strong>].<br>
        There are no more adjacent non-coprime numbers.
      </td>
    </tr>
    <tr>
      <td style="padding: 12px 15px; border-bottom: 1px solid #444;">2</td>
      <td style="padding: 12px 15px; border-bottom: 1px solid #444;"><code style="font-family: monospace; background-color: #444; padding: 2px 5px; border-radius: 4px;">nums = [2,2,1,1,3,3,3]</code></td>
    </tr> -->
     <tr>
      <td colspan="3" style="padding: 10px 15px; background-color: #333942;">
        <strong>Explanation:</strong><br>
        - (3, 3) are non-coprime with LCM(3, 3) = 3. Now, nums = [2,2,1,1,<strong>3</strong>,3].<br>
        - (3, 3) are non-coprime with LCM(3, 3) = 3. Now, nums = [2,2,1,1,<strong>3</strong>].<br>
        - (2, 2) are non-coprime with LCM(2, 2) = 2. Now, nums = [<strong>2</strong>,1,1,3].<br>
        There are no more adjacent non-coprime numbers.
      </td>
    </tr>
  </tbody>
</table>
</div>

---

### 💡 Approach (Stack-based Simulation)

The most important clue in the problem statement is: **"...replacing adjacent non-coprime numbers in any arbitrary order will lead to the same result."**

This guarantee simplifies the problem immensely. Since any order works, we can choose the most convenient order: a single pass from **left to right**.

This problem can be perfectly modeled using a **Stack**. We can use a `vector` in C++ to simulate this stack behavior.

Our goal is to build the final, "stable" array in our `result` vector. For each new number `num` from the input `nums`:

1.  This `num` is the "adjacent" number to whatever is currently at the end of our `result` vector (i.e., `result.back()`, or the stack's top).
2.  We must check if `num` and `result.back()` are non-coprime (`GCD > 1`).
3.  **If they are non-coprime**: We must merge them.
    - Pop the element from `result`.
    - Calculate the LCM of the popped element and `num`.
    - Crucially, this **new LCM** now becomes our `num`.
4.  Why? Because this new LCM is now adjacent to the _next_ element on the stack (the new `result.back()`). We must repeat step 2: check if this _new LCM_ is non-coprime with the _new_ `result.back()`.
5.  We continue this process (pop, merge, update `num` to LCM) in a `while` loop until either the `result` vector becomes empty OR we find a number at `result.back()` that is **coprime** (`GCD == 1`) with our current `num`.
6.  **If they are coprime** (or if the `result` vector was empty to begin with): The merging process stops. This `num` (which is either the original number or the final merged LCM from the loops) is now "stable" for the moment, and we can safely push it onto the `result` vector.
7.  Repeat this for all numbers in the input array. The final `result` vector will be the answer.

---

### 💻 Solution Code (Optimized C++)

```cpp
// Intuition: The problem states that any order of merging adjacent non-coprime numbers yields the same result. This suggests we can process the array in a single direction (left-to-right) and maintain a "final" list of numbers. When a new number arrives, it might need to merge with the *last* number in our current final list. If they merge, the *result* of that merge (their LCM) might *then* need to merge with the *new* last number in the list. This "merge-backwards" behavior is perfectly modeled by a stack.
// Approach:
// 1. Initialize an empty vector `result` which will act like a stack.
// 2. Iterate through each `num` in the input `nums` array from left to right.
// 3. Start an inner `while` loop that runs as long as `result` is not empty.
// 4. Inside the loop, get `prev = result.back()` and set `curr = num`.
// 5. Calculate the `GCD = gcd(prev, curr)`. (This solution assumes C++17 or newer for std::gcd. If not, a manual Euclidean algo function is needed).
// 6. If GCD == 1 (they are coprime), they cannot be merged. Break the inner loop.
// 7. If GCD > 1 (they are non-coprime):
//    - We must merge them. Pop the last element from `result`.
//    - Calculate their LCM using the overflow-safe formula: `LCM = (long long)prev / GCD * curr`.
//    - Update `num` to be this new `LCM`.
//    - The `while` loop continues, checking this *new* `num` (the LCM) against the *new* `result.back()`.
// 8. After the inner `while` loop finishes (either because `result` became empty or we found a coprime neighbor), push the final value of `num` onto the `result` vector.
// 9. After iterating through all numbers in `nums`, return the `result` vector.
// Time Complexity: O(n * log(M)), where n is the length of nums and M is the maximum possible value an LCM can reach (10^8 as per constraints). Each element is pushed once. An element can cause multiple pops, but the total number of pops across the entire run is at most n. The dominant cost is the GCD calculation inside the while loop, which runs an amortized O(1) times per element, each taking O(log(M)).
// Space Complexity: O(n) or O(k), where k is the length of the returned array. This is for storing the `result` vector (stack). If the result array is not counted as extra space, the user-provided O(1) implies we do not count the output array.
class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> result; // Use a vector as a stack. Or you can use a stack.

        // Processing left to right, since the order is guaranteed to produce the same result.
        for(int num : nums) {

            // This new 'num' must be checked against the current "top" of our final list (result.back())
            // Keep merging backwards as long as the list is not empty and they are non-coprime.
            while(!result.empty()) {
                // Cast to long long to prevent overflow during intermediate calculations.
                long long prev = result.back(); // Get the last valid number in our list (stack top)
                long long curr = num;           // The new number we are trying to add

                long long GCD = gcd(prev, curr); // Calculate the Greatest Common Divisor

                if(GCD == 1) {
                    // They are coprime. They cannot be merged. Stop the merging loop.
                    break;
                }

                // If GCD > 1, they are NON-coprime. They MUST be merged.
                result.pop_back(); // Pop the 'prev' element, as it will be replaced by the new LCM.

                // Calculate LCM using the formula: LCM(a, b) = (a * b) / GCD(a, b)
                // We write it as (prev / GCD) * curr to prevent multiplication overflow *before* division.
                long long LCM = (prev / GCD) * curr;

                num = (int)LCM; // The merged number (LCM) becomes the *new* current number 'num'.
                // The while loop will now repeat to check THIS NEW number against the NEW stack top.
            }

            // After the loop breaks (either stack is empty or we found a coprime neighbor),
            // add the final resulting number (either the original 'num' or the final merged LCM) to our list.
            result.push_back(num); //merged num put back to result
        }
        return result; // This vector holds the final, fully merged array.
    }
};

/*
*
* Dry Run
*
* Input: nums = [6, 4, 3, 2, 7, 6, 2]
*
* 1.  Initialize result = []
*
* 2.  Process num = 6:
* - while loop doesn't run (result is empty).
* - result.push_back(6).
* - result = [6]
*
* 3.  Process num = 4:
* - while loop: !result.empty() is true.
* - prev = 6, curr = 4.
* - GCD(6, 4) = 2.
* - GCD is not 1.
* - result.pop_back(). result = []
* - LCM = (6 / 2) * 4 = 12.
* - num becomes 12.
* - while loop condition check: result.empty() is true. Loop terminates.
* - result.push_back(12).
* - result = [12]
*
* 4.  Process num = 3:
* - while loop: !result.empty() is true.
* - prev = 12, curr = 3.
* - GCD(12, 3) = 3.
* - GCD is not 1.
* - result.pop_back(). result = []
* - LCM = (12 / 3) * 3 = 12.
* - num becomes 12.
* - while loop condition check: result.empty() is true. Loop terminates.
* - result.push_back(12).
* - result = [12]
*
* 5.  Process num = 2:
* - while loop: !result.empty() is true.
* - prev = 12, curr = 2.
* - GCD(12, 2) = 2.
* - GCD is not 1.
* - result.pop_back(). result = []
* - LCM = (12 / 2) * 2 = 12.
* - num becomes 12.
* - while loop condition check: result.empty() is true. Loop terminates.
* - result.push_back(12).
* - result = [12]
*
* 6.  Process num = 7:
* - while loop: !result.empty() is true.
* - prev = 12, curr = 7.
* - GCD(12, 7) = 1.
* - GCD is 1. Break loop.
* - result.push_back(7).
* - result = [12, 7]
*
* 7.  Process num = 6:
* - while loop: !result.empty() is true.
* - prev = 7, curr = 6.
* - GCD(7, 6) = 1.
* - GCD is 1. Break loop.
* - result.push_back(6).
* - result = [12, 7, 6]
*
* 8.  Process num = 2:
* - while loop: !result.empty() is true.
* - prev = 6, curr = 2.
* - GCD(6, 2) = 2.
* - GCD is not 1.
* - result.pop_back(). result = [12, 7]
* - LCM = (6 / 2) * 2 = 6.
* - num becomes 6.
* - while loop condition check: !result.empty() is true.
* - prev = 7, curr = 6.
* - GCD(7, 6) = 1.
* - GCD is 1. Break loop.
* - result.push_back(6).
* - result = [12, 7, 6]
*
* 9.  End of nums array.
* 10. Return result = [12, 7, 6]
*
*/
```

---

### 🔑 Key Insights

- **Order Invariance**: The problem explicitly states that any order of operations leads to the same result. This is the key insight that allows us to simplify the problem from a complex simulation (where we have to repeatedly scan the array) to a single-pass stack-based approach.
- **Stack Behavior**: When a new number `X` merges with the last number `Y` to form `Z` (their LCM), this new number `Z` is now adjacent to the number that _came before_ `Y`. This "chain reaction" going backwards is the classic definition of a stack operation.
- **LCM/GCD Formula**: The relationship `LCM(a, b) = (a * b) / GCD(a, b)` is fundamental. To prevent 64-bit integer overflow (since `a * b` can exceed the limit even if the final LCM doesn't), we must use the form `LCM = (a / GCD(a, b)) * b`. This is mathematically equivalent and safe, as `a` is guaranteed to be divisible by the GCD.

---

### 🔗 References

- [Euclidean Algorithm for GCD](https://en.wikipedia.org/wiki/Euclidean_algorithm)
- [LCM and GCD Relation](https://en.wikipedia.org/wiki/Least_common_multiple#Using_the_greatest_common_divisor)

---

### 🏷️ Tags

`Array` `Math` `Stack` `Number Theory` `Simulation`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/replace-non-coprime-numbers-in-array/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
