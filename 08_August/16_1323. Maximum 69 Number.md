# 🔱 1323. Maximum 69 Number

<p align="center">
  <img src="https://img.shields.io/badge/Difficulty-Easy-green" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Tags-Math-blue" alt="Tags" />
  <img src="https://img.shields.io/badge/Tags-Greedy-yellow" alt="Tags" />
</p>

---

## 📝 Problem Statement

You are given a positive integer `num` consisting only of digits `6` and `9`.

Return the maximum number you can get by changing **at most one** digit (`6` becomes `9`, and `9` becomes `6`).

---

## ⛓️ Constraints

- `1 <= num <= 10^4`
- `num` consists of only `6` and `9` digits.

---

## 📋 Examples

| Input  | Output | Explanation                                                                            |
| :----- | :----- | :------------------------------------------------------------------------------------- |
| `9669` | `9969` | Change the '6' at the second position to '9'. This yields the largest possible number. |
| `9996` | `9999` | Change the last digit '6' to '9' to get the maximum number.                            |
| `9999` | `9999` | No change is needed as the number is already at its maximum possible value.            |

---

## 🧠 Approach

The core idea is to apply a **greedy strategy**. To maximize the number, we should aim to change a '6' to a '9' at the most significant position possible (i.e., the leftmost '6'). Changing a '9' to a '6' will always result in a smaller number, so we only consider changing '6' to '9'.

A clever way to achieve this without string manipulation is through a mathematical approach. Changing a '6' to a '9' at any position is equivalent to adding '3' to that digit's place value.

For example, in the number `9669`:

- The first '6' is in the hundreds place ($10^2$).
- Changing it to '9' is the same as adding $3 \times 10^2 = 300$.
- So, `9669 + 300 = 9969`.

The algorithm is as follows:

1.  Iterate through the digits of the number from right to left (least significant to most significant) using the modulo operator.
2.  Keep track of the current place value (0 for units, 1 for tens, etc.).
3.  Whenever we encounter a '6', we record its place value. Since we are moving from right to left, the last recorded place value will correspond to the **leftmost '6'**.
4.  If no '6' is found, the number is already maximal, and we return it as is.
5.  Otherwise, we add `3 * pow(10, placeValueOfLeftmostSix)` to the original number to get our result.

<details>
<summary>Step-by-Step Walkthrough (num = 9669)</summary>

- **Initialize:** `placeValue = 0`, `placeValueOfSix = -1`, `temp = 9669`.

- **Iteration 1:**

  - `remainder = 9669 % 10 = 9`. Not 6.
  - `placeValue` becomes `1`.
  - `temp` becomes `966`.

- **Iteration 2:**

  - `remainder = 966 % 10 = 6`. It's a 6!
  - Update `placeValueOfSix` to current `placeValue`, so `placeValueOfSix = 1`.
  - `placeValue` becomes `2`.
  - `temp` becomes `96`.

- **Iteration 3:**

  - `remainder = 96 % 10 = 6`. It's a 6!
  - Update `placeValueOfSix` to current `placeValue`, so `placeValueOfSix = 2`.
  - `placeValue` becomes `3`.
  - `temp` becomes `9`.

- **Iteration 4:**

  - `remainder = 9 % 10 = 9`. Not 6.
  - `placeValue` becomes `4`.
  - `temp` becomes `0`. Loop terminates.

- **Final Calculation:**
  - The last recorded `placeValueOfSix` is `2`.
  - The result is `num + 3 * pow(10, placeValueOfSix)`.
  - `9669 + 3 * pow(10, 2) = 9669 + 3 * 100 = 9669 + 300 = 9969`.
  - Return `9969`.

</details>

---

## 💻 Solution Code

### Method 1: String Conversion (Less Optimal)

```cpp
// Intuition:
// The most straightforward way is to treat the number as a sequence of characters.
// We can convert the number to a string, find the first occurrence of '6',
// change it to '9', and then convert it back to an integer.

// Approach:
// 1. Convert the input integer `num` to its string representation.
// 2. Iterate through the string from left to right.
// 3. If a '6' is found, change it to '9' and break the loop, as we only need to change the first one.
// 4. Convert the modified string back to an integer and return it.
// 5. If the loop completes without finding any '6', the original number is returned.

// Time Complexity: O(log10(num)) or O(D) where D is the number of digits.
// This is due to the string conversion and iteration, which are proportional to the number of digits.

// Space Complexity: O(log10(num)) or O(D) to store the string representation of the number.

class Solution {
public:
    int maximum69Number (int num) {
        // Convert the integer to a string for easy character manipulation.
        string s = to_string(num);

        // Iterate through the string to find the first '6'.
        for (char &c : s) {
            // If the leftmost '6' is found...
            if (c == '6') {
                // ...change it to '9' and exit the loop immediately.
                c = '9';
                break;
            }
        }
        // Convert the modified string back to an integer.
        return stoi(s);
    }
};

/*
*
* Dry Run
* Input: num = 9669
*
* 1. `s` becomes "9669".
* 2. Loop starts.
* 3. First char is '9', continue.
* 4. Second char is '6'.
* - Change it to '9'. `s` is now "9969".
* - `break` the loop.
* 5. Convert "9969" back to an integer.
* 6. Return 9969.
*
*/
```

### Method 2: Mathematical Approach (Optimized)

```cpp
// Intuition:
// The goal is to change the leftmost '6' to a '9' to maximize the number.
// Changing a '6' to a '9' is mathematically equivalent to adding 3 at that digit's place value.
// For example, in 9669, the leftmost '6' is in the hundreds place (10^2).
// Adding 3 * 10^2 = 300 to 9669 gives 9969.
// We can find the place value of the leftmost '6' by iterating through digits from right to left.

// Approach:
// 1. Initialize `placeValueOfSix` to -1 (to indicate no '6' found yet) and a `placeValue` counter to 0.
// 2. Create a temporary copy of `num` to process.
// 3. Loop while `temp > 0`.
// 4. In each iteration, get the last digit using `temp % 10`.
// 5. If the digit is '6', update `placeValueOfSix` with the current `placeValue`.
//    (This ensures `placeValueOfSix` always holds the position of the leftmost '6' found so far).
// 6. Increment `placeValue` and remove the last digit from `temp` using `temp / 10`.
// 7. After the loop, if `placeValueOfSix` is still -1, it means no '6' was found, so return the original `num`.
// 8. Otherwise, return `num + 3 * pow(10, placeValueOfSix)`.

// Time Complexity: O(log10(num)), because we iterate once for each digit in the number.
// Space Complexity: O(1), as we only use a few integer variables regardless of the input size.

class Solution {
public:
    int maximum69Number (int num) {
        // Tracks the current place value (0 for units, 1 for tens, etc.).
        int placeValue = 0;
        // Stores the place value of the leftmost '6' found so far. Initialized to -1.
        int placeValueOfSix = -1;

        // Use a temporary variable to preserve the original `num`.
        int temp = num;
        // Loop through each digit from right to left.
        while(temp > 0) {
            // Get the last digit.
            int remainder = temp % 10;
            // If the digit is 6, record its place value.
            if(remainder == 6) {
                placeValueOfSix = placeValue;
            }

            // Move to the next place value.
            placeValue++;
            // Remove the last digit.
            temp = temp / 10;
        }

        // If no '6' was found, the number is already maximized.
        if(placeValueOfSix == -1) {
            return num;
        }
        // Add 3 at the highest place value where a '6' was found.
        return num + 3 * pow(10, placeValueOfSix);
    }
};

/*
*
* Dry Run
* Input: num = 9669
*
* Initial state: placeValue = 0, placeValueOfSix = -1, temp = 9669
*
* Loop 1:
* remainder = 9669 % 10 = 9
* placeValue = 1
* temp = 966
*
* Loop 2:
* remainder = 966 % 10 = 6
* placeValueOfSix = 1
* placeValue = 2
* temp = 96
*
* Loop 3:
* remainder = 96 % 10 = 6
* placeValueOfSix = 2  (updated because this '6' is further to the left)
* placeValue = 3
* temp = 9
*
* Loop 4:
* remainder = 9 % 10 = 9
* placeValue = 4
* temp = 0. Loop ends.
*
* Final step:
* placeValueOfSix is not -1. It is 2.
* Return num + 3 * pow(10, 2) => 9669 + 3 * 100 => 9669 + 300 = 9969.
*
*/
```

---

## 💡 Key Insights

- **Greedy Choice**: The optimal change is always converting the leftmost '6' to a '9'. This provides the largest increase in value.
- **Mathematical Transformation**: Converting a number to a string and back can be less efficient than a direct mathematical manipulation. The "add 3 at the correct place value" trick is a common and elegant pattern for digit-based problems.
- **Right-to-Left Traversal**: Iterating through a number's digits from right to left (using modulo and division) is a standard technique. In this case, it allows us to naturally find the leftmost '6' by simply overwriting a variable, ensuring the final value stored is from the highest place value.

## 🚀 Further Exploration

- Can you generalize this solution to a function that takes a number, two digits `d1` and `d2`, and returns the largest number by changing at most one `d1` to `d2`?
- What if you could make up to `k` changes? How would the strategy change?

---

## 📚 References

- [LeetCode Problem: Maximum 69 Number](https://leetcode.com/problems/maximum-69-number/)
- [GeeksforGeeks: Place Value in Maths](https://www.geeksforgeeks.org/maths/place-value-maths/)

---

## 🏷️ Tags

`Math`, `Greedy`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

> **This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [LeetCode problem statement](https://leetcode.com/problems/maximum-69-number/) for original content and copyright.**

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)
